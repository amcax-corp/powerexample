/// @file      MakeArcOfCircle2d.hpp
/// @brief     Class of making arcs of 2D circle
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/MakeGeometry.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
class Geom2TrimmedCurve;

/// @brief Class of making arcs of 2D circle
class MakeArcOfCircle2d : public MakeGeometry
{
public:
	/// @brief Construct an arc of circle from a base circle with the first and last parameters
	/// @param c The base circle
	/// @param alpha1 The first parameter
	/// @param alpha2 The last parameter
	/// @param sense Determine whether the orientation preserves the base circle
	AMCAX_API MakeArcOfCircle2d(const Circle2& c, double alpha1, double alpha2, bool sense = true);

	/// @brief Construct an arc of circle from a base circle with the first point and the last parameter
	/// @param c The base circle
	/// @param p The first point
	/// @param alpha The last parameter
	/// @param sense Determine whether the orientation preserves the base circle
	AMCAX_API MakeArcOfCircle2d(const Circle2& c, const Point2& p, double alpha, bool sense = true);

	/// @brief Construct an arc of circle from a base circle with the first and last points
	/// @param c The base circle
	/// @param p1 The first point
	/// @param p2 The last point
	/// @param sense Determine whether the orientation preserves the base circle
	AMCAX_API MakeArcOfCircle2d(const Circle2& c, const Point2& p1, const Point2& p2, bool sense = true);

	/// @brief Construct an arc of circle from three points p1, p2, p3
	/// @param p1 The start point
	/// @param p2 The middle point
	/// @param p3 The end point
	AMCAX_API MakeArcOfCircle2d(const Point2& p1, const Point2& p2, const Point2& p3);

	/// @brief Construct an arc of circle from two points p1, p2 and a tangent vector v at p1
	/// @param p1 The start point
	/// @param v The tangent vector at p1
	/// @param p2 The end point
	AMCAX_API MakeArcOfCircle2d(const Point2& p1, const Vector2& v, const Point2& p2);

	/// @brief Get the constructed arc of circle
	/// @return The arc of circle
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2TrimmedCurve>& Value() const;

	/// @brief Get the constructed arc of circle
	/// @return The arc of circle
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2TrimmedCurve>&() const;

private:
	std::shared_ptr<Geom2TrimmedCurve> arc;
};
} // namespace AMCAX
