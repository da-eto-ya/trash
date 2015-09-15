cmake_minimum_required(VERSION 3.3)
project(simple_examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

add_executable(roots roots)
add_executable(syntax syntax)
add_executable(sum sum)
add_executable(power power)
add_executable(space_eater space_eater)
add_executable(intlog intlog)
