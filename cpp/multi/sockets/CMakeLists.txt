cmake_minimum_required(VERSION 2.8.4)
project(sockets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")

add_executable(server server.cpp)
add_executable(client client.cpp)
