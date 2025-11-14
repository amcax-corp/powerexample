#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #ifdef PFC_BASE_EXPORTS
        #define PFC_BASE_API __declspec(dllexport)
    #else
        #define PFC_BASE_API __declspec(dllimport)
    #endif

    #ifdef PFC_APP_EXPORTS
        #define PFC_APP_API __declspec(dllexport)
    #else
        #define PFC_APP_API __declspec(dllimport)
    #endif

    #ifdef PFC_GUI_EXPORTS
        #define PFC_GUI_API __declspec(dllexport)
    #else
        #define PFC_GUI_API __declspec(dllimport)
    #endif
#else
// Linux/macOS - use visibility attributes
    #if defined(PFC_BASE_EXPORTS) || defined(PFC_APP_EXPORTS) || defined(PFC_GUI_EXPORTS)
        #define PFC_BASE_API __attribute__((visibility("default")))
        #define PFC_APP_API __attribute__((visibility("default")))
        #define PFC_GUI_API __attribute__((visibility("default")))
    #else
        #define PFC_BASE_API
        #define PFC_APP_APIF
        #define PFC_GUI_API
    #endif
#endif

#define NAMESPACE_GUI "gui::"
#define NAMESPACE_APP "app::"

#define PFC_UNUSED(x) (void)x

#define FUTURE_IMPLEMENT(FUNC_NAME, FAKE_RETURN) \
    return FAKE_RETURN

#define FUTURE_IMPLEMENT_VARIABLE(FUNC_NAME)
