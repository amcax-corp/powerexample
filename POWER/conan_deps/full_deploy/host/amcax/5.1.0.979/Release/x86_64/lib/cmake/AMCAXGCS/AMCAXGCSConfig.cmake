

# Set package version
set(AMCAXGCS_VERSION 1.0.1.1)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXGCSTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXGCS_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXGCS_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXGCS_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXGCS_RUNTIME_DIR ${_prefix}/bin)
endif()
