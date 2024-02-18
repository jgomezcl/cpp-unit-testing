cmake_minimum_required(VERSION 3.8)

# Add here your header files (remove if none)
set_property(GLOBAL PROPERTY Headers
    ../src/header_1.h
)

# Add here your source files (remove if none)
set_property(GLOBAL PROPERTY Sources
    ../src/source_1.cpp
)

# Add here your directories to be included (remove if none)
set_property(GLOBAL PROPERTY Directories
    ../src/
)

# Add here your test files
set_property(GLOBAL PROPERTY Tests
    ../test/example.cpp
)
