#include "coinbase_client.hpp"

void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void Coinbase::SynchronousMarketDataClient(std::string& host, std::string& port)
{
    try
    {
        std::string sub_string = R"({"type": "subscribe", "product_ids": ["BTC-USD"], "channel": "ticker"})";
        auto sub_json = json::parse(sub_string);

        net::io_context ioc;

        ssl::context ctx(ssl::context::tlsv12_client);

        tcp::resolver resolver(ioc);
        websocket::stream<beast::ssl_stream<tcp::socket>> ws{ioc, ctx};

        auto const results = resolver.resolve(host, port);

        auto ep = net::connect(get_lowest_layer(ws), results);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
            throw beast::system_error(
                beast::error_code(
                    static_cast<int>(::ERR_get_error()),
                    net::error::get_ssl_category()),
                "Failed to set SNI Hostname");

        host += ':' + std::to_string(ep.port());

        ws.next_layer().handshake(ssl::stream_base::client);

        ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }
        ));

        ws.handshake(host, "/");

        ws.write(net::buffer(sub_string));

        beast::flat_buffer buffer;

        ws.read(buffer);

        ws.close(websocket::close_code::normal);

        std::cout << beast::make_printable(buffer.data()) << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }  
}

// construct client with resolver and socket using an io_context
Coinbase::AsynchronousMarketDataClient::AsynchronousMarketDataClient(net::io_context& ioc, ssl::context& ctx)
    : m_resolver(net::make_strand(ioc))
    , m_ws(net::make_strand(ioc), ctx)
{
}

void Coinbase::AsynchronousMarketDataClient::run(std::string& host, std::string& port, std::string& msg)
{
    m_host = host;
    m_port = port;
    m_msg  = msg;

    m_resolver.async_resolve(
        m_host,
        m_port,
        beast::bind_front_handler(
            &AsynchronousMarketDataClient::on_resolve,
            shared_from_this()
        )
    );
}

void Coinbase::AsynchronousMarketDataClient::on_resolve(beast::error_code ec, tcp::resolver::results_type results)
{
    if(ec) return fail(ec, "resolve");

    // set connection timeout
    beast::get_lowest_layer(m_ws).expires_after(std::chrono::seconds(30));

    // connect on the IP addresses from lookup
    beast::get_lowest_layer(m_ws).async_connect(
        results,
        beast::bind_front_handler(
            &AsynchronousMarketDataClient::on_connect,
            shared_from_this()
        )
    );
}

void Coinbase::AsynchronousMarketDataClient::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
{
    if(ec) return fail(ec, "connect");

    // set connection timeout
    beast::get_lowest_layer(m_ws).expires_after(std::chrono::seconds(30));

    // set SNI hostname in order to complete handshake successfully
    if(!SSL_set_tlsext_host_name(m_ws.next_layer().native_handle(), m_host.c_str()))
    {
        ec = beast::error_code(static_cast<int>(::ERR_get_error()),
            net::error::get_ssl_category());
        return fail(ec, "connect");
    }

    // update the host
    m_host += ':' + std::to_string(ep.port());

    // perform the SSL handshake
    m_ws.next_layer().async_handshake(
        ssl::stream_base::client,
        beast::bind_front_handler(
            &AsynchronousMarketDataClient::on_ssl_handshake,
            shared_from_this()
        )
    );
}

void Coinbase::AsynchronousMarketDataClient::on_ssl_handshake(beast::error_code ec)
{
    if(ec) return fail(ec, "ssl_handshake");

    beast::get_lowest_layer(m_ws).expires_never();

    m_ws.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::client
        )
    );

    // set user agent decorator
    m_ws.set_option(websocket::stream_base::decorator(
        [](websocket::request_type& req)
        {
            req.set(http::field::user_agent, 
                std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-async-ssl");
        }
    ));

    // perform handshake
    m_ws.async_handshake(m_host, "/",
        beast::bind_front_handler(
            &AsynchronousMarketDataClient::on_handshake,
            shared_from_this()
        ));
}

void Coinbase::AsynchronousMarketDataClient::on_handshake(beast::error_code ec)
{
    if(ec) return fail(ec, "handshake");

    // std::string text = "";

    // Send message
    m_ws.async_write(
        net::buffer(m_msg),
        beast::bind_front_handler(
            &AsynchronousMarketDataClient::on_write,
            shared_from_this()
        )
    );
}

void Coinbase::AsynchronousMarketDataClient::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec) return fail(ec, "write");

    m_ws.async_read(
        m_buffer, 
        beast::bind_front_handler(
            &AsynchronousMarketDataClient::on_read,
            shared_from_this()
        )
    );
}

void Coinbase::AsynchronousMarketDataClient::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec) return fail(ec, "read");

    // Close the Websocket connection
    m_ws.async_close(websocket::close_code::normal,
        beast::bind_front_handler(
            &AsynchronousMarketDataClient::on_close, shared_from_this()
        ));
}

void Coinbase::AsynchronousMarketDataClient::on_close(beast::error_code ec)
{
    if(ec) return fail(ec, "close");

    std::cout << beast::make_printable(m_buffer.data()) << std::endl;
}


Coinbase::AsynchronousMarketDataClient::~AsynchronousMarketDataClient()
{
    std::cout << "session ended!" << std::endl;
}