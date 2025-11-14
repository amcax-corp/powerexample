/// @file      MakeGeom2Hyperbola.hpp
/// @brief     Class of making 2D geometric hyperbolas
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Hyperbola.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 2D geometric hyperbolas
class MakeGeom2Hyperbola : public MakeGeometry
{
public:
	/// @brief Construct from a hyperbola
	/// @param h The hyperbola
	AMCAX_API explicit MakeGeom2Hyperbola(const Hyperbola2& h);

	/// @brief Construct a hyperbola from a major axis, a major radius and a minor radius
	/// @param majorAxis The major axis
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Hyperbola(const Axis2& majorAxis, double majorRadius, double minorRadius, bool sense);

	/// @brief Construct a hyperbola from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	AMCAX_API MakeGeom2Hyperbola(const Frame2& frame, double majorRadius, double minorRadius);

	/// @brief Construct a hyperbola from a point on the major axis, a point on the minor axis and a center point
	/// @param s1 The point on the major axis
	/// @param s2 The point on the minor axis
	/// @param center The center point
	AMCAX_API MakeGeom2Hyperbola(const Point2& s1, const Point2& s2, const Point2& center);

	/// @brief Get the constructed hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2Hyperbola>& Value() const;

	/// @brief Get the constructed hyperbola
	/// @return The hyperbola
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2Hyperbola>&() const;

private:
	std::shared_ptr<Geom2Hyperbola> hyperbola;
};
} // namespace AMCAX
