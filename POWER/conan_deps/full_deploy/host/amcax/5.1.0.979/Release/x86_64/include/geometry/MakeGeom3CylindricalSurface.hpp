/// @file      MakeGeom3CylindricalSurface.hpp
/// @brief     Class of making geometric cylindrical surfaces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3CylindricalSurface.hpp>
#include <geometry/MakeGeometry.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
/// @brief Class of making geometric cylindrical surfaces
class MakeGeom3CylindricalSurface : public MakeGeometry
{
public:
	/// @brief Construct a cylindrical surface from a local frame and a radius
	/// @param frame The local frame
	/// @param radius The radius
	AMCAX_API MakeGeom3CylindricalSurface(const Frame3& frame, double radius);

	/// @brief Construct from a cylinder
	/// @param c The cylinder
	AMCAX_API explicit MakeGeom3CylindricalSurface(const Cylinder& c);

	/// @brief Construct a cylindrical surface coaxial to a given cylinder and passing through a point
	/// @param c The given cylinder
	/// @param point The point
	AMCAX_API MakeGeom3CylindricalSurface(const Cylinder& c, const Point3& point);

	/// @brief Construct a cylindrical surface coaxial to a given cylinder with a distance
	/// @param c The given cylinder
	/// @param dist The distance
	AMCAX_API MakeGeom3CylindricalSurface(const Cylinder& c, double dist);

	/// @brief Construct a cylindrical surface from two points on the axis and a point on the cylinder
	/// @param p1 The first point on the axis
	/// @param p2 The second point on the axis
	/// @param p3 The point on the cylinder
	AMCAX_API MakeGeom3CylindricalSurface(const Point3& p1, const Point3& p2, const Point3& p3);

	/// @brief Construct a cylindrical surface from an axis and a radius
	/// @param axis The axis
	/// @param radius The radius
	AMCAX_API MakeGeom3CylindricalSurface(const Axis3& axis, double radius);

	/// @brief Construct a cylindrical surface from a circle
	/// @param c The circle
	AMCAX_API explicit MakeGeom3CylindricalSurface(const Circle3& c);

	/// @brief Get the constructed cylindrical surface
	/// @return The cylindrical surface
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3CylindricalSurface>& Value() const;

	/// @brief Get the constructed cylindrical surface
	/// @return The cylindrical surface
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3CylindricalSurface>&() const;

private:
	std::shared_ptr<Geom3CylindricalSurface> cylinder;
};
} // namespace AMCAX
