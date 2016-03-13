cmake_minimum_required(VERSION 3.0)
project ("test")

if(MSVC)
else()
	SET(CMAKE_CXX_FLAGS "-std=c++11")
endif(MSVC)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:20971520")

include_directories(../../include)

add_executable(testall
	testSolution.cpp
)

target_link_libraries(testall ../../lib/gtest_main)
target_link_libraries(testall ../../lib/gtest)

install(TARGETS testall DESTINATION bin)

