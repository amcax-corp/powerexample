/**
 * @file OBJReader.hpp
 * @brief Obj file reader.
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
 * @brief Read triangle soup from an OBJ file.
 * @tparam Traits Define types for points, normals triangles.
 * OBJReader will definen variables of these types to store results.
 */
template <typename Traits>
class OBJReader
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
	using ti_t = std::remove_reference_t<decltype(std::declval<Triangle>()[0])>;

	// Material list type
	using iMTLMaterial = MTLMaterial<Color>;
	using MaterialIds  = std::map<std::string, size_t>;
	using TextureInfo  = std::map<size_t, std::string>;
	// Object and Group type
	using iOBJBaseGeo  = OBJBaseGeo<Traits>;
	using iOBJObject   = OBJObject<Traits>;
	using iOBJGroup    = OBJGroup<Traits>;

public:
	AMCAXMeshing_API OBJReader();
	AMCAXMeshing_API ~OBJReader() noexcept;

	/**
	 * @brief Read triangle soup from the file. results will be stored in member
	 * variables of reader, e.g., \ref points, \ref faces.
	 * @param[in] filename path/name of the file.
	 * @param[inout] opt Options given by user, used to alternately read parts of
	 * file. File may not provide all options required by user, so, the common
	 * parts are returned.
	 * @return true if succeed to read the file.
	 */
	AMCAXMeshing_API bool read(const std::string &filename, IOOptions &opt);

	/**
	 * @brief Read triangle soup from the file. results will be stored in member
	 * variables of reader, e.g., \ref points, \ref faces.
	 * @param[in] input file stream.
	 * @param[inout] opt Options given by user, used to alternately read parts of
	 * file. File may not provide all options required by user, so, the common
	 * parts are returned.
	 * @return true if succeed to read the file.
	 */
	AMCAXMeshing_API bool read(std::istream &is, IOOptions &opt);

	/// @brief Clear all the read data.
	AMCAXMeshing_API void clear();
	/// @brief Split mesh into objects.
	AMCAXMeshing_API void split_by_object();
	/// @brief Split mesh into groups.
	AMCAXMeshing_API void split_by_group();

	// clang-format off
	Points    m_points;                      ///< point position
	Normals   m_pts_normals;                 ///< point normal
	Colors    m_pts_colors;                  ///< point color
	Tex2Ds    m_pts_texcoords2d;             ///< point texture 2d coordinates
	Tex3Ds    m_pts_texcoords3d;             ///< point texture 3d coordinates
	Triangles m_triangles;                   ///< triangle faces
	Colors    m_tris_colors;                 ///< triangle colors, if no color, will be set 1.0
	ColorAs   m_tris_coloras;				 ///< triangle colors with alpha, if no color, will be set 1.0
	Tex2Ds    m_tris_texcoords2d;            ///< triangles texture 2d coordinates
	Tex3Ds    m_tris_texcoords3d;            ///< triangle texture 3d coordinates
	std::vector<iMTLMaterial> m_materials;   ///< mesh material
	MaterialIds               m_mat_ids;     ///< mesh material index
	std::vector<size_t>       m_tris_matids; ///< triangle material index, -1 is no material
	std::vector<size_t>       m_tris_texids; ///< triangle texture index, 0 is no texture
	TextureInfo               m_tex_infos;   ///< mesh texture information
	std::vector<iOBJObject>   m_objects;     ///< mesh objects
	std::vector<iOBJGroup>    m_groups;      ///< mesh groups
	std::vector<size_t>	m_smooth_groups;     ///< mesh smooth groups, "0", "null", "off" means smooth off
	// clang-format on
private:
	std::string get_extensions() const { return "obj"; }

	/**
	 * @brief Check if reader is able to open/read the file.
	 * @param filename path/name of the file.
	 * @return true if reader can read the file.
	 */
	bool can_read(const std::string &filename) const;

	/**
	 * @brief After reading file as stream, load triangle soup from the stream.
	 * @param in input stream
	 * @param opt options given by user, used to alternately read part of triangle
	 * soup from file.
	 * @return true if succeed to read the triangle soup.
	 */
	bool load_from_stream(std::istream &in, IOOptions &opt);

	/**
	 * @brief Read vertices from the stream, including points, texture coordinates,
	 * normals.
	 * @param in input stream
	 * @return true if succeed to read vertices.
	 */
	bool read_vertices(std::istream &in);

	/// @brief When key_word is v, process data store in stream.
	bool read_v(std::stringstream &stream);
	/// @brief When key_word is vt, process data store in stream.
	bool read_vt(std::stringstream &stream);
	/// @brief When key_word is vc, process data store in stream.
	bool read_vc(std::stringstream &stream);
	/// @brief When key_word is vn, process data store in stream.
	bool read_vn(std::stringstream &stream);

	/**
	 * @brief Read faces from the stream. A line of face data contains multiple
	 * blocks (v0 v1 v2), each blocks may contains multiple components
	 * (vertex/texcoord/normal).
	 * @param in input stream.
	 * @return
	 */
	bool read_faces(std::istream &in);

	/**
	 * @brief Read a face data from a line of obj file.
	 * @param stream a line of obj file, containing multiple blocks
	 * (vertex/texCoord/normal).
	 */
	void read_a_face(std::stringstream &stream, const std::string &mat_name,
	                 size_t smooth_id);

	/// @brief Read a material file.
	/// @param file_path MTL file path.
	/// @return True, if read ok, otherwise not.
	bool read_material(const std::string &file_path, size_t &texture_id,
	                   size_t &material_id);

	/**
	 * @brief Process a block of face data.
	 * @param block block string
	 * @param comp_value the index, may be negative.
	 * @param component indicates which component the index belongs to.
	 * @return true if succeed to get current component.
	 */
	bool get_component_from_block(std::string &block, size_t &comp_idx,
	                              int &comp_value);

	/// @brief when process a vertex block data of face, process vertex component.
	index_t set_face_vertex(int comp_value);

	/// @brief when process a vertex block data of face, process texture
	/// coordinate component.
	void set_face_tex(int comp_value, index_t vert_idx);

	/// @brief when process a vertex block data of face, process normal component.
	void set_face_normal(int comp_value, index_t vert_idx);

	void postfix_when_no_faces();

	void split_obj_geo(iOBJBaseGeo &base_geo);

private:
	std::string path;

	IOOptions user_options;
	IOOptions file_options;

	/// @name Used for temporarily store content of file.
	/// @{
	std::vector<PointT>  t_points;
	std::vector<NormalT> t_normals;
	std::vector<Color>   t_colors;
	std::vector<Tex2D>   t_texcoords2d;
	std::vector<Tex3D>   t_texcoords3d;
	/// @}

	/// @name Used for building faces
	/// @{
	size_t n_point, n_tex, n_normal;
	/// @}
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API OBJReader<TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API OBJReader<TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API OBJReader<TriSoupTraits_Coord>;
#endif

} // namespace Mesh
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "OBJReader.inl"
#endif