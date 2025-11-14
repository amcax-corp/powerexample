/// @file      MeshSubdivideRender.hpp
/// @brief     Class of PolyMesh API for mesh subdividion,
///	only supports generating unstructured subdivision meshes using full triangle or full quadrilateral meshes.
///	Compared to methods based on half edge structures, the performance is better.	
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.

#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for quadrilateral mesh Catmull-Clark subdivision
class MeshSubdivideRenderCC
{
public:
	/// @brief Default constructor
	MeshSubdivideRenderCC() = default;

	/// @brief Do Catmull-Clark subdivision
	/// @param mesh The input quadrilateral mesh 
	/// @param subtime The number of subdivision
	/// @return Thue if the subdivide is successful
	AMCAX_API bool DoCatmullClark(PolyMesh* mesh, size_t subtime);

	/// @brief Get result Position
	/// @return Position vector
	const std::vector<Point3>& Points() const
	{
		return mPoints;
	}

	/// @brief Get result faces
	/// @return Faces vecotr
	const std::vector<std::array<int, 4>>& Faces() const
	{
		return mFaces;
	}

private:
	std::vector<Point3> mPoints;
	std::vector<std::array<int, 4>> mFaces;

};

/// @brief Class of PolyMesh API for triangle mesh Loop subdividion
class MeshSubdivideRenderLoop
{
public:
	/// @brief Default constructor
	MeshSubdivideRenderLoop() = default;

	/// @brief Do Loop subdivision
	/// @param mesh The input triangle mesh 
	/// @param subtime The number of subdivision
	/// @return Thue if the subdivide is successful
	AMCAX_API bool DoLoop(PolyMesh* mesh, size_t subtime);

	/// @brief Get result Position
	/// @return Position vector
	const std::vector<Point3>& Points() const
	{
		return mPoints;
	}

	/// @brief Get result faces
	/// @return Faces vecotr
	const std::vector<std::array<int, 3>>& Faces() const
	{
		return mFaces;
	}

private:
	std::vector<Point3> mPoints;
	std::vector<std::array<int, 3>> mFaces;
};

} // namespace SubD
} // namespace AMCAX