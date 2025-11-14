#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXNextMesh" for configuration "Release"
set_property(TARGET AMCAXNextMesh APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXNextMesh PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXNextMesh.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXCommon;AMCAXPart;AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXNextMesh.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXNextMesh )
list(APPEND _cmake_import_check_files_for_AMCAXNextMesh "${_IMPORT_PREFIX}/lib/Release/AMCAXNextMesh.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXNextMesh.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
