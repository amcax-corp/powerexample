/// @file      MeshTransform.hpp
/// @brief     Class of transforming a PolyMesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>
#include <common/GeneralTransformationT.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of transforming a PolyMesh
class MeshTransform
{
public:
	/// @brief Set the Transformation to be applied
	/// @param t The transformation to be applied
	AMCAX_API void SetTransformation(const Transformation3& t);

	/// @brief Set the GeneralTransformation to be applied
	/// @param gt The general transformation(affine transformation) to be applied
	AMCAX_API void SetGTransformation(const GeneralTransformation3& gt);

	/// @brief Applying transformations to a PolyMesh
	/// @param mesh input PolyMesh to be applied
	AMCAX_API void TranformMesh(PolyMesh* mesh);

	/// @brief Applying transformations to vert list in a PolyMesh
	/// @param mesh input PolyMesh to be applied
	/// @param vlist indices of the verts in mesh
	AMCAX_API void TransformMeshVertices(PolyMesh* mesh, const std::vector<int>& vlist);

	/// @brief Applying transformations to edge list in a PolyMesh
	/// @param mesh input PolyMesh to be applied
	/// @param elist indices of the edge in mesh
	AMCAX_API void TransformMeshEdges(PolyMesh* mesh, const std::vector<int>& elist);

	/// @brief Applying transformations to face list in a PolyMesh
	/// @param mesh input PolyMesh to be applied
	/// @param flist indices of the face in mesh
	AMCAX_API void TransformMeshFaces(PolyMesh* mesh, const std::vector<int>& flist);

private:
	GeneralTransformation3 trsf_;
};

} // namespace SubD
} // namespace AMCAX
