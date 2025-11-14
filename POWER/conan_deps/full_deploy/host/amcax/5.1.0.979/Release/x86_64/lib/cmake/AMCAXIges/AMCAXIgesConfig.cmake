

# Set package version
set(AMCAXIges_VERSION 2.1.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXIgesTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXIges_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXIges_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXIges_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXIges_RUNTIME_DIR ${_prefix}/bin)
endif()

