cmake_minimum_required(VERSION 3.12)

project(unit_testing LANGUAGES C CXX)

option(ENABLE_COVERAGE "Enable code coverage flags" ON)

if(ENABLE_COVERAGE)
    message(STATUS "Building with coverage instrumentation")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-O0 -g --coverage)
        add_link_options(--coverage)
    else()
        message(WARNING "Coverage only supported with GCC or Clang")
    endif()
endif()

# Path to the project source code
if(NOT DEFINED PROJECT_SRC_DIR)
    set(PROJECT_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/../src" CACHE PATH "Path to the project's source folder")
endif()

if(NOT PROJECT_SRC_DIR)
    message(FATAL_ERROR "You must set PROJECT_SRC_DIR to the project's source folder")
endif()

# Path to the project test code
if(NOT DEFINED PROJECT_TEST_DIR)
    set(PROJECT_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/../test" CACHE PATH "Path to the project's test folder")
endif()

if(NOT PROJECT_TEST_DIR)
    message(FATAL_ERROR "You must set PROJECT_TEST_DIR to the project's test folder")
endif()

# Collect source and header files from the project
file(GLOB_RECURSE PROJECT_C_SOURCES  "${PROJECT_SRC_DIR}/*.c")
file(GLOB_RECURSE PROJECT_CPP_SOURCES "${PROJECT_SRC_DIR}/*.cpp")

set(PROJECT_SOURCES ${PROJECT_C_SOURCES} ${PROJECT_CPP_SOURCES})

if(NOT PROJECT_SOURCES)
    message(FATAL_ERROR "No .c/.cpp source files found in ${PROJECT_SRC_DIR}")
endif()

# List all source files found
message(NOTICE "[NOTICE] Found source files:")
foreach(src IN LISTS PROJECT_SOURCES)
    message(NOTICE "    - ${src}")
endforeach()

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
add_subdirectory(googletest EXCLUDE_FROM_ALL)

# Collect all test files
file(GLOB TEST_SOURCES "${PROJECT_TEST_DIR}/test_*.cpp")

# Convert semicolon-separated string to a list
separate_arguments(SKIP_UNIT_TESTS)
set(SKIP_HEADER_PRINTED FALSE CACHE INTERNAL "Flag to print skip header once")

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)

    # Skip if this test is in the skip list
    list(FIND SKIP_UNIT_TESTS ${test_name} skip_index)
    if(NOT skip_index EQUAL -1)
        if(NOT SKIP_HEADER_PRINTED)
            message(NOTICE "[NOTICE] Skipped tests:")
            set(SKIP_HEADER_PRINTED TRUE CACHE INTERNAL "")
        endif()
        message(NOTICE "    - ${test_name}")
        continue()
    endif()

    add_executable(${test_name} ${test_src})

    # Include mocks if present
    target_include_directories(${test_name}
        PRIVATE
        ${PROJECT_TEST_DIR}/mock
    )

    target_link_libraries(${test_name} PRIVATE project_lib gtest gtest_main)

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

find_program(GCOVR_EXECUTABLE gcovr)

# if(NOT GCOVR_EXECUTABLE)
#         message(WARNING
#             "⚠️  gcovr not found. Please install it with:\n"
#             "   pip install gcovr\n"
#             "Then re-run cmake -DENABLE_COVERAGE=ON -B build"
#         )
# endif()

if(ENABLE_COVERAGE AND GCOVR_EXECUTABLE)
    add_custom_target(coverage
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND ${GCOVR_EXECUTABLE}
            -r ${CMAKE_SOURCE_DIR}
            --object-directory ${CMAKE_BINARY_DIR}
            --html --html-details -o coverage.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "📊 Running tests and generating HTML coverage report..."
        VERBATIM
    )
endif()
