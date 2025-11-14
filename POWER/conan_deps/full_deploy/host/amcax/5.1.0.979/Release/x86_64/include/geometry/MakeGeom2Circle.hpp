/// @file      MakeGeom2Circle.hpp
/// @brief     Class of making 2D geometric circles
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Circle.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 2D geometric circles
class MakeGeom2Circle : public MakeGeometry
{
public:
	/// @brief Construct from a circle
	/// @param c The circle
	AMCAX_API explicit MakeGeom2Circle(const Circle2& c);

	/// @brief Construct a circle from an axis and a radius
	/// @param axis The x axis
	/// @param radius The radius
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Circle(const Axis2& axis, double radius, bool sense = true);

	/// @brief Construct a circle from a local frame and a radius
	/// @param frame The local frame
	/// @param radius The radius
	AMCAX_API MakeGeom2Circle(const Frame2& frame, double radius);

	/// @brief Construct a circle concentric with a given circle with a distance
	/// @param c The given circle
	/// @param dist The dist from the given circle
	AMCAX_API MakeGeom2Circle(const Circle2& c, double dist);

	/// @brief Construct a circle concentric with a given circle and passing through a point
	/// @param c The given circle
	/// @param point The point
	AMCAX_API MakeGeom2Circle(const Circle2& c, const Point2& point);

	/// @brief Construct a circle passing through three points
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param p3 The third point
	AMCAX_API MakeGeom2Circle(const Point2& p1, const Point2& p2, const Point2& p3);

	/// @brief Construct a circle from a center point and a radius
	/// @param p The center point
	/// @param radius The radius
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Circle(const Point2& p, double radius, bool sense = true);

	/// @brief Construct a circle from a center point and passing through a point
	/// @param center The center point
	/// @param point The point
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Circle(const Point2& center, const Point2& point, bool sense = true);

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2Circle>& Value() const;

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2Circle>&() const;

private:
	std::shared_ptr<Geom2Circle> circle;
};
} // namespace AMCAX
