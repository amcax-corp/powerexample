/**
 * @file TriSoup_FastQEM.hpp
 * @brief Fast QEM simplification algorithm.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once
#include <mesh/TriSoup.hpp>

#include <utilities/IndexDef.hpp>
#include <utilities/Exception.hpp>

#include <vector>
#include <memory>
#include <functional>

namespace AMCAX {
namespace Meshing {
namespace Remeshing {

template <typename Traits>
class FastQEM_Impl;

/**
 * @brief Implement a fast QEM simplification algorithm based on triangle soup.
 * @tparam Traits Define type of point, points and triangles.
 */
template <typename Traits>
class FastQEM
{
public:
	/** @brief Point type.
	 * E.g., Vec3d from any library or a wrapper of it.
	 */
	using iPointT   = typename Traits::PointT;
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
	// initialize by moving points and triangles.
	AMCAXMeshing_API FastQEM(iPoints &&points, iTriangles &&triangles);

	// initialize by copying points and triangles.
	AMCAXMeshing_API FastQEM(const iPoints &points, const iTriangles &triangles);

	AMCAXMeshing_API ~FastQEM() noexcept;

public:
	/**
	 * @brief Algorithm stage reported in process function.
	 */
	enum Stage
	{
		Initialize = 0, // input, calculate quadric error, initialize heap...
		Simplify,       // collapse edges...
		Ending,         // garbage collection, output....
		Total           // Use it to make progress bar :)
	};

	/// @brief function that reports process
	/// @param stage We will report stage (see above `Stage`) by this parameter.
	/// @param current Current sub-stage (e.g., 3/5) or current progress
	/// percentage (e.g., 42/100).
	/// @param total Total sub-stages or total percentage.
	/// @param cancel If set to true, algorithm will be terminated.
	using ProFn =
	  std::function<void(int stage, int current, int total, bool &cancel)>;

	/**
	 * @brief Simplify the triangle mesh.
	 * @param target_fn Target face number. The triangle mesh will be simplified
	 * to the target face number, until it can't be simplified because of
	 * constraints.
	 * @param error_bound Geometrical error bound, given as the percentage of the
	 * diagonal length of the model's bounding box. Value range is (0, 1).
	 * If given error bound if larger than 1, this bound is ignored.
	 * @param max_valence Maximal vertex valence, usually set from 6 to 20.
	 * @param pro_fn function that reports process.
	 * @return No return. The results are stored m_points and m_triangles inplace.
	 *
	 * @details
	 * error_bound =============================================================
	 *   In QEM simplification, each edge is associated with an error, which
	 * evaluates the geometric error when collapsing the edge. The less the
	 * geometric error, the more similar the shape remains. So, the edge with
	 * minimal error is first collapsed, then the edge with the second minimal
	 * error is collapsed, and so on. Once an edge's error is larger than
	 * error_bound, the simplification stops.
	 *   A small error_bound stops simplification earlier and keeps shape better,
	 * while a large error_bound reduce more faces at the expense of shape
	 * similarity.
	 * =========================================================================
	 *
	 * max_valence =============================================================
	 *   Valence of a vertex is the number of its adajcent faces. A mesh is seen
	 * as a high-quality mesh if its vertices' valence are as close to 6 as
	 * possible.
	 *   max_valance constrains the maximal valence of a vertex during
	 * simplification, i.e., if collapsing an edge cause vertices whose valence
	 * exceed max_valence, the edge won't be collapsed anyway.
	 * =========================================================================
	 */
	AMCAXMeshing_API void simplify(size_t target_fn, iNT error_bound,
	                               size_t max_valence, ProFn pro_fn = ProFn());

public:
	/*** input/output data ***/
	iPoints    m_points;
	iTriangles m_triangles;

private:
	/*** Implementation class ***/
	std::unique_ptr<FastQEM_Impl<Traits>> m_impl;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API FastQEM<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API FastQEM<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits 
extern template class AMCAXMeshing_CLASS_API FastQEM<Mesh::TriSoupTraits_Coord>;
#endif
// clang-format on

} // namespace Remeshing
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriSoup_FastQEM.inl"
#endif