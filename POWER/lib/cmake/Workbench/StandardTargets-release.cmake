#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "PowerFC::Standard" for configuration "Release"
set_property(TARGET PowerFC::Standard APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::Standard PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/Standard.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "PowerFC::Base;PowerFC::Logging;PowerFC::App;PowerFC::Gui;PowerFC::Widgets;AMCAXRender::AMCAXRender;Qt6::Core;Qt6::Gui;Qt6::Widgets;Qt6::OpenGL;Qt6::OpenGLWidgets;Qt6::Concurrent;Qt6::Network;Qt6::HttpServer;SARibbonBar::SARibbonBar;AMCAXCommon;AMCAXPart;AMCAXStep;AMCAXOCCTIO;SARibbonBar::SARibbonBar;AMCAXCommon;AMCAXPart;AMCAXStep;AMCAXOCCTIO"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/Workbench/Standard.dll"
  )

list(APPEND _cmake_import_check_targets PowerFC::Standard )
list(APPEND _cmake_import_check_files_for_PowerFC::Standard "${_IMPORT_PREFIX}/lib/Release/Standard.lib" "${_IMPORT_PREFIX}/bin/Release/Workbench/Standard.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
