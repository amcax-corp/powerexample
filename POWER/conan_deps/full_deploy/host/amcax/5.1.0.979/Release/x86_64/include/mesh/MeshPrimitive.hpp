/**
 * @file MeshPrimitive.hpp
 * @brief Defines primitives used in mesh.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <utilities/Exception.hpp>
#include <utilities/IndexDef.hpp>

#include <array>
#include <unordered_set>
#include <vector>

namespace AMCAX {
namespace Meshing {
namespace Mesh {

/**
 * @brief Simple representation of edges in mesh. It represent the general edge
 * of mesh in topological sense. It store two end vertices and doesn't store any
 * geometrical information or other extra information.
 * @note Compared with HalfEdge, Edge is always unoriented.
 * @note In some contexts (e.g., polyline mesh), two vertices are put in
 * from->to order [ev0->ev1].
 * @note In some contexts (e.g., triangle mesh), two vertices are unoriented.
 */
class Edge
{
public:
	Edge() = default;

	explicit Edge(index_t v0, index_t v1, bool unique = false)
	{
		m_ev0 = v0;
		m_ev1 = v1;
		if (unique)
			make_unique();
	}

public:
	Edge unique() const
	{
		if (ev0() < ev1())
			return *this;
		else
			return Edge(ev1(), ev0());
	}

	Edge &make_unique()
	{
		if (ev0() > ev1())
			std::swap(ev0(), ev1());
		return *this;
	}

public: /* Comparators */
	/**
	 * @brief Compare two unique edges.
	 * @note Make sure that two Edges are both unique.
	 */
	bool operator<(const Edge &rhs) const
	{
		if (ev0() < rhs.ev0())
			return true;
		else if (ev0() > rhs.ev0())
			return false;
		else
			return ev1() < rhs.ev1();
	}

	bool operator==(const Edge &rhs) const
	{
		return ev0() == rhs.ev0() && ev1() == rhs.ev1();
	}

public:
	index_t &ev0() { return m_ev0; }
	index_t  ev0() const { return m_ev0; }

	index_t &ev1() { return m_ev1; }
	index_t  ev1() const { return m_ev1; }

private:
	/// @brief The vertices of an edge. In any mesh, there is always 2
	/// vertices in an edge.
	index_t m_ev0, m_ev1;
};

/**
 * @brief Simple representation of halfedges in mesh. It represent the general
 * halfedge of mesh in topological sense. It store two end vertices and doesn't
 * store any geometrical information or other extra information.
 * @note Compared with Edge, HalfEdge is always oriented,
 * it starts from `from()` and point to `to()`.
 */
class HalfEdge
{
public:
	HalfEdge() = default;

	explicit HalfEdge(index_t from, index_t to)
	{
		m_from = from;
		m_to   = to;
	}

	bool operator<(const HalfEdge &rhs) const
	{
		if (from() < rhs.from())
			return true;
		else if (from() > rhs.from())
			return false;
		else
			return to() < rhs.to();
	}

	bool operator==(const HalfEdge &rhs) const
	{
		return from() == rhs.from() && to() == rhs.to();
	}

public:
	index_t &from() { return m_from; }
	index_t  from() const { return m_from; }

	index_t &to() { return m_to; }
	index_t  to() const { return m_to; }

	bool exist(index_t vidx) const { return m_from == vidx || m_to == vidx; }

private:
	/// @brief The vertices of a halfedge. In any mesh, there is always 2
	/// vertices in a halfedge.
	index_t m_from;
	index_t m_to;
};

/**
 * @brief Simple representation of faces in triangle mesh. It represent the
 * general face of mesh in topological sense. It store three vertices (in
 * indices). It doesn't store any geometrical information or other extra
 * information.
 * @note We refer to three vertices as v0, v1 and v2.
 * @note In some contexts (e.g. triangle mesh), three vertices are put in
 * couter-clock-wise order [0->1->2].
 * @note In other contexts (e.g., tetrahedral mesh), three vertices are ordered
 * but unoriented, i.e., the order of the three vertices is uncertain whether it
 * is clockwise or counterclockwise.
 */
