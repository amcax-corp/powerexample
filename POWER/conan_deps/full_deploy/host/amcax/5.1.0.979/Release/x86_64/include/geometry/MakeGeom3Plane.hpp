/// @file      MakeGeom3Plane.hpp
/// @brief     Class of making geometric planes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Plane.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making geometric planes
class MakeGeom3Plane : public MakeGeometry
{
public:
	/// @brief Construct from a plane
	/// @param p The plane
	AMCAX_API explicit MakeGeom3Plane(const Plane& p);

	/// @brief Construct a plane from a location point and a normal direction
	/// @param p The location point
	/// @param v The normal direction
	AMCAX_API MakeGeom3Plane(const Point3& p, const Direction3& v);

	/// @brief Construct a plane from the coefficients of algebraic representation
	/// @param a,b,c,d The coefficients of algebraic representation
	AMCAX_API MakeGeom3Plane(double a, double b, double c, double d);

	/// @brief Construct a plane parallel to a given plane and passing through a given point
	/// @param p The given plane
	/// @param point The point
	AMCAX_API MakeGeom3Plane(const Plane& p, const Point3& point);

	/// @brief Construct a plane parallel to a given plane with a distance
	/// @param p The given plane
	/// @param dist The distance
	AMCAX_API MakeGeom3Plane(const Plane& p, double dist);

	/// @brief Construct a plane from three points
	/// @param p1,p2,p3 The points
	AMCAX_API MakeGeom3Plane(const Point3& p1, const Point3& p2, const Point3& p3);

	/// @brief Construct a plane perpendicular to an axis
	/// @param axis The axis
	AMCAX_API explicit MakeGeom3Plane(const Axis3& axis);

	/// @brief Get the constructed plane
	/// @return The plane
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Plane>& Value() const;

	/// @brief Get the constructed plane
	/// @return The plane
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3Plane>&() const;

private:
	std::shared_ptr<Geom3Plane> plane;
};
} // namespace AMCAX
