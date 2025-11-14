

# Set package version
set(AMCAXStep_VERSION )

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXStepTargets.cmake")

#get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../.. ABSOLUTE)
get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXStep_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXStep_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXStep_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXStep_RUNTIME_DIR ${_prefix}/bin)
endif()
