#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXIges" for configuration "Release"
set_property(TARGET AMCAXIges APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXIges PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXIges.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXCommon;AMCAXPart;AMCAXOCCTIO;AMCAXAF;AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXIges.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXIges )
list(APPEND _cmake_import_check_files_for_AMCAXIges "${_IMPORT_PREFIX}/lib/Release/AMCAXIges.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXIges.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
