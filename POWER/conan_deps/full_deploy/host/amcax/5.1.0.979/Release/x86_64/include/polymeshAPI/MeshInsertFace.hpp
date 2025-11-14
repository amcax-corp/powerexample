/// @file      MeshInsertFace.hpp
/// @brief     Class of PolyMesh API for Adding faces
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
class MeshInsertFace
{
public:
	/// @brief add a single face constructed from points to PolyMesh
	/// @param mesh the PolyMesh
	/// @param points the points for constructing face
	/// @return the result face
	AMCAX_API static MPolyFace* AddSingleFace(PolyMesh* mesh, const std::vector<Point3>& points);

	/// @brief add a single face constructed from some PolyMesh vert
	/// @param mesh the PolyMesh
	/// @param vlist the vert for constructing face
	/// @return the result face
	AMCAX_API static MPolyFace* EmbedSingleFace(PolyMesh* mesh, const std::vector<int>& vlist);

	/// @brief add a single face constructed from two edges
	/// @param mesh the PolyMesh
	/// @param edge1 the first edge
	/// @param edge2 the second edge
	/// @return the result face
	AMCAX_API static MPolyFace* AddFaceByEdge(PolyMesh* mesh, int edge1, int edge2);
};

} // namespace SubD
} // namespace AMCAX
