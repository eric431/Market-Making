#ifndef COINBASE_CLIENT_H
#define COINBASE_CLIENT_H

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
#include <functional>
#include <memory>
#include <string>
#include <string_view>

// #include "trading_messages.hpp"


namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;

namespace Coinbase
{
    void SynchronousMarketDataClient(std::string& host);

    class AsynchronousMarketDataClient : public std::enable_shared_from_this<AsynchronousMarketDataClient>
    {
        public:
            explicit AsynchronousMarketDataClient(net::io_context& ioc, ssl::context& ctx);

            void run(std::string& host, std::string& port);
            
            void on_resolve(beast::error_code ec, tcp::resolver::results_type results);

            void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep);

            void on_ssl_handshake(beast::error_code ec);

            void on_handshake(beast::error_code ec);

            void on_write(beast::error_code ec, std::size_t bytes_transferred);

            void on_read(beast::error_code ec);

            void on_close(beast::error_code ec);

            ~AsynchronousMarketDataClient();

        private:
            std::string m_host{};
            std::string m_port{};

            tcp::resolver m_resolver{};
            websocket::stream<ssl::stream<beast::tcp_stream>> m_ws{};
            boost::beast::flat_buffer m_buffer{};
    };
}

#endif