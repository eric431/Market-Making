cmake_minimum_required(VERSION 3.14)

project(feed_handler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)

add_library(feed_handler_library STATIC src/api_handler.cpp header/api_handler.hpp)
target_include_directories(feed_handler_library PUBLIC header)

add_executable(api_handler main/api_handler_main.cpp)
target_link_libraries(api_handler PUBLIC feed_handler_library)

add_executable(listener main/coinbase_websocket_listener.cpp)
target_link_libraries(listener PRIVATE nlohmann_json::nlohmann_json)