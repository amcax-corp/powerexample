/// @file      GeomAPIPointsToBSplineSurface.hpp
/// @brief     Class of computing a B spline surface approximating points
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <approx/ApproxParameterizationType.hpp>
#include <common/Array2.hpp>
#include <common/PointT.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class Geom3BSplineSurface;

/// @brief Class of computing a B spline surface approximating points
class GeomAPIPointsToBSplineSurface
{
public:
	/// @brief Default constructor
	GeomAPIPointsToBSplineSurface() noexcept = default;

	/// @brief Construct from points
	/// @param points The points
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API explicit GeomAPIPointsToBSplineSurface(const Array2<Point3>& points, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Construct from points and a specified approximation parameterization type
	/// @param points The points
	/// @param parType The type of parameterization used in approximation
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API GeomAPIPointsToBSplineSurface(const Array2<Point3>& points, ApproxParameterizationType parType, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Construct from a points and three weights
	/// @details The algorithm tries to find a result minimizing weight1 * length + weight2 * curvature + weight3 * torsion
	/// @param points The points
	/// @param weight1 The weight of length
	/// @param weight2 The weight of curvature
	/// @param weight3 The weight of torsion
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API GeomAPIPointsToBSplineSurface(const Array2<Point3>& points, double weight1, double weight2, double weight3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Construct from points of constant incremental x and y coordinates
	/// @param zPoints The z coordinates of points
	/// @param x0 The x coordinate of the first point
	/// @param dx The incremental value of x coordinate
	/// @param y0 The y coordinate of the first point
	/// @param dy The incremental value of y coordinate
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API GeomAPIPointsToBSplineSurface(const Array2<double>& zPoints, double x0, double dx, double y0, double dy, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Initialize and construct from points
	/// @param points The points
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const Array2<Point3>& points, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Interpolate the points
	/// @param points The points to be interpolated
	/// @param periodic Whether the surface is periodic
	AMCAX_API void Interpolate(const Array2<Point3>& points, bool periodic = false);

	/// @brief Interpolate the points with a specified approximation parameterization type
	/// @param points The points to be interpolated
	/// @param parType The type of parameterization used in approximation
	/// @param periodic Whether the surface is periodic
	AMCAX_API void Interpolate(const Array2<Point3>& points, ApproxParameterizationType parType, bool periodic = false);

	/// @brief Initialize and construct from points of constant incremental x and y coordinates
	/// @param zPoints The z coordinates of points
	/// @param x0 The x coordinate of the first point
	/// @param dx The incremental value of x coordinate
	/// @param y0 The y coordinate of the first point
	/// @param dy The incremental value of y coordinate
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const Array2<double>& zPoints, double x0, double dx, double y0, double dy, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Interpolate the points of constant incremental x and y coordinates
	/// @param zPoints The z coordinates of points
	/// @param x0 The x coordinate of the first point
	/// @param dx The incremental value of x coordinate
	/// @param y0 The y coordinate of the first point
	/// @param dy The incremental value of y coordinate
	AMCAX_API void Interpolate(const Array2<double>& zPoints, double x0, double dx, double y0, double dy);

	/// @brief Initialize and construct from points and a specified approximation parameterization type
	/// @param points The points
	/// @param parType The type of parameterization used in approximation
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	/// @param periodic Whether the surface is periodic
	AMCAX_API void Init(const Array2<Point3>& points, ApproxParameterizationType parType, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3, bool periodic = false);

	/// @brief Initialize and construct from a points and three weights
	/// @details The algorithm tries to find a result minimizing weight1 * length + weight2 * curvature + weight3 * torsion
	/// @param points The points
	/// @param weight1 The weight of length
	/// @param weight2 The weight of curvature
	/// @param weight3 The weight of torsion
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const Array2<Point3>& points, double weight1, double weight2, double weight3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Get the resulting surface
	/// @return The resulting surface
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom3BSplineSurface>& Surface() const;

	/// @brief Get the resulting surface
	/// @return The resulting surface
	[[nodiscard]] AMCAX_API operator std::shared_ptr<Geom3BSplineSurface>() const;

	/// @brief Is the algorithm done
	/// @return True if the approximation is successful
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

private:
	bool isDone = false;
	std::shared_ptr<Geom3BSplineSurface> surface;
};
} // namespace AMCAX
