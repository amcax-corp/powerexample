/**
 * @file OBJGeometry.hpp
 * @brief Obj file geometry part definition.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <mesh/TriSoup.hpp>

namespace AMCAX::Meshing::Mesh {

template <typename Traits>
class OBJBaseGeo
{
public:
	/** @brief An array that stores points for vertices.
	 * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	 */
	using Points    = typename Traits::Points;
	/** @brief An array that stores normals.
	 * E.g., std::vector<NormalT> or Eigen::VectorX<NormalT>.
	 */
	using Normals   = typename Traits::Normals;
	/** @brief An array that stores texture 2d coordinates. */
	using Tex2Ds    = typename Traits::Tex2Ds;
	/** @brief An array that stores texture 3d coordinates. */
	using Tex3Ds    = typename Traits::Tex3Ds;
	/** @brief An array that stores colors . */
	using Colors    = typename Traits::Colors;
	/** @brief An array that stores colorAs . */
	using ColorAs    = typename Traits::ColorAs;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using Triangles = typename Traits::Triangles;

public:
	OBJBaseGeo()
	  : m_start_f{static_cast<size_t>(-1)}
	  , m_end_f{static_cast<size_t>(-1)}
	  , m_label{""}
	{
	}

	const std::string &label() const { return m_label; }
	size_t             start_face() const { return m_start_f; }
	size_t             end_face() const { return m_end_f; }
	std::string       &label() { return m_label; }
	size_t            &start_face() { return m_start_f; }
	size_t            &end_face() { return m_end_f; }

private:
	/// @brief  The two variables record the start and end global index, with a
	/// left-closed and right-open range.
	size_t      m_start_f;
	size_t      m_end_f;
	std::string m_label;

public:
	// clang-format off
	/// @brief If mesh is split to object or group, these will store local mesh.
	Points    m_points;				   ///< point position
	Normals   m_pts_normals;		   ///< point normal
	Colors    m_pts_colors;			   ///< point color
	Tex2Ds    m_pts_texcoords2d;	   ///< point texture 2d coordinates
	Tex3Ds    m_pts_texcoords3d;	   ///< point texture 3d coordinates
	Triangles m_triangles;			   ///< triangle faces
	Colors    m_tris_colors;		   ///< triangle colors
	ColorAs   m_tris_coloras;		   ///< triangle coloras
	Tex2Ds    m_tris_texcoords2d;	   ///< trianlge texture 2d coordinates
	Tex3Ds    m_tris_texcoords3d;	   ///< triangle texture 3d coordinates
	std::vector<size_t> m_tris_matids; ///< triangle material index, -1 is no material
	std::vector<size_t> m_tris_texids; ///< triangle texture index, 0 is no texture
	// clang-format on
};

template <typename Traits>
class OBJGroup : public OBJBaseGeo<Traits>
{
public:
	OBJGroup()
	  : m_group_id{static_cast<size_t>(-1)}
	{
	}

	size_t  id() const { return m_group_id; }
	size_t &id() { return m_group_id; }

private:
	size_t m_group_id;
};

template <typename Traits>
class OBJObject : public OBJBaseGeo<Traits>
{
public:
	OBJObject()
	  : m_object_id{static_cast<size_t>(-1)}
	{
	}

	size_t  id() const { return m_object_id; }
	size_t &id() { return m_object_id; }

private:
	size_t m_object_id;

public:
	std::vector<size_t> m_groups;
};

} // namespace AMCAX::Meshing::Mesh