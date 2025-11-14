/**
 * @file TriMeshRepair.hpp
 * @brief Repair triangle mesh to clean mesh.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

// clang-format off
#include <utilities/Macros.hpp>
#include <mesh/TriSoup.hpp>
// clang-format on

#include <deque>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <stack>
#include <thread>
#include <unordered_map>
#include <vector>

namespace AMCAX {
namespace Meshing {
namespace MeshTools {

template <typename Traits>
class TriMeshRepair_Impl;

template <typename Traits>
class TriMeshRepair
{
public:
	/** @brief Point type.
	 * E.g., Vec3d from any library or a wrapper of it.
	 */
	using iPointT   = typename Traits::PointT;
	/** @brief Vector type.
	 * It is derived from PointT, representing the difference between two points.
	 */
	using iTriangle = typename Traits::Triangle;
	/** @brief Number type in PointT.
	 * We also expect that PointT provides x(), y() and z().
	 */
	using iNT  = std::remove_reference_t<decltype(std::declval<iPointT>().x())>;
	/** @brief index in triangle */
	using ti_t = std::remove_reference_t<decltype(std::declval<iTriangle>()[0])>;
	static constexpr ti_t invalid_ti = (ti_t)-1;

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
	AMCAXMeshing_API
	TriMeshRepair(unsigned int thread_num = std::thread::hardware_concurrency());

	AMCAXMeshing_API
	TriMeshRepair(iPoints &&points, iTriangles &&triangles,
	              unsigned int thread_num = std::thread::hardware_concurrency());

	AMCAXMeshing_API
	TriMeshRepair(const iPoints &points, const iTriangles &triangles,
	              unsigned int thread_num = std::thread::hardware_concurrency());

	AMCAXMeshing_API ~TriMeshRepair() noexcept;

public: /* Stage Report ******************************************************/
	enum Stage
	{
		Preprocess = 0,
		Routine1,
		Routine2,
		Routine3,
		Routine4,
		Routine5,
		Routine6,
		Total // Use it to make progress bar :)
	};

	/// @brief function that reports process
	/// @param stage We will report stage (see above `Stage`) by this parameter.
	/// @param cancel If set to true, algorithm will be terminated.

	using ProFn = std::function<void(int stage, bool &cancel)>;

public: /* Interfaces ********************************************************/
	/**
	 * @brief add a triangle mesh (triangle soup) as input.
	 * @param points points of the mesh.
	 * @param triangles triangles of the mesh.
	 */
	AMCAXMeshing_API void setInput(const iPoints    &points,
	                               const iTriangles &triangles);

	/**
	 * @brief Repair triangle soup by calling all routines.
	 * @param points points of the mesh.
	 * @param triangles triangles of the mesh.
	 * @return No return. The results are stored in m_points and m_triangles
	 * inplace. Some faces which are judged dangling open surfaces are stored in
	 * m_sheets_points and m_sheets_triangles
	 * @note This func use a radical method and may remove too much faces that
	 * need left.If this func can't produce a good result mesh,
	 * orient_polygon_soup or hole_filling can be used instead which will can
	 * leave all triangles that bound the solid.
	 */
	AMCAXMeshing_API void repair(bool hole_fill, ProFn pro_fn = ProFn());
	/**
	 * @brief Preprocess the triangle soup and orient all triangles.
	 * @return No return. The results are stored in m_points and m_triangles
	 * inplace.
	 */
	AMCAXMeshing_API void orient_polygon_soup();
	/**
	 * @brief Fill all holes in triangle soup.
	 * @return No return. The results are stored in m_points and m_triangles
	 * inplace.
	 */
	AMCAXMeshing_API void hole_filling();

	AMCAXMeshing_API void stitch_triangles(const double tolerance = 0.0001);

	AMCAXMeshing_API size_t
	remove_duplicate_vertices(const double tolerance = 0.0001);

	AMCAXMeshing_API size_t remove_double_triangles();

	AMCAXMeshing_API size_t remove_isolated_vertices();

	AMCAXMeshing_API void remove_tiny_shells(const size_t min_faces_num = 5);
	iPoints               m_points;
	iTriangles            m_triangles;
	// Dangling open surfaces remained that do not bound any solid. These are
	// saved to m_sheets_points and m_sheets_triangles
	iPoints               m_sheets_points;
	iTriangles            m_sheets_triangles;

private:
	class RepairTraits;

	/// Implement class
	std::unique_ptr<TriMeshRepair_Impl<RepairTraits>> m_impl;

	unsigned int m_thread_num;
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API TriMeshRepair<Mesh::TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API
  TriMeshRepair<Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API
  TriMeshRepair<Mesh::TriSoupTraits_Coord>;
#endif

} // namespace MeshTools
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "TriMeshRepair.inl"
#endif