# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# Name project
SET(ProjectName Aqua)
# Set the board used
set(PICO_BOARD pico_w) 

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set any variables required for importing libraries
# Get the FreeRTOS kernel path from the environment variable
if(DEFINED ENV{FREERTOS_KERNEL_PATH})
    set(FREERTOS_KERNEL_PATH $ENV{FREERTOS_KERNEL_PATH})
else()
    message(FATAL_ERROR "Environment variable FREERTOS_KERNEL_PATH not set")
endif()

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/helene/pi/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")


# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
include(lwip_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Define project
project(${ProjectName})

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add subdirectories
add_subdirectory(src)

# if you have anything in "lib" folder then uncomment below - remember to add a CMakeLists.txt
# file to the "lib" directory
# add_subdirectory(lib)

