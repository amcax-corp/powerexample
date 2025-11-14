/// @file      MeshReduce.hpp
/// @brief     Class of PolyMesh API for Reduce a Mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for Reduce a Mesh
class MeshReduce
{
public:
	/// @brief Delete given faces in PolyMesh
	/// @param mesh a PolyMesh
	/// @param flist indices of the faces to be delete
	AMCAX_API static void DeleteFaces(PolyMesh* mesh, const std::vector<int>& flist);

	/// @brief Delete all isolated vertices in PolyMesh
	/// @param mesh a PolyMesh
	AMCAX_API static void DeleteIsolatedVertices(PolyMesh* mesh);
};
} // namespace SubD
} // namespace AMCAX
