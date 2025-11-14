#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXCommon" for configuration "Release"
set_property(TARGET AMCAXCommon APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXCommon PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXCommon.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXCommon.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXCommon )
list(APPEND _cmake_import_check_files_for_AMCAXCommon "${_IMPORT_PREFIX}/lib/Release/AMCAXCommon.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXCommon.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
