cmake_minimum_required(VERSION 3.8)

set(This unit_tests)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

# Main paths
set(source_path "../src")
set(test_path "../test")
set(mock_path "${test_path}/mock")

add_subdirectory(googletest)
add_subdirectory(${test_path} build)

list(APPEND libraries gtest_main)
include(CTest)

# Get properties from config file in /tests
get_property(header_files GLOBAL PROPERTY header_files)
get_property(source_files GLOBAL PROPERTY source_files)
get_property(directories GLOBAL PROPERTY directories)
get_property(test_files GLOBAL PROPERTY test_files)

# Additional compiler symbols
add_compile_options("-DDEBUG")

# Build source code, if present
if (DEFINED header_files AND DEFINED source_files)

    list(TRANSFORM header_files PREPEND "${source_path}/")
    list(TRANSFORM source_files PREPEND "${source_path}/")

    add_library(source_lib STATIC ${source_files} ${header_files})

    # Add directories where included header files can be found
    list(TRANSFORM directories PREPEND "${source_path}/")

    target_include_directories(source_lib PUBLIC
        ${mock_path}
        ${directories}
        "${source_path}/"
    )

    # Add to the libraries list
    list(APPEND libraries source_lib)

endif(DEFINED header_files AND DEFINED source_files)


list(TRANSFORM test_files PREPEND "${test_path}/")

add_executable(${This} ${test_files})

target_link_libraries(${This} PUBLIC
    ${libraries}
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
