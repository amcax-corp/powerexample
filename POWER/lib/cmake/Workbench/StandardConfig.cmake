# StandardConfig.cmake
include("${CMAKE_CURRENT_LIST_DIR}/StandardTargets.cmake")

# 根据配置类型设置库路径
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(Standard_LIBRARY_DIR "${CMAKE_CURRENT_LIST_DIR}/../../Debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(Standard_LIBRARY_DIR "${CMAKE_CURRENT_LIST_DIR}/../../Release")
else()
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
endif()

# 链接时使用正确的库路径
link_directories(${Standard_LIBRARY_DIR})

set(Standard_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../include/Standard" "${CMAKE_CURRENT_LIST_DIR}/../../../include")
include_directories(${Standard_INCLUDE_DIRS})