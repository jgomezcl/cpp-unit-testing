cmake_minimum_required(VERSION 3.12)
project(my_project LANGUAGES C CXX)
include(CTest)

# Set source and test folders (only needed if your directories are different from /src and /test)
set(PROJECT_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROJECT_TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# List of test names (without extension) to skip separated by semicolons
set(SKIP_UNIT_TESTS "")

# Include the unit-testing infrastructure
add_subdirectory(unit_testing)
