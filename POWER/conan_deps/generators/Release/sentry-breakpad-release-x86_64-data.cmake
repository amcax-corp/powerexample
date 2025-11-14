########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(sentry-breakpad_COMPONENT_NAMES "")
if(DEFINED sentry-breakpad_FIND_DEPENDENCY_NAMES)
  list(APPEND sentry-breakpad_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES sentry-breakpad_FIND_DEPENDENCY_NAMES)
else()
  set(sentry-breakpad_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(sentry-breakpad_PACKAGE_FOLDER_RELEASE "${CMAKE_CURRENT_LIST_DIR}/../../full_deploy/host/sentry-breakpad/0.6.5/Release/x86_64")
set(sentry-breakpad_BUILD_MODULES_PATHS_RELEASE )


set(sentry-breakpad_INCLUDE_DIRS_RELEASE "${sentry-breakpad_PACKAGE_FOLDER_RELEASE}/include"
			"${sentry-breakpad_PACKAGE_FOLDER_RELEASE}/include/breakpad")
set(sentry-breakpad_RES_DIRS_RELEASE )
set(sentry-breakpad_DEFINITIONS_RELEASE )
set(sentry-breakpad_SHARED_LINK_FLAGS_RELEASE )
set(sentry-breakpad_EXE_LINK_FLAGS_RELEASE )
set(sentry-breakpad_OBJECTS_RELEASE )
set(sentry-breakpad_COMPILE_DEFINITIONS_RELEASE )
set(sentry-breakpad_COMPILE_OPTIONS_C_RELEASE )
set(sentry-breakpad_COMPILE_OPTIONS_CXX_RELEASE )
set(sentry-breakpad_LIB_DIRS_RELEASE "${sentry-breakpad_PACKAGE_FOLDER_RELEASE}/lib")
set(sentry-breakpad_BIN_DIRS_RELEASE )
set(sentry-breakpad_LIBRARY_TYPE_RELEASE STATIC)
set(sentry-breakpad_IS_HOST_WINDOWS_RELEASE 1)
set(sentry-breakpad_LIBS_RELEASE breakpad_client)
set(sentry-breakpad_SYSTEM_LIBS_RELEASE )
set(sentry-breakpad_FRAMEWORK_DIRS_RELEASE )
set(sentry-breakpad_FRAMEWORKS_RELEASE )
set(sentry-breakpad_BUILD_DIRS_RELEASE )
set(sentry-breakpad_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(sentry-breakpad_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${sentry-breakpad_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${sentry-breakpad_COMPILE_OPTIONS_C_RELEASE}>")
set(sentry-breakpad_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${sentry-breakpad_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${sentry-breakpad_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${sentry-breakpad_EXE_LINK_FLAGS_RELEASE}>")


set(sentry-breakpad_COMPONENTS_RELEASE )