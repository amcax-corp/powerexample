/// @file      TMSTriangleMesh.hpp
/// @brief     Class of TMSpline triangle mesh structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/PointT.hpp>
#include <common/VectorT.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of vertex of TMSpline triangle mesh
struct TR_Vert
{
	Point3 position_; ///< vertex position
	Vector3 normal_;  ///< vertex normal

	size_t T_face_index_; ///< true spline face index
	Point2 T_Param_;	  ///< texture parameter

	std::vector<double> Additional_; ///< additional information
};

/// @brief Class of edge of TMSpline triangle mesh
struct TR_Edge
{
	size_t v1_, v2_; ///< indices of vertices

	size_t T_index_; ///< patch spline edge index

	std::vector<double> Additional_; ///< additional information
};

/// @brief Class of triangle of TMSpline triangle mesh
struct TR_Triangle
{
	size_t vert_[3]; ///< indices of vertices

	Vector3 normal_; ///< face normal

	size_t T_index_; ///< patch spline face index
};

/// @brief Class of TMSpline triangle mesh structure
struct TMSTriangleMesh
{
	std::vector<TR_Vert> vert_lsit_;	 ///< list of vertices
	std::vector<TR_Edge> edge_list_;	 ///< list of edges
	std::vector<TR_Triangle> face_list_; ///< list of faces

#ifndef DOXYGEN_SKIP

	[[nodiscard]] size_t numVertices() const noexcept;
	[[nodiscard]] size_t numEdges() const noexcept;
	[[nodiscard]] size_t numFaces() const noexcept;

	[[nodiscard]] const TR_Vert& getVert(size_t index) const noexcept;
	[[nodiscard]] const TR_Edge& getEdge(size_t index) const noexcept;
	[[nodiscard]] const TR_Triangle& getFace(size_t index) const noexcept;

	void clear() noexcept;
	void reserve(size_t v_num, size_t e_num, size_t f_num);

	size_t addVert(const TR_Vert& v);
	size_t addEdge(const TR_Edge& e);
	size_t addFace(const TR_Triangle& f);

	void updateMeshFaceNormalOnly();
	void updateMeshNormal();

#endif

};

} // namespace TMS
} // namespace AMCAX
