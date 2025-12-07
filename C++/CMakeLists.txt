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
cmake_minimum_required(VERSION 3.20)		# Minimum version of CMake required

# Setup compiler settings
# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)		# make compiler fail if C standard is not met
set(CMAKE_C_EXTENSIONS ON)				# enable C language extensions
# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)		# make compiler fail if C++ standard is not met
set(CMAKE_CXX_EXTENSIONS ON)			# enable C++ language extensions

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME App)				# project name

# Include toolchain file
#include()

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME} VERSION 1.0 LANGUAGES C CXX)				# add 'RC' for resource files (windows)
message("Build type: " ${CMAKE_BUILD_TYPE})


########################################
# EXECUTABLE
########################################

# add the executable
add_executable(${CMAKE_PROJECT_NAME})

# add subdirectories
add_subdirectory(src)

#include
#include()

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME}
PRIVATE
	main.cpp
PUBLIC
INTERFACE
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME}
PRIVATE
PUBLIC
INTERFACE
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME}
PRIVATE
	-DUNICODE			# define UNICODE for Windows API
	-D_UNICODE
PUBLIC
INTERFACE
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME}
PRIVATE
	include
PUBLIC
INTERFACE
)

# Link directories setup: rarely needed
target_link_directories(${CMAKE_PROJECT_NAME}
PRIVATE
PUBLIC
INTERFACE
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
PRIVATE
PUBLIC
INTERFACE
)

# set_target_properties(${CMAKE_PROJECT_NAME}
# PROPERTIES 
# 	WIN32_EXECUTABLE ON
# )

target_compile_options(${CMAKE_PROJECT_NAME}
PRIVATE	
	# /utf-8			# Set source and execution character sets to UTF-8 (MSVC)
	$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>		# Set source character set to UTF-8 (MSVC)
	$<$<CXX_COMPILER_ID:MSVC>:/execution-charset:.936>		# Set execution character set to gb2312 (MSVC)
PUBLIC
INTERFACE
)

# information
include(${CMAKE_SOURCE_DIR}/My_cmake/common/PrintCommonInfo.cmake)
# print_common_info()