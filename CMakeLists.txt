cmake_minimum_required(VERSION 3.10)

project(Robot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a library for the core logic so it can be shared between main and tests
add_library(robot_core STATIC
    src/robot_map.cpp
    src/command.cpp
    src/command_parser.cpp
)

# Include directories for the library
target_include_directories(robot_core PUBLIC include)

# Main executable
add_executable(robot src/main.cpp)
target_link_libraries(robot PRIVATE robot_core)

# Google Test
# Prevent GoogleTest from overriding our compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(external/googletest)

# Test executable
add_executable(robot_test
    tests/main.cpp
    tests/unittest/robot_map_test.cpp
    tests/unittest/command_test.cpp
    tests/unittest/command_parser_test.cpp
)

# Link against the core library and Google Test
target_link_libraries(robot_test PRIVATE robot_core gtest)

# Compiler options
if(MSVC)
    target_compile_options(robot PRIVATE /W4 /EHsc)
    target_compile_options(robot_core PRIVATE /W4 /EHsc)
    target_compile_options(robot_test PRIVATE /W4 /EHsc)
else()
    target_compile_options(robot PRIVATE -Wall -Wextra)
    target_compile_options(robot_core PRIVATE -Wall -Wextra)
    target_compile_options(robot_test PRIVATE -Wall -Wextra)
endif()