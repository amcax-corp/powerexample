/// @file      MakeLine3.hpp
/// @brief     Class of making 3D lines
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
/// @brief Class of making 3D lines
class MakeLine3 : public MakeGeometry
{
public:
	/// @brief Construct a line from an axis
	/// @param axis The axis
	AMCAX_API explicit MakeLine3(const Axis3& axis) noexcept;

	/// @brief Construct a line from a point and a direction
	/// @param p The point
	/// @param v The direction
	AMCAX_API MakeLine3(const Point3& p, const Direction3& v) noexcept;

	/// @brief Construct a line parallel to a given line passing through a point
	/// @param l The given line
	/// @param point The point
	AMCAX_API MakeLine3(const Line3& l, const Point3& point) noexcept;

	/// @brief Construct a line passing through two points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeLine3(const Point3& p1, const Point3& p2) noexcept;

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API const Line3& Value() const;

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API operator const Line3&() const;

private:
	Line3 line;
};
} // namespace AMCAX
