/// @file      MakeCircle3.hpp
/// @brief     Class of making 3D circles
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/CircleT.hpp>

namespace AMCAX
{
class Plane;

/// @brief Class of making 3D circles
class MakeCircle3 : public MakeGeometry
{
public:
	/// @brief Construct a circle from a local frame and a radius
	/// @param frame The local frame
	/// @param radius The radius
	AMCAX_API MakeCircle3(const Frame3& frame, double radius) noexcept;

	/// @brief Construct a circle coaxial with a given circle with a distance
	/// @param c The given circle
	/// @param dist The dist from the given circle
	AMCAX_API MakeCircle3(const Circle3& c, double dist) noexcept;

	/// @brief Construct a circle coaxial with a given circle and passing through a point
	/// @param c The given circle
	/// @param point The point
	AMCAX_API MakeCircle3(const Circle3& c, const Point3& point) noexcept;

	/// @brief Construct a circle passing through three points
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param p3 The third point
	AMCAX_API MakeCircle3(const Point3& p1, const Point3& p2, const Point3& p3);

	/// @brief Construct a circle from a center point, a normal direction and a radius
	/// @param center The center point
	/// @param norm The normal direction
	/// @param radius The radius
	AMCAX_API MakeCircle3(const Point3& center, const Direction3& norm, double radius) noexcept;

	/// @brief Construct a circle from a center point, the normal of a plane and a radius
	/// @param center The center point
	/// @param plane The plane
	/// @param radius The radius
	AMCAX_API MakeCircle3(const Point3& center, const Plane& plane, double radius) noexcept;

	/// @brief Construct a circle from a center point, a point showing the normal direction and a radius
	/// @param center The center point
	/// @param ptaxis The point showing the normal direction
	/// @param radius The radius
	AMCAX_API MakeCircle3(const Point3& center, const Point3& ptaxis, double radius) noexcept;

	/// @brief Construct a circle from a normal axis and a radius
	/// @param axis The axis of the center point and the normal direction
	/// @param radius The radius
	AMCAX_API MakeCircle3(const Axis3& axis, double radius) noexcept;

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API const Circle3& Value() const;

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API operator const Circle3&() const;

private:
	Circle3 circle;
};
} // namespace AMCAX
