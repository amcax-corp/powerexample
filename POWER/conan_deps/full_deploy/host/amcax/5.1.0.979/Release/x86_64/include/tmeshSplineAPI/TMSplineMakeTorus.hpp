/// @file      TMSplineMakeTorus.hpp
/// @brief     Class of TMSpline API for make a Torus
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a Torus
class TMSplineMakeTorus
{
public:
	/// @brief Construct from origin, a major radius and a minor radius
	/// @param majorRadius The major radius, must > minorRadius
	/// @param minorRadius The minor radius, must > 0
	/// @param majorSeg The number of segments in major rotation, must >= 4
	/// @param minorSeg The number of segments in minor rotation, must >= 4
	AMCAX_API TMSplineMakeTorus(double majorRadius, double minorRadius, size_t majorSeg = 8, size_t minorSeg = 4);

	/// @brief Construct from frame, a major radius and a minor radius
	/// @param frame The frame
	/// @param majorRadius The major radius, must > minorRadius
	/// @param minorRadius The minor radius, must > 0
	/// @param majorSeg The number of segments in major rotation, must >= 4
	/// @param minorSeg The number of segments in minor rotation, must >= 4
	AMCAX_API TMSplineMakeTorus(const Frame3& frame, double majorRadius, double minorRadius, size_t majorSeg = 8, size_t minorSeg = 4);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeTorusImp(TMSpline*& tsp);

	Point3 ControlForTorus(int su, int sv);

private:
	Frame3 frame_;
	double outerRadius_;
	double innerRadius_;
	size_t segR_, segV_;
};

} // namespace TMS
} // namespace AMCAX
