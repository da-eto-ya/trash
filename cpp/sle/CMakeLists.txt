cmake_minimum_required(VERSION 3.3)
project(sle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++98 -O2 -static")

set(SOURCE_FILES main.cpp)
add_executable(sle ${SOURCE_FILES})
