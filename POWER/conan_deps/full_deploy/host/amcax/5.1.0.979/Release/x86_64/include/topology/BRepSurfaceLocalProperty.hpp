/// @file      BRepSurfaceLocalProperty.hpp
/// @brief     Class of local property of BRep surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/SurfaceLocalProperty.hpp>
#include <topology/BRepAdaptorSurface.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP

extern template class AMCAX_CLASS_API SurfaceLocalProperty<BRepAdaptorSurface>;

#endif

/// @brief Class of local property of BRep surfaces
using BRepSurfaceLocalProperty = SurfaceLocalProperty<BRepAdaptorSurface>;
} // namespace AMCAX
