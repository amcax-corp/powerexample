/// @file      BasicRender.h
/// @brief     Render Component Object
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef BasicRender_h
#define BasicRender_h

#include "EntityFactory.h"
#include "EntityManage.h"
#include "StyleManage.h"
#include "InteractionCenter.h"
#include "CameraManage.h"
#include "PluginManage.h"
#include "CloudVisltFactory.h"
#include "CloudVisltManage.h"
#include "LightManager.h"

#include <QWidget>
#include "MaterialManager.h"
#include "TextureManager.h"

namespace AMCAXRender {

    /// @brief General Render Component
    struct AMCAX_RENDER_API CBasicRender
    {
        /// @brief Entity Factory
        std::shared_ptr<EntityFactory> entityFactory;

        /// @brief Entity Management
        std::shared_ptr<EntityManage> entityManage;

        /// @brief Style Management
        std::shared_ptr<StyleManage> styleManage;

        /// @brief Interaction Center
        std::shared_ptr<InteractionCenter> interactionCenter;

        /// @brief Camera Management
        std::shared_ptr<CameraManage> cameraManage;

        /// @brief Plugin Management
        std::shared_ptr<PluginManage> pluginManage;

        /// @brief Cloud Factory
        std::shared_ptr<CloudVisltFactory> cloudVisltFactory;

        /// @brief Cloud Management
        std::shared_ptr<CloudVisltManage> cloudVisltManage;

        std::shared_ptr<LightManager> lightManager;

        std::shared_ptr<MaterialManager> materialManager;

        std::shared_ptr<TextureManager> textureManager;

        /// @brief Render Main Window
        QWidget* widget;

        std::map<ViewType, QWidget*> widgetsMap;
    };
}

#endif