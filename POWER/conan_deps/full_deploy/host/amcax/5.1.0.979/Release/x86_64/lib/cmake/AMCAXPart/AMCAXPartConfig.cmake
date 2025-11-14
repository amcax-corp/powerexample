

# Set package version
set(AMCAXPart_VERSION 2.3.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXPartTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXPart_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXPart_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXPart_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXPart_RUNTIME_DIR ${_prefix}/bin)
endif()
