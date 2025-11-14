# Set package version
set(AMCAXMeshing_VERSION 1.1.0)

# Configuration for including directories in the package
include("${CMAKE_CURRENT_LIST_DIR}/AMCAXMeshingTargets.cmake")

set(AMCAX_CONFIG_TARGET AMCAXMeshing)

if(NOT DEFINED AMCAX_CONFIGDEP_AMCAX)
  set(AMCAX_CONFIGDEP_AMCAX ON)
endif()
if(NOT DEFINED AMCAX_CONFIGDEP_AMCAX_COMPONENTS)
  set(AMCAX_CONFIGDEP_AMCAX_COMPONENTS Common)
endif()
if(NOT DEFINED AMCAX_CONFIGDEP_EIGEN)
  set(AMCAX_CONFIGDEP_EIGEN OFF)
endif()
if(NOT DEFINED AMCAX_CONFIGDEP_BOOST)
  set(AMCAX_CONFIGDEP_BOOST OFF)
endif()
if(NOT DEFINED AMCAX_CONFIGDEP_TBB)
  set(AMCAX_CONFIGDEP_TBB OFF)
endif()
if(NOT DEFINED AMCAX_CONFIGDEP_PHMAP)
  set(AMCAX_CONFIGDEP_PHMAP OFF)
endif()
if(NOT DEFINED AMCAX_CONFIGDEP_GMP)
  set(AMCAX_CONFIGDEP_GMP OFF)
endif()
if(NOT DEFINED AMCAX_CONFIGDEP_MPFR)
  set(AMCAX_CONFIGDEP_MPFR OFF)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/AMCAXMeshing_ConfigureDeps.cmake")

get_filename_component(_prefix ${CMAKE_CURRENT_LIST_DIR}/../../.. ABSOLUTE)

if(MSVC)
  set(AMCAXMeshing_LIBRARY_DIR ${_prefix}/lib/$<CONFIG>)
  set(AMCAXMeshing_RUNTIME_DIR ${_prefix}/bin/$<CONFIG>)
else()
  set(AMCAXMeshing_LIBRARY_DIR ${_prefix}/lib)
  set(AMCAXMeshing_RUNTIME_DIR ${_prefix}/bin)
endif()
