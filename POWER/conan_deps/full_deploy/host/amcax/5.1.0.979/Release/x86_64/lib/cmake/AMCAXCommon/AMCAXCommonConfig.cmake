

# Set package version
set(AMCAXCommon_VERSION 1.4.1)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXCommonTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXCommon_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXCommon_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXCommon_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXCommon_RUNTIME_DIR ${_prefix}/bin)
endif()
