/**
 * @file MeshBoolean.hpp
 * @brief Mesh boolean algorithm.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

// Definitions from mesh arrangements
#include <meshModeling/ArrangementUtils.hpp>
// Triangle soup for input and output
#include <mesh/TriSoup.hpp>
// Utils
#include <utilities/IndexDef.hpp>
#include <utilities/Macros.hpp>

#include <bitset>
#include <memory>
#include <thread>
#include <vector>

namespace AMCAX {
namespace Meshing {

namespace Geometry {
class ExactIndirectPredicatesApproxConstructions;
using EIAC = ExactIndirectPredicatesApproxConstructions;
} // namespace Geometry

namespace Boolean {

enum class MeshBooleanOp
{
	UNION,
	INTERSECTION,
	SUBTRACTION,
	XOR,
	NONE
};

template <typename Traits>
class MeshBoolean_Impl;

template <typename Kernel, typename Traits>
class MeshBoolean
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
	using iSourceFaceInfo = Arrangements::SourceFaceInfo<ti_t>;
	/** @brief Intersection segments type.
	 */
	using InterSegments   = Arrangements::InterSegments<ti_t>;
	/** @brief Target mesh labels.
	 */
	using Labels = Arrangements::Labels;

public: /* Constructors ******************************************************/
	AMCAXMeshing_API
	MeshBoolean(bool         _verbose,
	            unsigned int _thread_num = std::thread::hardware_concurrency(),
	            bool         _use_global_cached = true);
	AMCAXMeshing_API ~MeshBoolean() noexcept;

	MeshBoolean(const MeshBoolean &) = delete;
	MeshBoolean(MeshBoolean &&)      = delete;

public: /* Interfaces ********************************************************/
	/**
	 * @brief add a triangle mesh (triangle soup) as one input.
	 * @param points points of the mesh.
	 * @param triangles triangles of the mesh.
	 * @return index_t The internal index of the added mesh. It will used in
	 * labels of output triangle mesh.
	 * @note We only store pointers to input, won't store a copy, make sure the
	 * pointers are always valid during boolean.
	 */
	AMCAXMeshing_API index_t addTriMeshAsInput(const iPoints    &points,
	                                           const iTriangles &triangles);

	///** return single mesh
	// * @brief Set the arrangement mesh (triangle soup) as output destination.
	// * @param points points of the arrangement mesh.
	// * @param triangles triangles of the arrangement mesh.
	// * @note We store pointers to output and write to them without check.
	// */
	AMCAXMeshing_API void setArrangeMeshAsOutput(iPoints    &points,
	                                             iTriangles &triangles);

	/**
	 * @brief Set the result_meshes (triangle soup) as output destination.
	 * @param result_meshes split the output mesh into sub-meshes based on connected components
	 * @note We store pointers to output and write to them without check.
	 */
	AMCAXMeshing_API void setTriMeshAsOutput(std::vector<std::pair<iPoints,iTriangles>> &result_meshes);


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
	setOutputLabels(std::vector<std::vector<Arrangements::Label>> &labels);

	///////////////////////////////////////////////////////////////////////
	/// Complete boolean pipeline contains four steps:                  ///
	/// (1) Run arrangements on all triangles.                          ///
	/// (2) Label triangles.                                            ///
	/// (3) apply boolean operation based on label.                     ///
	/// (4) compute explicit result and output.                         ///
	///////////////////////////////////////////////////////////////////////

	/// @brief Run (1)arrangements and (2)labeling. Store arrangements results and
	/// labels internally. (Then, users can apply different boolean operations and
	/// get final results faster.)
	AMCAXMeshing_API void
	computeLabels(bool ignore_intersection_in_same_mesh = true);

	/// @brief Compute target labels for the mesh with the given index. Other
	/// meshes' labels maybe not correct.
	AMCAXMeshing_API void
	computeTargetLabels(size_t mesh_id,
	                    bool   ignore_intersection_in_same_mesh =
	                      true); // compute arr_out_label and patches

	/// @brief In order to obtain the intersection segments, we need call this
	/// after computing labels.
	AMCAXMeshing_API void computeInterSegments();

	/// @brief apply (3)UNION and (4)put result to output mesh.
	AMCAXMeshing_API void Union();
	/// @brief apply (3)INTERSECTION and (4)put result to output mesh.
	AMCAXMeshing_API void Intersection();
	/// @brief apply (3)SUBTRACTION and (4)put result to output mesh.
	AMCAXMeshing_API void Subtraction();
	/// @brief apply (3)XOR and (4)put result to output mesh.
	AMCAXMeshing_API void Xor();

	/// @brief Get the face infomation from input meshes to output meshes.
	/// @brief For output meshes with multiple connected components.
	/// @return The face infomation from input meshes to output meshes.
	AMCAXMeshing_API std::vector<std::vector<iSourceFaceInfo>> &getSourceFaceInfoMeshes();


	/// @brief Get the vertex index of the intersection segments.
	/// brief For output meshes with multiple connected components.
	/// @return the vertex index of the intersection segments.
	AMCAXMeshing_API std::vector<std::vector<InterSegments>> &getInterSegmentsMeshes();


	AMCAXMeshing_API Labels &getTargetLabels();  // arr_out_label

	AMCAXMeshing_API std::vector<std::vector<ti_t>> getTrisPatches(); //patches

	/// @brief Clear input meshes, output mesh, and all internal data.
	/// Clearing is equivalent to reseting all to initial state.
	AMCAXMeshing_API void clear();

private:
	struct iTriSoup
	{
		const iPoints    *points;
		const iTriangles *triangles;
	};
	std::vector<iTriSoup> input_meshes;
	std::vector<std::pair<iPoints, iTriangles>> *output_meshes = nullptr;
	iPoints    *arrange_points = nullptr;
	iTriangles *arrange_triangles = nullptr;
	std::vector<std::vector<Arrangements::Label>> *output_labels_meshes = nullptr;
	std::vector<std::vector<iSourceFaceInfo>>      output_face_info_meshes;
	std::vector<std::vector<InterSegments>>        output_inter_segs_meshes;

private: /* Internal boolean traits *******************************************/
	class BooleanTraits;
	/// Implement class
	std::unique_ptr<MeshBoolean_Impl<BooleanTraits>> m_impl;

private: /* Auxiliary classes and functions ***********************************/
	// Behavior control flags
	bool verbose;

	unsigned int thread_num;

	bool use_global_cached;

	class loadMultipleMeshes;

	void booleanPipeline(MeshBooleanOp op);
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API
  MeshBoolean<Geometry::EIAC, Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API
  MeshBoolean<Geometry::EIAC, Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API
  MeshBoolean<Geometry::EIAC, Mesh::TriSoupTraits_Coord>;
#endif

} // namespace Boolean
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "MeshBoolean.inl"
#endif