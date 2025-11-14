#ifndef Macros_h
#define Macros_h

#ifdef BUILDING_AMCAX_RENDER_DLL
    #ifdef _MSC_VER
        #define AMCAX_RENDER_API __declspec(dllexport)
    #else
        #define AMCAX_RENDER_API __attribute__((visibility("default")))
    #endif
#elif defined(USING_AMCAX_RENDER_DLL)
    #ifdef _MSC_VER
        #define AMCAX_RENDER_API __declspec(dllimport)
    #else
        #define AMCAX_RENDER_API
    #endif
#else
    #define AMCAX_RENDER_API
#endif

#endif