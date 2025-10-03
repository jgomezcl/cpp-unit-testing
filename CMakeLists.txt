cmake_minimum_required(VERSION 3.12)

project(unit_testing LANGUAGES C CXX)

# Path to the project source code
set(PROJECT_SRC_DIR "" CACHE PATH "Path to the project's source code folder")
# Path to the project's test folder
set(PROJECT_TEST_DIR "" CACHE PATH "Path to the project's test folder")


# Validate inputs
if(NOT PROJECT_SRC_DIR)
    message(FATAL_ERROR "You must set PROJECT_SRC_DIR to the project's source folder")
endif()

if(NOT PROJECT_TEST_DIR)
    message(FATAL_ERROR "You must set PROJECT_TEST_DIR to the project's test folder")
endif()

# Collect source and header files from the project
file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_SRC_DIR}/*.c)
file(GLOB_RECURSE PROJECT_HEADERS ${PROJECT_SRC_DIR}/*.h)

# Build the project library
add_library(project_lib ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Include all subfolders of source folder
file(GLOB_RECURSE ALL_SUBDIRS LIST_DIRECTORIES true ${PROJECT_SRC_DIR}/*)
set(INCLUDE_DIRS ${PROJECT_SRC_DIR})
foreach(dir ${ALL_SUBDIRS})
    if(IS_DIRECTORY ${dir})
        list(APPEND INCLUDE_DIRS ${dir})
    endif()
endforeach()

target_include_directories(project_lib PUBLIC ${INCLUDE_DIRS})

# Enable testing and add GoogleTest
enable_testing()
add_subdirectory(googletest)

# Collect all test files
file(GLOB TEST_SOURCES "${PROJECT_TEST_DIR}/test_*.cpp")

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)

    add_executable(${test_name} ${test_src})

    # Include mocks if present
    target_include_directories(${test_name}
        PRIVATE
        ${PROJECT_TEST_DIR}/mock
    )

    target_link_libraries(${test_name} PRIVATE project_lib gtest gtest_main)

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
