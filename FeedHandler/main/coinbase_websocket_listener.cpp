#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <vector>

namespace beast = boost::beast;
namespace webssocket = beast::websocket;
using tcp = boost::asio::ip::tcp;

static const std::string URI = "wss://ws-direct.sandbox.exchange.coinbase.com";
const char* API_KEY = std::getenv("API_KEY");

namespace Coinbase
{
    void websocket_listener()
    {
        ;
    }
};

int main()
{

    std::cout << "compiled successfully" << std::endl;
    std::cout << "API_KEY is " << API_KEY << std::endl;
}