/// @file      Geom3SurfaceLocalProperty.hpp
/// @brief     Class of local property of surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/SurfaceLocalProperty.hpp>

namespace AMCAX
{
class Geom3Surface;

#ifndef DOXYGEN_SKIP

extern template class AMCAX_CLASS_API SurfaceLocalProperty<std::shared_ptr<Geom3Surface>>;

#endif

/// @brief Class of local property of surfaces
using Geom3SurfaceLocalProperty = SurfaceLocalProperty<std::shared_ptr<Geom3Surface>>;
} // namespace AMCAX
