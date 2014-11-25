cmake_minimum_required(VERSION 3.0)
project ("LeetCodePlayground")


SET(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(runLeetCode 	Solution.h
							LeetCodeSolutions.cpp
							MaxDepth.h
							BuyStock.h
							SearchInsertPosition.h
							PascalTree.h
							ReverseInteger.h
							IsSameTree.h
							SingleNumber.h)

install(TARGETS runLeetCode DESTINATION bin)