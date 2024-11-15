cmake_minimum_required(VERSION 3.14)
# project(feed_handler
#         Description "Project to parse FIX messages"
#         LANGUAGE CXX)

project(feed_handler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(CURL REQUIRED)
find_package(Boost REQUIRED)

# if(NOT CURL_FOUND)
#     message(SEND_ERROR "Failed to find Curl")
#     return()
# else()
#     include_directories(${CURL_INCLUDE_DIR})
# endif()

add_library(feed_handler_library STATIC src/api_handler.cpp header/api_handler.hpp)
target_include_directories(feed_handler_library PUBLIC header)

add_executable(api_handler main/api_handler_main.cpp)
target_link_libraries(api_handler PUBLIC feed_handler_library)