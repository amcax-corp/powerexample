/// @file      MakeCone3.hpp
/// @brief     Class of making cones
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/Cone.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
/// @brief Class of making cones
class MakeCone3 : public MakeGeometry
{
public:
	/// @brief Construct a cone from a local frame, a radius and a semi-angle
	/// @param frame The local frame
	/// @param radius The radius
	/// @param angle The semi-angle
	AMCAX_API MakeCone3(const Frame3& frame, double radius, double angle);

	/// @brief Construct a cone from two points on the axis, a point on the base circle and another point on the cone
	/// @param p1 The first point of the axis
	/// @param p2 The second point of the axis
	/// @param p3 The point on the base reference circle
	/// @param p4 The other point on the cone
	AMCAX_API MakeCone3(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4);

	/// @brief Construct a cone from an axis, a point on the base circle and a point on the cone
	/// @param axis The axis
	/// @param p1 The point on the base reference circle
	/// @param p2 The other point on the cone
	AMCAX_API MakeCone3(const Axis3& axis, const Point3& p1, const Point3& p2);

	/// @brief Construct a cone from a line, a point on the base circle and a point on the cone
	/// @param axis The line
	/// @param p1 The point on the base reference circle
	/// @param p2 The other point on the cone
	AMCAX_API MakeCone3(const Line3& axis, const Point3& p1, const Point3& p2);

	/// @brief Construct a cone from two points on the axis, the radii of section circles at the two points
	/// @param p1 The first point of the axis
	/// @param p2 The second point of the axis
	/// @param r1 The radius of the section circle at the first point
	/// @param r2 The radius of the section circle at the second point
	AMCAX_API MakeCone3(const Point3& p1, const Point3& p2, double r1, double r2);

	/// @brief Get the constructed cone
	/// @return The cone
	[[nodiscard]] AMCAX_API const Cone& Value() const;

	/// @brief Get the constructed cone
	/// @return The cone
	[[nodiscard]] AMCAX_API operator const Cone&() const;

private:
	Cone cone;
};
} // namespace AMCAX
