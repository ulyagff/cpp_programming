cmake_minimum_required(VERSION 3.20)
project(Circular_buffer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Circular_buffer main.cpp circul_buf.h curcul_buf.cpp iterator.cpp)
