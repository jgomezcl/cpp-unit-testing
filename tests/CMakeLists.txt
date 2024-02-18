cmake_minimum_required(VERSION 3.8)

set(This unit_tests)

# Add here your files containing tests
set(Sources
    test_example.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    source_code
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
