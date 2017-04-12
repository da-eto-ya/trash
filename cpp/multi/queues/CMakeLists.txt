cmake_minimum_required(VERSION 2.8.4)
project(queues)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v -Wall -lrt")


add_executable(sysv_queue_server sysv_queue_server.cpp)
add_executable(sysv_queue_sender sysv_queue_sender.cpp)

add_executable(posix_server posix_server.cpp)
target_link_libraries(posix_server rt)

add_executable(posix_sender posix_sender.cpp)
target_link_libraries(posix_sender rt)
