/// @file      MakeSegment.hpp
/// @brief     Class of making 3D line segments
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/MakeGeometry.hpp>
#include <math/LineT.hpp>

namespace AMCAX
{
class Geom3TrimmedCurve;

/// @brief Class of making 3D line segments
class MakeSegment : public MakeGeometry
{
public:
	/// @brief Construct a line segment from two points
	/// @param p1 The start point
	/// @param p2 The end point
	AMCAX_API MakeSegment(const Point3& p1, const Point3& p2);

	/// @brief Construct a line segment from a line and two parameters
	/// @param l The line
	/// @param u1 The first parameter
	/// @param u2 The last parameter
	AMCAX_API MakeSegment(const Line3& l, double u1, double u2);

	/// @brief Construct a line segment from a line, a start point and a last parameter
	/// @param l The line
	/// @param p The point
	/// @param ulast The last parameter
	AMCAX_API MakeSegment(const Line3& l, const Point3& p, double ulast);

	/// @brief Construct a line segment from a line and two points
	/// @param l The line
	/// @param p1 The start point
	/// @param p2 The end point
	AMCAX_API MakeSegment(const Line3& l, const Point3& p1, const Point3& p2);

	/// @brief Get the constructed line segment
	/// @return The line segment
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3TrimmedCurve>& Value() const;

	/// @brief Get the constructed line segment
	/// @return The line segment
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3TrimmedCurve>&() const;

private:
	/// @brief Line segment
	std::shared_ptr<Geom3TrimmedCurve> segment;
};
} // namespace AMCAX
