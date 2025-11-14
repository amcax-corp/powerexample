/// @file      MakeTrimmedCylinder.hpp
/// @brief     Class of making trimmed cylinders
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/MakeGeometry.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
class Geom3TrimmedSurface;

/// @brief Class of making trimmed cylinders
class MakeTrimmedCylinder : public MakeGeometry
{
public:
	/// @brief Construct a trimmed cylinder from two points on the axis and a point on the cylinder
	/// @details The cylinder is trimmed by the section circles at p1 and p2
	/// @param p1 The first point on the axis
	/// @param p2 The second point on the axis
	/// @param p3 The point on the cylinder
	AMCAX_API MakeTrimmedCylinder(const Point3& p1, const Point3& p2, const Point3& p3);

	/// @brief Construct a trimmed cylinder from a circle and a height
	/// @param c The circle
	/// @param height The height
	AMCAX_API MakeTrimmedCylinder(const Circle3& c, double height);

	/// @brief Construct a trimmed cylinder from an axis, a radius and a height
	/// @param a1 The axis
	/// @param radius The radius
	/// @param height The height
	AMCAX_API MakeTrimmedCylinder(const Axis3& a1, double radius, double height);

	/// @brief Get the constructed trimmed cylinder
	/// @return The trimmed cylinder
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3TrimmedSurface>& Value() const;

	/// @brief Get the constructed trimmed cylinder
	/// @return The trimmed cylinder
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3TrimmedSurface>&() const;

private:
	std::shared_ptr<Geom3TrimmedSurface> cylinder;
};
} // namespace AMCAX
