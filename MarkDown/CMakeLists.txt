cmake_minimum_required(VERSION 3.14)
project(MarkDown)

set(CMAKE_CXX_STANDARD 11)

add_executable(MarkDown main.cpp Parser.cpp Parser.h Values.cpp)