cmake_minimum_required(VERSION 3.12)
project(my_project LANGUAGES C CXX)
include(CTest)

# Set source and test folders
set(PROJECT_SRC_DIR ${CMAKE_SOURCE_DIR}/unit_testing/src)
set(PROJECT_TEST_DIR ${CMAKE_SOURCE_DIR}/unit_testing/test)

# Include the unit-testing infrastructure
add_subdirectory(unit_testing)
