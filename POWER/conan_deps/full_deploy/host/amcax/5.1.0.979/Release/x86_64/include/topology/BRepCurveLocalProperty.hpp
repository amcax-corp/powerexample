/// @file      BRepCurveLocalProperty.hpp
/// @brief     Class of local property of BRep curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/CurveLocalProperty.hpp>
#include <topology/BRepAdaptorCurve3.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP

extern template class AMCAX_CLASS_API CurveLocalProperty<BRepAdaptorCurve3, 3>;

#endif

/// @brief Class of local property of BRep curves
using BRepCurveLocalProperty = CurveLocalProperty<BRepAdaptorCurve3, 3>;
} // namespace AMCAX