class TriFace
{
public:
	TriFace() = default;

	explicit TriFace(index_t v0, index_t v1, index_t v2) noexcept
	  : m_fv({v0, v1, v2})
	{
	}

	// Default copy and move

public:
	/******** Access vertices ********/
	using fv_container       = typename std::array<index_t, 3>;
	using fv_iterator        = typename fv_container::iterator;
	using fv_reference       = typename fv_container::reference;
	using fv_const_iterator  = typename fv_container::const_iterator;
	using fv_const_reference = typename fv_container::const_reference;

	fv_container       &fv() { return m_fv; }
	const fv_container &fv() const { return m_fv; }

	fv_iterator       fv_begin() { return m_fv.begin(); }
	fv_const_iterator fv_begin() const { return m_fv.cbegin(); }

	fv_iterator       fv_end() { return m_fv.end(); }
	fv_const_iterator fv_end() const { return m_fv.cend(); }

	index_t &fv0() { return m_fv[0]; }
	index_t &fv1() { return m_fv[1]; }
	index_t &fv2() { return m_fv[2]; }

	index_t fv0() const { return m_fv[0]; }
	index_t fv1() const { return m_fv[1]; }
	index_t fv2() const { return m_fv[2]; }

	bool exist(index_t vidx) const
	{
		return m_fv[0] == vidx || m_fv[1] == vidx || m_fv[2] == vidx;
	}

private:
	/// @brief The vertices of a face. In triangle mesh, there is always 3
	/// vertices in a face.
	fv_container m_fv;
};

/**
 * @brief Simple representation of tetrahedra cells in tet mesh. It represents
 * the general cell of mesh in topological sense. It store the adjacent relation
 * with other mesh elements, like vertices. It doesn't store any geometrical
 * information or other extra information.
 * @note We refer to four vertices as v0, v1, v2 and v3.
 * @note The orientation of a face is counter-clock-wise when seen from inside
 * of the tet. In other words, the normal of a face is point towards inside. So
 * the orientations of vertices of faces are as below:
 * [0->1->2], [0->3->1], [1->3->2], [2->3->0].
 */
class TetCell
{
public:
	TetCell() = default;

	explicit TetCell(index_t v0, index_t v1, index_t v2, index_t v3) noexcept
	  : m_cv({v0, v1, v2, v3})
	{
	}

	// Default copy and move

public:
	/******** Access vertices ********/
	using cv_container       = typename std::array<index_t, 4>;
	using cv_iterator        = typename cv_container::iterator;
	using cv_reference       = typename cv_container::reference;
	using cv_const_iterator  = typename cv_container::const_iterator;
	using cv_const_reference = typename cv_container::const_reference;

	cv_container       &cv() { return m_cv; }
	const cv_container &cv() const { return m_cv; }

	cv_iterator       cv_begin() { return m_cv.begin(); }
	cv_const_iterator cv_begin() const { return m_cv.cbegin(); }

	cv_iterator       cv_end() { return m_cv.end(); }
	cv_const_iterator cv_end() const { return m_cv.cend(); }

	index_t &cv0() { return m_cv[0]; }
	index_t &cv1() { return m_cv[1]; }
	index_t &cv2() { return m_cv[2]; }
	index_t &cv3() { return m_cv[3]; }

	index_t cv0() const { return m_cv[0]; }
	index_t cv1() const { return m_cv[1]; }
	index_t cv2() const { return m_cv[2]; }
	index_t cv3() const { return m_cv[3]; }

	bool exist(index_t vidx) const
	{
		return m_cv[0] == vidx || m_cv[1] == vidx || m_cv[2] == vidx ||
		       m_cv[3] == vidx;
	}

private:
	/// @brief The four vertices of a tet cell.
	/// We call them v0, v1, v2 and v3 in order.
	/// The normal of a face is point towards inside.
	/// So the orientations of vertices of faces are as below:
	/// 0->1->2, 0->3->1, 1->3->2, 2->3->0.
	cv_container m_cv;
};

} // namespace Mesh
} // namespace Meshing
} // namespace AMCAX