

# Set package version
set(AMCAXNextMesh_VERSION 1.5.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXNextMeshTargets.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXNextMesh_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXNextMesh_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXNextMesh_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXNextMesh_RUNTIME_DIR ${_prefix}/bin)
endif()
