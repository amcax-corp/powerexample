/// @file      MakeArcOfParabola2d.hpp
/// @brief     Class of making arcs of 2D parabola
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <geometry/MakeGeometry.hpp>
#include <math/ParabolaT.hpp>

namespace AMCAX
{
class Geom2TrimmedCurve;

/// @brief Class of making arcs of 2D parabola
class MakeArcOfParabola2d : public MakeGeometry
{
public:
	/// @brief Construct an arc of parabola from a base parabola with the first and last parameters
	/// @param pb The base parabola
	/// @param alpha1 The first parameter
	/// @param alpha2 The last parameter
	/// @param sense Determine whether the orientation preserves the base parabola
	AMCAX_API MakeArcOfParabola2d(const Parabola2& pb, double alpha1, double alpha2, bool sense = true);

	/// @brief Construct an arc of parabola from a base parabola with the first point and the last parameter
	/// @param pb The base parabola
	/// @param p The first point
	/// @param alpha The last parameter
	/// @param sense Determine whether the orientation preserves the base parabola
	AMCAX_API MakeArcOfParabola2d(const Parabola2& pb, const Point2& p, double alpha, bool sense = true);

	/// @brief Construct an arc of parabola from a base parabola with the first and last points
	/// @param pb The base parabola
	/// @param p1 The first point
	/// @param p2 The last point
	/// @param sense Determine whether the orientation preserves the base parabola
	AMCAX_API MakeArcOfParabola2d(const Parabola2& pb, const Point2& p1, const Point2& p2, bool sense = true);

	/// @brief Get the constructed arc of parabola
	/// @return The arc of parabola
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2TrimmedCurve>& Value() const;

	/// @brief Get the constructed arc of parabola
	/// @return The arc of parabola
	[[nodiscard]] AMCAX_API operator const std::shared_ptr<Geom2TrimmedCurve>&() const;

private:
	std::shared_ptr<Geom2TrimmedCurve> arc;
};
} // namespace AMCAX
