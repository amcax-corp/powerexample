

# Set package version
set(AMCAXOCCTIO_VERSION 1.3.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXOCCTIOTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXOCCTIO_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXOCCTIO_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXOCCTIO_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXOCCTIO_RUNTIME_DIR ${_prefix}/bin)
endif()
