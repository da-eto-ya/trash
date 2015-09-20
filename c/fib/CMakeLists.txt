cmake_minimum_required(VERSION 3.3)
project(fib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

add_executable(fib fib.c)
add_executable(classes_elf classes_elf.cpp)
add_executable(classes_order classes_order.cpp)
