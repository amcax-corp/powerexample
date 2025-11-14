#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXMeshing" for configuration "Release"
set_property(TARGET AMCAXMeshing APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXMeshing PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXMeshing.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXCommon;GMP;MPFR;AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXMeshing.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXMeshing )
list(APPEND _cmake_import_check_files_for_AMCAXMeshing "${_IMPORT_PREFIX}/lib/Release/AMCAXMeshing.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXMeshing.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
