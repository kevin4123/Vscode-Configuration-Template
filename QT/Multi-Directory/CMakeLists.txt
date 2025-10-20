########################################
# mkdir build
# cd build
########################################
# cmake -S .. -B . -G "Ninja"
# cmake --build .			|			ninja -v
#+++++++++++++++++++++++++++++++++++++++
# cmake -S .. -B . -G "MinGW Makefiles"
# cmake --build .			|			mingw32-make VERBOSE=1
########################################
cmake_minimum_required(VERSION 3.16)

# Set the project name
set(CMAKE_PROJECT_NAME QTApp)

project(${CMAKE_PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)       # enable automatic UI file generation
set(CMAKE_AUTOMOC ON)		# enable automatic MOC file generation
set(CMAKE_AUTORCC ON)		# enable automatic RCC file generation, enother way is 'qt_add_resources' 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set Qt6 path
set(CMAKE_PREFIX_PATH "D:\\Qt\\6.9.2\\msvc2022_64\\lib\\cmake\\Qt6")  	
# if you add high level components,low level components automatically added
# components: Core, Gui, Widgets	
find_package(Qt6 REQUIRED COMPONENTS Widgets) 								

qt_standard_project_setup()						# enable qt standard project setup

add_subdirectory(src/app)


########################################
# INFORMATION
########################################
message("")

message(STATUS "========== QT INFORMATION ==========")
message(STATUS "Qt Version Major: ${QT_VERSION_MAJOR}")
message(STATUS "Qt Version Minor: ${QT_VERSION_MINOR}")
message(STATUS "Qt Version Patch: ${QT_VERSION_PATCH}")
message(STATUS "Qt Version: ${QT_VERSION}")
message(STATUS "Qt Package Prefix Path: ${Qt6_DIR}")
message(STATUS "Qt CMake Modules Path: ${Qt6Core_DIR}")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

message(STATUS "")

message(STATUS "========== QT AUTOMOC / AUTOUIC / AUTORCC ==========")
get_target_property(AUTOMOC ${CMAKE_PROJECT_NAME} AUTOMOC)
get_target_property(AUTOUIC ${CMAKE_PROJECT_NAME} AUTOUIC)
get_target_property(AUTORCC ${CMAKE_PROJECT_NAME} AUTORCC)
message(STATUS "AUTOMOC: ${AUTOMOC}")
message(STATUS "AUTOUIC: ${AUTOUIC}")
message(STATUS "AUTORCC: ${AUTORCC}")

# UIC 搜索路径（Qt Designer 的 .ui 文件目录）
message(STATUS "AUTOUIC_SEARCH_PATHS: ${AUTOUIC_SEARCH_PATHS}")

# MOC 宏名（用于判断哪些类触发 moc 生成）
message(STATUS "MOC macro names: ${CMAKE_AUTOMOC_MACRO_NAMES}")

# 自动生成目录
message(STATUS "CMAKE_AUTOMOC_MOC_OPTIONS: ${CMAKE_AUTOMOC_MOC_OPTIONS}")
message(STATUS "CMAKE_AUTORCC_OPTIONS: ${CMAKE_AUTORCC_OPTIONS}")
message(STATUS "CMAKE_AUTOUIC_OPTIONS: ${CMAKE_AUTOUIC_OPTIONS}")

message(STATUS "")

message(STATUS "========== QT MODULES ==========")
# 检查已找到的 Qt 模块
foreach(module Core Gui Widgets Network Quick Multimedia)
    if(TARGET Qt6::${module})
        message(STATUS "Found Qt module: Qt6::${module}")
        get_target_property(_inc Qt6::${module} INTERFACE_INCLUDE_DIRECTORIES)
        get_target_property(_lib Qt6::${module} LOCATION)
        message(STATUS "    include dirs: ${_inc}")
        message(STATUS "    location: ${_lib}")
    endif()
endforeach()

message(STATUS "")

message(STATUS "========== QT PLUGINS ==========")
message(STATUS "QT_PLUGIN_PATH: ${QT_PLUGIN_PATH}")
message(STATUS "QT_QML_DIR: ${QT_QML_DIR}")
message(STATUS "QT_QML_OUTPUT_DIRECTORY: ${QT_QML_OUTPUT_DIRECTORY}")
message(STATUS "QT_QML_IMPORT_PATH: ${QT_QML_IMPORT_PATH}")

message(STATUS "")

message(STATUS "========== GLOBAL INFORMATION ==========")
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "Project version: ${PROJECT_VERSION}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "System version: ${CMAKE_SYSTEM_VERSION}")
message(STATUS "Host system: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

message(STATUS "")

message(STATUS "========== COMPILER INFORMATION ==========")
message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C compiler ID: ${CMAKE_C_COMPILER_ID}")
message(STATUS "C compiler version: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C standard: ${CMAKE_C_STANDARD}")
message(STATUS "C standard required: ${CMAKE_C_STANDARD_REQUIRED}")

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "C++ standard required: ${CMAKE_CXX_STANDARD_REQUIRED}")

message(STATUS "CMAKE_CXX_EXTENSIONS: ${CMAKE_CXX_EXTENSIONS}")
message(STATUS "CMAKE_C_EXTENSIONS: ${CMAKE_C_EXTENSIONS}")

message(STATUS "")

message(STATUS "========== BUILD FLAGS ==========")
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "CMAKE_MODULE_LINKER_FLAGS: ${CMAKE_MODULE_LINKER_FLAGS}")
message(STATUS "CMAKE_VERBOSE_MAKEFILE: ${CMAKE_VERBOSE_MAKEFILE}")

