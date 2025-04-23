cmake_minimum_required(VERSION 3.10)

project(StaticLib)

set(CMAKE_CXX_STANDARD 17)

add_library(SVALib STATIC
    binary_search.c
)


target_include_directories(SVALib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
