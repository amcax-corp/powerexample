/// @file      IRenderComponent.h
/// @brief     Render Component Initialization
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef IRenderComponent_h
#define IRenderComponent_h

#include <QWidget>
#include <memory>
#include "Constants.h"
#include "RenderConfig.h"
#include "BasicRender.h"

namespace AMCAXRender {

    /// @brief Render Component Class
    /// @details Mainly used for the initialization of the rendering SDK
    class AMCAX_RENDER_API IRenderComponent {
    protected:
        IRenderComponent(QWidget* parent) { _parent = parent; }
    public:
        virtual QWidget* GetRenderWidget(ViewType viewType, bool createIfNotExist) = 0;

        /// @brief Create Basic Render Component
        /// @param[in] config Configuration
        /// @return Basic Render Component Object
        virtual std::shared_ptr<CBasicRender> CreateBasicRender(const RenderConfig& config = RenderConfig()) = 0;
    protected:
        QWidget* _parent;
        std::shared_ptr<CBasicRender> _basicRender;
    };
}

#endif // ! IRenderComponent_h