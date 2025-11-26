########################################
# INFORMATION
########################################
function(print_qt_info)

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

endfunction()
