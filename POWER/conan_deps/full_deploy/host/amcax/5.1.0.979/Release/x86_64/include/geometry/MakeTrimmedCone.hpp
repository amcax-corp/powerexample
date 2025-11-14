/// @file      MakeTrimmedCone.hpp
/// @brief     Class of making trimmed cones
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
class Geom3TrimmedSurface;

/// @brief Class of making trimmed cones
class MakeTrimmedCone : public MakeGeometry
{
public:
	/// @brief Construct a trimmed cone from two points on the axis, a point on the base reference circle and another point on the cone
	/// @details The cone is trimmed by the section circles at p3 and p4
	/// @param p1 The first point of the axis
	/// @param p2 The second point of the axis
	/// @param p3 The point on the base reference circle
	/// @param p4 The other point on the cone
	AMCAX_API MakeTrimmedCone(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4);

	/// @brief Construct a trimmed cone from two points on the axis, the radii of section circles at the two points
	/// @details The cone is trimmed by the section circles at the two points
	/// @param p1 The first point of the axis
	/// @param p2 The second point of the axis
	/// @param r1 The radius of the section circle at the first point
	/// @param r2 The radius of the section circle at the second point
	AMCAX_API MakeTrimmedCone(const Point3& p1, const Point3& p2, double r1, double r2);

	/// @brief Get the constructed trimmed cone
	/// @return The trimmed cone
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3TrimmedSurface>& Value() const;

	/// @brief Get the constructed trimmed cone
	/// @return The trimmed cone
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3TrimmedSurface>&() const;

private:
	std::shared_ptr<Geom3TrimmedSurface> cone;
};
} // namespace AMCAX
