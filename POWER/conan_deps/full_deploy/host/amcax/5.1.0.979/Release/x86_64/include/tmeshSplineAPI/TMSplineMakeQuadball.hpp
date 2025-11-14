/// @file      TMSplineMakeQuadball.hpp
/// @brief     Class of TMSpline API for make a quadball
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a quadball
///        the quadball is a sphere divided into six equal parts, which is equally divided into a quadrilateral
class TMSplineMakeQuadball
{
public:
	/// @brief Construct from a center and radius
	/// @param center The center of sphere
	/// @param radius The radius of sphere, must > 0
	/// @param segment The number of segments in each parts, must >= 1
	AMCAX_API TMSplineMakeQuadball(const Point3& center, const double& radius, size_t segment = 2);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeQuadBallImp(TMSpline*& tsp);

private:
	Point3 center_;
	double radius_;

	size_t segment_;
};

} // namespace TMS
} // namespace AMCAX
