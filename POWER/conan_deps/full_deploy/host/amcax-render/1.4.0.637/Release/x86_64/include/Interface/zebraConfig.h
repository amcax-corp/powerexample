/// @file      zebraConfig.h
/// @brief     Zebra Stripe Configuration
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef ZEBRACONFIG_H
#define ZEBRACONFIG_H

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender
{
    /// @brief Zebra Stripe Configuration Class
    class AMCAX_RENDER_API ZebraConfig {
    public:
        ZebraConfig();
        ~ZebraConfig();

        /// @brief Set Line Width
        /// @param[in] thickness Line width
        virtual void SetWidth(LineThickness thickness);

        /// @brief Get Line Width
        /// @return Line width
        virtual LineThickness GetWidth() const;

        /// @brief Set Vertical Display
        /// @param[in] arg true: enable vertical, false: disable vertical, enable horizontal
        virtual void SetVertical(bool arg);

        /// @brief Get Direction
        /// @return true: vertical, false: horizontal
        virtual bool GetVertical() const;

        /// @brief Set Color
        /// @param[in] rgb Color components, range [0,1]
        virtual void SetColor(double rgb[3]);

        /// @brief Get Color
        /// @param[out] rgb Color components, range [0,1]
        virtual void GetColor(double rgb[3]) const;
    protected:
        class Impl;
        Impl* pImpl;
    };
}

#endif // ZEBRACONFIG_H