/// @file      MakeDirection3.hpp
/// @brief     Class of making 3D directions
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/VectorT.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 3D directions
class MakeDirection3 : public MakeGeometry
{
public:
	/// @brief Construct a direction from a vector
	/// @param v The vector
	AMCAX_API MakeDirection3(const Vector3& v);

	/// @brief Construct a direction from a coordinate
	/// @param coord The coordinate
	AMCAX_API MakeDirection3(const Coord3& coord);

	/// @brief Construct a direction from ccordinates
	/// @param x,y,z The coordinates
	AMCAX_API MakeDirection3(double x, double y, double z);

	/// @brief Construct a direction from one point to another point
	/// @param p1 The start point
	/// @param p2 The end point
	AMCAX_API MakeDirection3(const Point3& p1, const Point3& p2);

	/// @brief Get the constructed direction
	/// @return The direction
	[[nodiscard]] AMCAX_API const Direction3& Value() const;

	/// @brief Get the constructed direction
	/// @return The direction
	[[nodiscard]] AMCAX_API operator const Direction3&() const;

private:
	Direction3 direction;
};
} // namespace AMCAX
