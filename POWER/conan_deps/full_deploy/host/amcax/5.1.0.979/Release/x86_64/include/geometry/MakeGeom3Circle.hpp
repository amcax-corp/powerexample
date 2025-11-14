/// @file      MakeGeom3Circle.hpp
/// @brief     Class of making 3D geometric circles
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Circle.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 3D geometric circles
class MakeGeom3Circle : public MakeGeometry
{
public:
	/// @brief Construct from a circle
	/// @param c The circle
	AMCAX_API explicit MakeGeom3Circle(const Circle3& c);

	/// @brief Construct a circle from a local frame and a radius
	/// @param frame The local frame
	/// @param radius The radius
	AMCAX_API MakeGeom3Circle(const Frame3& frame, double radius);

	/// @brief Construct a circle coaxial with a given circle with a distance
	/// @param c The given circle
	/// @param dist The dist from the given circle
	AMCAX_API MakeGeom3Circle(const Circle3& c, double dist);

	/// @brief Construct a circle coaxial with a given circle and passing through a point
	/// @param c The given circle
	/// @param point The point
	AMCAX_API MakeGeom3Circle(const Circle3& c, const Point3& point);

	/// @brief Construct a circle passing through three points
	/// @param p1 The first point
	/// @param p2 The second point
	/// @param p3 The third point
	AMCAX_API MakeGeom3Circle(const Point3& p1, const Point3& p2, const Point3& p3);

	/// @brief Construct a circle from a center point, a normal direction and a radius
	/// @param center The center point
	/// @param norm The normal direction
	/// @param radius The radius
	AMCAX_API MakeGeom3Circle(const Point3& center, const Direction3& norm, double radius);

	/// @brief Construct a circle from a center point, a point showing the normal direction and a radius
	/// @param center The center point
	/// @param ptAxis The point showing the normal direction
	/// @param radius The radius
	AMCAX_API MakeGeom3Circle(const Point3& center, const Point3& ptAxis, double radius);

	/// @brief Construct a circle from a normal axis and a radius
	/// @param axis The axis of the center point and the normal direction
	/// @param radius The radius
	AMCAX_API MakeGeom3Circle(const Axis3& axis, double radius);

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Circle>& Value() const;

	/// @brief Get the constructed circle
	/// @return The circle
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3Circle>&() const;

private:
	std::shared_ptr<Geom3Circle> circle;
};
} // namespace AMCAX