message(STATUS "")

message(STATUS "========== TARGET INFORMATION ==========")
get_target_property(TARGET_TYPE ${CMAKE_PROJECT_NAME} TYPE)
get_target_property(SOURCES ${CMAKE_PROJECT_NAME} SOURCES)
get_target_property(INCLUDE_DIRS ${CMAKE_PROJECT_NAME} INCLUDE_DIRECTORIES)
get_target_property(LINK_DIRS ${CMAKE_PROJECT_NAME} LINK_DIRECTORIES)
get_target_property(LINK_LIBS ${CMAKE_PROJECT_NAME} LINK_LIBRARIES)
get_target_property(COMPILE_DEFS ${CMAKE_PROJECT_NAME} COMPILE_DEFINITIONS)
get_target_property(COMPILE_OPTIONS ${CMAKE_PROJECT_NAME} COMPILE_OPTIONS)
get_target_property(LINK_FLAGS ${CMAKE_PROJECT_NAME} LINK_FLAGS)
get_target_property(BINARY_DIR ${CMAKE_PROJECT_NAME} BINARY_DIR)
get_target_property(SOURCE_DIR ${CMAKE_PROJECT_NAME} SOURCE_DIR)
get_target_property(POSITION_INDEPENDENT ${CMAKE_PROJECT_NAME} POSITION_INDEPENDENT_CODE)
get_target_property(OUTPUT_NAME ${CMAKE_PROJECT_NAME} OUTPUT_NAME)
get_target_property(RUNTIME_OUTPUT_DIR ${CMAKE_PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
get_target_property(ARCHIVE_OUTPUT_DIR ${CMAKE_PROJECT_NAME} ARCHIVE_OUTPUT_DIRECTORY)
get_target_property(LIBRARY_OUTPUT_DIR ${CMAKE_PROJECT_NAME} LIBRARY_OUTPUT_DIRECTORY)

message(STATUS "Target type: ${TARGET_TYPE}")
message(STATUS "Source files: ${SOURCES}")
message(STATUS "Include dirs: ${INCLUDE_DIRS}")
message(STATUS "Link dirs: ${LINK_DIRS}")
message(STATUS "Linked libs: ${LINK_LIBS}")
message(STATUS "Compile defs: ${COMPILE_DEFS}")
message(STATUS "Compile options: ${COMPILE_OPTIONS}")
message(STATUS "Link flags: ${LINK_FLAGS}")
message(STATUS "Position independent: ${POSITION_INDEPENDENT}")
message(STATUS "Output name: ${OUTPUT_NAME}")
message(STATUS "Runtime output dir: ${RUNTIME_OUTPUT_DIR}")
message(STATUS "Archive output dir: ${ARCHIVE_OUTPUT_DIR}")
message(STATUS "Library output dir: ${LIBRARY_OUTPUT_DIR}")

message(STATUS "")

message(STATUS "========== ENVIRONMENT & CACHE ==========")
message(STATUS "CMAKE_COMMAND: ${CMAKE_COMMAND}")
message(STATUS "CMAKE_MAKE_PROGRAM: ${CMAKE_MAKE_PROGRAM}")
message(STATUS "CMAKE_BUILD_TOOL: ${CMAKE_BUILD_TOOL}")
message(STATUS "CMAKE_AR: ${CMAKE_AR}")
message(STATUS "CMAKE_RANLIB: ${CMAKE_RANLIB}")
message(STATUS "CMAKE_NM: ${CMAKE_NM}")
message(STATUS "CMAKE_STRIP: ${CMAKE_STRIP}")
message(STATUS "CMAKE_OBJCOPY: ${CMAKE_OBJCOPY}")
message(STATUS "CMAKE_OBJDUMP: ${CMAKE_OBJDUMP}")
message(STATUS "CMAKE_LINKER: ${CMAKE_LINKER}")

# Example of reading environment variable
# message(STATUS "PATH: $ENV{PATH}")
# message(STATUS "CMAKE_CACHEFILE_DIR: ${CMAKE_CACHEFILE_DIR}")

message(STATUS "")

# WARNING: very verbose, use only for debugging
# message(STATUS "========== ALL VARIABLES ==========")
# get_cmake_property(_vars VARIABLES)
# foreach(_var ${_vars})
#     message(STATUS "${_var} = ${${_var}}")
# endforeach()

message(STATUS "")

# WARNING: also very verbose
# message(STATUS "========== ALL TARGET PROPERTIES ==========")
# get_all_properties(_props ${CMAKE_PROJECT_NAME})
# foreach(_p ${_props})
#     get_target_property(_val ${CMAKE_PROJECT_NAME} ${_p})
#     if(_val)
#         message(STATUS "${_p} = ${_val}")
#     endif()
# endforeach()

message(STATUS "")
# Enable debug output of target properties
# set(CMAKE_DEBUG_TARGET_PROPERTIES 
#   INCLUDE_DIRECTORIES 
#   INTERFACE_INCLUDE_DIRECTORIES
#   LINK_OPTIONS
# )