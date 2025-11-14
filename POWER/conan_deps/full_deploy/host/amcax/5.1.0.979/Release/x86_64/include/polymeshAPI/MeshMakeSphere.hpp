/// @file      MeshMakeSphere.hpp
/// @brief     Class of PolyMesh API for make a sphere
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for make a sphere
class MeshMakeSphere
{
public:
	/// @brief Construct from origin and radius
	/// @param r The radius
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API explicit MeshMakeSphere(double r, size_t rseg = 8, size_t vseg = 4);

	/// @brief Construct from frame and radius
	/// @param frame The frame
	/// @param r The radius
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API MeshMakeSphere(Frame3 frame, double r, size_t rseg = 8, size_t vseg = 4);

	/// @brief Build and get the result PolyMesh
	AMCAX_API PolyMesh* BuildMesh();

private:
	void MakeSphereImp(PolyMesh*& mesh);

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

} // namespace SubD
} // namespace AMCAX
