cmake_minimum_required(VERSION 3.3)
project(simple_examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

add_executable(roots roots.cpp)
add_executable(syntax syntax.cpp)
add_executable(sum sum.cpp)
add_executable(power power.cpp)
add_executable(space_eater space_eater.cpp)
add_executable(intlog intlog.cpp)
add_executable(newref newref.cpp)
