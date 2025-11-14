/// @file      MeshSeparate.hpp
/// @brief     Class of PolyMesh API for separate edges
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for separate edge, obtain new boundaries in the separated edges
class MeshSeparate
{
public:
	/// @brief Separate edges into each other, the result edges will remain on top of each other until they are moved
	/// @param tsp The PolyMesh
	/// @param elist the edges that need to build chamfers
	/// @return true if the process successful
	AMCAX_API static bool SeparateEdges(PolyMesh* mesh, const std::vector<int>& edges);
};

} // namespace SubD
} // namespace AMCAX
