/// @file      Macros.hpp
/// @brief     Basic macros defined for compatibility on different platforms
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

/// @def AMCAX_API
/// @brief The macro for exporting symbols when building shared library with compiler MSVC and GCC
/// @details The macro has no effect with other compilers.

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define AMCAX_API EMSCRIPTEN_KEEPALIVE
#elif defined(_MSC_VER) && defined(BUILD_SHARED)
#define AMCAX_API __declspec(dllexport)
#elif defined(__GNUG__) && defined(BUILD_SHARED)
#define AMCAX_API __attribute__((visibility("default")))
#else
#define AMCAX_API
#endif

/// @def AMCAX_CLASS_API
/// @brief The macro for exporting vtable with the compiler GCC
/// @details The macro has no effect with other compilers.

#if defined(__GNUG__) && defined(BUILD_SHARED)
#define AMCAX_CLASS_API __attribute__((visibility("default")))
#else
#define AMCAX_CLASS_API
#endif

#ifndef DOXYGEN_SKIP

#if defined(_MSC_VER) && defined(BUILD_SHARED) && defined(INTERNAL_TEST)
#define AMCAX_TEST_API __declspec(dllexport)
#elif defined(__GNUG__) && defined(BUILD_SHARED) && defined(INTERNAL_TEST)
#define AMCAX_TEST_API __attribute__((visibility("default")))
#else
#define AMCAX_TEST_API
#endif

#if defined(__GNUG__) && defined(BUILD_SHARED) && defined(INTERNAL_TEST)
#define AMCAX_TEST_CLASS_API __attribute__((visibility("default")))
#else
#define AMCAX_TEST_CLASS_API
#endif

#endif

