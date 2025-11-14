/// @file      MeshCreaseTool.hpp
/// @brief     Class of PolyMesh API for make crease edge
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for make crease edge
class MeshCreaseTool
{
public:
	/// @brief creat and change crease edge for subdive in a PolyMesh
	/// @param mesh input PolyMesh
	/// @param eIds indices of the edge to be creat crease
	/// @param creaseLevel the crease level for each crease edge
	AMCAX_API static void AddCreaseEdge(PolyMesh* mesh, const std::vector<int>& eIds, const std::vector<double>& creaseLevel);

	/// @brief remove crease edge in a PolyMesh
	/// @param mesh input PolyMesh
	/// @param eIds indices of the edge to be remove crease
	AMCAX_API static void RemoveCreaseEdge(PolyMesh* mesh, const std::vector<int>& eIds);
};

} // namespace SubD
} // namespace AMCAX
