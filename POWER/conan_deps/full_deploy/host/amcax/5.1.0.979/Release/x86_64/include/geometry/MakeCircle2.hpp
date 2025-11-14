/// @file      MakeCircle2.hpp
/// @brief     Class of making 2D circles
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
/// @brief Class of making 2D circles
class MakeCircle2 : public MakeGeometry
{
public:
	/// @brief Construct a circle from an axis and a radius
	/// @param xAxis The x axis
	/// @param radius The radius
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeCircle2(const Axis2& xAxis, double radius, bool sense = true) noexcept;

	/// @brief Construct a circle from a local frame and a radius
	/// @param frame The local frame
	/// @param radius The radius
	AMCAX_API MakeCircle2(const Frame2& frame, double radius) noexcept;

	/// @brief Construct a circle concentric with a given circle with a distance
	/// @param c The given circle
	/// @param dist The dist from the given circle
	AMCAX_API MakeCircle2(const Circle2& c, double dist) noexcept;

	/// @brief Construct a circle concentric with a given circle and passing through a point
	/// @param c The given circle
	/// @param point The point
	AMCAX_API MakeCircle2(const Circle2& c, const Point2& point) noexcept;

	/// @brief Construct a circle passing through three points
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param p3 The third point
	AMCAX_API MakeCircle2(const Point2& p1, const Point2& p2, const Point2& p3);

	/// @brief Construct a circle from a center point and a radius
	/// @param center The center point
	/// @param radius The radius
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeCircle2(const Point2& center, double radius, bool sense = true) noexcept;

	/// @brief Construct a circle from a center point and passing through a point
	/// @param center The center point
	/// @param point The point
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeCircle2(const Point2& center, const Point2& point, bool sense = true) noexcept;

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API const Circle2& Value() const;

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API operator const Circle2&() const;

private:
	Circle2 circle;
};
} // namespace AMCAX
