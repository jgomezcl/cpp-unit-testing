#include <cstdlib>
#include <gtest/gtest.h>

#ifndef PROJECT_SRC_DIR
#error "PROJECT_SRC_DIR not defined"
#endif

#ifndef PROJECT_BUILD_DIR
#error "PROJECT_BUILD_DIR not defined"
#endif

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Run all tests
    int test_result = RUN_ALL_TESTS();

    // Build the gcovr command
    std::string cmd = "gcovr -r " PROJECT_SRC_DIR
                      " -d " PROJECT_BUILD_DIR
                      " --html --html-details -o coverage.html -v";

    int coverage_result = std::system(cmd.c_str());
    if (coverage_result != 0) {
        std::cerr << "Coverage generation failed!" << std::endl;
    }

    return test_result;
}


// # Add coverage runner executable
// add_executable(coverage_runner unit_testing/coverage_runner.cpp)

// target_link_libraries(coverage_runner PRIVATE project_lib gtest gtest_main)

// target_include_directories(coverage_runner PRIVATE ${PROJECT_SRC_DIR} ${PROJECT_TEST_DIR})

// # Pass source and build paths to the executable
// target_compile_definitions(coverage_runner PRIVATE
//     PROJECT_SRC_DIR="${PROJECT_SRC_DIR}"
//     PROJECT_BUILD_DIR="${CMAKE_BINARY_DIR}"
// )