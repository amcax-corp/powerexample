/// @file      GeomAPIPointsToBSpline2.hpp
/// @brief     Class of computing a 2D B spline curve approximating 2D points
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <approx/ApproxParameterizationType.hpp>
#include <common/PointT.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class Geom2BSplineCurve;

/// @brief Class of computing a 2D B spline curve approximating 2D points
class GeomAPIPointsToBSpline2
{
public:
	/// @brief Default constructor
	GeomAPIPointsToBSpline2() noexcept = default;

	/// @brief Construct from points
	/// @param points The points
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API explicit GeomAPIPointsToBSpline2(const std::vector<Point2>& points, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-6);

	/// @brief Construct from points of constant incremental x coordinates
	/// @param yValues The y coordinates of points
	/// @param x0 The x coordinate of the first point
	/// @param dx The incremental value of x coordinate
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API GeomAPIPointsToBSpline2(const std::vector<double>& yValues, double x0, double dx, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-6);

	/// @brief Construct from points and a specified approximation parameterization type
	/// @param points The points
	/// @param parType The type of parameterization used in approximation
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API GeomAPIPointsToBSpline2(const std::vector<Point2>& points, ApproxParameterizationType parType, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Construct from points and parameters
	/// @param points The points
	/// @param parameters The parameters
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API GeomAPIPointsToBSpline2(const std::vector<Point2>& points, const std::vector<double>& parameters, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Construct from a points and three weights
	/// @details The algorithm tries to find a result minimizing weight1 * length + weight2 * curvature + weight3 * torsion
	/// @param points The points
	/// @param weight1 The weight of length
	/// @param weight2 The weight of curvature
	/// @param weight3 The weight of torsion
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API GeomAPIPointsToBSpline2(const std::vector<Point2>& points, double weight1, double weight2, double weight3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Initialize and construct from points
	/// @param points The points
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const std::vector<Point2>& points, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-6);

	/// @brief Initialize and construct from points of constant incremental x coordinates
	/// @param yValues The y coordinates of points
	/// @param x0 The x coordinate of the first point
	/// @param dx The incremental value of x coordinate
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const std::vector<double>& yValues, double x0, double dx, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-6);

	/// @brief Initialize and construct from points and a specified approximation parameterization type
	/// @param points The points
	/// @param parType The type of parameterization used in approximation
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const std::vector<Point2>& points, ApproxParameterizationType parType, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Initialize and construct from points and parameters
	/// @param points The points
	/// @param parameters The parameters
	/// @param degMin The minimal degree of B spline curve
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const std::vector<Point2>& points, const std::vector<double>& parameters, int degMin = 3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Initialize and construct from a points and three weights
	/// @details The algorithm tries to find a result minimizing weight1 * length + weight2 * curvature + weight3 * torsion
	/// @param points The points
	/// @param weight1 The weight of length
	/// @param weight2 The weight of curvature
	/// @param weight3 The weight of torsion
	/// @param degMax The maximal degree of B spline curve
	/// @param continuity The continuity type
	/// @param tol The computing tolerance
	AMCAX_API void Init(const std::vector<Point2>& points, double weight1, double weight2, double weight3, int degMax = 8, ContinuityType continuity = ContinuityType::C2, double tol = 1e-3);

	/// @brief Get the resulting curve
	/// @return The resulting curve
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2BSplineCurve>& Curve() const;

	/// @brief Get the resulting curve
	/// @return The resulting curve
	[[nodiscard]] AMCAX_API operator std::shared_ptr<Geom2BSplineCurve>() const noexcept;

	/// @brief Is the algorithm done
	/// @return True if the approximation is successful
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

private:
	bool isDone = false;
	std::shared_ptr<Geom2BSplineCurve> curve;
};
} // namespace AMCAX
