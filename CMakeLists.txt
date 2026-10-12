cmake_minimum_required(VERSION 3.21)
project(stratosphere CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(portaudio CONFIG REQUIRED)
add_executable(stratosphere src/main.cpp "src/AudioInput.h"  "src/logging/Logging.h")
target_link_libraries(stratosphere PRIVATE portaudio)