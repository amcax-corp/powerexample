#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AMCAXOCCTIO" for configuration "Release"
set_property(TARGET AMCAXOCCTIO APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(AMCAXOCCTIO PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Release/AMCAXOCCTIO.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "AMCAXLicense"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Release/AMCAXOCCTIO.dll"
  )

list(APPEND _cmake_import_check_targets AMCAXOCCTIO )
list(APPEND _cmake_import_check_files_for_AMCAXOCCTIO "${_IMPORT_PREFIX}/lib/Release/AMCAXOCCTIO.lib" "${_IMPORT_PREFIX}/bin/Release/AMCAXOCCTIO.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
