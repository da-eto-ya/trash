cmake_minimum_required(VERSION 2.8.4)
project(threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(threads threads.cpp)
target_link_libraries(threads rt pthread)

add_executable(mutex mutex.cpp)
target_link_libraries(mutex rt pthread)

add_executable(cond cond.cpp)
target_link_libraries(cond rt pthread)
