/**
 * @file TriMesh_DefectDetector.hpp
 * @brief TriMesh NonManifold detector algorithm.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once
#include <mesh/TriSoup.hpp>
#include <utilities/Macros.hpp>
#include <vector>
#include <memory>

namespace AMCAX::Meshing::MeshTools {

template <typename Traits>
class TriMesh_DefectDetector_Impl;

template <typename Traits>
class TriMesh_DefectDetector
{
public:
	/* Traits about input data ********************************************/
	/** @brief Point type.
	 * E.g., Vec3d from any library or a wrapper of it.
	 */
	using iPointT         = typename Traits::PointT;
	/** @brief Vector type.
	 * It is derived from PointT, representing the difference between two points.
	 */
	using iVecT     = typename Traits::VecT;
	/** @brief Triangle type. */
	using iTriangle = typename Traits::Triangle;
	/** @brief Number type in PointT.
	 * We also expect that PointT provides x(), y() and z().
	 */
	using iNT  = std::remove_reference_t<decltype(std::declval<iPointT>().x())>;
	/** @brief index in triangle*/
	using ti_t = std::remove_reference_t<decltype(std::declval<iTriangle>()[0])>;
	/** @brief An array that stores points for vertices.
	 * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	 */
	using iPoints    = typename Traits::Points;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using iTriangles = typename Traits::Triangles;

public:
	// Initialize by inputting the trimesh points and tris
	AMCAXMeshing_API TriMesh_DefectDetector(const iPoints    &points,
	                                        const iTriangles &triangles);

	AMCAXMeshing_API ~TriMesh_DefectDetector() noexcept;

public:
	/**
	 * @brief Detects non-manifold vertices in the mesh.
	 * @return std::vector<size_t> List of vertex indices that are non-manifold,
	 *         sorted in ascending order. Returns empty if none found.
	 */
	AMCAXMeshing_API std::vector<size_t> DetectNonManifoldVertices() const;

	/**
	 * @brief Detects non-manifold edges in the mesh.
	 * @return std::vector<std::pair<size_t, size_t>> List of non-manifold edges, 
	           each represented as a pair of vertex indices (undirected).
	 */
	AMCAXMeshing_API std::vector<std::pair<size_t, size_t>>
	                 DetectNonManifoldEdges() const;

	/**
	 * @brief Detects non-manifold edges for 3D printing.
	 *
	 * Includes both edges shared by more than two faces and
	 * boundary (free) edges. Both are invalid for watertight 3D printable meshes.
	 *
	 * @return std::vector<std::pair<size_t, size_t>> List of non-manifold edges,
	           each represented as a pair of vertex indices (undirected).
	 */
	AMCAXMeshing_API std::vector<std::pair<size_t, size_t>>
	                 DetectNonManifoldEdgesFor3DPrint() const;

	/**
	 * @brief Detects free (boundary) edges in the mesh.
	 * @return std::vector<std::pair<size_t, size_t>> List of free (boundary) edges, 
	           each represented as a pair of vertex indices(undirected).
	 */
	AMCAXMeshing_API std::vector<std::pair<size_t, size_t>>
	                 DetectFreeEdges() const;

	/**
	 * @brief Detects groups of duplicate vertices within a given tolerance.
	 * @param epsilon Maximum distance for vertices to be considered identical.
	 * @return std::vector<std::vector<size_t>> List of clusters, 
	           each containing indices of duplicate vertices (size > 1).
	 */
	AMCAXMeshing_API std::vector<std::vector<size_t>>
	                 DetectDuplicateVertices(double epsilon = 0.0) const;

	/// @brief Detects duplicate faces in the mesh.
	/// @return std::vector<size_t> List of face indices that are duplicates.
	AMCAXMeshing_API std::vector<size_t> DetectDuplicateFaces() const;

	/**
	 * @brief Detects degenerate (invalid) faces in the mesh.
	 * @param epsilon Maximum edge length or area threshold for a face to be
	 * considered degenerate.
	 * @return std::vector<size_t> List of indices of degenerate faces.
	 */
	AMCAXMeshing_API std::vector<size_t>
	                 DetectDegenerateFaces(double epsilon = 0.0) const;

	/**
	 * @brief Detects isolated faces in the mesh.
	 * @return std::vector<size_t> List of indices of isolated faces.
	 */
	AMCAXMeshing_API std::vector<size_t> DetectIsolatedFaces() const;

	/**
	 * @brief Detects self-intersecting faces in the mesh.
	 * @return std::vector<size_t> List of indices of faces involved in
	 * intersections.
	 */
	AMCAXMeshing_API std::vector<size_t> DetectSelfIntersectingFaces() const;

	/**
	 * @brief Detects faces with inconsistent normals within each connected component.
	 * @return std::vector<std::pair<std::vector<size_t>, std::vector<size_t>>>
	 *         Each pair represents two sets of face indices in a connected
	 *         component that have conflicting (opposite) normals.
	 */
    AMCAXMeshing_API
	  std::vector<std::pair<std::vector<size_t>, std::vector<size_t>>>
	  DetectFacesWithInconsistentNormals() const;

private:
	/// Implement class
	std::unique_ptr<TriMesh_DefectDetector_Impl<Traits>> m_impl;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API TriMesh_DefectDetector<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API TriMesh_DefectDetector<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits 
extern template class AMCAXMeshing_CLASS_API TriMesh_DefectDetector<Mesh::TriSoupTraits_Coord>;
#endif
// clang-format on

} // namespace AMCAX::Meshing::MeshTools

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriMesh_DefectDetector.inl"
#endif