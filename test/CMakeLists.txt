cmake_minimum_required(VERSION 3.14)
project(tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

enable_testing()

add_executable(
    example_test
    example_test.cpp
)

target_link_libraries(
    example_test
    PRIVATE
    GTest::Gtest
    test
)

# add_test(test_example1)

# include(GoogleTest)
# gtest_discover_tests(example_test)