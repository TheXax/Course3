cmake_minimum_required(VERSION 3.30)
project(laba1)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

# Определение ОС
if(WIN32)
    message("Hello, I am Windows!")
elseif(APPLE)
    message("Hello, I am macOS!")
elseif(UNIX)
    message("Hello, I am Linux!")
endif()


add_subdirectory(lab1c)

include(CheckLanguage)
check_language(CSharp)

if(CMAKE_CSharp_COMPILER)
  enable_language(CSharp)
  message(STATUS "Yes C# support")
  add_subdirectory(lab1cs)
else()
  message(STATUS "No c# support")
endif()