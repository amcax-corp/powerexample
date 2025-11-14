# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()
message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()

########## 'user_toolchain' block #############
# Include one or more CMake user toolchain from tools.cmake.cmaketoolchain:user_toolchain



########## 'generic_system' block #############
# Definition of system, platform and toolset





########## 'compilers' block #############



########## 'libcxx' block #############
# Definition of libcxx from 'compiler.libcxx' setting, defining the
# right CXX_FLAGS for that libcxx



########## 'vs_runtime' block #############
# Definition of VS runtime CMAKE_MSVC_RUNTIME_LIBRARY, from settings build_type,
# compiler.runtime, compiler.runtime_type

cmake_policy(GET CMP0091 POLICY_CMP0091)
if(NOT "${POLICY_CMP0091}" STREQUAL NEW)
    message(FATAL_ERROR "The CMake policy CMP0091 must be NEW, but is '${POLICY_CMP0091}'")
endif()
message(STATUS "Conan toolchain: Setting CMAKE_MSVC_RUNTIME_LIBRARY=$<$<CONFIG:Release>:MultiThreadedDLL>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Release>:MultiThreadedDLL>")


########## 'vs_debugger_environment' block #############
# Definition of CMAKE_VS_DEBUGGER_ENVIRONMENT from "bindirs" folders of dependencies
# for execution of applications with shared libraries within the VS IDE

set(CMAKE_VS_DEBUGGER_ENVIRONMENT "PATH=$<$<CONFIG:Release>:${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/boost/1.78.0/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/bzip2/1.0.8/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/saribbonbar/2.3.0/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/catch2/3.5.3/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/zlib/1.3.1/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/sentry-breakpad/0.6.5/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-render/1.4.0.637/Release/x86_64/bin/Release;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/onetbb/2021.10.0/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/hwloc/2.9.3/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-holefind/0.0.2/Release/x86_64/bin/Release;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/bin;${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/bin/Release>;%PATH%")


########## 'cppstd' block #############
# Define the C++ and C standards from 'compiler.cppstd' and 'compiler.cstd'

message(STATUS "Conan toolchain: C++ Standard 17 with extensions OFF")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


########## 'parallel' block #############
# Define VS paralell build /MP flags

string(APPEND CONAN_CXX_FLAGS " /MP2")
string(APPEND CONAN_C_FLAGS " /MP2")


########## 'extra_flags' block #############
# Include extra C++, C and linker flags from configuration tools.build:<type>flags
# and from CMakeToolchain.extra_<type>_flags

# Conan conf flags start: Release
# Conan conf flags end


########## 'cmake_flags_init' block #############
# Define CMAKE_<XXX>_FLAGS from CONAN_<XXX>_FLAGS

foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


########## 'extra_variables' block #############
# Definition of extra CMake variables from tools.cmake.cmaketoolchain:extra_variables



########## 'try_compile' block #############
# Blocks after this one will not be added when running CMake try/checks

get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()


########## 'find_paths' block #############
# Define paths to find packages, programs, libraries, etc.

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/saribbonbar/2.3.0/Release/x86_64/lib/cmake/SARibbonBar" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/catch2/3.5.3/Release/x86_64/lib/cmake/Catch2" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-render/1.4.0.637/Release/x86_64/lib/cmake" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-holefind/0.0.2/Release/x86_64/lib/cmake" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXTMSpline" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXSubD" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXStep" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXPart" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXOCCTIO" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXNextMesh" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXMeshing" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXIges" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXGeomE" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXGCS" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXCommon" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXAF")
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The explicitly defined "builddirs" of "host" context dependencies must be in PREFIX_PATH
list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/saribbonbar/2.3.0/Release/x86_64/lib/cmake/SARibbonBar" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/catch2/3.5.3/Release/x86_64/lib/cmake/Catch2" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-render/1.4.0.637/Release/x86_64/lib/cmake" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-holefind/0.0.2/Release/x86_64/lib/cmake" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXTMSpline" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXSubD" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXStep" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXPart" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXOCCTIO" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXNextMesh" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXMeshing" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXIges" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXGeomE" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXGCS" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXCommon" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib/cmake/AMCAXAF")
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/boost/1.78.0/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/bzip2/1.0.8/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/saribbonbar/2.3.0/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/catch2/3.5.3/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/zlib/1.3.1/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/sentry-breakpad/0.6.5/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-render/1.4.0.637/Release/x86_64/lib/Release" "lib" "lib" "lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/onetbb/2021.10.0/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/hwloc/2.9.3/Release/x86_64/lib" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-holefind/0.0.2/Release/x86_64/lib/Release" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/lib")
list(PREPEND CMAKE_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/eigen/3.4.0/include/eigen3" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/boost/1.78.0/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/bzip2/1.0.8/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/saribbonbar/2.3.0/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/catch2/3.5.3/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/zlib/1.3.1/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/sentry-breakpad/0.6.5/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/sentry-breakpad/0.6.5/Release/x86_64/include/breakpad" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-render/1.4.0.637/Release/x86_64/include" "include" "include" "include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/onetbb/2021.10.0/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/hwloc/2.9.3/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax-holefind/0.0.2/Release/x86_64/include" "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/amcax/5.1.0.979/Release/x86_64/include")
set(CONAN_RUNTIME_LIB_DIRS "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/boost/1.78.0/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/bzip2/1.0.8/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/saribbonbar/2.3.0/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/catch2/3.5.3/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/zlib/1.3.1/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/sentry-breakpad/0.6.5/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/amcax-render/1.4.0.637/Release/x86_64/bin/Release>" "$<$<CONFIG:Release>:bin>" "$<$<CONFIG:Release>:bin>" "$<$<CONFIG:Release>:bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/onetbb/2021.10.0/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/hwloc/2.9.3/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/amcax-holefind/0.0.2/Release/x86_64/bin/Release>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/amcax/5.1.0.979/Release/x86_64/bin>" "$<$<CONFIG:Release>:C:/Users/jenkins/workspace/Power-platform_dev/conan_deps/full_deploy/host/amcax/5.1.0.979/Release/x86_64/bin/Release>" )



########## 'pkg_config' block #############
# Define pkg-config from 'tools.gnu:pkg_config' executable and paths

if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()


########## 'rpath' block #############
# Defining CMAKE_SKIP_RPATH



########## 'output_dirs' block #############
# Definition of CMAKE_INSTALL_XXX folders

set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_SBINDIR "bin")
set(CMAKE_INSTALL_LIBEXECDIR "bin")
set(CMAKE_INSTALL_LIBDIR "lib")
set(CMAKE_INSTALL_INCLUDEDIR "include")
set(CMAKE_INSTALL_OLDINCLUDEDIR "include")


########## 'variables' block #############
# Definition of CMake variables from CMakeToolchain.variables values

# Variables
# Variables  per configuration



########## 'preprocessor' block #############
# Preprocessor definitions from CMakeToolchain.preprocessor_definitions values

# Preprocessor definitions per configuration



if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()
