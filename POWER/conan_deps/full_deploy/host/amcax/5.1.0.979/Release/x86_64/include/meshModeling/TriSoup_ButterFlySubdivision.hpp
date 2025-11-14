/**
 * @file TriSoup_ButterFlySubdivision.hpp
 * @brief Implement ButterFly subdivision algorithm.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

// Triangle Mesh
#include <mesh/TriSoup.hpp>
#include <mesh/MeshPrimitive.hpp>

#include <utilities/Exception.hpp>
#include <utilities/Macros.hpp>

#include <functional>
#include <vector>

namespace AMCAX {
namespace Meshing {
namespace Subdivision {

/**
 * @brief Modified butterfly subdivision for triangle mesh.
 * Interpolating subdivision for meshes with arbitrary topology, in Proceedings
 * of SIGGRAPH 1996, ACM SIGGRAPH, 1996, pp. 189-192.
 * @tparam Traits Define types.
 * @tparam Modfied Use Modified butterfly subdivision? it handles irregular
 * vertices.
 */
template <typename Traits, bool Modified = true>
class TriSoup_ButterFlySubdivision
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

	using HalfEdge = Mesh::HalfEdge;

	class Face
	{
	public:
		std::array<bool, 3>    m_edge_is_boundary;
		std::array<index_t, 3> m_split_vidx;
	};

	struct VF_Adj;
	class OrderedOneRingVertices;

public:
	AMCAXMeshing_API TriSoup_ButterFlySubdivision(Points    &points,
	                                              Triangles &triangles)
	  : m_points(points)
	  , m_triangles(triangles)
	{
	}

	AMCAXMeshing_API TriSoup_ButterFlySubdivision(Points    &&points,
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
	 * @brief Perform ButterFly subdivision once.
	 * @param update_position update position of vertices. if don't update
	 * position, it is equivalent to simple global 1-4 subdivision.
	 */
	AMCAXMeshing_API void subdivide(bool  update_position = true,
	                                ProFn pro_fn          = ProFn());

public:
	Points    m_points;
	Triangles m_triangles;

protected:
	void clear();

	void initialize_boundary();
	void initialize_ordered_one_ring_vertices();
	void initialize_weights();

	HalfEdge find_oppo_halfedge(index_t fidx, index_t vidx);

	void initialize();

	void split_edges();

	/**
	 * @brief When the edge is a boundary edge, use boundary scheme to split it.
	 * @param helper edge operation helper.
	 * @return Point where to split the edge.
	 */
	PointT boundary_scheme(Edge &e);

	/**
	 * @brief When the edge is an inner edge, and both end vertices are regular
	 * vertices (valence is 6) or boundary vertices, use this regular scheme to
	 * split the edge.
	 * @param helper edge operation helper
	 * @return Point where to split the edge.
	 */
	PointT inner_regular_scheme(Edge &e);

	/**
	 * @brief When the edge to split is an inner edge, and at least one end vertex
	 * is irregular and not boundary vertex, use this irregular schema.
	 * @param helper edge operation helper
	 * @return Point where to split the edge.
	 */
	PointT inner_irregular_scheme(Edge &e);

	void split_faces();

protected:
	bool m_update_position;

	/// vertices
	std::vector<Vertex>  m_vertices;
	/// edges
	std::vector<Edge>    m_edges;
	std::vector<index_t> m_unique_edge_start;
	/// faces
	std::vector<Face>    m_faces;
	/// vertices-faces adjacent relation
	std::vector<VF_Adj>  m_vf_adj;

	std::vector<std::vector<NT>> m_weights;

	/// The inner vector stores ordered one ring vertices for a vertex.
	/// The outer vectro stores the inner one for all vertices.
	std::vector<OrderedOneRingVertices> m_ordered_one_ring_vertices;

private:
	const PointT &point(index_t i) { return m_points[i]; }
};

template <typename Traits, bool Modified>
struct TriSoup_ButterFlySubdivision<Traits, Modified>::VF_Adj
{
	index_t vidx, fidx;
	VF_Adj() = default;
	VF_Adj(index_t v, index_t f)
	  : vidx(v)
	  , fidx(f)
	{
	}
	bool operator<(const VF_Adj &rhs) const { return vidx < rhs.vidx; }
	bool operator<=(const VF_Adj &rhs) const { return vidx <= rhs.vidx; }
	bool operator==(const VF_Adj &rhs) const { return vidx == rhs.vidx; }
};

template <typename Traits, bool Modified>
class TriSoup_ButterFlySubdivision<Traits, Modified>::OrderedOneRingVertices
{
public:
	class Iterator
	{
	public:
		Iterator(index_t i, OrderedOneRingVertices *container);
		Iterator &operator++();
		Iterator &operator--();
		bool      is_valid() const;
		index_t   operator*() const { return m_container->m_vertices[m_i]; }
		index_t  *operator->() const { return &m_container->m_vertices[m_i]; }

	private:
		index_t                 m_i;
		OrderedOneRingVertices *m_container;
	};

public:
	size_t   size() const { return m_vertices.size(); }
	void     reserve(size_t n) { m_vertices.reserve(n); }
	void     clear() { m_vertices.clear(); }
	/// @brief push an index of vertex into the loop
	void     push(index_t vidx) { m_vertices.push_back(vidx); }
	/// @brief find the iterator of a given index of vertex.
	Iterator find(index_t vidx);

	/// @brief find the iterator by a given pred.
	template <typename Pred>
	Iterator find_if(const Pred &pred);

	Iterator begin() { return Iterator(0, this); }
	Iterator end() { return Iterator(m_vertices.size(), this); }

	// return the index in the front when loop is open.
	index_t front() const;
	// return the index at the back when loop is open.
	index_t back() const;

	bool is_closed() const { return m_is_closed; }
	bool is_open() const { return !m_is_closed; }

	void set_closed() { m_is_closed = true; }
	void set_open() { m_is_closed = false; }

private:
	std::vector<index_t> m_vertices;
	/// When loop is closed, it doesn't have a explicit start and end position.
	/// When loop is open, we must put begin to the first position and end to
	/// the last position.
	bool                 m_is_closed;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API TriSoup_ButterFlySubdivision<Mesh::TriSoupTraits, true>;
extern template class AMCAXMeshing_CLASS_API TriSoup_ButterFlySubdivision<Mesh::TriSoupTraits, false>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API TriSoup_ButterFlySubdivision<Mesh::TriSoupTraits_Eigen, true>;
extern template class AMCAXMeshing_CLASS_API TriSoup_ButterFlySubdivision<Mesh::TriSoupTraits_Eigen, false>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API TriSoup_ButterFlySubdivision<Mesh::TriSoupTraits_Coord, true>;
extern template class AMCAXMeshing_CLASS_API TriSoup_ButterFlySubdivision<Mesh::TriSoupTraits_Coord, false>;
#endif
// clang-format on

} // namespace Subdivision
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriSoup_ButterFlySubdivision.inl"
#endif