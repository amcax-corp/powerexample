/// @file      MeshMakeTorus.hpp
/// @brief     Class of PolyMesh API for make a Torus
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>
#include <common/FrameT.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for make a Torus
class MeshMakeTorus
{
public:
	/// @brief Construct from origin, a major radius and a minor radius
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param majorSeg The number of segments in major rotation, must >= 4
	/// @param minorSeg The number of segments in minor rotation, must >= 4
	AMCAX_API MeshMakeTorus(double majorRadius, double minorRadius, size_t majorSeg = 8, size_t minorSeg = 4);

	/// @brief Construct from frame, a major radius and a minor radius
	/// @param frame The frame
	/// @param majorRadius The major radius
	/// @param minorRadius The minor radius
	/// @param majorSeg The number of segments in major rotation, must >= 4
	/// @param minorSeg The number of segments in minor rotation, must >= 4
	AMCAX_API MeshMakeTorus(const Frame3& frame, double majorRadius, double minorRadius, size_t majorSeg = 8, size_t minorSeg = 4);

	/// @brief Build and get the result PolyMesh
	AMCAX_API PolyMesh* BuildMesh();

private:
	void MakeTorusImp(PolyMesh*& mesh);

	Point3 ControlForTorus(int su, int sv) const;

private:
	Frame3 frame_;
	double outerRadius_;
	double innerRadius_;
	size_t segR_, segV_;
};

} // namespace SubD
} // namespace AMCAX
