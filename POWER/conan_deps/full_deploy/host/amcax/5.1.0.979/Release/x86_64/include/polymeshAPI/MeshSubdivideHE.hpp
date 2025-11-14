/// @file      MeshSubdivideHE.hpp
/// @brief     Class of PolyMesh API for mesh subdividion, which will use half-edge data structure to modify the mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for mesh subdividion, which will use half-edge data structure to modify the mesh
class MeshSubdivideHE
{
public:
	/// @brief Catmull-Clark Subdivision for input mesh
	/// @param mesh The input mesh
	/// @param subTime The number of subdivision
	AMCAX_API static void CatmullClark(PolyMesh* mesh, size_t subTime);

	/// @brief Loop subdivision for input mesh, only for triangular mesh
	/// @param mesh The input triangular mesh
	/// @param subTime The number of subdivision
	AMCAX_API static void Loop(PolyMesh* mesh, size_t subTime);
};

} // namespace SubD
} // namespace AMCAX
