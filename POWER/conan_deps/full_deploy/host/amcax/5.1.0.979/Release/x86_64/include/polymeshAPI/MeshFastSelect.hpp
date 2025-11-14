/// @file      MeshFastSelect.hpp
/// @brief     Class of PolyMesh useful select Tool
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh useful select Tool
class MeshFastSelect
{
public:
	/// @brief find the vector of boundary edges where the input edge is located
	/// @param mesh a PolyMesh
	/// @param edge the input edge
	/// @param boundaryEdges indices of the boundary edges
	AMCAX_API static void FindBoundaryEdges(const PolyMesh* mesh, const int edge, std::vector<int>& boundaryEdges);

	/// @brief find a connect edge loop where the input edge is located
	/// @param mesh a PolyMesh
	/// @param edge the input edge
	/// @param loopEdges indices of the edges in edge loop
	AMCAX_API static void FindLoopEdges(const PolyMesh* mesh, const int edge, std::vector<int>& loopEdges);
};

} // namespace SubD
} // namespace AMCAX
