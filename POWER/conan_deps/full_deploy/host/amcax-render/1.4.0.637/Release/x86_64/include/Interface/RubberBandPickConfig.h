/// @file      RubberBandPickConfig.h
/// @brief     Rubber Band Pick Configuration
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef RUBBERBANDPICKCONFIG_H
#define RUBBERBANDPICKCONFIG_H

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender
{
    /// @brief Rubber Band Pick Configuration Class
    class AMCAX_RENDER_API RubberBandPickConfig {
    public:
        enum class SelectionMode {
            Normal,  // Normal Selection
            Inverse  // Inverse Selection
        };

        enum class PickMode {
            Intersection,  // Intersection Pick
            Color          // Color Pick
        };

        RubberBandPickConfig();
        ~RubberBandPickConfig();

        // Get Selection Mode
        SelectionMode GetMode() const;

        // Set Selection Mode
        void SetMode(SelectionMode newMode);

        // Get Pick Mode
        PickMode GetPickMode() const;

        // Set Pick Mode
        void SetPickMode(PickMode newPickMode);

        PickType GetPickType() const;
        void SetPickType(PickType newPickType);

        // Get Blend Color
        void GetBlendColor(unsigned char blendColor[3]) const;

        // Set Blend Color
        void SetBlendColor(const unsigned char newBlendColor[3]);

        // Get Include Boundary
        bool GetIncludeBoundary() const;

        // Set Include Boundary
        void SetIncludeBoundary(bool newIncludeBoundary);

        // Print Configuration
        void PrintConfig() const;

    protected:
        class Impl;
        Impl* pImpl;
    };
}

#endif // RUBBERBANDPICKCONFIG_H