cmake_minimum_required(VERSION 3.21)
project(staticcaster CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(portaudio CONFIG REQUIRED)
add_executable(staticcaster src/main.cpp "src/IO/AudioInput.h"  "src/logging/Logging.h" "src/IO/AudioContext.cpp" "src/IO/AudioContext.h" "src/utils/ErrorHandling.h")
target_link_libraries(staticcaster PRIVATE portaudio)