# Unit testing
Pre-configured unit testing environment for C/C++ projects, based on [Google Test](https://google.github.io/googletest/).

## Requirements
* GCC
* CMake
* (optional) VS Code
* (optional) CMakeTools (VS Code extension)
* (optional) C++ TestMate (VS Code extension)

## Envinronment setup (Windows)
* Download and install [MSYS2](https://www.msys2.org/).
* Open an UCRT64 terminal and install the MinGW-w64 toolchain.
```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```
* Install CMake.
```bash
pacman -S mingw-w64-x86_64-cmake
```
* Add the MinGW-w64 install folder to the PATH environment variable (default *C:\msys64\ucrt64\bin*).

* In VS Code, locate and install the CMakeTools extension.
* In VS Code, locate and install the C++ TestMate extension.

# Usage
## Import into a project
* Add the repository as a submodule, at the same level as the */src* folder.
* Create an additional folder at the same level of */src* named */tests*.
* Add as many test files as required into the folder */tests* following the example available in *examples/test_example.cpp*.
* Copy the file *examples/CMakeLists.txt* into the folder */tests* and adapt it to your project structure.

## Create tests
* All tests belonging to a module should be in a single test file.
* All tests belonging to a tested file should belong to the same test suite.
* See [Google Test](https://google.github.io/googletest/) for instructions about how to define tests.

## Run tests (VS Code)
* Launch the tests from the *Testing* tab.

## Debug unit tests (VS Code)
* Create a *launch.json* file in */.vscode* and add the following settings
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
