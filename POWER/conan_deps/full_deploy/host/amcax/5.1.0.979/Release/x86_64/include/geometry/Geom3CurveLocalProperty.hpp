/// @file      Geom3CurveLocalProperty.hpp
/// @brief     Class of local property of 3D curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/CurveLocalProperty.hpp>

namespace AMCAX
{
class Geom3Curve;

#ifndef DOXYGEN_SKIP

extern template class AMCAX_CLASS_API CurveLocalProperty<std::shared_ptr<Geom3Curve>, 3>;

#endif

/// @brief Class of local property of 3D curves
using Geom3CurveLocalProperty = CurveLocalProperty<std::shared_ptr<Geom3Curve>, 3>;
} // namespace AMCAX
