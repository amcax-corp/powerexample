/// @file      TMSplineMakeCube.hpp
/// @brief     Class of TMSpline API for make a cube
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for make a cube
class TMSplineMakeCube
{
public:
	/// @brief Construct from two corner points
	/// @param pMin The min corner point
	/// @param pMax The max corner point
	/// @param segX The number of segments in x direction, must >= 1
	/// @param segY The number of segments in y direction, must >= 1
	/// @param segZ The number of segments in z direction, must >= 1
	AMCAX_API TMSplineMakeCube(const Point3& pMin, const Point3& pMax, size_t segX = 2, size_t segY = 2, size_t segZ = 2);

	/// @brief Construct from a corner point and its size
	/// @param p1 The corner point
	/// @param dx The size in x direction, dx <0 indicates reverse x direction
	/// @param dy The size in y direction, dy <0 indicates reverse y direction
	/// @param dz The size in z direction, dz <0 indicates reverse z direction
	/// @param segX The number of segments in x direction, must >= 1
	/// @param segY The number of segments in y direction, must >= 1
	/// @param segZ The number of segments in z direction, must >= 1
	AMCAX_API TMSplineMakeCube(const Point3& p1, double dx, double dy, double dz, size_t segX = 2, size_t segY = 2, size_t segZ = 2);

	/// @brief Construct from a frame and its size
	/// @param frame The frame
	/// @param dx The size in x direction, dx <0 indicates reverse x direction
	/// @param dy The size in y direction, dy <0 indicates reverse y direction
	/// @param dz The size in z direction, dz <0 indicates reverse z direction
	/// @param segX The number of segments in x direction, must >= 1
	/// @param segY The number of segments in y direction, must >= 1
	/// @param segZ The number of segments in z direction, must >= 1
	AMCAX_API TMSplineMakeCube(const Frame3& frame, double dx, double dy, double dz, size_t segX = 2, size_t segY = 2, size_t segZ = 2);

	/// @brief Build and get the result TMSpline
	AMCAX_API TMSpline* BuildSpline();

private:
	void MakeCubeImp(TMSpline*& tsp);

	void MakeCubeOneSeg(TMSpline*& tsp);

private:
	Frame3 frame_;
	double dx_, dy_, dz_;
	size_t segX_, segY_, segZ_;
};

} // namespace TMS
} // namespace AMCAX
