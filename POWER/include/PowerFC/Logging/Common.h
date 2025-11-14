#pragma once
#undef LOGGING_HEADER_ONLY
#if defined(LOGGING_SHARED_LIB)
    #if defined(_WIN32)
        #ifdef LOGGING_EXPORTS
            #define LOGGING_API __declspec(dllexport)
        #else
            #define LOGGING_API __declspec(dllimport)
        #endif
    #else
        #define LOGGING_API __attribute__((visibility("default")))
    #endif
#else
    #define LOGGING_API
#endif
#define LOGGING_INLINE
