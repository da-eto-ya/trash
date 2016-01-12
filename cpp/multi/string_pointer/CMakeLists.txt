cmake_minimum_required(VERSION 2.8.4)
project(string_pointer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(string_pointer ${SOURCE_FILES})