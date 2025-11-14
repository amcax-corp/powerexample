# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/sentry-breakpad-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${sentry-breakpad_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${sentry-breakpad_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET sentry-breakpad::sentry-breakpad)
    add_library(sentry-breakpad::sentry-breakpad INTERFACE IMPORTED)
    message(${sentry-breakpad_MESSAGE_MODE} "Conan: Target declared 'sentry-breakpad::sentry-breakpad'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/sentry-breakpad-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()