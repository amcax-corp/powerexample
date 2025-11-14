/// @file      MeshMakeCone.hpp
/// @brief     Class of PolyMesh API for make a cone
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for make a cone
class MeshMakeCone
{
public:
	/// @brief Construct from a bottom radius and a height
	/// @param r The bottom radius
	/// @param h The height
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API MeshMakeCone(double r, double h, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Construct from a local coordinate system, a bottom radius and a height
	/// @param frame The local coordinate system
	/// @param r The bottom radius
	/// @param h The height
	/// @param isBottom Whether keep bottom faces
	/// @param rseg The number of segments in rotation, must >= 4
	/// @param vseg The number of segments in vertical, must >= 2
	AMCAX_API MeshMakeCone(Frame3 frame, double r, double h, bool isBottom = true,
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
	AMCAX_API MeshMakeCone(Frame3 frame, double r1, double r2, double h, bool isTop = true, bool isBottom = true,
		size_t rseg = 8, size_t vseg = 4);

	/// @brief Build and get the result PolyMesh
	AMCAX_API PolyMesh* BuildMesh();

private:
	void MakeConeImp(PolyMesh*& mesh);
	void MakeTruncatedConeImp(PolyMesh*& mesh);

	Point3 ControlForCone(int su, int sv) const;

private:
	Frame3 frame_;
	double radius_;
	double rTop_;
	double height_;

	bool is_top_;
	bool is_bottom_;
	size_t segR_, segV_;
};

} // namespace SubD
} // namespace AMCAX
