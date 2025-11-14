

# Set package version
set(AMCAXGeomE_VERSION 1.0.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXGeomETargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXGeomE_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXGeomE_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXGeomE_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXGeomE_RUNTIME_DIR ${_prefix}/bin)
endif()
