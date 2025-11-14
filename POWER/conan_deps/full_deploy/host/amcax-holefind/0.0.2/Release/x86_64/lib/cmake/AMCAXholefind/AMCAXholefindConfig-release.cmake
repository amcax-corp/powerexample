#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXholefind" for configuration "Release"
set_property(TARGET AMCAXholefind APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXholefind PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXholefind.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXholefind.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXholefind )
list(APPEND _cmake_import_check_files_for_AMCAXholefind "${_IMPORT_PREFIX}/lib/Release/AMCAXholefind.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXholefind.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
