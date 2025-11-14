

# Set package version
set(AMCAXTMSpline_VERSION 1.3.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXTMSplineTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXTMSpline_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXTMSpline_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXTMSpline_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXTMSpline_RUNTIME_DIR ${_prefix}/bin)
endif()
