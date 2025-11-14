/// @file      Geom2CurveLocalProperty.hpp
/// @brief     Class of local property of 2D curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/CurveLocalProperty.hpp>

namespace AMCAX
{
class Geom2Curve;

#ifndef DOXYGEN_SKIP

extern template class AMCAX_CLASS_API CurveLocalProperty<std::shared_ptr<Geom2Curve>, 2>;

#endif

/// @brief Class of local property of 2D curves
using Geom2CurveLocalProperty = CurveLocalProperty<std::shared_ptr<Geom2Curve>, 2>;
} // namespace AMCAX
