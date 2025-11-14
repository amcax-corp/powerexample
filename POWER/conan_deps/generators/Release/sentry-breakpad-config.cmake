########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(sentry-breakpad_FIND_QUIETLY)
    set(sentry-breakpad_MESSAGE_MODE VERBOSE)
else()
    set(sentry-breakpad_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/sentry-breakpadTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${sentry-breakpad_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(sentry-breakpad_VERSION_STRING "0.6.5")
set(sentry-breakpad_INCLUDE_DIRS ${sentry-breakpad_INCLUDE_DIRS_RELEASE} )
set(sentry-breakpad_INCLUDE_DIR ${sentry-breakpad_INCLUDE_DIRS_RELEASE} )
set(sentry-breakpad_LIBRARIES ${sentry-breakpad_LIBRARIES_RELEASE} )
set(sentry-breakpad_DEFINITIONS ${sentry-breakpad_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${sentry-breakpad_BUILD_MODULES_PATHS_RELEASE} )
    message(${sentry-breakpad_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


