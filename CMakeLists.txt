cmake_minimum_required(VERSION 3.10)

project(RobotDrawing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(robot
    src/main.cpp
    src/robot_map.cpp
    src/command.cpp
)

target_include_directories(robot PRIVATE include)

if(MSVC)
    target_compile_options(robot PRIVATE /W4 /EHsc)
else()
    target_compile_options(robot PRIVATE -Wall -Wextra)
endif()
