/// @file      MakeEllipse3.hpp
/// @brief     Class of making 3D ellipses
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/EllipseT.hpp>

namespace AMCAX
{
/// @brief Class of making 3D ellipses
class MakeEllipse3 : public MakeGeometry
{
public:
	/// @brief Construct an ellipse from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	AMCAX_API MakeEllipse3(const Frame3& frame, double majorRadius, double minorRadius);

	/// @brief Construct an ellipse from two points on the major and minor axis, and a center point
	/// @param s1 The point on the major axis
	/// @param s2 The point on the minor axis
	/// @param center The center point
	AMCAX_API MakeEllipse3(const Point3& s1, const Point3& s2, const Point3& center);

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API const Ellipse3& Value() const;

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API operator const Ellipse3&() const;

private:
	Ellipse3 ellipse;
};
} // namespace AMCAX
