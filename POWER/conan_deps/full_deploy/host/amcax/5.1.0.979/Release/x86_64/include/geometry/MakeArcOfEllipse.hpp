/// @file      MakeArcOfEllipse.hpp
/// @brief     Class of making arcs of 3D ellipse
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/MakeGeometry.hpp>
#include <math/EllipseT.hpp>

namespace AMCAX
{
class Geom3TrimmedCurve;

/// @brief Class of making arcs of 3D ellipse
class MakeArcOfEllipse : public MakeGeometry
{
public:
	/// @brief Construct an arc of ellipse from a base ellipse with the first and last parameters
	/// @param e The base ellipse
	/// @param alpha1 The first parameter
	/// @param alpha2 The last parameter
	/// @param sense Determine whether the orientation preserves the base ellipse
	AMCAX_API MakeArcOfEllipse(const Ellipse3& e, double alpha1, double alpha2, bool sense);

	/// @brief Construct an arc of ellipse from a base ellipse with the first point and the last parameter
	/// @param e The base ellipse
	/// @param p The first point
	/// @param alpha The last parameter
	/// @param sense Determine whether the orientation preserves the base ellipse
	AMCAX_API MakeArcOfEllipse(const Ellipse3& e, const Point3& p, double alpha, bool sense);

	/// @brief Construct an arc of ellipse from a base ellipse with the first and last points
	/// @param e The base ellipse
	/// @param p1 The first point
	/// @param p2 The last point
	/// @param sense Determine whether the orientation preserves the base ellipse
	AMCAX_API MakeArcOfEllipse(const Ellipse3& e, const Point3& p1, const Point3& p2, bool sense);

	/// @brief Get the constructed arc of ellipse
	/// @return The arc of ellipse
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3TrimmedCurve>& Value() const;

	/// @brief Get the constructed arc of ellipse
	/// @return The arc of ellipse
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3TrimmedCurve>&() const;

private:
	std::shared_ptr<Geom3TrimmedCurve> arc;
};
} // namespace AMCAX
