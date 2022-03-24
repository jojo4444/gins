cmake_minimum_required(VERSION 3.21)
project(gins)

set(CMAKE_CXX_STANDARD 20)

add_executable(gins main.cpp primitives/point.h polygon/polygon.h polygon/data.h polygon/data.cpp)
