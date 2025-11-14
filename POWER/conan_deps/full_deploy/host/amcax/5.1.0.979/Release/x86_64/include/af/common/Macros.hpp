/// @file      Macros.hpp
/// @brief     The Definations of Macros of AMCAXAF
/// @details   Define macros for AMCAXAF
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once

/// @brief The macro for Attribute Constructor
#define ATTR_CTOR [[nodiscard]] explicit

#ifndef DOXYGEN_SKIP
#ifdef _WIN32
    #ifdef AMCAXAF_LIBRARY_EXPORTS
        #define AMCAXAF_API __declspec(dllexport)
    #else
        #define AMCAXAF_API __declspec(dllimport)
    #endif
#else
    #define AMCAXAF_API __attribute__((visibility("default")))
#endif
#endif
