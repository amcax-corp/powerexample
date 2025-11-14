#pragma once

#ifdef Dev_EXPORTS
    #define Dev_API __declspec(dllexport)
#else
    #define Dev_API __declspec(dllimport)
#endif
