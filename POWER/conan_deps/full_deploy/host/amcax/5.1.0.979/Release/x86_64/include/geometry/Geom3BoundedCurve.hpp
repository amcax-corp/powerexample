/// @file      Geom3BoundedCurve.hpp
/// @brief     Base class of 3D bounded curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Curve.hpp>

namespace AMCAX
{
/// @brief Base class of 3D bounded curve
class AMCAX_CLASS_API Geom3BoundedCurve : public Geom3Curve
{
public:
	/// @brief Get the start point
	/// @return The start point
	[[nodiscard]] AMCAX_API virtual Point3 StartPoint() const = 0;

	/// @brief Get the end point
	/// @return The end point
	[[nodiscard]] AMCAX_API virtual Point3 EndPoint() const = 0;
};
} // namespace AMCAX
