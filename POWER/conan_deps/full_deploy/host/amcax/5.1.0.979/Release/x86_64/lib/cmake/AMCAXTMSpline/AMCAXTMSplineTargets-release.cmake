#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXTMSpline" for configuration "Release"
set_property(TARGET AMCAXTMSpline APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXTMSpline PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXTMSpline.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXTMSpline.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXTMSpline )
list(APPEND _cmake_import_check_files_for_AMCAXTMSpline "${_IMPORT_PREFIX}/lib/Release/AMCAXTMSpline.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXTMSpline.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
