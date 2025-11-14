/// @file      MakeGeom2Line.hpp
/// @brief     Class of making 2D geometric lines
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Line.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 2D geometric lines
class MakeGeom2Line : public MakeGeometry
{
public:
	/// @brief Construct a line from an axis
	/// @param axis The axis
	AMCAX_API explicit MakeGeom2Line(const Axis2& axis);

	/// @brief Construct from a line
	/// @param l The line
	AMCAX_API explicit MakeGeom2Line(const Line2& l);

	/// @brief Construct a line from a point and a direction
	/// @param p The point
	/// @param v The direction
	AMCAX_API MakeGeom2Line(const Point2& p, const Direction2& v);

	/// @brief Construct a line parallel to a given line passing through a point
	/// @param l The given line
	/// @param point The point
	AMCAX_API MakeGeom2Line(const Line2& l, const Point2& point);

	/// @brief Construct a line parallel to a given line at a distance
	/// @param l The given line
	/// @param dist The distance
	AMCAX_API MakeGeom2Line(const Line2& l, double dist);

	/// @brief Construct a line passing through two points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeGeom2Line(const Point2& p1, const Point2& p2);

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2Line>& Value() const;

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2Line>&() const;

private:
	std::shared_ptr<Geom2Line> line;
};
} // namespace AMCAX
