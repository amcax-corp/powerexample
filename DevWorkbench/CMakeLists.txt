set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${POWER_HOME}/bin/$<CONFIG>/Workbench)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${POWER_HOME}/bin/$<CONFIG>/Workbench)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${POWER_HOME}/lib/$<CONFIG>/Workbench)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE STANDARD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

qt6_add_resources(QRC_FILES ./Resources/icon.qrc)

list(APPEND STANDARD_SOURCES ${QRC_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(DevWorkbench SHARED ${STANDARD_SOURCES})

target_link_libraries(DevWorkbench PRIVATE POWER_LIBRARIES)

 set_target_properties(DevWorkbench PROPERTIES
             COMPILE_FLAGS "/Zi"
             LINK_FLAGS "/DEBUG /PDB:${POWER_HOME}/DevWorkbench.pdb  /OPT:REF /OPT:ICF"
        )