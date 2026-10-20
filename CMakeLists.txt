cmake_minimum_required(VERSION 3.21)
project(staticcaster CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(portaudio CONFIG REQUIRED)

add_executable(staticcaster
    src/main.cpp
    "src/audio/Stream.cpp"
    "src/audio/Context.cpp"
    src/utils/Logging.cpp
    src/utils/Errors.cpp
 "src/utils/Types.h" "src/utils/Devices.cpp" "src/utils/Devices.h" "src/utils/CLIParser.cpp" "src/utils/CLIParser.h")

target_include_directories(staticcaster PRIVATE src)
target_link_libraries(staticcaster PRIVATE portaudio)