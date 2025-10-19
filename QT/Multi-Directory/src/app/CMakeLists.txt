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


# qt_add_resources(${CMAKE_PROJECT_NAME} "app_images"
#     PREFIX "/"
#     FILES
#         images/copy.png
# )

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

