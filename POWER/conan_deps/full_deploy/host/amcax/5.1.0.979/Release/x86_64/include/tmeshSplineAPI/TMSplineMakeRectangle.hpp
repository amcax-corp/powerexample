/// @file      TMSplineMakeRectangle.hpp
/// @brief     Class of TMSpline API for make a plane rectangle
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a plane rectangle
class TMSplineMakeRectangle
{
public:
	/// @brief Construct  a rectangle from [0, 1] x [0, 1];
	AMCAX_API TMSplineMakeRectangle();

	/// @brief Construct from tow corner points
	/// @param p0 The min corner point
	/// @param p1 The max corner point
	/// @param useg The number of segments in x direction
	/// @param vseg The number of segments in y direction
	AMCAX_API TMSplineMakeRectangle(const Point2& p0, const Point2& p1, size_t useg = 2, size_t vseg = 2);

	/// @brief Construct from a frame xy plane and its size
	/// @param frame The frame
	/// @param dx The size in x direction
	/// @param dy The size in y direction
	/// @param useg The number of segments in x direction
	/// @param vseg The number of segments in y direction
	AMCAX_API TMSplineMakeRectangle(const Frame3& frame, double dx, double dy, size_t useg = 2, size_t vseg = 2);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeRectangleImp(TMSpline*& tsp_);

private:
	Frame3 frame_;
	double dx_, dy_;
	size_t segU_, segV_;
};

} // namespace TMS
} // namespace AMCAX
