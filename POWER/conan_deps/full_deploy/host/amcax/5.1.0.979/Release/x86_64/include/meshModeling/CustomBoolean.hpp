/**
 * @file CustomBoolean.hpp
 * @brief Custom mesh boolean algorithm. Internal use only.
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

namespace AMCAX::Meshing {

namespace Geometry {
class ExactIndirectPredicatesApproxConstructions;
using EIAC = ExactIndirectPredicatesApproxConstructions;
} // namespace Geometry

namespace Boolean {

template <typename Traits>
class CustomBoolean_Impl;

template <typename Kernel, typename Traits>
class CustomBoolean
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
	using Labels          = Arrangements::Labels;

public: /* Constructors ******************************************************/
	AMCAXMeshing_API
	CustomBoolean(bool         _verbose,
	              unsigned int _thread_num = std::thread::hardware_concurrency(),
	              bool         _use_global_cached = true);
	AMCAXMeshing_API ~CustomBoolean() noexcept;

	CustomBoolean(const CustomBoolean &) = delete;
	CustomBoolean(CustomBoolean &&)      = delete;

public: /* Interfaces ********************************************************/
	AMCAXMeshing_API void InitRefTree(const iPoints    &points,
	                                  const iTriangles &triangles);

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

	/**
	 * @brief Set the triangle mesh (triangle soup) as output destination.
	 * @param points points of the output mesh.
	 * @param triangles triangles of the output mesh.
	 * @note We store pointers to output and write to them without check.
	 */
	AMCAXMeshing_API void setTriMeshAsOutput(iPoints    &points,
	                                         iTriangles &triangles);

	/// @brief apply INTERSECTION and put result to output mesh.
	AMCAXMeshing_API void Intersection();

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

	iPoints    *output_points    = nullptr;
	iTriangles *output_triangles = nullptr;

private: /* Internal boolean traits *******************************************/
	class CustomBooleanTraits;
	class RefTree;
	/// Implement class
	std::unique_ptr<CustomBoolean_Impl<CustomBooleanTraits>> m_impl;
	std::unique_ptr<RefTree>                                 m_tree;

private: /* Auxiliary classes and functions ***********************************/
	// Behavior control flags
	bool         verbose;
	unsigned int thread_num;
	bool         use_global_cached;
	class loadMultipleMeshes;
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API
  CustomBoolean<Geometry::EIAC, Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API
  CustomBoolean<Geometry::EIAC, Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API
  CustomBoolean<Geometry::EIAC, Mesh::TriSoupTraits_Coord>;
#endif

} // namespace Boolean
} // namespace AMCAX::Meshing

#ifdef AMCAXMeshing_HAS_IMPL
	#include "CustomBoolean.inl"
#endif