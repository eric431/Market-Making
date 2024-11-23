#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "order_book_struct.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <vector>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

static const std::string URI = "wss://ws-direct.sandbox.exchange.coinbase.com";
const char* API_KEY = std::getenv("API_KEY");
const char* SECRET_KEY = std::getenv("SECRET_KEY");

namespace Coinbase
{
    // synchonous websocket listener
    void websocket_listener(std::string& host)
    {
        try
        {
            std::string host = "";
            std::string port = "";
            std::string text = "";

            net::io_context ioc;

            tcp::resolver resolver(ioc);
            websocket::stream<tcp::socket> ws{ioc};

            auto const results = resolver.resolve(host, port);

            auto ep = net::connect(ws.next_layer(), results);

            host += ':' + std::to_string(ep.port());


            // ws.set_option(websocket::stream_base::decorator(
            //     [](websocket::request_type& req)
            //     {
            //         req.set(/* fill in with appropriate lambda function*/);
            //     }
            // ));

            ws.handshake(host, "/");

            ws.write(net::buffer(std::string(text)));

            beast::flat_buffer buffer;

            ws.read(buffer);

            ws.close(websocket::close_code::normal);

            std::cout << beast::make_printable(buffer.data()) << std::endl;
        }
        catch(std::exception const& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }   
    }
};

int main()
{
    std::cout << "compiled successfully" << std::endl;
    std::cout << "API_KEY is " << API_KEY << std::endl;
    std::cout << "SECRET_KEY is " << SECRET_KEY << std::endl;
}