/// @file      MakeGeom3Line.hpp
/// @brief     Class of making 3D geometric lines
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Line.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
class Geom3Line;

/// @brief Class of making 3D geometric lines
class MakeGeom3Line : public MakeGeometry
{
public:
	/// @brief Construct a line from an axis
	/// @param a The axis
	AMCAX_API explicit MakeGeom3Line(const Axis3& a);

	/// @brief Construct from a line
	/// @param l The line
	AMCAX_API explicit MakeGeom3Line(const Line3& l);

	/// @brief Construct a line from a point and a direction
	/// @param p The point
	/// @param v The direction
	AMCAX_API MakeGeom3Line(const Point3& p, const Direction3& v);

	/// @brief Construct a line parallel to a given line passing through a point
	/// @param l The given line
	/// @param p The point
	AMCAX_API MakeGeom3Line(const Line3& l, const Point3& p);

	/// @brief Construct a line passing through two points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeGeom3Line(const Point3& p1, const Point3& p2);

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Line>& Value() const;

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3Line>&() const;

private:
	/// @brief Line
	std::shared_ptr<Geom3Line> line;
};
} // namespace AMCAX
