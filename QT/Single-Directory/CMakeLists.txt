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

########################################
# EXECUTABLE
########################################

# qt_add_library

# wrapper for add_executable, additional logic
qt_add_executable(${CMAKE_PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME}		
PRIVATE    
	main.cpp
	# Wigets needed
    mainwindow.ui
    mainwindow.cpp
PUBLIC
INTERFACE
)

target_link_libraries(${CMAKE_PROJECT_NAME}
PRIVATE
	# Qt6::Core
	# Qt6::Gui
	Qt6::Widgets
PUBLIC
INTERFACE
)


set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON			# Prevent the creation of a console window on Windows
    MACOSX_BUNDLE ON			# Create an application bundle on macOS
)


# information
include(${CMAKE_SOURCE_DIR}/cmake/common/PrintCommonInfo.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/qt/PrintQtInfo.cmake)
print_common_info()
print_qt_info()