/// @file      MakeGeom3Hyperbola.hpp
/// @brief     Class of making 3D geometric hyperbolas
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Hyperbola.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 3D geometric hyperbolas
class MakeGeom3Hyperbola : public MakeGeometry
{
public:
	/// @brief Construct from a hyperbola
	/// @param h The hyperbola
	AMCAX_API explicit MakeGeom3Hyperbola(const Hyperbola3& h);

	/// @brief Construct a hyperbola from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	AMCAX_API MakeGeom3Hyperbola(const Frame3& frame, double majorRadius, double minorRadius);

	/// @brief Construct a hyperbola from a point on the major axis, a point on the minor axis and a center point
	/// @param s1 The point on the major axis
	/// @param s2 The point on the minor axis
	/// @param center The center point
	AMCAX_API MakeGeom3Hyperbola(const Point3& s1, const Point3& s2, const Point3& center);

	/// @brief Get the constructed hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Hyperbola>& Value() const;

	/// @brief Get the constructed hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3Hyperbola>&() const;

private:
	std::shared_ptr<Geom3Hyperbola> hyperbola;
};
} // namespace AMCAX
