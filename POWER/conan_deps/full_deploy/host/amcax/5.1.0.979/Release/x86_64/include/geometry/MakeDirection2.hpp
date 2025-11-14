/// @file      MakeDirection2.hpp
/// @brief     Class of making 2D directions
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/VectorT.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 2D directions
class MakeDirection2 : public MakeGeometry
{
public:
	/// @brief Construct a direction from a vector
	/// @param v The vector
	AMCAX_API MakeDirection2(const Vector2& v);

	/// @brief Construct a direction from a coordinate
	/// @param coord The coordinate
	AMCAX_API MakeDirection2(const Coord2& coord);

	/// @brief Construct a direction from ccordinates
	/// @param x,y The coordinates
	AMCAX_API MakeDirection2(double x, double y);

	/// @brief Construct a direction from one point to another point
	/// @param p1 The start point
	/// @param p2 The end point
	AMCAX_API MakeDirection2(const Point2& p1, const Point2& p2);

	/// @brief Get the constructed direction
	/// @return The direction
	[[nodiscard]] AMCAX_API const Direction2& Value() const;

	/// @brief Get the constructed direction
	/// @return The direction
	[[nodiscard]] AMCAX_API operator const Direction2&() const;

private:
	Direction2 direction;
};
} // namespace AMCAX
