cmake_minimum_required(VERSION 3.18)
project(DemoService)

add_executable(DemoService
    DemoService.cpp
    ServiceUtils.cpp
    ServiceUtils.h
)

target_link_libraries(DemoService
    ws2_32
)