/**
 * @file TriMeshCut.hpp
 * @brief Greedy cut algorithm for triangle mesh.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

// Triangle soup for input and output
#include <mesh/TriSoup.hpp>

#include <memory>
#include <thread>

namespace AMCAX::Meshing::TriMeshCut {

template <typename Traits>
class GreedyCut_Impl;

template <typename Traits>
class GreedyCut
{
public: /* Traits about input data ********************************************/
	/** @brief Point type.
	 * E.g., Vec3d from any library or a wrapper of it.
	 */
	using iPoint    = typename Traits::PointT;
	/** @brief Triangle type. */
	using iTriangle = typename Traits::Triangle;
	/** @brief Number type in PointT.
	 * We also expect that PointT provides x(), y() and z().
	 */
	using iNT  = std::remove_reference_t<decltype(std::declval<iPoint>().x())>;
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
	AMCAXMeshing_API
	GreedyCut(const iPoints &i_points, const iTriangles &i_triangles,
	          bool         verbose    = false,
	          unsigned int thread_num = std::thread::hardware_concurrency());

	AMCAXMeshing_API ~GreedyCut() noexcept;

	/// @brief Triangle mesh cut function.
	/// @param o_points Output mesh points.
	/// @param o_triangles Output mesh triangle.
	/// @param cut_length The length of cut path, the value is smaller, the path
	/// is longer.
	AMCAXMeshing_API void cut(iPoints &o_points, iTriangles &o_triangles,
	                          size_t cut_length = 20);

	AMCAXMeshing_API void construct_select_faces(iPoints    &o_select_pts,
	                                             iTriangles &o_select_tris,
	                                             ti_t        start_id, double raduis);

private:
	/// Implement class
	std::unique_ptr<GreedyCut_Impl<Traits>> m_impl;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API GreedyCut<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API GreedyCut<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API GreedyCut<Mesh::TriSoupTraits_Coord>;
#endif
// clang-format on

} // namespace AMCAX::Meshing::TriMeshCut

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriMeshCut.inl"
#endif