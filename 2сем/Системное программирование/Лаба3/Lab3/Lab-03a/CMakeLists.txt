cmake_minimum_required(VERSION 3.20)

include_directories(${CMAKE_SOURCE_DIR}/SVALib/binary_search.h)

add_executable(Lab-03a main.c)

target_link_libraries(Lab-03a SVALib)
