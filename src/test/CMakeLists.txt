cmake_minimum_required(VERSION 3.0)
project ("test")

if(MSVC)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:20971520")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
	SET(CMAKE_CXX_FLAGS "-std=c++11")
endif(MSVC)


add_executable(testall
	testSolution.cpp
)

if(MSVC)

	target_link_libraries(testall ../../lib/windows/gtest_main)
	target_link_libraries(testall ../../lib/windows/gtest)
	include_directories(../../include/windows)
else()
    find_library(GTEST_LIBS NAMES gtest gtest_main PATHS ../../lib/linux/gtest/)
    target_link_libraries(testall ${GTEST_LIBS})
    include_directories(../../include/linux)
endif(MSVC)


install(TARGETS testall DESTINATION bin)

