cmake_minimum_required(VERSION 3.14)

project(feed_handler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(feed_handler_library STATIC src/coinbase_client.cpp header/coinbase_client.hpp
                                        src/trading_messages.cpp header/trading_messages.hpp)
target_include_directories(feed_handler_library PUBLIC header)
target_link_libraries(feed_handler_library PRIVATE nlohmann_json::nlohmann_json
                                                   OpenSSL::SSL
    )

add_executable(listener main/coinbase_client_main.cpp)
target_link_libraries(listener PUBLIC feed_handler_library)