/// @file      AMCAXRender.h
/// @brief     Component Creation
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef AMCAXRender_h
#define AMCAXRender_h

#include "Interface/Macros.h"
#include "Interface/IRenderComponent.h"

namespace AMCAXRender {

    /// @brief Create Render Component
    /// @param[in] parent Parent Object
    AMCAX_RENDER_API std::shared_ptr<IRenderComponent> CreateRenderComponent(QWidget* parent);
}
#endif