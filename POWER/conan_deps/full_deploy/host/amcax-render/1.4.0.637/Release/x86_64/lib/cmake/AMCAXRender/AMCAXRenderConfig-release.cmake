#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXRender::AMCAXRender" for configuration "Release"
set_property(TARGET AMCAXRender::AMCAXRender APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXRender::AMCAXRender PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXRender.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXCommon;AMCAXPart;AMCAXStep;AMCAXPm::AMCAXPm"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXRender.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXRender::AMCAXRender )
list(APPEND _cmake_import_check_files_for_AMCAXRender::AMCAXRender "${_IMPORT_PREFIX}/lib/Release/AMCAXRender.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXRender.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
