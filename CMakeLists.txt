cmake_minimum_required(VERSION 3.16)
project(gins)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pthread")

set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3 -march=native")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)