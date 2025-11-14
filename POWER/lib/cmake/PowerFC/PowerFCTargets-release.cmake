#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "PowerFC::Logging" for configuration "Release"
set_property(TARGET PowerFC::Logging APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::Logging PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/Logging.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/Logging.dll"
  )

list(APPEND _cmake_import_check_targets PowerFC::Logging )
list(APPEND _cmake_import_check_files_for_PowerFC::Logging "${_IMPORT_PREFIX}/lib/Release/Logging.lib" "${_IMPORT_PREFIX}/bin/Release/Logging.dll" )

# Import target "PowerFC::Base" for configuration "Release"
set_property(TARGET PowerFC::Base APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::Base PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/Base.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "PowerFC::Logging;Qt6::Core"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/Base.dll"
  )

list(APPEND _cmake_import_check_targets PowerFC::Base )
list(APPEND _cmake_import_check_files_for_PowerFC::Base "${_IMPORT_PREFIX}/lib/Release/Base.lib" "${_IMPORT_PREFIX}/bin/Release/Base.dll" )

# Import target "PowerFC::App" for configuration "Release"
set_property(TARGET PowerFC::App APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::App PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/App.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "PowerFC::Base;PowerFC::Logging;AMCAXCommon;AMCAXPart;AMCAXStep;AMCAXSubD;AMCAXTMSpline;AMCAXOCCTIO;AMCAXGCS;Qt6::Core"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/App.dll"
  )

list(APPEND _cmake_import_check_targets PowerFC::App )
list(APPEND _cmake_import_check_files_for_PowerFC::App "${_IMPORT_PREFIX}/lib/Release/App.lib" "${_IMPORT_PREFIX}/bin/Release/App.dll" )

# Import target "PowerFC::Gui" for configuration "Release"
set_property(TARGET PowerFC::Gui APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::Gui PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/Gui.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "PowerFC::Base;PowerFC::Logging;PowerFC::App;AMCAXRender::AMCAXRender;Qt6::Core;Qt6::Gui;Qt6::Widgets;Qt6::OpenGL;Qt6::OpenGLWidgets;Qt6::Concurrent;Qt6::Network;Qt6::HttpServer;Qt6::Designer;Qt6::PrintSupport;SARibbonBar::SARibbonBar;AMCAXCommon;AMCAXPart;AMCAXStep;AMCAXSubD;AMCAXTMSpline;AMCAXOCCTIO;AMCAXGCS"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/Gui.dll"
  )

list(APPEND _cmake_import_check_targets PowerFC::Gui )
list(APPEND _cmake_import_check_files_for_PowerFC::Gui "${_IMPORT_PREFIX}/lib/Release/Gui.lib" "${_IMPORT_PREFIX}/bin/Release/Gui.dll" )

# Import target "PowerFC::PowerLauncher" for configuration "Release"
set_property(TARGET PowerFC::PowerLauncher APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::PowerLauncher PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/PowerLauncher.exe"
  )

list(APPEND _cmake_import_check_targets PowerFC::PowerLauncher )
list(APPEND _cmake_import_check_files_for_PowerFC::PowerLauncher "${_IMPORT_PREFIX}/bin/Release/PowerLauncher.exe" )

# Import target "PowerFC::PowerFCMain" for configuration "Release"
set_property(TARGET PowerFC::PowerFCMain APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::PowerFCMain PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/PowerFCMain.exe"
  )

list(APPEND _cmake_import_check_targets PowerFC::PowerFCMain )
list(APPEND _cmake_import_check_files_for_PowerFC::PowerFCMain "${_IMPORT_PREFIX}/bin/Release/PowerFCMain.exe" )

# Import target "PowerFC::Widgets" for configuration "Release"
set_property(TARGET PowerFC::Widgets APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(PowerFC::Widgets PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/Widgets.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "Qt6::Widgets;Qt6::Designer;PowerFC::Gui;PowerFC::App;PowerFC::Base;AMCAXCommon;AMCAXPart;AMCAXStep;AMCAXOCCTIO;SARibbonBar::SARibbonBar;AMCAXRender::AMCAXRender"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/Widgets.dll"
  )

list(APPEND _cmake_import_check_targets PowerFC::Widgets )
list(APPEND _cmake_import_check_files_for_PowerFC::Widgets "${_IMPORT_PREFIX}/lib/Release/Widgets.lib" "${_IMPORT_PREFIX}/bin/Release/Widgets.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
