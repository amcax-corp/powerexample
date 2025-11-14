/// @file      MakePlane3.hpp
/// @brief     Class of making planes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/MakeGeometry.hpp>
#include <math/Plane.hpp>

namespace AMCAX
{
/// @brief Class of making planes
class MakePlane3 : public MakeGeometry
{
public:
	/// @brief Construct a plane from a local frame
	/// @param frame The local frame
	AMCAX_API explicit MakePlane3(const Frame3& frame) noexcept;

	/// @brief Construct a plane from a location point and a normal direction
	/// @param p The location point
	/// @param v The normal direction
	AMCAX_API MakePlane3(const Point3& p, const Direction3& v) noexcept;

	/// @brief Construct a plane from the coefficients of algebraic representation
	/// @param a,b,c,d The coefficients of algebraic representation
	AMCAX_API MakePlane3(double a, double b, double c, double d);

	/// @brief Construct a plane parallel to a given plane and passing through a given point
	/// @param p The given plane
	/// @param point The point
	AMCAX_API MakePlane3(const Plane& p, const Point3& point) noexcept;

	/// @brief Construct a plane parallel to a given plane with a distance
	/// @param p The given plane
	/// @param dist The distance
	AMCAX_API MakePlane3(const Plane& p, double dist) noexcept;

	/// @brief Construct a plane from three points
	/// @param p1,p2,p3 The points
	AMCAX_API MakePlane3(const Point3& p1, const Point3& p2, const Point3& p3);

	/// @brief Construct a plane perpendicular to a line passing through two points
	/// @param p1,p2 The points which the normal line passes through
	AMCAX_API MakePlane3(const Point3& p1, const Point3& p2);

	/// @brief Construct a plane perpendicular to an axis
	/// @param axis The axis
	AMCAX_API explicit MakePlane3(const Axis3& axis) noexcept;

	/// @brief Get the constructed plane
	/// @return The plane
	[[nodiscard]] AMCAX_API const Plane& Value() const;

	/// @brief Get the constructed plane
	/// @return The plane
	[[nodiscard]] AMCAX_API operator const Plane&() const;

private:
	Plane plane;
};
} // namespace AMCAX
