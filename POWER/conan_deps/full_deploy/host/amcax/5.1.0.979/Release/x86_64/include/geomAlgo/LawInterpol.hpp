/// @file      LawInterpol.hpp
/// @brief     Class of interpolated B spline law function
/// @details   This class defines the B spline law function from interpolating points.
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <geomAlgo/LawBSplineFunction.hpp>

namespace AMCAX
{
/// @brief Class of B spline function built by interpolation
class AMCAX_CLASS_API LawInterpol : public LawBSplineFunction
{
public:
	/// @brief Build the BSpline function by interpolation
	/// @param paraAndRadius The data points to be interpolated
	/// @param periodic If the function is periodic
	AMCAX_API void Set(const std::vector<Point2>& paraAndRadius, bool periodic = false);

	/// @brief Build the BSpline function by interpolation
	/// @param paraAndRadius The data points to be interpolated
	/// @param df The first derivative at the first point
	/// @param dl The first derivative at the last point
	/// @param periodic If the function is periodic
	AMCAX_API void Set(const std::vector<Point2>& paraAndRadius, double df, double dl, bool periodic = false);
};
} // namespace AMCAX
