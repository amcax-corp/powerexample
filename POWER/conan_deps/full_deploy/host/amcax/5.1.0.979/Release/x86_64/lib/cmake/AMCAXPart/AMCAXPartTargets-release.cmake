#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXPart" for configuration "Release"
set_property(TARGET AMCAXPart APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXPart PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXPart.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXPart.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXPart )
list(APPEND _cmake_import_check_files_for_AMCAXPart "${_IMPORT_PREFIX}/lib/Release/AMCAXPart.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXPart.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
