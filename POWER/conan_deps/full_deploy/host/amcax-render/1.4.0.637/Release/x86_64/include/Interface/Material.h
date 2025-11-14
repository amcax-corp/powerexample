/// @file      Material.h
/// @brief     Material Configuration
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Macros.h"
#include "Constants.h"
#include "Texture.h"
#include <memory>

namespace AMCAXRender
{
    /// @brief Material Configuration Class
    class AMCAX_RENDER_API Material {
    public:
        /// @brief get the Material unique Id
        virtual int GetMaterialId() const = 0;

        // @brief Sets the ambient light coefficient for the material.
        // @param ambient The ambient coefficient (typically [0.0, 1.0]), controlling the intensity of ambient light reflection.
        virtual void SetAmbient(float ambient) = 0;

        // @brief Gets the ambient light coefficient of the material.
        // @return The ambient coefficient (float, typically [0.0, 1.0]).
        virtual float GetAmbient() = 0;

        // @brief Sets the diffuse light coefficient for the material.
        // @param diffuse The diffuse coefficient (typically [0.0, 1.0]), controlling the intensity of diffuse light reflection.
        virtual void SetDiffuse(float diffuse) = 0;

        // @brief Gets the diffuse light coefficient of the material.
        // @return The diffuse coefficient (float, typically [0.0, 1.0]).
        virtual float GetDiffuse() = 0;

        // @brief Sets the specular light coefficient for the material.
        // @param specular The specular coefficient (typically [0.0, 1.0]), controlling the intensity of specular highlights.
        virtual void SetSpecular(float specular) = 0;

        // @brief Gets the specular light coefficient of the material.
        // @return The specular coefficient (float, typically [0.0, 1.0]).
        virtual float GetSpecular() = 0;

        // @brief Sets the specular power (shininess) for the material.
        // @param specularPower The shininess value (typically [0.0, 128.0]), controlling the sharpness of specular highlights.
        //virtual void SetSpecularPower(float specularPower) = 0;

        // @brief Gets the specular power (shininess) of the material.
        // @return The shininess value (float, typically [0.0, 128.0]).
        //virtual float GetSpecularPower() = 0;

        // @brief Sets the texture for the material.
        // @param texture, controlling the image of texture.
        virtual void SetTexture(std::shared_ptr<Texture> texture) = 0;

        // @brief Gets the texture of the material.
        // @return The texture.
        virtual std::shared_ptr<Texture> GetTexture() = 0;

        /// @brief Set Ambient Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void SetAmbientColor(double rgb[3]) = 0;

        /// @brief Get Ambient Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void GetAmbientColor(double rgb[3]) = 0;

        /// @brief Set Diffuse Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void SetDiffuseColor(double rgb[3]) = 0;

        /// @brief Get Diffuse Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void GetDiffuseColor(double rgb[3]) = 0;

        /// @brief Set Specular Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void SetSpecularColor(double rgb[3]) = 0;

        /// @brief Get Specular Color
        /// @param[in] rgb Color
        /// @note Color range [0,1]
        virtual void GetSpecularColor(double rgb[3]) = 0;
    };
}

#endif // MATERIAL_H