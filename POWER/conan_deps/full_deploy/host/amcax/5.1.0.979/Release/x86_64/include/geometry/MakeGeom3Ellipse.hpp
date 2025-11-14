/// @file      MakeGeom3Ellipse.hpp
/// @brief     Class of making 3D geometric ellipses
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Ellipse.hpp>
#include <geometry/MakeGeometry.hpp>

namespace AMCAX
{
/// @brief Class of making 3D geometric ellipses
class MakeGeom3Ellipse : public MakeGeometry
{
public:
	/// @brief Construct from an ellipse
	/// @param e The ellipse
	AMCAX_API explicit MakeGeom3Ellipse(const Ellipse3& e);

	/// @brief Construct an ellipse from a local frame, a major radius and a minor radius
	/// @param frame The local frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	AMCAX_API MakeGeom3Ellipse(const Frame3& frame, double majorRadius, double minorRadius);

	/// @brief Construct an ellipse from two points on the major and minor axis, and a center point
	/// @param s1 The point on the major axis
	/// @param s2 The point on the minor axis
	/// @param center The center point
	AMCAX_API MakeGeom3Ellipse(const Point3& s1, const Point3& s2, const Point3& center);

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3Ellipse>& Value() const;

	/// @brief Get the constructed ellipse
	/// @return The ellipse
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3Ellipse>&() const;

private:
	std::shared_ptr<Geom3Ellipse> ellipse;
};
} // namespace AMCAX
