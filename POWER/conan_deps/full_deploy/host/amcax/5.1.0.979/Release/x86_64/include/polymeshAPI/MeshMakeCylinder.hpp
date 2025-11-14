/// @file      MeshMakeCylinder.hpp
/// @brief     Class of PolyMesh API for make a cylinder
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for make a cylinder
class MeshMakeCylinder
{
public:
	/// @brief Construct from a radius and a height
	/// @param r The radius
	/// @param h The height
	/// @param isTop Whether keep top faces
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API MeshMakeCylinder(double r, double h, bool isTop = true, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Construct from a frame, radius and a height
	/// @param frmae The frame
	/// @param r The radius
	/// @param h The height
	/// @param isTop Whether keep top faces
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API MeshMakeCylinder(Frame3 frmae, double r, double h, bool isTop = true, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Build and get the result PolyMesh
	AMCAX_API PolyMesh* BuildMesh();

private:
	void MakeCylinderImp(PolyMesh*& mesh);

	Point3 ControlForCylinder(int su, int sv) const;

private:
	Frame3 frame_;
	double radius_;
	double height_;

	bool is_top_, is_bottom_;
	size_t segR_, segV_;
};

} // namespace SubD
} // namespace AMCAX
