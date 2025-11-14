/// @file      Geom2BoundedCurve.hpp
/// @brief     Base class of 2D bounded curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Curve.hpp>

namespace AMCAX
{
/// @brief Base class of 2D bounded curve
class AMCAX_CLASS_API Geom2BoundedCurve : public Geom2Curve
{
public:
	/// @brief Get the start point
	/// @return The start point
	[[nodiscard]] AMCAX_API virtual Point2 StartPoint() const = 0;

	/// @brief Get the end point
	/// @return The end point
	[[nodiscard]] AMCAX_API virtual Point2 EndPoint() const = 0;
};
} // namespace AMCAX
