#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXGCS" for configuration "Release"
set_property(TARGET AMCAXGCS APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXGCS PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXGCS.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXGCS.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXGCS )
list(APPEND _cmake_import_check_files_for_AMCAXGCS "${_IMPORT_PREFIX}/lib/Release/AMCAXGCS.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXGCS.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
