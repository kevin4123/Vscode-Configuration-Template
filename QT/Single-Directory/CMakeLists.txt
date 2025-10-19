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


########################################
# INFORMATION | DEBUG
########################################
get_target_property(AUTORCC ${CMAKE_PROJECT_NAME} AUTORCC)
message(STATUS "AUTORCC:${AUTORCC}")								# show autorcc property
get_target_property(AUTOUIC ${CMAKE_PROJECT_NAME} AUTOUIC)						
message(STATUS "AUTOUIC:${AUTOUIC}")								# show autouic property
get_target_property(AUTOMOC ${CMAKE_PROJECT_NAME} AUTOMOC)						
message(STATUS "AUTOMOC:${AUTOMOC}")								# show automoc property
message(STATUS "MOC MACROS:${CMAKE_AUTOMOC_MACRO_NAMES}")			# show all macro names
message(STATUS "QT version:${QT_VERSION_MAJOR}")					# show qt version	
message(STATUS ${AUTOUIC_SEARCH_PATHS})								# show autouic search paths
get_target_property(SOURCES ${CMAKE_PROJECT_NAME} SOURCES)			
message(STATUS "SOURCES:${SOURCES}")								# show all sources
get_target_property(HEADERS ${CMAKE_PROJECT_NAME} HEADERS)			
message(STATUS "HEADERS:${HEADERS}")								# show all headers
get_target_property(WIN32_EXECUTABLE ${CMAKE_PROJECT_NAME} WIN32_EXECUTABLE)
message(STATUS "WIN32_EXECUTABLE:${WIN32_EXECUTABLE}")				# show win32 executable
get_target_property(MACOSX_BUNDLE ${CMAKE_PROJECT_NAME} MACOSX_BUNDLE)
message(STATUS "MACOSX_BUNDLE:${MACOSX_BUNDLE}")					# show macosx bundle
