#pragma once

#ifdef Standard_EXPORTS
    #define Standard_API __declspec(dllexport)
#else
    #define Standard_API __declspec(dllimport)
#endif
