cmake_minimum_required(VERSION 3.20)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(SVADLib++ SHARED binary_search.cpp)
