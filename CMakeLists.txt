cmake_minimum_required(VERSION 3.26)
project(03_homework)

set(CMAKE_CXX_STANDARD 17)

add_executable(03_homework main.cpp
        src/factorial.cpp
        src/CustomAllocator.hpp
)
