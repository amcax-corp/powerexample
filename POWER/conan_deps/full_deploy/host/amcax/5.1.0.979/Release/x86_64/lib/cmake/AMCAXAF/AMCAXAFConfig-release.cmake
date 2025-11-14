#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXAF" for configuration "Release"
set_property(TARGET AMCAXAF APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXAF PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXAF.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXPart;AMCAXCommon;AMCAXOCCTIO;AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXAF.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXAF )
list(APPEND _cmake_import_check_files_for_AMCAXAF "${_IMPORT_PREFIX}/lib/Release/AMCAXAF.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXAF.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
