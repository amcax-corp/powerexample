/// @file		STEPMesh.hpp
/// @brief		Class for reading STEP file and convert solid to mesh.
/// @copyright	Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par		This file is part of AMCAX kernel.
#pragma once

#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <memory>
#include <optional>

#include <common/Macros.hpp>

#include <mesh/TriSoup.hpp>

#include <topology/TopologyMacros.hpp>

#include <step/mesh/STEPMeshProgress.hpp>

namespace AMCAX
{
// forward declarations
class TopoShape;
// end forward declarations
namespace STEP
{
/// @brief Class for reading STEP file and convert solid to mesh.
template<typename Traits>
class STEPMesh
{
public:
	/// @brief Point type.
	using PointT = typename Traits::PointT;
	/// @brief Vector type.
	using NormalT = typename Traits::NormalT;

	/// @brief triangle.
	using Triangle = typename Traits::Triangle;

	/// @brief An array that stores points for vertices.
	/// E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	using Points = typename Traits::Points;

	/// @brief An array that stores normals.
	/// E.g., std::vector<NormalT> or Eigen::VectorX<NormalT>.
	using Normals = typename Traits::Normals;

	/// @brief An array that stores indices of three vertices for all faces.
	/// E.g., std::vector<std::array<index_t,3>> or
	/// Eigen::VectorX<Eigen::Vector3i>.
	using Triangles = typename Traits::Triangles;

	using pn_t = std::remove_reference_t<decltype(std::declval<PointT>()[0])>;
	using nn_t = std::remove_reference_t<decltype(std::declval<NormalT>()[0])>;
	using ti_t = std::remove_reference_t<decltype(std::declval<Triangle>()[0])>;

public:
	static constexpr double DefaultLinDeflection = 1e-2;

public:
	/// @brief Default constructor.
	AMCAX_API STEPMesh();

	/// @brief Default destructor.
	AMCAX_API ~STEPMesh() noexcept;

	/// @brief Read triangle soup from the file. results will be stored in member
	/// variables of reader, e.g., \ref points, \ref triangles.
	/// @param shape The shape to be meshed. Required to have at least one TopoShell element.
	/// @param linDeflection The linear deflection.
	/// @param isRelative Determine whether the deflection is computed relatively
	/// @return true if succeed to read the file.
	AMCAX_API bool read(const TopoShape& shape, double linDeflection = 1e-2,
		bool isRelative = true);

	/// @brief Read triangle soup from the file. results will be stored in member
	/// variables of reader, e.g., \ref points, \ref triangles.
	/// @param shape The shape to be meshed. Required to have at least one TopoShell element.
	/// @param linDeflection The linear deflection.
	/// @param isRelative Determine whether the deflection is computed relatively
	/// @param angDeflection The angle deflection
	/// @return true if succeed to read the file.
	AMCAX_API bool read(const TopoShape& shape, double linDeflection,
		bool isRelative, double angDeflection);

	/// @brief Convert pre-existing mesh data to STEPMesh format.
	/// @param shape TopoShape object with pre-existing mesh data.
	/// @return true if succeed to do the conversion.
	AMCAX_API bool readPreMeshed(const TopoShape& shape);

	/// @brief Get Point positions
	/// @return An array that stores points for vertices.
	AMCAX_API const Points& MPoints() const;

	/// @brief Get Point normals
	/// @return An array that stores normals.
	AMCAX_API const Normals& MNormals() const;

	/// @brief Get triangle faces
	/// @return An array that stores indices of three vertices for all faces.
	AMCAX_API const Triangles& MTriangles() const;

private:
	Points m_points;	   ///< point position
	Normals m_normals;	   ///< point normal
	Triangles m_triangles; ///< triangle faces
};

#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAX_CLASS_API STEPMesh<Meshing::Mesh::TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAX_CLASS_API STEPMesh<Meshing::Mesh::TriSoupTraits_Coord>;
#endif
} // namespace STEP
} // namespace AMCAX
