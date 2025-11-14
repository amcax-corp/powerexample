/// @file      MeshWeld.hpp
/// @brief     Class of PolyMesh API for weld edges
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for weld edges
class MeshWeld
{
public:
	/// @brief filter input edges and remove edges which can not be weld
	/// @param mesh the PolyMesh
	/// @param [in,out] elist the edges that need to be checked
	/// @return true if the process successful
	AMCAX_API static bool FilterVoidWeldEdges(PolyMesh* mesh, std::vector<int>& elist);

	/// @brief find all edges in a PolyMesh by input edges with tolerance and Weld them to inner edges
	/// @param mesh the PolyMesh
	/// @param elist the edges that need to be weld
	/// @param tolerance the tolerance used to find additional edges
	AMCAX_API static void MeshWeldEdges(PolyMesh* mesh, const std::vector<int>& elist, double tolerance = 0.01);
};

} // namespace SubD
} // namespace AMCAX
