/// @file      MeshTool.hpp
/// @brief     Class of PolyMesh Tool
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <polymesh/PolyMesh.hpp>
#include <common/VectorT.hpp>
#include <common/BoundingBox3.hpp>

namespace AMCAX
{
namespace SubD
{
/// @brief Class of PolyMesh Tool
class MeshTool
{
public:
	/// @brief Return the position of vert in PolyMesh
	/// @param mesh The input mesh
	/// @param vert The index of vertex 
	/// @return a point in space
	AMCAX_API static const Point3& Position(PolyMesh* mesh, int vert);

	/// @brief Return the normal of vert in PolyMesh
	/// @param mesh The input mesh
	/// @param vert the index of vertex
	/// @return a unit vector
	AMCAX_API static const Vector3& VertNormal(PolyMesh* mesh, int vert);

	/// @brief Return the normal of face in PolyMesh
	/// @param mesh The input mesh
	/// @param face the index of face
	/// @return a unit vector
	AMCAX_API static const Vector3& FaceNormal(PolyMesh* mesh, int face);

	/// @brief Update all normal of the PolyMesh
	/// @param mesh The input mesh
	AMCAX_API static void UpdateNormal(PolyMesh* mesh);

	/// @brief Update the normal of the regions affected by vertices in the PolyMesh
	/// @param mesh The input mesh
	/// @param vlist indices of the verts in mesh
	AMCAX_API static void UpdateNormalVertexRegion(PolyMesh* mesh, const std::vector<int>& vlist);

	/// @brief Reverse all normal of the PolyMesh
	/// @param mesh The input mesh
	AMCAX_API static void ReverseMeshNormal(PolyMesh* mesh);

	/// @brief Get the vertices of the edge in PolyMesh.
	/// @details If the edge is boundary, return the order of vertices along the boundary; otherwise, return any order.
	/// @param mesh The input mesh
	/// @param edge The index of edge
	/// @param vfirst The first index of edge vertex
	/// @param vlast The second index of edge vertex
	AMCAX_API static void EdgeVertexIndexs(PolyMesh* mesh, int edge, int& vfirst, int& vlast);

	/// @brief Return the vertices of the face in PolyMesh
	/// @param mesh The input mesh
	/// @param face the index of face
	/// @return The indices of vertices in face
	AMCAX_API static std::vector<int> FaceVertexIndexs(PolyMesh* mesh, int face);

	/// @brief Return the edges of the face in PolyMesh
	/// @param mesh The input mesh
	/// @param face The index of face
	/// @return The indices of edges in face
	AMCAX_API static std::vector<int> FaceEdgeIndexs(PolyMesh* mesh, int face);

	/// @brief Return the faces adjacent to the input edge in PolyMesh
	/// @param mesh The input mesh
	/// @param edge The index of edge 
	/// @return the indices of faces adjacent to edge
	AMCAX_API static std::vector<int> EdgeFaceIndexs(PolyMesh* mesh, int edge);

	/// @brief Return the edges adjacent to the input vertex in PolyMesh
	/// @param mesh The input mesh
	/// @param vert The index of vertex 
	/// @return the indices of edges adjacent to vert
	AMCAX_API static std::vector<int> VertEdgeIndexs(PolyMesh* mesh, int vert);

	/// @brief Return the faces adjacent to the input vertex in PolyMesh
	/// @param mesh The input mesh
	/// @param vert The index of vertex 
	/// @return the indices of faces adjacent to vert
	AMCAX_API static std::vector<int> VertFaceIndexs(PolyMesh* mesh, int vert);

	/// @brief Return the faces adjacent to the input face in PolyMesh
	/// @param mesh The input mesh
	/// @param face The index of face 
	/// @return the indices of faces adjacent to face
	AMCAX_API static std::vector<int> FaceAdjacentFaces(PolyMesh* mesh, int face);

	/// @brief Compute the Bounding box of Mesh
	/// @param mesh The input mesh
	/// @return the bounding box of mesh
	AMCAX_API static BoundingBox3 MeshBoundingBox(const PolyMesh* mesh);

	/// @brief Make a mesh to triangular mesh
	/// @param mesh The input mesh
	AMCAX_API static void MeshTriangles(PolyMesh* mesh);
};

} // namespace SubD
} // namespace AMCAX
