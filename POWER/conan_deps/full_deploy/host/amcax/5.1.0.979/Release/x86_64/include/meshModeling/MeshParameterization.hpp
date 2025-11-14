/**
 * @file MeshParameterization.hpp
 * @brief Bijective parameterization algorithm.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

// Triangle soup for input and output
#include <mesh/TriSoup.hpp>

#include <memory>

namespace AMCAX::Meshing::Parameterization {

template <typename Traits>
class BijectivePara_Impl;

template <typename Traits>
class BijectivePara
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
	/// @brief The function of bijective parameterization algorithm.
	/// @param ipts The points of input mesh.
	/// @param itris The triangles of input mesh.
	/// @param opts The parameter coordinate of input mesh.
	AMCAXMeshing_API BijectivePara(const iPoints &i_pts, const iTriangles &i_tris,
	                               iPoints &o_pts, bool verbose = false);

	AMCAXMeshing_API ~BijectivePara() noexcept;

	/// @brief Check if input mesh has open boundary.
	AMCAXMeshing_API bool hasBoundary();

	/// @brief Perform parameterization of input mesh.
	/// @param max_iter_num Maximum number of iterations.
	AMCAXMeshing_API void parameterization(size_t max_iter_num = 5000);

private:
	/// Implement class
	std::unique_ptr<BijectivePara_Impl<Traits>> m_impl;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API BijectivePara<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API BijectivePara<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API BijectivePara<Mesh::TriSoupTraits_Coord>;
#endif
// clang-format on

} // namespace AMCAX::Meshing::Parameterization

