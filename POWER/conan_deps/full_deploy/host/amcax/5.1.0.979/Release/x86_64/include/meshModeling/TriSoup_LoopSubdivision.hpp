/**
 * @file TriSoup_LoopSubdivision.hpp
 * @brief Implement loop subdivision algorithm.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

// Triangle Mesh
#include <mesh/TriSoup.hpp>
#include <mesh/MeshPrimitive.hpp>

#include <utilities/Exception.hpp>

#include <array>
#include <cmath>
#include <execution>
#include <functional>
#include <map>
#include <vector>

namespace AMCAX {
namespace Meshing {
namespace Subdivision {

/**
 * @brief Loop subdivision for triangle mesh.
 * @details
 * Each triangle in original mesh is subdivided into four new triangles in new
 * mesh. So, new mesh contains original vertices and new vertices on original
 * edges.
 * The position of vertices in new mesh is a weighted sum of position of
 * original vertices in original mesh.
 *
 * =============================================================================
 *
 * For new vertices on original edges, weights are:
 * @verbatim
 *            v2 (1/8)
 *             /| \
 *            / |  \
 *          /   |   \
 *         / f0 | f2 \
 *        /     |     \
 * (3/8) v0-----vmid---v1 (3/8)
 *        \     |     /
 *         \ f1 | f3 /
 *          \   |   /
 *           \  |  /
 *            \ | /
 *           v3 (1/8)
 * @endverbatim
 *
 * For original vertices, update rule is:
 *
 * new_pos = (1 - valence * alpha) * old_pos + sum_of_one_ring(alpha * adj_pos),
 *
 * where alpha is:
 *
 * alpha = (1 / valence) * (5/8 - (3/8 + cos(2*pi / valence) / 4)^2 ).
 *
 * =============================================================================
 *
 * For new boundary vertices on original, weights are:
 *
 * (1/2) v0-----vmid---v1 (1/2)
 *
 * For original boundary vertices, update rule is:
 *
 * (1/8) v_left-----vmid(3/4)---v_right (1/2)
 *
 * =============================================================================
 *
 * @tparam Traits Defines types
 */
template <typename Traits>
class TriSoup_LoopSubdivision
{
public:
	/** @brief Point type.
	 * E.g., Vec3d from any library or a wrapper of it.
	 */
	using PointT   = typename Traits::PointT;
	/** @brief Vector type.
	 * It is derived from PointT, representing the difference between two points.
	 */
	using VecT     = decltype(std::declval<PointT>() - std::declval<PointT>());
	/** @brief Triangle type. */
	using Triangle = typename Traits::Triangle;
	/** @brief Number type in PointT.
	 * We also expect that PointT provides x(), y() and z().
	 */
	using NT     = std::remove_reference_t<decltype(std::declval<PointT>().x())>;
	/** @brief index in triangle*/
	using ti_t   = std::remove_reference_t<decltype(std::declval<Triangle>()[0])>;
	/** @brief An array that stores points for vertices.
	 * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	 */
	using Points = typename Traits::Points;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using Triangles = typename Traits::Triangles;

	class Vertex
	{
	public:
		unsigned int m_valence = 0;
		bool         m_is_boundary;
	};

	using EdgeBase = Mesh::Edge;
	class Edge : public EdgeBase
	{
	public:
		Edge(index_t v0, index_t v1, index_t fidx, index_t local_eidx)
		  : EdgeBase(v0, v1, /*unique*/ true)
		{
			m_fidx       = fidx;
			m_local_eidx = local_eidx;
		}

	public:
		index_t m_fidx;
		index_t m_local_eidx;
	};

	class Face
	{
	public:
		std::array<bool, 3>    m_edge_is_boundary;
		std::array<index_t, 3> m_split_vidx;
	};

public:
	AMCAXMeshing_API TriSoup_LoopSubdivision(Points &points, Triangles &triangles)
	  : m_points(points)
	  , m_triangles(triangles)
	{
	}

	AMCAXMeshing_API TriSoup_LoopSubdivision(Points    &&points,
	                                         Triangles &&triangles)
	  : m_points(std::move(points))
	  , m_triangles(std::move(triangles))
	{
	}

public:
	/**
	 * @brief Algorithm stage reported in process function.
	 */
	enum Stage
	{
		Initialize = 0, // input, initialize edges...
		Smooth,         // smooth original vertices...
		SplitEdges,     // split edges, calculate new points...
		SplitFaces,     // split faces...
		Ending,         // output....
		Total           // Use it to make progress bar :)
	};

	/// @brief function that reports process
	/// @param stage We will report stage (see above `Stage`) by this parameter.
	/// @param cancel If set to true, algorithm will be terminated.
	/// @note We can't report sub-stages or percentages, because each stage is
	/// parallalized.
	using ProFn = std::function<void(int stage, bool &cancel)>;

	/**
	 * @brief Perform Loop subdivision once.
	 * @param update_position update position of vertices. if don't update
	 * position, it is equivalent to simple global 1-4 subdivision.
	 */
	AMCAXMeshing_API void subdivide(bool  update_position = true,
	                                ProFn pro_fn          = ProFn());

public:
	Points    m_points;
	Triangles m_triangles;

protected:
	/**
	 * @brief Pre-initialize weights used in calculating new position of vertices.
	 */
	void initialize();

	/**
	 * @brief Clear auxiliary data.
	 */
	void clear();

	/**
	 * @brief Calculate the new position of original vertices.
	 */
	void smooth_original_vertices();

	/**
	 * @brief Split edges at their mid-points. If updating position, calculate the
	 * new position of all new vertices.
	 */
	void split_edges();

	void split_faces();

protected:
	bool m_update_position;

	/// new position for all vertices (including both original and new)
	Points m_vert_new_pos;

	/// vertices
	std::vector<Vertex>  m_vertices;
	/// edges
	std::vector<Edge>    m_edges;
	std::vector<index_t> m_unique_edge_start;
	/// faces
	std::vector<Face>    m_faces;

	/// pair(1 - valence * alpha, alpha)
	std::vector<std::pair<NT, NT>> m_weights;
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API TriSoup_LoopSubdivision<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API TriSoup_LoopSubdivision<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API TriSoup_LoopSubdivision<Mesh::TriSoupTraits_Coord>;
#endif

} // namespace Subdivision
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriSoup_LoopSubdivision.inl"
#endif