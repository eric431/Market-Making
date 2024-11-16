#include "api_handler.hpp"

ApiHandler::ApiHandler(std::string_view server)
{
    tcp::resolver resolver(m_io_context);

    tcp::resolver::results_type m_endpoints = 
        resolver.resolve(server, "coinbase");
}

ApiHandler::~ApiHandler()
{

}

void ApiHandler::handle_connection()
{
    tcp::socket socket(m_io_context);

    boost::asio::connect(socket, m_endpoints);

    try
    {
        for(;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;
    
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
    
            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);
    
            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}