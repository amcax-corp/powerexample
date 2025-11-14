/**
 * @file MeshArrangements.hpp
 * @brief Interfaces of mesh arrangements.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <meshModeling/ArrangementUtils.hpp>

// Triangle soup
#include <mesh/TriSoup.hpp>
// Utils
#include <utilities/IndexDef.hpp>
#include <utilities/Macros.hpp>

#include <memory>
#include <thread>

namespace AMCAX {
namespace Meshing {

namespace Geometry {
class ExactIndirectPredicatesApproxConstructions;
using EIAC = ExactIndirectPredicatesApproxConstructions;
} // namespace Geometry

namespace Arrangements {

template <typename Traits>
class MeshArrangements_Impl;

template <typename Kernel, typename Traits>
class MeshArrangements
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
	using iPoints         = typename Traits::Points;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using iTriangles      = typename Traits::Triangles;
	/** @brief Source face info type.
	 */
	using iSourceFaceInfo = SourceFaceInfo<ti_t>;
	/** @brief Intersection segments type.
	 */
	using InterSegments   = Arrangements::InterSegments<ti_t>;

public: /* Constructors ******************************************************/
	AMCAXMeshing_API MeshArrangements(
	  bool         _verbose,
	  unsigned int _thread_num = std::thread::hardware_concurrency(),
	  bool         _use_global_cached = true);

	AMCAXMeshing_API ~MeshArrangements() noexcept;

	MeshArrangements(const MeshArrangements &) = delete;
	MeshArrangements(MeshArrangements &&)      = delete;

public: /* Interfaces ********************************************************/
	/**
	 * @brief add a triangle mesh (triangle soup) as one input.
	 * @param points points of the mesh.
	 * @param triangles triangles of the mesh.
	 * @return index_t The internal index of the just added mesh.
	 * @note We only store pointers to input, won't store a copy.
	 */
	AMCAXMeshing_API index_t addTriMeshAsInput(const iPoints    &points,
	                                           const iTriangles &triangles);

	/**
	 * @brief Set the triangle mesh (triangle soup) as output destination.
	 * @param points points of the mesh.
	 * @param triangles triangles of the mesh.
	 * @note We store pointers to output and write to them without check.
	 */
	AMCAXMeshing_API void setTriMeshAsOutput(iPoints    &points,
	                                         iTriangles &triangles);

	/**
	 * @brief Set the output labels.
	 * @details
	 * * Each input triangle mesh will be attached with an index internally
	 *   (the index is the return value of addTriMeshAsInput).
	 * * Each output triangle's label indicates the triangle mesh it locates on.
	 * * Labels are used to transfer attributes from input triangle meshes to
	 * output triangle meshes.
	 * @param labels labels of the output mesh.
	 * @return AMCAXMeshing_API
	 */
	AMCAXMeshing_API void
	setOutputLabels(std::vector<Arrangements::Label> &labels);

	/// @brief Get the face infomation from input meshes to output meshes.
	/// @return
	AMCAXMeshing_API std::vector<iSourceFaceInfo> &getSourceFaceInfo();

	/// @brief Get the vertex index of the intersection segments.
	/// @return the vertex index of the intersection segments.
	AMCAXMeshing_API std::vector<InterSegments> &getInterSegments();

	/// @brief Clear input meshes and output mesh.
	AMCAXMeshing_API void clear();

	/// @brief Apply arrangement operation on input meshes and save explicit
	/// result to output mesh.
	/// @param ignore_intersection_in_same_mesh If set to true, algorithm will
	/// ignore intersection between triangles in the same mesh. This is a feature
	/// used by mesh boolean.
	/// @param output_explicit_result If set to true, the explicit result (points
	/// and triangles) will be saved in output mesh set by setTriMeshAsOutput.
	/// All middle data will be cleared.
	AMCAXMeshing_API void meshArrangements(bool ignore_intersection_in_same_mesh,
	                                       bool output_explicit_result);

	/// @brief In order to obtain the intersection segments, we need call this
	/// after computing labels.
	AMCAXMeshing_API void computeInterSegments();

	AMCAXMeshing_API MeshArrangements_Stats &stats();

private:
	/// Input data
	struct iTriSoup
	{
		const iPoints    *points    = nullptr;
		const iTriangles *triangles = nullptr;
	};
	std::vector<iTriSoup>      input_meshes;
	/// Output data
	iPoints                   *output_points    = nullptr;
	iTriangles                *output_triangles = nullptr;

	std::vector<Arrangements::Label> *output_labels = nullptr;
	std::vector<InterSegments>        output_inter_segs;

	/// behavior control flags
	bool                   verbose;
	MeshArrangements_Stats arr_stats;
	unsigned int           thread_num;
	bool                   use_global_cached;

private:
	class ArrangementsTraits;

	/// Implement class
	std::unique_ptr<MeshArrangements_Impl<ArrangementsTraits>> m_impl;

	class loadMultipleMeshes;
};

// clang-format off
#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API MeshArrangements<Geometry::EIAC, Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API MeshArrangements<Geometry::EIAC, Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API MeshArrangements<Geometry::EIAC, Mesh::TriSoupTraits_Coord>;
#endif
// clang-format on

} // namespace Arrangements
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "MeshArrangements.inl"
#endif