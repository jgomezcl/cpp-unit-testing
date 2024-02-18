cmake_minimum_required(VERSION 3.8)

set(This source_code)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

include(CTest)

# Add here your header files
set(Headers
    src/header.h
)

# Add here your source files
set(Sources
    src/source.cpp
)

# Add here any required compiler symbols
add_compile_options("-DDEBUG")

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)
