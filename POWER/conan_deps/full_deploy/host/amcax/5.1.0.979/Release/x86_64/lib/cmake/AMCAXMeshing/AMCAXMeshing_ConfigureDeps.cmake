# ##############################################################################
#
# What does this script do?
#
# It configures third party dependencies for a target of AMCAX. These third
# party dependencies are shared by others libs or users, but not included in
# AMCAX release package. So, AMCAX uses this script to automatically find those
# dependencies.
#
# How to use this script?
#
# 1. Set AMCAX_CONFIG_TARGET before including this script. The
#    AMCAX_CONFIG_TARGET will be used in target_include_directories and other
#    similar commands.
# 2. Set specific variables for each dependency before including the script. See
#    details in the description of each dependency.
#
# Dependency list:
#
# * AMCAX
# * Boost
# * Eigen
# * TBB
# * phmap
# * gmp
# * mpfr
#
# ##############################################################################

get_target_property(_AMCAX_IS_TARGET_IMPORTED ${AMCAX_CONFIG_TARGET} IMPORTED)
if(_AMCAX_IS_TARGET_IMPORTED)
  set(_AMCAX_TARGET_KEYWORD "INTERFACE")
else()
  set(_AMCAX_TARGET_KEYWORD "PRIVATE")
endif()

# ##############################################################################
# AMCAXKernel
#
# How to use:
#
# * Set AMCAX_CONFIGDEP_AMCAX to ON to configure AMCAX as a dependency.
# * Set AMCAX_DEP_AMCAX_COMPONENTS as a list of components of AMCAXKernel for
#   linking.
# * This script will call find_package to find the components. Users may provide
#   hints for find_package, for example, CMAKE_PREFIX_PATH.
# * If found, the components will be linked to AMCAX_CONFIG_TARGET.
#
# ##############################################################################

if(DEFINED AMCAX_CONFIGDEP_AMCAX AND AMCAX_CONFIGDEP_AMCAX)

  foreach(_COMPONENT ${AMCAX_CONFIGDEP_AMCAX_COMPONENTS})

    set(_COMPONENT_FULL_NAME "AMCAX${_COMPONENT}")

    find_package(${_COMPONENT_FULL_NAME} REQUIRED)

    target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD}
                          ${_COMPONENT_FULL_NAME})

  endforeach()

endif()

# ##############################################################################
# Boost
#
# How to use:
#
# * Set AMCAX_CONFIGDEP_BOOST to ON to configure boost as a dependency.
# * Set AMCAX_CONFIGDEP_BOOST_COMPONENTS to find specified components, e.g.,
#   filesystem.
# * It calls find_package to find boost, users may provide hints to
#   find_package.
# * If boost is found, boost::headers and required components will be linked to
#   AMCAX_CONFIG_TARGET.
#
# ##############################################################################

if(DEFINED AMCAX_CONFIGDEP_BOOST AND AMCAX_CONFIGDEP_BOOST)

  # set options for boost
  set(Boost_DEBUG OFF)
  set(Boost_NO_WARN_NEW_VERSIONS ON)
  set(Boost_USE_STATIC_LIBS ON)

  # At least 1.78
  # if(AMCAXMeshing_EDITION_STANDARD OR AMCAXMeshing_EDITION_INTERNAL)
  #     # At least 1.78
  #   find_package(Boost 1.78.0 REQUIRED
  #     COMPONENTS)
  # elseif(AMCAXMeshing_EDITION_BAMBOO)
  #   if(CMAKE_HOST_WIN32)
  #     set(Boost_ROOT "${BambooDeps}/windows/lib/cmake")
  #   else()
  #     message(FATAL_ERROR "[AMCAX] Unsupported host for Boost: ${CMAKE_HOST_SYSTEM_NAME}")
  #   endif()

    find_package(Boost 1.78.0 REQUIRED ${AMCAX_CONFIGDEP_BOOST_COMPONENTS} NO_MODULE)
  # endif()

  # check if boost is found and report
  if(Boost_FOUND)
    if(AMCAX_VERBOSE OR AMCAX_DEBUG)
      message(STATUS "[AMCAX] Boost include dirs: ${Boost_INCLUDE_DIRS}")
      message(STATUS "[AMCAX] Boost libraries: ${Boost_LIBRARIES}")
    endif()
    target_compile_definitions(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} BOOST_DISABLE_CURRENT_LOCATION)
  else()
    message(FATAL_ERROR "[AMCAX] Can't find Boost.")
  endif()

  # link boost targets
  target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD}
                        Boost::headers)
  foreach(_COMPONENT ${AMCAX_CONFIGDEP_BOOST_COMPONENTS})
    target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD}
                          Boost::${_COMPONENT})
  endforeach()

endif()

