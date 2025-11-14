/// @file      Texture.h
/// @brief     Texture Configuration
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender
{
    /// @brief Texture Configuration Class
    class AMCAX_RENDER_API Texture {
    public:
        /// @brief get the Texture unique Id
        virtual int GetTextureId() const = 0;

        // @brief Sets the image for the Texture.
        // @param filename image filename.
        virtual void LoadImageFromFile(const std::string& filename) = 0;

    };
}

#endif // TEXTURE_H