/// @file      TMSplineMakeCylinder.hpp
/// @brief     Class of TMSpline API for make a cylinder
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a cylinder
class TMSplineMakeCylinder
{
public:
	/// @brief Construct from a radius and a height
	/// @param r The radius, must > 0
	/// @param h The height, a reversed TMSpline will be obtained when the h < 0
	/// @param isTop Whether keep top faces
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API TMSplineMakeCylinder(double r, double h, bool isTop = true, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Construct from a frame, radius and a height
	/// @param frame The frame
	/// @param r The radius, must > 0
	/// @param h The height, a reversed TMSpline will be obtained when the h < 0
	/// @param isTop Whether keep top faces
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API TMSplineMakeCylinder(Frame3 frame, double r, double h, bool isTop = true, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeCylinderImp(TMSpline*& tsp);

	Point3 ControlForCylinder(int su, int sv);

private:
	Frame3 frame_;
	double radius_;
	double height_;

	bool is_top_, is_bottom_;
	size_t segR_, segV_;
};

} // namespace TMS
} // namespace AMCAX
