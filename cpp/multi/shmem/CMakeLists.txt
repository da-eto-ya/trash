cmake_minimum_required(VERSION 2.8.4)
project(shmem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(sysv_shm sysv_shm.cpp)
add_executable(posix_shm posix_shm.cpp)
target_link_libraries(posix_shm rt pthread)
