/// @file      TMSplineMakeSphere.hpp
/// @brief     Class of TMSpline API for make a sphere
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a sphere
class TMSplineMakeSphere
{
public:
	/// @brief Construct from origin and radius
	/// @param r The radius, must > 0
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API explicit TMSplineMakeSphere(double r, size_t rseg = 8, size_t vseg = 4);

	/// @brief Construct from frame and radius
	/// @param frame The frame
	/// @param r The radius, must > 0
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API TMSplineMakeSphere(Frame3 frame, double r, size_t rseg = 8, size_t vseg = 4);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeSphereImp(TMSpline*& tsp);

	Point3 ControlForSphere(size_t su, size_t sv);
	Point3 ControlForSphereTop();
	Point3 ControlForSphereBootom();
	Point3 ControlForSphereTopExpand(int su);
	Point3 ControlForSphereBootomExpand(int su);

private:
	Frame3 frame_;
	double radius_;
	size_t segR_, segV_;
};

} // namespace TMS
} // namespace AMCAX
