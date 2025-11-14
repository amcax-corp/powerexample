/// @file      MeshCopy.hpp
/// @brief     Class of Copy PolyMesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of Copy PolyMesh
class MeshCopy
{
public:
	/// @brief Extract faces form a PolyMesh to generate a new PolyMesh.
	/// @param meshSrc input PolyMesh
	/// @param faces indices of the face to be extracted
	/// @return new PolyMesh
	AMCAX_API static PolyMesh* ExtractMeshFaces(const PolyMesh* meshSrc, const std::vector<int>& faces);

	/// @brief Copy a PolyMesh
	/// @param meshSrc input PolyMesh
	/// @return new PolyMesh
	AMCAX_API static PolyMesh* CopyMesh(const PolyMesh* meshSrc);

	/// @brief Append one PolyMesh to another PolyMesh
	/// @param meshFin the target PolyMesh
	/// @param meshAdd the from PolyMesh
	AMCAX_API static void CombineMesh(PolyMesh* meshFin, const PolyMesh* meshAdd);
};

} // namespace SubD
} // namespace AMCAX
