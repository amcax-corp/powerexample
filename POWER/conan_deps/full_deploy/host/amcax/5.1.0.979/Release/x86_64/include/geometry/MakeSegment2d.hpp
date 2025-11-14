/// @file      MakeSegment2d.hpp
/// @brief     Class of making 2D line segments
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/MakeGeometry.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
class Geom2TrimmedCurve;

/// @brief Class of making 2D line segments
class MakeSegment2d : public MakeGeometry
{
public:
	/// @brief Construct a line segment from two points
	/// @param p1 The start point
	/// @param p2 The end point
	AMCAX_API MakeSegment2d(const Point2& p1, const Point2& p2);

	/// @brief Construct a line segment from a point and a direction, ending with another point projected to the line
	/// @param p1 The start point
	/// @param v The direction
	/// @param p2 The end point
	AMCAX_API MakeSegment2d(const Point2& p1, const Direction2& v, const Point2& p2);

	/// @brief Construct a line segment from a line and two parameters
	/// @param l The line
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	AMCAX_API MakeSegment2d(const Line2& l, double u1, double u2);

	/// @brief Construct a line segment from a line, a start point and a last parameter
	/// @param l The line
	/// @param point The point
	/// @param ulast The last parameter
	AMCAX_API MakeSegment2d(const Line2& l, const Point2& point, double ulast);

	/// @brief Construct a line segment from a line and two points
	/// @param l The line
	/// @param p1 The start point
	/// @param p2 The end point
	AMCAX_API MakeSegment2d(const Line2& l, const Point2& p1, const Point2& p2);

	/// @brief Get the constructed line segment
	/// @return The line segment
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2TrimmedCurve>& Value() const;

	/// @brief Get the constructed line segment
	/// @return The line segment
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2TrimmedCurve>&() const;

private:
	std::shared_ptr<Geom2TrimmedCurve> segment;
};
} // namespace AMCAX
