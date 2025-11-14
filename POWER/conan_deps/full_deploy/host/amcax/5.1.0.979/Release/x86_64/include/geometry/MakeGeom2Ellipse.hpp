/// @file      MakeGeom2Ellipse.hpp
/// @brief     Class of making 2D geometric ellipses
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom2Ellipse.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 2D geometric ellipses
class MakeGeom2Ellipse : public MakeGeometry
{
public:
	/// @brief Construct from an ellipse
	/// @param e The ellipse
	AMCAX_API explicit MakeGeom2Ellipse(const Ellipse2& e);

	/// @brief Construct an ellipse from a major axis, a major radius and a minor radius
	/// @param majorAxis The major axis
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param sense Determine whether the local frame is right-handed
	AMCAX_API MakeGeom2Ellipse(const Axis2& majorAxis, double majorRadius, double minorRadius, bool sense = true);

	/// @brief Construct an ellipse from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	AMCAX_API MakeGeom2Ellipse(const Frame2& frame, double majorRadius, double minorRadius);

	/// @brief Construct an ellipse from two points on the major and minor axis, and a center point
	/// @param s1 The point on the major axis
	/// @param s2 The point on the minor axis
	/// @param center The center point
	AMCAX_API MakeGeom2Ellipse(const Point2& s1, const Point2& s2, const Point2& center);

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2Ellipse>& Value() const;

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2Ellipse>&() const;

private:
	std::shared_ptr<Geom2Ellipse> ellipse;
};
} // namespace AMCAX
