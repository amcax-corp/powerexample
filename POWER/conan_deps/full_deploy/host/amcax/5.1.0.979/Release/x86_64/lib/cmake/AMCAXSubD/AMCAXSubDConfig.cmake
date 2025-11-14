

# Set package version
set(AMCAXSubD_VERSION 2.1.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXSubDTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXSubD_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXSubD_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXSubD_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXSubD_RUNTIME_DIR ${_prefix}/bin)
endif()
