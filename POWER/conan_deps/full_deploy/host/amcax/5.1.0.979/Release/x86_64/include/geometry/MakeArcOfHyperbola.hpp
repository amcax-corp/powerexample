/// @file      MakeArcOfHyperbola.hpp
/// @brief     Class of making arcs of 3D hyperbola
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/MakeGeometry.hpp>
#include <math/HyperbolaT.hpp>

namespace AMCAX
{
class Geom3TrimmedCurve;

/// @brief Class of making arcs of 3D hyperbola
class MakeArcOfHyperbola : public MakeGeometry
{
public:
	/// @brief Construct an arc of hyperbola from a base hyperbola with the first and last parameters
	/// @param h The base hyperbola
	/// @param alpha1 The first parameter
	/// @param alpha2 The last parameter
	/// @param sense Determine whether the orientation preserves the base hyperbola
	AMCAX_API MakeArcOfHyperbola(const Hyperbola3& h, double alpha1, double alpha2, bool sense);

	/// @brief Construct an arc of hyperbola from a base hyperbola with the first point and the last parameter
	/// @param h The base hyperbola
	/// @param p The first point
	/// @param alpha The last parameter
	/// @param sense Determine whether the orientation preserves the base hyperbola
	AMCAX_API MakeArcOfHyperbola(const Hyperbola3& h, const Point3& p, double alpha, bool sense);

	/// @brief Construct an arc of hyperbola from a base hyperbola with the first and last points
	/// @param h The base hyperbola
	/// @param p1 The first point
	/// @param p2 The last point
	/// @param sense Determine whether the orientation preserves the base hyperbola
	AMCAX_API MakeArcOfHyperbola(const Hyperbola3& h, const Point3& p1, const Point3& p2, bool sense);

	/// @brief Get the constructed arc of hyperbola
	/// @return The arc of hyperbola
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3TrimmedCurve>& Value() const;

	/// @brief Get the constructed arc of hyperbola
	/// @return The arc of hyperbola
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom3TrimmedCurve>&() const;

private:
	std::shared_ptr<Geom3TrimmedCurve> arc;
};
} // namespace AMCAX
