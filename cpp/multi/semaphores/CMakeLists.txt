cmake_minimum_required(VERSION 2.8.4)
project(semaphores)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(semaphores semaphores.cpp)
add_executable(posix_sem posix_sem.cpp)
target_link_libraries(posix_sem rt pthread)
