/// @file      MeshOffset.hpp
/// @brief     Class of PolyMesh API for Thicken a Mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh API for Thicken a Mesh
class MeshOffset
{
public:
	/// @brief make a mesh approximately offset mesh
	/// @param mesh the PolyMesh
	/// @param dist The reference offset distance
	/// @return new PolyMesh
	AMCAX_API static PolyMesh* OffsetMesh(PolyMesh* mesh, double dist);

	/// @brief Thicken a mesh to give a approximately shell or thickness.
	/// @param mesh the PolyMesh
	/// @param dist The reference thickening distance
	/// @param isConnect Does the offset mesh connect to the original mesh
	/// @return True if process succeeded
	AMCAX_API static bool ThickenMesh(PolyMesh* mesh, double dist, bool isConnect = true);
};

} // namespace SubD
} // namespace AMCAX
