/// @file      TMSplineMakeDonut.hpp
/// @brief     Class of TMSpline API for make a dount
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a donut
class TMSplineMakeDonut
{
public:
	/// @brief Construct from outer radius and inner radius,
	/// @param outRadius The outer radius, must > 0
	/// @param inRadius The inner radius, must > 0
	/// @param angle The rotation angle in [0 - 2PI]
	/// @param seg The number of segments in rotation, seg > angle / PI
	AMCAX_API TMSplineMakeDonut(double outRadius, double inRadius, double angle = Constants::two_pi, size_t seg = 4);

	/// @brief Construct from frame, outer radius and inner radius,
	/// @param frame The frame
	/// @param outRadius The outer radius, must > 0
	/// @param inRadius The inner radius, must > 0
	/// @param angle The rotation angle in [0 - 2PI]
	/// @param seg The number of segments in rotation, seg > angle / PI
	AMCAX_API TMSplineMakeDonut(const Frame3& frame, double outRadius, double inRadius, double angle = Constants::two_pi, size_t seg = 4);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

public:
	void MakeDonutCloseImp(TMSpline*& tsp);

	void MakeDonutOpenImp(TMSpline*& tsp);

private:
	Frame3 frame_;
	double outerRadius_;
	double innerRadius_;
	double angle_;
	size_t seg_;
};

} // namespace TMS
} // namespace AMCAX
