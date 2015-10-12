cmake_minimum_required(VERSION 2.8.4)
project(euler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03 -Wall")

set(SOURCE_FILES main.cpp)
add_executable(euler ${SOURCE_FILES})