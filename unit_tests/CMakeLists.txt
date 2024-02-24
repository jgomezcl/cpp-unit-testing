cmake_minimum_required(VERSION 3.8)

set(This unit_tests)

set(test_path "../../test")

add_subdirectory("${test_path}" test)

get_property(Tests GLOBAL PROPERTY Tests)
get_property(source_code GLOBAL PROPERTY source_code)

# Update the paths
foreach(test ${Tests})
    list(APPEND test_files "${test_path}/${test}")
endforeach()

add_executable(${This} ${test_files})

target_link_libraries(${This} PUBLIC
    gtest_main
    ${source_code}
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
