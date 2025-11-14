#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXSubD" for configuration "Release"
set_property(TARGET AMCAXSubD APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXSubD PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXSubD.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXSubD.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXSubD )
list(APPEND _cmake_import_check_files_for_AMCAXSubD "${_IMPORT_PREFIX}/lib/Release/AMCAXSubD.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXSubD.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
