cmake_minimum_required(VERSION 3.0)
project ("LeetCodePlayground")


SET(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(runLeetCode LeetCodeSolutions.cpp)

install(TARGETS runLeetCode DESTINATION bin)