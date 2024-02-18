cmake_minimum_required(VERSION 3.8)

set(This unit_tests)

add_subdirectory(../../test test)

get_property(Tests GLOBAL PROPERTY Tests)
get_property(source_code GLOBAL PROPERTY source_code)

add_executable(${This} ../${Tests})

target_link_libraries(${This} PUBLIC
    gtest_main
    ${source_code}
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
