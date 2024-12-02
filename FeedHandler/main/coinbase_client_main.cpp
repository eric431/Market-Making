#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "order_book_struct.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;

static const std::string URI = "advanced-trade-ws.coinbase.com";

// const char* API_KEY = std::getenv("API_KEY");
// const char* SECRET_KEY = std::getenv("SECRET_KEY");

namespace Coinbase
{
    // synchonous market data client
    void SynchronousMarketDataClient(std::string& host)
    {
        try
        {
            // CoinbaseRequest::Channel subscribe_message{
            //     .type = "subscribe",
            //     .product_ids = {"BTC-USD"},
            //     .channel = {.type = "ticker"},
            // }

            auto const port = "443";

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

    class AsynchronousMarketDataClient
    {
        public:
            AsynchronousMarketDataClient()
            {
                std::cout << "Connecting to Coinbase Market Data endpoint\n";
            }

            ~AsynchronousMarketDataClient()
            {
                std::cout << "Session ended!\n";
            }

        private:
            std::string m_host{};
            std::string m_port{};
    };
};

int main()
{
    std::string host{URI};
    Coinbase::SynchronousMarketDataClient(host);
}