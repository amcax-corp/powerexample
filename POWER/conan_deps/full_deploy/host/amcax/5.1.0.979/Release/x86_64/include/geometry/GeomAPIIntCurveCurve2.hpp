/// @file      GeomAPIIntCurveCurve2.hpp
/// @brief     Class of computing intersection points for two 2D curves
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/PointT.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom2Curve;
class IntRes2Intersection;
#endif

/// @brief Class of computing intersection points for two 2D curves
class GeomAPIIntCurveCurve2
{
public:
	/// @brief Construct from two curves
	/// @param c1 The first curve
	/// @param c2 The second curve
	/// @param tol The tolerance for computing intersection
	AMCAX_API GeomAPIIntCurveCurve2(const std::shared_ptr<Geom2Curve>& c1, const std::shared_ptr<Geom2Curve>& c2, double tol = 1.0e-6);

	/// @brief Construct from one curve for finding self-intersections
	/// @param c1 The curve
	/// @param tol The tolerance for computing self-intersection
	AMCAX_API explicit GeomAPIIntCurveCurve2(const std::shared_ptr<Geom2Curve>& c1, double tol = 1.0e-6);

	/// @brief Get the number of intersection points
	/// @return The number of intersection points
	[[nodiscard]] AMCAX_API int NPoints() const;

	/// @brief Get the intersection point at a given index
	/// @param index The index
	/// @return The intersection point
	[[nodiscard]] AMCAX_API Point2 Point(int index) const;

	/// @brief Get the parameter of intersection point on the first curve at a given index
	/// @param index The index
	/// @return The parameter of intersection point on the first curve
	[[nodiscard]] AMCAX_API double ParamOnCurve1(int index) const;

	/// @brief Get the parameter of intersection point on the second curve at a given index
	/// @param index The index
	/// @return The parameter of intersection point on the second curve
	[[nodiscard]] AMCAX_API double ParamOnCurve2(int index) const;

	/// @brief Get the number of intersection segments
	/// @return The number of intersection segments
	[[nodiscard]] AMCAX_API int NSegments() const;

	/// @brief Get the intersection segments at a given index
	/// @param[in] index The index
	/// @param[out] paramOnCurve1 The first and last parameters of the intersection segment on the first curve
	/// @param[out] paramOnCurve2 The first and last parameters of the intersection segment on the second curve
	AMCAX_API void Segment(int index, std::pair<double, double>& paramOnCurve1, std::pair<double, double>& paramOnCurve2) const;

private:
	bool isDone = false;
	std::shared_ptr<IntRes2Intersection> intersector;
};
} // namespace AMCAX