# ##############################################################################
# Eigen
#
# How to use:
#
# * Set AMCAX_CONFIGDEP_EIGEN to ON to configure eigen as a dependency.
# * It calls find_package(Eigen3) to find Eigen.
# * Users may provide FindEigen3.cmake with EIGEN3_INCLUDE_DIR or
#   Eigen3Config.cmake.
#
# ##############################################################################

if(DEFINED AMCAX_CONFIGDEP_EIGEN AND AMCAX_CONFIGDEP_EIGEN)
  if(Eigen3_INCLUDE_DIR)
    # include dir
    target_include_directories(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD}
    ${Eigen3_INCLUDE_DIR})
  else()
    # find Eigen3
    find_package(Eigen3 REQUIRED)

    if(Eigen3_FOUND)
      # report
      if(AMCAX_VERBOSE OR AMCAX_DEBUG)
        message(
          STATUS "[AMCAX] Add Eigen as a dependency: ${Eigen3_INCLUDE_DIR}.")
      endif()
      # include dir
      target_include_directories(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD}
                                ${Eigen3_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR})
    else()
      message(FATAL_ERROR "[AMCAX] Can't find Eigen3.")
    endif()

  endif()
endif()

# ##############################################################################
# TBB
#
# How to use:
#
# * Set AMCAX_CONFIGDEP_TBB to ON to configure TBB as a dependency.
#
# * The user need provide target tbb to link it to the current target.
#
#   * The target tbb may be (1) automatically generated by TBB or (2) manually
#     added by the user.
#   * The target tbb is required to have include directory and library as its
#     target properties.
#
# * If target tbb is not provided, this script calls find_package to find tbb.
#   Users may provide hints for find_package.
#
# ##############################################################################

if(DEFINED AMCAX_CONFIGDEP_TBB AND AMCAX_CONFIGDEP_TBB)
  if(TARGET tbb)
    target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} tbb)
    target_compile_definitions(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD}
                                                      TBB_PARALLEL=1)
  else()
    find_package(TBB REQUIRED)
    if(TBB_FOUND)
        if(ENABLE_WASM)
            target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} TBB::tbb)
        else()
            target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} onetbb::onetbb)
        endif()
      target_compile_definitions(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD}
                                                        TBB_PARALLEL=1)
    else()
      message(FATAL_ERROR "[AMCAX] Can't find TBB.")
    endif()
  endif()

  # TBB compatible for different gcc version
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0)
        message("Change the parallel policy to use the sequential version of the parallel policies.")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
            target_compile_definitions(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} PSTL_USE_PARALLEL_POLICIES=0)
        else()
            target_compile_definitions(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} _GLIBCXX_USE_TBB_PAR_BACKEND=0)
        endif()
      endif()
  endif()
endif()

# ##############################################################################
# phmap
#
# How to use:
#
# * Set AMCAX_CONFIGDEP_PHMAP to ON to configure eigen as a dependency.
# * It calls find_package(phmap) to find phmap.
# * Users may provide phmapConfig.cmake.
#
# ##############################################################################

if(DEFINED AMCAX_CONFIGDEP_PHMAP AND AMCAX_CONFIGDEP_PHMAP)
    find_package(phmap REQUIRED)
    if(phmap_FOUND)
      target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} phmap)
    else()
      message(FATAL_ERROR "[AMCAX] Can't find phmap.")
    endif()
endif()

# ##############################################################################
# GMP
#
# How to use:
#
# * Set AMCAX_CONFIGDEP_GMP to ON to configure eigen as a dependency.
# * It calls find_package(GMP NO_MODULE) to find gmp.
# * Users may provide GMPConfig.cmake.
#
# ##############################################################################

if(DEFINED AMCAX_CONFIGDEP_GMP AND AMCAX_CONFIGDEP_GMP)
    find_package(GMP REQUIRED NO_MODULE)
    if(GMP_FOUND)
      target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} GMP)
    else()
      message(FATAL_ERROR "[AMCAX] Can't find GMP.")
    endif()
endif()

# ##############################################################################
# MPFR
#
# How to use:
#
# * Set AMCAX_CONFIGDEP_MPFR to ON to configure eigen as a dependency.
# * It calls find_package(MPFR NO_MODULE) to find mpfr.
# * Users may provide MPFRConfig.cmake.
#
# ##############################################################################
if(DEFINED AMCAX_CONFIGDEP_MPFR AND AMCAX_CONFIGDEP_MPFR)
    find_package(MPFR REQUIRED NO_MODULE)
    if(MPFR_FOUND)
      target_link_libraries(${AMCAX_CONFIG_TARGET} ${_AMCAX_TARGET_KEYWORD} MPFR)
    else()
      message(FATAL_ERROR "[AMCAX] Can't find MPFR.")
    endif()
endif()