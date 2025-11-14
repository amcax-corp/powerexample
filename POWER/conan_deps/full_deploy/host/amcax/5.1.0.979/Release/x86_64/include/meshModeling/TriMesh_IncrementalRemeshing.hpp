/**
 * @file TriMesh_IncrementalRemeshing.hpp
 * @brief Interfaces of triMesh incremental remeshing.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */
#pragma once

#include <mesh/TriSoup.hpp>
#include <utilities/Macros.hpp>

#include <memory>

namespace AMCAX {
namespace Meshing {
namespace Remeshing {

template <typename Traits>
class TriMesh_IncrementalRemeshing_Impl;

template <typename Traits>
class TriMesh_IncrementalRemeshing
{
public: /* Traits about input data ********************************************/
	/** @brief An array that stores points for vertices.
	 * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	 */
	using iPoints    = typename Traits::Points;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using iTriangles = typename Traits::Triangles;

	/**
	 * @brief the parameters that control the remeshing
	 */
	struct Params
	{
		/**
		* @brief Max error between reference mesh and variable mesh
		*/
		double Max_error        = 0.0005;
		/**
		 * @brief Target edge length expressed as a percentage of the mean
		 * length of all edges
		 */
		double targetEdgeLength = 0.5;
		/**
		 * @brief If true, adaptive remeshing; else, isotropic remeshing
		 */
		bool   isAdaptive       = false;
		/**
		 * @brief Whether keep the feature or not, not yet implemented
		 */
		bool   featurePreserved = false;
		/**
		 * @brief Dihedral angle greater than tolAngle (in radians) will be
		 * recognized as a feature edge, default value pi/4
		 */
		double tolAngle         = 0.7854;
		/**
		 * @brief The iterations number
		 */
		size_t iterNum          = 5;
	};

public:
	AMCAXMeshing_API TriMesh_IncrementalRemeshing();
	AMCAXMeshing_API ~TriMesh_IncrementalRemeshing() noexcept;

	/**
	 * @brief add a triangle mesh (triangle soup) as one input.
	 * @param points points of the mesh.
	 * @param triangles triangles of the mesh.
	 * @note We only store pointers to input, won't store a copy, make sure the
	 * pointers are always valid during remeshing.
	 */
	AMCAXMeshing_API void setReferenceMesh(const iPoints    &points,
	                                       const iTriangles &triangles);

	/**
	 * @brief Set the triangle mesh (triangle soup) as output destination.
	 * @param points points of the output mesh.
	 * @param triangles triangles of the output mesh.
	 * @note We store pointers to output and write to them without check.
	 */
	AMCAXMeshing_API void setVariableMesh(iPoints &points, iTriangles &triangles);


	/**
	 * @brief Adaptive/Isotropic remeshing controled by the control parameters
	 * @param params remeshing control parameters
	 */
	AMCAXMeshing_API void remesh(Params params);


private:
	/// Implement class
	class IncRemTraits;
	std::unique_ptr<TriMesh_IncrementalRemeshing_Impl<IncRemTraits>> r_impl;


	const iPoints    *input_points     = nullptr;
	const iTriangles *input_triangles  = nullptr;
	iPoints          *output_points    = nullptr;
	iTriangles       *output_triangles = nullptr;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API TriMesh_IncrementalRemeshing<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API TriMesh_IncrementalRemeshing<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API TriMesh_IncrementalRemeshing<Mesh::TriSoupTraits_Coord>;
#endif
// clang-format on

} // namespace Remeshing
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriMesh_IncrementalRemeshing.inl"
#endif