cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-g")

project(UCS)
enable_testing()

add_subdirectory(lib)
add_subdirectory(src)

