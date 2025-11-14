/// @file      LawS.hpp
/// @brief     Class of the "S" shape law function
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geomAlgo/LawBSplineFunction.hpp>

namespace AMCAX
{
/// @brief Class of the "S" shape law function
class AMCAX_CLASS_API LawS : public LawBSplineFunction
{
public:
	/// @brief Set the "S" shape with two points, the derivatives of the points are set zero
	/// @param paraFirst The parameter of the first point
	/// @param valueFirst The value of the first point
	/// @param paraLast The parameter of the second point
	/// @param valueLast The value of the second point
	AMCAX_API void Set(double paraFirst, double valueFirst, double paraLast, double valueLast);

	/// @brief Set the "S" shape with two points and the derivatives of the points
	/// @param paraFirst The parameter of the first point
	/// @param valueFirst The value of the first point
	/// @param ddeb The derivative of the first point
	/// @param paraLast The parameter of the second point
	/// @param valueLast The value of the second point
	/// @param dfin The derivative of the second point
	AMCAX_API void Set(double paraFirst, double valueFirst, double ddeb, double paraLast, double valueLast, double dfin);
};
} // namespace AMCAX
