if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CONAN_TOOLCHAIN_DIR "${CMAKE_CURRENT_LIST_DIR}/../conan_deps/generators")
if(EXISTS "${CONAN_TOOLCHAIN_DIR}/${CMAKE_BUILD_TYPE}/conan_toolchain.cmake")
    include(${CONAN_TOOLCHAIN_DIR}/${CMAKE_BUILD_TYPE}/conan_toolchain.cmake)
else()
    message(WARNING "The conan_toolchain.cmake is not included!")
endif()


list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/../lib/cmake)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")

find_package(PowerFC REQUIRED)
find_package(SARibbonBar REQUIRED)
find_package(AMCAXCommon REQUIRED)
find_package(AMCAXOCCTIO REQUIRED)
find_package(AMCAXPart REQUIRED)
find_package(AMCAXStep REQUIRED)
find_package(AMCAXRender REQUIRED)
find_package(boost REQUIRED)
find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(SARibbonBar REQUIRED)

add_library(POWER_LIBRARIES INTERFACE)
target_link_libraries(POWER_LIBRARIES INTERFACE 
            AMCAXCommon AMCAXPart AMCAXOCCTIO AMCAXStep 
            AMCAXRender::AMCAXRender 
            PowerFC::Base PowerFC::Logging PowerFC::App PowerFC::Gui PowerFC::Widgets 
            Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets 
            Boost::headers Boost::boost 
            SARibbonBar::SARibbonBar)