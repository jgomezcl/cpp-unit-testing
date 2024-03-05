cmake_minimum_required(VERSION 3.8)

# Add here the header files (relative to /src folder)
set_property(GLOBAL PROPERTY header_files
    raggastar/mcb/mcb_crc.h
    raggastar/mcb/mcb_state_machine.h
    raggastar/mcb/mcb_frame.h
    raggastar/mcb/field/mcb_field.h
    raggastar/mcb/field/mcb_field_config.h
    raggastar/mcb/field/mcb_field_cyclic.h
)

# Add here your source files (relative to /src folder)
set_property(GLOBAL PROPERTY source_files
    raggastar/mcb/mcb_crc.cpp
    raggastar/mcb/mcb_state_machine.cpp
    raggastar/mcb/mcb_frame.cpp
    raggastar/mcb/field/mcb_field.cpp
    raggastar/mcb/field/mcb_field_config.cpp
    raggastar/mcb/field/mcb_field_cyclic.cpp
)

# Add here any additional directories to be included (relative to /src folder)
set_property(GLOBAL PROPERTY directories
    raggastar/mcb
    raggastar/mcb/mode
    raggastar/mcb/field
)

# Add here the test files (relative to /test folder)
set_property(GLOBAL PROPERTY test_files
    test_ecat.cpp
    test_mcb_crc.cpp
    test_mcb_state_machine.cpp
    test_mcb_frame.cpp
    test_mcb_field_config.cpp
    test_mcb_field_cyclic.cpp
)
