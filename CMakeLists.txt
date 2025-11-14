# cmake版本需求
cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# POWER库所在路径，路径中尽量避免使用中文
set(POWER_HOME "${CMAKE_CURRENT_SOURCE_DIR}/POWER")


INCLUDE("${POWER_HOME}/toolchain/powerfc_toolchain.cmake")

# C++版本需求
set(CMAKE_CXX_STANDARD 20)

#指定下一级目录为子项目
add_subdirectory(DevWorkbench)