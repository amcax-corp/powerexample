/// @file      MakeCylinder3.hpp
/// @brief     Class of making cylinders
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/CircleT.hpp>
#include <math/Cylinder.hpp>

namespace AMCAX
{
/// @brief Class of making cylinders
class MakeCylinder3 : public MakeGeometry
{
public:
	/// @brief Construct a cylinder from a local frame and a radius
	/// @param frame The local frame
	/// @param radius The radius
	AMCAX_API MakeCylinder3(const Frame3& frame, double radius);

	/// @brief Construct a cylinder coaxial to a given cylinder and passing through a point
	/// @param c The given cylinder
	/// @param point The point
	AMCAX_API MakeCylinder3(const Cylinder& c, const Point3& point);

	/// @brief Construct a cylinder coaxial to a given cylinder with a distance
	/// @param c The given cylinder
	/// @param dist The distance
	AMCAX_API MakeCylinder3(const Cylinder& c, double dist);

	/// @brief Construct a cylinder from two points on the axis and a point on the cylinder
	/// @param p1 The first point on the axis
	/// @param p2 The second point on the axis
	/// @param p3 The point on the cylinder
	AMCAX_API MakeCylinder3(const Point3& p1, const Point3& p2, const Point3& p3);

	/// @brief Construct a cylinder from an axis and a radius
	/// @param axis The axis
	/// @param radius The radius
	AMCAX_API MakeCylinder3(const Axis3& axis, double radius);

	/// @brief Construct a cylinder from a circle
	/// @param c The circle
	AMCAX_API MakeCylinder3(const Circle3& c);

	/// @brief Get the constructed cylinder
	/// @return The cylinder
	[[nodiscard]] AMCAX_API const Cylinder& Value() const;

	/// @brief Get the constructed cylinder
	/// @return The cylinder
	[[nodiscard]] AMCAX_API operator const Cylinder&() const;

private:
	Cylinder cylinder;
};
} // namespace AMCAX
