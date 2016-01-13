cmake_minimum_required(VERSION 2.8.4)
project(simple_allocator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(simple_allocator ${SOURCE_FILES})