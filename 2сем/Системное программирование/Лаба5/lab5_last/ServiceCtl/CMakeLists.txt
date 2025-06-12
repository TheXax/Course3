cmake_minimum_required(VERSION 3.18)

project(ServiceCtl)

add_executable(ServiceCtl
    ServiceCtl.cpp
)

target_link_libraries(ServiceCtl
    advapi32
)
