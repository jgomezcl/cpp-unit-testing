# Unit testing
Pre-configured unit testing environment for C/C++ projects, based on [Google Test](https://github.com/google/googletest).

## Requirements
* GCC
* CMake
* (optional) VS Code
* (optional) CMakeTools extension (for VS Code)
* (optional) C++ TestMate extension (for VS Code)

## Environment setup (Windows)
* Download and install [MSYS2](https://www.msys2.org/).
* Open an UCRT64 terminal and install the MinGW-w64 toolchain:
```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```
* Install CMake:
```bash
pacman -S mingw-w64-x86_64-cmake
```
* Add the MinGW-w64 installation folder to the PATH environment variable (default is *C:\msys64\ucrt64\bin*).

* In VS Code, locate and install the CMakeTools extension.
* In VS Code, locate and install the C++ TestMate extension.

# Usage
## Import into another project
* Add the repository as a submodule.
    * Place the submodule at the same level as your project’s `src` folder:
    ```text
    project/
    ├─ src/
    ├─ unit_testing/
    ```
* Create a folder for your tests.
    * Create a folder `test` at the same level as `src` (or configure a custom folder if desired):
    ```text
    project/
    ├─ src/
    ├─ test/
    ├─ unit_testing/
    ```
    * Add your test files in this folder.
    * Test filenames should start with `test_` (e.g., test_math.cpp).
    * You can follow the example in `examples/test_example.cpp`.
* Configure the `CMakeLists.txt`.
    * Copy `configuration/CMakeLists.txt` to your project root (same folder as `src` and the submodule).
    * Edit it to set the correct paths for your project:
    ```text
    set(PROJECT_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
    set(PROJECT_TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
    ```

## Create tests
* All tests belonging to a file under test should be in a single test file.
* All tests belonging to a module should belong to the same test suite.
* Refer to [Google Test](https://google.github.io/googletest/) for instructions on defining tests.

## Run tests (VS Code)
* Restart VS code and select the appropriate CMake folder and compiler kit.
* Add the following entry to *settings.json* to build the project in the */test* folder:
```bash
"cmake.buildDirectory": "${workspaceFolder}/test/build"
```
* Add the following entry to *settings.json* so C++ TestMate can locate the generated executable:
```bash
"testMate.cpp.test.advancedExecutables": [
        {
          "pattern": "test/{build,Build,BUILD,out,Out,OUT}/**/*{test,Test,TEST}*",
        }
    ],
```
* Launch tests from the *Testing* tab as usual.

## Debug unit tests (VS Code)
* Create a *launch.json* file in */.vscode* and add the following settings:
```bash
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug tests",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/unit_tests/unit_tests.exe",
            "environment": [{ "name": "config", "value": "Debug" }],
            "cwd": "${workspaceFolder}"
        }
    ]
}
```
* Launch the debug session from the *Run and Debug* tab.

## Resources

* [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)
* [Configure C/C++ debugging](https://code.visualstudio.com/docs/cpp/launch-json-reference)
