#include "DevWorkbench.h"

extern "C" __declspec(dllexport) void* CreateInstance()
{
    return new Dev::DevWorkbench();
}