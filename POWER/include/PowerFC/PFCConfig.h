#ifndef POWERFC_PFCCONFIG_H
#define POWERFC_PFCCONFIG_H
#pragma once

#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#   ifndef PFC_OS_WIN32
#   define PFC_OS_WIN32
#   endif
#   ifndef PFC_OS_WIN64
#   define PFC_OS_WIN64
#   endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   ifndef PFC_OS_WIN32
#   define PFC_OS_WIN32
#   endif
#elif defined(__APPLE__)
#   ifndef PFC_OS_MACOSX
#   define PFC_OS_MACOSX
#   endif
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__GLIBC__)
#   ifndef PFC_OS_LINUX
#   define PFC_OS_LINUX
#   endif
#else
#   error "PowerFC 不支持当前的操作系统"
#endif

#ifdef PFC_OS_WIN32
#   define PATH_SEP '\\'
#else
#   define PATH_SEP '/'
#endif

#include <PFCGlobal.h>

#endif