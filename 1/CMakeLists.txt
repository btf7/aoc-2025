cmake_minimum_required(VERSION 3.31.6) # Only tested version

project(solution)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED True)
set(CXX_EXTENSIONS False)

if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
	add_compile_options(-Wall -Wextra -Wpedantic -Og -g3)
else()
	message(NOTICE "Compiler is not g++, using default CMake options")
endif()

add_executable(1 1.cpp)
add_executable(2 2.cpp)