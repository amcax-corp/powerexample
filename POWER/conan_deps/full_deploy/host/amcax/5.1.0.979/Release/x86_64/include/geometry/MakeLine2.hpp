/// @file      MakeLine2.hpp
/// @brief     Class of making 2D lines
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
/// @brief Class of making 2D lines
class MakeLine2 : public MakeGeometry
{
public:
	/// @brief Construct a line from an axis
	/// @param axis The axis
	AMCAX_API explicit MakeLine2(const Axis2& axis) noexcept;

	/// @brief Construct a line from a point and a direction
	/// @param p The point
	/// @param v The direction
	AMCAX_API MakeLine2(const Point2& p, const Direction2& v) noexcept;

	/// @brief Construct a line from the coefficients of algebraic representation
	/// @param a,b,c The coefficients
	AMCAX_API MakeLine2(double a, double b, double c);

	/// @brief Construct a line parallel to a given line at a distance
	/// @param l The given line
	/// @param dist The distance
	AMCAX_API MakeLine2(const Line2& l, double dist) noexcept;

	/// @brief Construct a line parallel to a given line passing through a point
	/// @param l The given line
	/// @param point The point
	AMCAX_API MakeLine2(const Line2& l, const Point2& point) noexcept;

	/// @brief Construct a line passing through two points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeLine2(const Point2& p1, const Point2& p2);

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API const Line2& Value() const;

	/// @brief Get the constructed line
	/// @return The line
	[[nodiscard]] AMCAX_API operator const Line2&() const;

private:
	Line2 line;
};
} // namespace AMCAX
