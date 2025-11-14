/// @file      MeshSplit.hpp
/// @brief     Class of PolyMesh API for split mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for split mesh
class MeshSplit
{
public:
	/// @brief Split a loop faces generated from edge
	/// @param mesh the Mesh
	/// @param eId the input edge
	/// @param t the ratio of the distance between the starting point and the dividing point of an edge to the length of the edge
	/// @return true if the process successful
	AMCAX_API static bool SplitLoop(PolyMesh* mesh, const int eId, double t = 0.5);

	/// @brief Split faces by sequentially cross the point of the edges in Mesh
	/// @param mesh the Mesh
	/// @param elist the edges that need to be sequentially cross
	/// @param newControl the point in each edges
	/// @return true if the process successful
	AMCAX_API static bool SplitFaceWithEdge(PolyMesh* mesh, const std::vector<int>& elist, const std::vector<Point3>& newControl);

	/// @brief Split faces by sequentially cross vertices in Mesh
	/// @param mesh The Mesh
	/// @param vlist the vertices that need to be sequentially cross
	/// @return true if the process successful
	AMCAX_API static bool SplitFaceWithVertex(PolyMesh* mesh, const std::vector<int>& vlist);
};

} // namespace SubD
} // namespace AMCAX
