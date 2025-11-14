/// @file      MakeGeom3ConicalSurface.hpp
/// @brief     Class of making geometric conical surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3ConicalSurface.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making geometric conical surfaces
class MakeGeom3ConicalSurface : public MakeGeometry
{
public:
	/// @brief Construct a conical surface from a local frame, a radius and a semi-angle
	/// @param frame The local frame
	/// @param radius The radius
	/// @param angle The semi-angle
	AMCAX_API MakeGeom3ConicalSurface(const Frame3& frame, double radius, double angle);

	/// @brief Construct from a cone
	/// @param c The cone
	AMCAX_API explicit MakeGeom3ConicalSurface(const Cone& c);

	/// @brief Construct a conical surface from two points on the axis, a point on the base circle and another point on the cone
	/// @param p1 The first point of the axis
	/// @param p2 The second point of the axis
	/// @param p3 The point on the base reference circle
	/// @param p4 The other point on the cone
	AMCAX_API MakeGeom3ConicalSurface(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4);

	/// @brief Construct a conical surface from two points on the axis, the radii of section circles at the two points
	/// @param p1 The first point of the axis
	/// @param p2 The second point of the axis
	/// @param r1 The radius of the section circle at the first point
	/// @param r2 The radius of the section circle at the second point
	AMCAX_API MakeGeom3ConicalSurface(const Point3& p1, const Point3& p2, double r1, double r2);

	/// @brief Get the constructed conical surface
	/// @return The conical surface
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3ConicalSurface>& Value() const;

	/// @brief Get the constructed conical surface
	/// @return The conical surface
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3ConicalSurface>&() const;

private:
	std::shared_ptr<Geom3ConicalSurface> cone;
};
} // namespace AMCAX
