cmake_minimum_required(VERSION 3.14)
project(boost_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)        

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find Boost")
    return()
else()
    include_directories(${Boost_INCLUDE_DIR})
endif()

# add_library(feed_handler STATIC header/FIX.h)

add_executable(boost_example boost_example.cpp)