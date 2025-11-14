#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXStep" for configuration "Release"
set_property(TARGET AMCAXStep APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXStep PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXStep.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXCommon;AMCAXPart;AMCAXAF;AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXStep.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXStep )
list(APPEND _cmake_import_check_files_for_AMCAXStep "${_IMPORT_PREFIX}/lib/Release/AMCAXStep.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXStep.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
