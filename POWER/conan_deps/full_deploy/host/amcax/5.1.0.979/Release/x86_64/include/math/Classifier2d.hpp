/// @file      Classifier2d.hpp
/// @brief     Class of 2d classification
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/PointT.hpp>

namespace AMCAX
{
/// @brief Class of low-level 2d classification
class Classifier2d
{
public:
	/// @brief Construct from a 2D polygon and uv-bounds
	/// @details Require uMax > uMin, vMax > vMin, and at least 3 points
	/// @param pts The points of a 2D closed polygon, the last point does not required to repeat the first point
	/// @param tolU The tolerance of u bound
	/// @param tolV The tolerance of v bound
	/// @param uMin The lower bound of u
	/// @param vMin The lower bound of v
	/// @param uMax The upper bound of u
	/// @param vMax The upper bound of v
	AMCAX_API Classifier2d(const std::vector<Point2>& pts, double tolU, double tolV, double uMin, double vMin, double uMax, double vMax);

	/// @brief Check a point is in/on/out of the polygon
	/// @param p The test point
	/// @return 1: in; 0: on; -1: out
	[[nodiscard]] AMCAX_API int IsInOut(const Point2& p) const noexcept;

	/// @brief Check a point is in/on/out of the polygon
	/// @param p The test point
	/// @param tol The tolerance of the point
	/// @return 1: in; 0: on; -1: out
	[[nodiscard]] AMCAX_API int IsInOutOn(const Point2& p, double tol) const noexcept;

private:
	int InternalInOut(double x, double y) const noexcept;
	int InternalInOutOn(double x, double y) const noexcept;
	std::vector<double> ptsX, ptsY;
	double umin;
	double vmin;
	double umax;
	double vmax;
	double tolu;
	double tolv;
	int n;
};
} // namespace AMCAX
