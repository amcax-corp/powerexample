/// @file      MeshExtrude.hpp
/// @brief     Class of PolyMesh API for extrude method
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for extrude method
/// only change the topology, the new result is coincide the old result, and use MeshTransform to move the new result.
class MeshExtrude
{
public:
	/// @brief extrude the edges in PolyMesh
	/// @param mesh a PolyMesh
	/// @param edges indices of the edges to be extrude
	/// @param edgesNew indices of the edges after extrude
	/// @return true if the process successful
	AMCAX_API static bool ExtrudeEdge(PolyMesh* mesh, const std::vector<int>& edges, std::vector<int>& edgesNew);

	/// @brief extrude the faces in PolyMesh
	/// @param mesh a PolyMesh
	/// @param faces indices of the faces to be extrude
	/// @param facesNew indices of the faces after extrude
	/// @return true if the process successful
	AMCAX_API static bool ExtrudeFace(PolyMesh* mesh, const std::vector<int>& faces, std::vector<int>& facesNew);
};

} // namespace SubD
} // namespace AMCAX
