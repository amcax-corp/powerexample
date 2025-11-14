/// @file      MeshMakeQuadball.hpp
/// @brief     Class of PolyMesh API for make a quadball
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for make a quadball
///        the quadball is a sphere divided into six equal parts, which is equally divided into a quadrilateral
class MeshMakeQuadball
{
public:
	/// @brief Construct from a center and radius
	/// @param center The center of sphere
	/// @param radius The radius of sphere
	/// @param segment The number of segments in each parts, must >= 1
	AMCAX_API MeshMakeQuadball(const Point3& center, const double& radius, size_t segment = 2);

	/// @brief Build and get the result PolyMesh
	AMCAX_API PolyMesh* BuildMesh();

private:
	void MakeQuadBallImp(PolyMesh*& tsp);

private:
	Point3 center_;
	double radius_;
	size_t segment_;
};

} // namespace SubD
} // namespace AMCAX
