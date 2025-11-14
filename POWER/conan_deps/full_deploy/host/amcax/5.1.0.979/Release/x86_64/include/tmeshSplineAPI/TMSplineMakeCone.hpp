/// @file      TMSplineMakeCone.hpp
/// @brief     Class of TMSpline API for make a cone
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of TMSpline API for make a cone
class TMSplineMakeCone
{
public:
	/// @brief Construct from a bottom radius and a height
	/// @param r The bottom radius, must > 0
	/// @param h The height, a reversed TMSpline will be obtained when the h < 0
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API TMSplineMakeCone(double r, double h, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Construct from a local coordinate system, a bottom radius and a height
	/// @param frame The local coordinate system
	/// @param r The bottom radius, must > 0
	/// @param h The height, a reversed TMSpline will be obtained when the h < 0
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API TMSplineMakeCone(Frame3 frame, double r, double h, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Construct from a local coordinate system, a bottom radius, a top radius and a height
	/// @param frame The local coordinate system
	/// @param r1 The bottom radius
	/// @param r2 The top radius
	/// @param h The height
	/// @param isTop Whether keep top faces
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API TMSplineMakeCone(Frame3 frame, double r1, double r2, double h, bool isTop = true, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeConeImp(TMSpline*& tsp);
	void MakeTruncatedConeImp(TMSpline*& tsp);

	Point3 ControlForCone(int su, int sv);

private:
	Frame3 frame_;
	double radius_;
	double rTop_;
	double height_;

	bool is_top_;
	bool is_bottom_;
	size_t segR_, segV_;
};

} // namespace TMS
} // namespace AMCAX
