/**
 * @file OBJWriter.hpp
 * @brief Obj file writer.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <mesh/TriSoup.hpp>
#include <mesh/io/IOOptions.hpp>
#include <mesh/io/MTLMaterial.hpp>
#include <mesh/io/OBJGeometry.hpp>

#include <utilities/Exception.hpp>
#include <utilities/Macros.hpp>
#include <utilities/StringUtils.hpp>

#include <array>
#include <fstream>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace AMCAX {
namespace Meshing {
namespace Mesh {

/**
 * @brief Write triangle soup to an OBJ file.
 * @tparam Traits Traits Define types for points, normals triangles.
 * OBJWriter will definen variables of these types to store results.
 */
template <typename Traits>
class OBJWriter
{
public:
	/** @brief Point type. */
	using PointT    = typename Traits::PointT;
	/** @brief Vector type. */
	using NormalT   = typename Traits::NormalT;
	/** @brief texture 2D. */
	using Tex2D     = typename Traits::Tex2D;
	/** @brief texture 3D. */
	using Tex3D     = typename Traits::Tex3D;
	/** @brief color. */
	using Color     = typename Traits::Color;
	/** @brief color with alpha. */
	using ColorA    = typename Traits::ColorA;
	/** @brief triangle. */
	using Triangle  = typename Traits::Triangle;
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
	using ColorAs   = typename Traits::ColorAs;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using Triangles = typename Traits::Triangles;

	using pn_t = std::remove_reference_t<decltype(std::declval<PointT>()[0])>;
	using nn_t = std::remove_reference_t<decltype(std::declval<NormalT>()[0])>;
	using tn_t = std::remove_reference_t<decltype(std::declval<Tex3D>()[0])>;
	using cn_t = std::remove_reference_t<decltype(std::declval<Color>()[0])>;

	// Material list type
	using iMTLMaterial = MTLMaterial<Color>;
	using MaterialIds  = std::map<std::string, size_t>;
	using TextureInfo  = std::map<size_t, std::string>;
	// Object and Group type
	using iOBJBaseGeo  = OBJBaseGeo<Traits>;
	using iOBJObject   = OBJObject<Traits>;
	using iOBJGroup    = OBJGroup<Traits>;

public:
	AMCAXMeshing_API OBJWriter();
	AMCAXMeshing_API ~OBJWriter() noexcept;

	/**
	 * @brief Write triangle soup to file with given options and precison.
	 * @param opt Options to control which parts of triangle soup are written to
	 * file.
	 * @param precision precision of floating point numbers.
	 * @return true if succeed to write the triangle soup.
	 * @note Triangle soup must be stored in member variables of writer before
	 * writing.
	 */
	AMCAXMeshing_API bool write(const std::string &filename, IOOptions &opt,
	                            std::streamsize precision);

	/**
	 * @brief Write triangle soup to file with given options and precison.
	 * @param opt Options to control which parts of triangle soup are written to
	 * file.
	 * @param precision precision of floating point numbers.
	 * @return true if succeed to write the triangle soup.
	 * @note Triangle soup must be stored in member variables of writer before
	 * writing.
	 */
	AMCAXMeshing_API bool write(std::ostream &os, IOOptions &opt,
	                            std::streamsize precision);

	/// @brief Parse mesh face color to m_materials.
	/// @return True if succeed.
	AMCAXMeshing_API bool parse_face_color();

	/** @brief Clear data stored in writer */
	AMCAXMeshing_API void clear();

	// clang-format off
	Points                    m_points;          ///< point position
	Normals                   m_pts_normals;     ///< point normal
	Colors                    m_pts_colors;      ///< point color
	Tex2Ds                    m_pts_texcoords2d; ///< point texture 2d coordinates
	Tex3Ds                    m_pts_texcoords3d; ///< point texture 3d coordinates
	Triangles                 m_triangles;       ///< triangle faces
	Colors                    m_tris_colors;     ///< triangle colors
	ColorAs                   m_tris_coloras;    ///< triangle colors with alpha
	std::vector<iMTLMaterial> m_materials;       ///< mesh material
	MaterialIds               m_mat_ids;         ///< mesh material index
	std::vector<size_t>       m_tris_matids;     ///< triangle material index, -1 is no material
	std::vector<size_t>       m_tris_texids;     ///< triangle texture index, 0 is no texture
	TextureInfo               m_tex_infos;       ///< mesh texture information
	std::vector<iOBJObject>   m_objects;         ///< mesh objects
	std::vector<iOBJGroup>    m_groups;          ///< mesh groups
	std::vector<size_t>		  m_smooth_groups;	 ///< mesh smooth groups, "0", "null", "off" means smooth off
	// clang-format on
private:
	std::string get_extensions() const { return "obj"; }

	bool save_to_stream(std::ostream &out);

	void write_material(const std::vector<const char *> &mat_labels);

private:
	std::string path, obj_name;

	IOOptions user_options;
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API OBJWriter<TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API OBJWriter<TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API OBJWriter<TriSoupTraits_Coord>;
#endif

} // namespace Mesh
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "OBJWriter.inl"
#endif