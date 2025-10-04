# Unit Testing

Pre-configured unit testing environment for **C/C++** projects, based on [Google Test](https://github.com/google/googletest) and [VS Code](https://code.visualstudio.com/).

## Requirements

* **GCC**
* **CMake**
* **CMakeTools** extension for **VS Code**
* **C++ TestMate** extension for **VS Code**

## Getting Started
1. Import this repository into the project you want to unit test — ideally at the root level, alongside your source code folder `/src`.

2. Create a `/test` folder in your project to contain the unit tests.

3. Copy `configuration/CMakeLists.txt` from this repository into your project's root directory (the same level than `/src`).

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
* Test filenames should start with `test_` (for example, `test_math.cpp`).
* You can use the example in `examples/test_example.cpp` as a reference.
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
    - Install the **CMakeTools extension**.
    - Install the **C++ TestMate extension**.

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

## Resources

* [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)
* [Configure C/C++ debugging](https://code.visualstudio.com/docs/cpp/launch-json-reference)
* [Google Test documentation](https://google.github.io/googletest/)
