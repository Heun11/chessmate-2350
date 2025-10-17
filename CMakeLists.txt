cmake_minimum_required(VERSION 3.13)

# Import the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Project name
project(chessmate C CXX ASM)

# Initialize the SDK
pico_sdk_init()

# Collect all source files from source/
file(GLOB_RECURSE SOURCES "source/*.c")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Include the headers from source/
target_include_directories(${PROJECT_NAME} PRIVATE source)

# Link standard Pico libraries
target_link_libraries(${PROJECT_NAME} 
  pico_stdlib
)

# Create extra output formats (.uf2, .elf, .bin)
pico_add_extra_outputs(${PROJECT_NAME})

