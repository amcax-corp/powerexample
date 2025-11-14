/// @file      MakeHyperbola3.hpp
/// @brief     Class of making 3D hyperbolas
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/HyperbolaT.hpp>

namespace AMCAX
{
/// @brief Class of making 3D hyperbolas
class MakeHyperbola3 : public MakeGeometry
{
public:
	/// @brief Construct a hyperbola from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	AMCAX_API MakeHyperbola3(const Frame3& frame, double majorRadius, double minorRadius);

	/// @brief Construct a hyperbola from a point on the major axis, a point on the minor axis and a center point
	/// @param s1 The point on the major axis
	/// @param s2 The point on the minor axis
	/// @param center The center point
	AMCAX_API MakeHyperbola3(const Point3& s1, const Point3& s2, const Point3& center);

	/// @brief Get the constructed hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API const Hyperbola3& Value() const;

	/// @brief Get the constructed hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API operator const Hyperbola3&() const;

private:
	Hyperbola3 hyperbola;
};
} // namespace AMCAX
