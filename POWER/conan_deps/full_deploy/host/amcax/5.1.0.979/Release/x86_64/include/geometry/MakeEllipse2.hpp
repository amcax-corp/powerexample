/// @file      MakeEllipse2.hpp
/// @brief     Class of making 2D ellipses
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/EllipseT.hpp>

namespace AMCAX
{
/// @brief Class of making 2D ellipses
class MakeEllipse2 : public MakeGeometry
{
public:
	/// @brief Construct an ellipse from a major axis, a major radius and a minor radius
	/// @param majorAxis The major axis
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeEllipse2(const Axis2& majorAxis, double majorRadius, double minorRadius, bool sense = true);

	/// @brief Construct an ellipse from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	AMCAX_API MakeEllipse2(const Frame2& frame, double majorRadius, double minorRadius);

	/// @brief Construct an ellipse from two points on the major and minor axis, and a center point
	/// @param s1 The point on the major axis
	/// @param s2 The point on the minor axis
	/// @param center The center point
	AMCAX_API MakeEllipse2(const Point2& s1, const Point2& s2, const Point2& center);

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API const Ellipse2& Value() const;

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API operator const Ellipse2&() const;

private:
	Ellipse2 ellipse;
};
} // namespace AMCAX
