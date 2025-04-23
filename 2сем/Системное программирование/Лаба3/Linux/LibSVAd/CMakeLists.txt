cmake_minimum_required(VERSION 3.15)
project(LibSVAd C)

set(CMAKE_C_STANDARD 11)

add_library(LibSVAd SHARED
    binary_search.c
)

target_include_directories(LibSVAd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Установим путь к лог-файлу через компилятор
add_definitions(-DLOG_FILE_PATH="/tmp/libsvad_log.txt")
