cmake_minimum_required(VERSION 3.8)

set(This source_code)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

include(CTest)

# Add main project subdirectory and import configuratin properties
add_subdirectory(../test test)

get_property(Headers GLOBAL PROPERTY Headers)
get_property(Sources GLOBAL PROPERTY Sources)
get_property(Directories GLOBAL PROPERTY Directories)

# Update the paths
set(src_path "../src")

foreach(dir ${Directories})
    list(APPEND dirs "${src_path}/${dir}")
endforeach()
list(APPEND dirs ${source_path})
set(Directories ${dirs})

# Additional compiler symbols
add_compile_options("-DDEBUG")

# Build source code, if present
if (DEFINED Headers AND DEFINED Sources)

    # Update the paths
    foreach(head ${Headers})
        list(APPEND head_files "${src_path}/${head}")
    endforeach()

    foreach(src ${Sources})
        list(APPEND src_files "${src_path}/${src}")
    endforeach()

    add_library(${This} STATIC ${src_files} ${head_files})
    set_property(GLOBAL PROPERTY source_code ${This})

    # Add directories where included header files can be found
    target_include_directories(${This} PUBLIC
        utils/
        ${Directories}
    )

endif(DEFINED Headers AND DEFINED Sources)

add_subdirectory(unit_tests)
