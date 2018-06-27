cmake_minimum_required(VERSION 3.10)
project(compiler_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(compiler_test main.cpp Pipe.h Element.cpp Element.h Solution.cpp Solution.h)