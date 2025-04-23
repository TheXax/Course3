cmake_minimum_required(VERSION 3.15)
project(Lab03a C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab03a main.c)

target_include_directories(Lab03a PRIVATE
    ${CMAKE_SOURCE_DIR}/SVALib  # путь до библиотеки
)

target_link_libraries(Lab03a PRIVATE SVALib)
