/// @file      TMSplineMakeCircular.hpp
/// @brief     Class of TMSpline API for make a filled circular
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of TMSpline API for make a filled circular
class TMSplineMakeCircular
{
public:
	/// @brief Construct from a radius and a rotation angle
	/// @param r The radius
	/// @param ang The rotation angle in [0 - 2PI]
	/// @param seg The number of segments in rotation, seg > ang / PI
	AMCAX_API TMSplineMakeCircular(double r, double ang, size_t seg = 4);

	/// @brief Construct from a local coordinate system, a radius, a rotation angle
	/// @param frame The local coordinate system
	/// @param r The radius
	/// @param ang The rotation angle in [0 - 2PI]
	/// @param seg The number of segments in rotation, seg > ang / PI
	AMCAX_API TMSplineMakeCircular(const Frame3& frame, double r, double ang, size_t seg = 4);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeCircularCloseImp(TMSpline*& tsp);
	void MakeCircularOpenImp(TMSpline*& tsp);

private:
	Frame3 frame_;
	double radius_;
	double angle_;
	size_t seg_;
};

} // namespace TMS
} // namespace AMCAX
