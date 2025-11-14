/// @file      GeomAPIInterpolate2.hpp
/// @brief     Class of computing a curve interpolating 2D points
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/PointT.hpp>
#include <common/VectorT.hpp>

namespace AMCAX
{
class Geom2BSplineCurve;

/// @brief Class of computing a curve interpolating 2D points
class GeomAPIInterpolate2
{
public:
	/// @brief Construct from points
	/// @param points The points
	/// @param periodic Whether constructing a periodic curve
	/// @param tolerance The computing tolerance
	AMCAX_API GeomAPIInterpolate2(const std::vector<Point2>& points, bool periodic, double tolerance);

	/// @brief Construct from points and parameters
	/// @param points The points
	/// @param parameters The parameters
	/// @param periodic Whether constructing a periodic curve
	/// @param tolerance The computing tolerance
	AMCAX_API GeomAPIInterpolate2(const std::vector<Point2>& points, const std::vector<double>& parameters, bool periodic, double tolerance);

	/// @brief Load the tangent vector at the start and end point as constraints
	/// @param initialTangent The tangent vector at the start point
	/// @param finalTangent The tangent vector at the end point
	/// @param scale Whether the tangent is to be scaled
	AMCAX_API void Load(const Vector2& initialTangent, const Vector2& finalTangent, bool scale = true);

	/// @brief Load the tangent vector at each point as constraints
	/// @param tangents The tangent vectors
	/// @param tangentFlags The tangent flags, only the points with true flag have tangent vector constaints
	/// @param scale Whether the tangent is to be scaled
	AMCAX_API void Load(const std::vector<Vector2>& tangents, const std::vector<bool>& tangentFlags, bool scale = true);

	/// @brief Perform the algorithm
	AMCAX_API void Perform();

	/// @brief Get the interpolation curve
	/// @return The interpolation curve
	[[nodiscard]] AMCAX_API const std::shared_ptr<Geom2BSplineCurve>& Curve() const;

	/// @brief Get the interpolation curve
	/// @return The interpolation curve
	[[nodiscard]] AMCAX_API operator std::shared_ptr<Geom2BSplineCurve>() const noexcept;

	/// @brief Is the algorithm done
	/// @return True if the algorithm is successful
	[[nodiscard]] AMCAX_API bool IsDone() const noexcept;

private:
	void PerformNonPeriodic();
	void PerformPeriodic();

	double tolerance;
	std::shared_ptr<Geom2BSplineCurve> curve;
	const std::vector<Point2>* points;
	std::vector<Vector2> tangents;
	std::vector<bool> tangentFlags;
	std::vector<double> parameters;
	bool isDone = false;
	bool periodic;
	bool tangentRequest = false;
};
} // namespace AMCAX
