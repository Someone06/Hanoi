cmake_minimum_required(VERSION 3.22)
project(hanoi)

set(CMAKE_CXX_STANDARD 20)

add_executable(hanoi_interactive main.cpp)
target_compile_definitions(hanoi_interactive PRIVATE INTERACTIVE)

add_executable(hanoi_test main.cpp)
