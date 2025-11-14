/// @file      MeshMakeCube.hpp
/// @brief     Class of PolyMesh API for make a cube
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for make a cube
class MeshMakeCube
{
public:
	/// @brief Construct from two corner points
	/// @param pMin The min corner point
	/// @param pMax The max corner point
	/// @param segX The number of segments in x direction, must >= 1
	/// @param segY The number of segments in y direction, must >= 1
	/// @param segZ The number of segments in z direction, must >= 1
	AMCAX_API MeshMakeCube(const Point3& pMin, const Point3& pMax, size_t segX = 2, size_t segY = 2, size_t segZ = 2);

	/// @brief Construct from a corner point and its size
	/// @param p1 The corner point
	/// @param dx The size in x direction, must > 0.0
	/// @param dy The size in y direction, must > 0.0
	/// @param dz The size in z direction, must > 0.0
	/// @param segX The number of segments in x direction, must >= 1
	/// @param segY The number of segments in y direction, must >= 1
	/// @param segZ The number of segments in z direction, must >= 1
	AMCAX_API MeshMakeCube(const Point3& p1, double dx, double dy, double dz, size_t segX = 2, size_t segY = 2, size_t segZ = 2);

	/// @brief Construct from a frame and its size
	/// @param frame The frame
	/// @param dx The size in x direction, must > 0.0
	/// @param dy The size in y direction, must > 0.0
	/// @param dz The size in z direction, must > 0.0
	/// @param segX The number of segments in x direction, must >= 1
	/// @param segY The number of segments in y direction, must >= 1
	/// @param segZ The number of segments in z direction, must >= 1
	AMCAX_API MeshMakeCube(const Frame3& frame, double dx, double dy, double dz, size_t segX = 2, size_t segY = 2, size_t segZ = 2);

	/// @brief Build and get the result PolyMesh
	AMCAX_API PolyMesh* BuildMesh();

private:
	void MakeCubeImp(PolyMesh*& mesh);

	void MakeCubeOneSeg(PolyMesh*& mesh);

private:
	Frame3 frame_;
	double dx_, dy_, dz_;
	size_t segX_, segY_, segZ_;
};

} // namespace SubD
} // namespace AMCAX
