/**
 * @file TriMeshExtrude.hpp
 * @brief Mesh extrude functions.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once
// Utils
#include <utilities/Macros.hpp>
// Triangle soup for input and output
#include <mesh/TriSoup.hpp>

namespace AMCAX::Meshing::MeshTools {

template <typename Traits>
class TriMeshExtrude
{
public:
	/* Traits about input data ********************************************/
	/** @brief Vector type. */
	using iVec       = typename Traits::VecT;
	/** @brief An array that stores points for vertices.
	 * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	 */
	using iPoints    = typename Traits::Points;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using iTriangles = typename Traits::Triangles;

public: /* Constructors ******************************************************/
	AMCAXMeshing_API TriMeshExtrude(iPoints &points, iTriangles &triangles,
	                                const iVec &vec);

	AMCAXMeshing_API ~TriMeshExtrude() noexcept = default;
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API TriMeshExtrude<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API TriMeshExtrude<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API TriMeshExtrude<Mesh::TriSoupTraits_Coord>;
#endif

} // namespace AMCAX::Meshing::MeshTools

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriMeshExtrude.inl"
#endif