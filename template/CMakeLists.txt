cmake_minimum_required(VERSION 3.31.6) # Only tested version

project(solution)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)
set(CXX_EXTENSIONS False)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(1 1.cpp)
add_executable(2 2.cpp)