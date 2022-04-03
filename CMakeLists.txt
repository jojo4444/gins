cmake_minimum_required(VERSION 3.21)
project(gins)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

add_executable(gins main.cpp primitives/point.h pdata/data.h pdata/data.cpp errors/errors.h errors/errors.cpp solve/algo.cpp solve/algo.h solve/low/Low.cpp solve/low/Low.h)
