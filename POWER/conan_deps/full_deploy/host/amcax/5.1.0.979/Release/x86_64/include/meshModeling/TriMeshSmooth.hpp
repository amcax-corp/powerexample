/**
 * @file TriMeshSmooth.hpp
 * @brief Triangle mesh smooth algorithm.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */


#pragma once

#include <mesh/TriSoup.hpp>

#include <memory>

namespace AMCAX::Meshing::MeshTools {

template <typename Traits>
class TriMeshSmooth_Impl;

template <typename Traits>
class TriMeshSmooth
{
public:
	/* Traits about input data ********************************************/
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
	AMCAXMeshing_API TriMeshSmooth(iPoints &points, iTriangles &triangles,
	                               size_t smooth_times, iNT sigma_normal,
	                               bool is_manifold = true);

	AMCAXMeshing_API ~TriMeshSmooth() noexcept;

private:
	std::unique_ptr<TriMeshSmooth_Impl<Traits>> m_impl;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
	extern template class AMCAXMeshing_CLASS_API TriMeshSmooth<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
	extern template class AMCAXMeshing_CLASS_API TriMeshSmooth<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
	extern template class AMCAXMeshing_CLASS_API TriMeshSmooth<Mesh::TriSoupTraits_Coord>;
#endif
// clang-format on
} // namespace AMCAX::Meshing::MeshTools

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriMeshSmooth.inl"
#endif