/// @file      RenderConfig.h
/// @brief     General Rendering Module Global Configuration
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef RENDERCONFIG_H
#define RENDERCONFIG_H
#pragma once
#include "Macros.h"
#include <utility>
#include <Interface/Constants.h>
namespace AMCAXRender 
{
    /// @brief Rendering Configuration Class
    class AMCAX_RENDER_API RenderConfig {
    public:
        RenderConfig();
        ~RenderConfig();

        /// @brief Set Face Offset Coefficient
        /// @param[in] first 
        /// @param[in] second 
        void SetFaceOffset(double first, double second);

        /// @brief Get Offset Parameters
        /// @return Offset Coefficient 
        std::pair<double, double> GetFaceOffset() const;

        /// @brief Set Line Offset Coefficient
        /// @param[in] first 
        /// @param[in] second
        void SetLineOffset(double first, double second);
       
        /// @brief Get Line Offset Parameters
        /// @return Offset Coefficient
        std::pair<double, double> GetLineOffset() const;

        void SetViewType(ViewType viewType);
        ViewType GetViewType() const;

    private:
        class Impl;
        Impl* pImpl;
    };
}

#endif // RENDERCONFIG_H