cmake_minimum_required(VERSION 3.15)
project(Lab03c)

set(CMAKE_C_STANDARD 11)

# Исполняемый файл
add_executable(Lab03c main.c)

target_link_libraries(Lab03c PRIVATE LibSVAd dl)
target_include_directories(Lab03c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
