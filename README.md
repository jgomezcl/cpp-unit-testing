# C/C++ Unit Testing [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


Pre-configured unit testing environment for **C/C++** projects, based on [Google Test](https://github.com/google/googletest) and [VS Code](https://code.visualstudio.com/).

**Note**: This setup has been tested primarily on Windows (MSYS2 / MinGW-w64). It should also work on Linux systems with minor adjustments to paths or shell syntax.

## Requirements

* **GCC**
* **CMake**
* **[CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)** extension for **VS Code**
* **[C++ TestMate](https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter)** extension for **VS Code**

## Getting Started
1. Import this repository into the project you want to unit test — ideally at the root level, alongside your source folder `/src`.

2. Create a `/test` folder in your project to contain the unit tests.

3. Copy `configuration/CMakeLists.txt` from this repository into your project's root directory (the same level as `/src`).

    ```
    project/
    ├─ CMakeLists.txt <--
    ├─ src/
    ├─ test/
    └─ unit_testing/
    ```

4. Edit the copied `CMakeLists.txt` so that it points to your source and/or test directories if they have different names or are nested differently.

    ```cmake
    set(PROJECT_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
    set(PROJECT_TEST_DIR ${CMAKE_SOURCE_DIR}/test)
    ```

## Adding Unit Tests

* Add your test files in the `/test` folder.
* Test filenames should start with `test_` (for example, `test_math.cpp`). All files in the `/test` folder that start with `test_` will be automatically added to the build as tests.
* Use `examples/test_example.cpp` as a reference for creating new tests.
* Refer to [Google Test](https://google.github.io/googletest/) for additional instructions on defining tests.

## Environment Setup (Windows)
The following steps describe how to set up a Windows development environment using **MSYS2** and **VS Code**.

1. Download and install [MSYS2](https://www.msys2.org/).

2. Open an **UCRT64** terminal and install the **MinGW-w64** toolchain:

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

3. Install **CMake**:

```bash
pacman -S mingw-w64-x86_64-cmake
```

4. Add the **MinGW-w64** installation folder to your `PATH` environment variable (the default path is `C:\msys64\ucrt64\bin`).

5. In **VS Code**:
    - Install the **CMake Tools** extension.
    - Install the **C++ TestMate** extension.

## Running and Debugging Unit Tests

This section explains how to configure **VS Code** and **CMake** to build, run, and debug your unit tests.

### 1. Configure CMake and VS Code

1. Restart **VS Code** and select the appropriate **CMake** source directory and compiler kit.
   The selected source directory is stored in `.vscode/settings.json` under the key `"cmake.sourceDirectory"`.

2. Set the build directory for the test project by adding the following to `settings.json`:

    ```json
    "cmake.buildDirectory": "${workspaceFolder}/test/build"
    ```

3. Configure **C++ TestMate** to locate test executables by adding this entry to `settings.json`:

    ```json
    "testMate.cpp.test.advancedExecutables": [
        {
            "pattern": "test/{build,Build,BUILD,out,Out,OUT}/**/*{test,Test,TEST}*"
        }
    ],
    ```

### 2. Running Tests

- Launch tests from the **Testing** tab in **VS Code** as usual.
- TestMate will automatically detect files starting with `test_` and run them.

### 3. Debugging Tests

1. Create a `.vscode/launch.json` file (if it does not exist) with the following configuration:

    ```json
    {
        "version": "0.2.0",
        "configurations": [
            {
                "name": "Debug tests",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/test/build/unit_tests.exe",
                "environment": [{ "name": "config", "value": "Debug" }],
                "cwd": "${workspaceFolder}"
            }
        ]
    }
    ```

2. Launch a debug session from the **Run and Debug** tab in **VS Code**.

## ⚠️ Common Pitfalls

These are typical issues encountered when integrating **C/C++** unit tests with **Google Test** in **VS Code**.

* Missing C++ include guards in C headers.

    If your project contains **C headers** included in **C++ test files**, you may encounter **linker errors** like:

    ```text
    undefined reference to my_function()
    ```

    This often happens when the header is missing proper include guards or `extern "C"` blocks.

    **Solution:** Wrap your C headers with C++ guards:

    ```cpp
    #ifdef __cplusplus
    extern "C" {
    #endif

    // Your C header contents here

    #ifdef __cplusplus
    }
    #endif
    ```

* Unbuildable unit tests.

    Sometimes a unit test cannot be built due to a refactor in the source code.

    **Solution:** Skip the problematic tests by adding them to the `CMakeLists.txt`:

    ```cmake
    set(SKIP_UNIT_TESTS "test_skip1.cpp;test_skip2.cpp")
    ```

    These tests will be ignored during the build, preventing build errors while you fix them.

## (Optional) Code Coverage

Unit tests are already configured to generate coverage data files (`.gcno` and `.gcda`) inside the `/build` directory.

You can use `gcovr` to convert this raw data into human-readable reports.

### Installation

Install `gcovr` with:

```bash
pip install gcovr
```

### Generating a Coverage Report

To generate a coverage report, run:

```bash
gcovr -r ${source_code_folder} -d ${build_folder} --html --html-details -o coverage.html
```

**Notes**:

* Replace `${source_code_folder}` with the path to your source files (e.g. `../src`).

* Replace `${build_folder}` with the folder containing the compiled object and coverage data (e.g. `../build`).

* The `--html` and `--html-details` options create an interactive HTML report named `coverage.html`.

`gcovr` generates multiple output files in the folder where it runs, so it’s recommended to execute it from a separate directory.

### Output Location

`gcovr` generates several intermediate files (HTML, JSON, etc.) in the directory where it is executed.

For a cleaner workspace, it’s recommended to run this command from a separate folder, for example:

```bash
mkdir coverage
cd coverage
gcovr -r ../src -d ../build --html --html-details -o coverage.html
```

This will keep all generated files contained within the `coverage/` directory.

### LCOV Output for Editor Integration

If you also want to view coverage directly in **VSCode** or CI tools, add the `--lcov` option:

```bash
gcovr -r ../src -d ../build --html --html-details -o coverage.html --lcov=coverage.info
```

This creates:

* `coverage.html` → for browsing in a web browser
* `coverage.info` → for use with tools like VS Code’s [Coverage Gutters](https://marketplace.visualstudio.com/items?itemName=ryanluker.vscode-coverage-gutters) extension

### Output Generation Automation

The generation of coverage reports can be automated with a VS Code task defined in `.vscode/tasks.json`:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Generate coverage report",
            "type": "shell",
            "command": "gcovr",
            "args": [
                "-r", "../../src",
                "-d", "../build/unit_testing",
                "--html", "--html-details", "-o", "coverage.html",
                "--lcov=coverage.info",
            ],
            "options": {
                "cwd": "${workspaceFolder}/test/coverage"
            },
            "group": {
                "kind": "test",
                "isDefault": true
            },
            "problemMatcher": []
        }
    ]
}
```

## Resources

* [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)
* [Configure C/C++ debugging](https://code.visualstudio.com/docs/cpp/launch-json-reference)
* [Google Test documentation](https://google.github.io/googletest/)
