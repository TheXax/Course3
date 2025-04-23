cmake_minimum_required(VERSION 3.15)
project(SVALib C)

set(CMAKE_C_STANDARD 99)

add_library(SVALib STATIC
    binary_search.c
)

target_include_directories(SVALib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
