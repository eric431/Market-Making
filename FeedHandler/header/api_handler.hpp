#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <exception>
#include <string_view>


using boost::asio::ip::tcp;

class ApiHandler
{
    public:
        ApiHandler(std::string_view server);

        ~ApiHandler();

        void handle_connection();

    private:
        boost::asio::io_context m_io_context;
        tcp::resolver::results_type m_endpoints{};
};


#endif