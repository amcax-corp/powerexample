/// @file      MeshCheck.hpp
/// @brief     Class of PolyMesh check Tool
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh Check Tool
class MeshCheck
{
public:
	/// @brief check if the input index is valid vert
	/// @param mesh a PolyMesh
	/// @param vid input index
	/// @return return true if the input index is valid vert
	AMCAX_API static bool IsVertValid(PolyMesh* mesh, int vid);

	/// @brief check if the vert is boundary vert
	/// @param mesh a PolyMesh
	/// @param vid input vert index
	/// @return 0: input not valid,
	///			1: is boundary vert
	///		   -1: not boundaty vert
	AMCAX_API static int IsVertBoundary(PolyMesh* mesh, int vid);

	/// @brief check if the vert is inner vert
	/// @param mesh a PolyMesh
	/// @param vid input vert index
	/// @return 0: input not valid,
	///			1: is inner vert
	///		   -1: not inner vert
	AMCAX_API static int IsVertInner(PolyMesh* mesh, int vid);

	/// @brief check if the input index is valid edge
	/// @param mesh a PolyMesh
	/// @param eid input index
	/// @return return true if the input index is valid edge
	AMCAX_API static bool IsEdgeValid(PolyMesh* mesh, int eid);

	/// @brief check if the edge is boundary edge
	/// @param mesh a PolyMesh
	/// @param eid input edge index
	/// @return 0: input not valid,
	///			1: is boundary edge
	///		   -1: not boundaty edge
	AMCAX_API static int IsEdgeBoundary(PolyMesh* mesh, int eid);

	/// @brief check if the edge is inner edge
	/// @param mesh a PolyMesh
	/// @param eid input edge index
	/// @return 0: input not valid,
	///			1: is inner edge
	///		   -1: not inner edge
	AMCAX_API static int IsEdgeInner(PolyMesh* mesh, int eid);

	/// @brief check if the input index is valid face
	/// @param mesh a PolyMesh
	/// @param fid input index
	/// @return return true if the input index is valid face
	AMCAX_API static bool IsFaceValid(PolyMesh* mesh, int fid);

	/// @brief check if the two edges are connected
	/// @param mesh a PolyMesh
	/// @param edge0 the first edge
	/// @param edge1 the second edge
	AMCAX_API static bool IsTwoEdgeConnected(const PolyMesh* mesh, const int edge0, const int edge1);

	/// @brief check if mesh is triangular mesh
	/// @param mesh a mesh
	AMCAX_API static bool IsTriangularMesh(const PolyMesh* mesh);
};

} // namespace SubD
} // namespace AMCAX
