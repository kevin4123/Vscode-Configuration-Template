########################################
# mkdir build
# cd build
########################################
# cmake -S . -B build -G "Ninja"			-DCMAKE_BUILD_TYPE=Release | -DCMAKE_BUILD_TYPE=Debug
# cmake --build build			|			ninja -v: verbose for link info 
#+++++++++++++++++++++++++++++++++++++++
# cmake -S . -B build -G "MinGW Makefiles"
# cmake --build build			|			mingw32-make VERBOSE=1
########################################
cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME App)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
	${CMAKE_SOURCE_DIR}/Drivers/SYSTEM/sys/sys.c
	${CMAKE_SOURCE_DIR}/Drivers/SYSTEM/usart/usart.c
	${CMAKE_SOURCE_DIR}/Drivers/SYSTEM/delay/delay.c

	${CMAKE_SOURCE_DIR}/Drivers/BSP/LED/led.c
	${CMAKE_SOURCE_DIR}/Drivers/BSP/BEEP/beep.c
	${CMAKE_SOURCE_DIR}/Drivers/BSP/KEY/key.c
	${CMAKE_SOURCE_DIR}/Drivers/BSP/EXTI/exti.c
	${CMAKE_SOURCE_DIR}/Drivers/BSP/WDG/wdg.c
	${CMAKE_SOURCE_DIR}/Drivers/BSP/TIMER/btim.c
	${CMAKE_SOURCE_DIR}/Drivers/BSP/LCD/lcd.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
	${CMAKE_SOURCE_DIR}/Drivers
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

# information
include("My_cmake/embedded/PrintEmbeddedInfo.cmake")
include("My_cmake/common/PrintCommonInfo.cmake")
# print_common_info()
print_embedded_info()
