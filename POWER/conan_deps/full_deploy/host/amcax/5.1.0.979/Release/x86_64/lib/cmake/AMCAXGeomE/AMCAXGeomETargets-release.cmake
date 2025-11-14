#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXGeomE" for configuration "Release"
set_property(TARGET AMCAXGeomE APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXGeomE PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXGeomE.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXLicense;AMCAXCommon;AMCAXPart"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXGeomE.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXGeomE )
list(APPEND _cmake_import_check_files_for_AMCAXGeomE "${_IMPORT_PREFIX}/lib/Release/AMCAXGeomE.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXGeomE.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
