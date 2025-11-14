/**
 * @file STLWriter.hpp
 * @brief This file implement writer for STL file.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <mesh/TriSoup.hpp>
#include <mesh/io/IOOptions.hpp>

#include <utilities/Exception.hpp>
#include <utilities/Macros.hpp>
#include <utilities/StringUtils.hpp>

#include <array>
#include <fstream>
#include <string>
#include <vector>

namespace AMCAX {
namespace Meshing {
namespace Mesh {

/**
 * @brief Write mesh to an STL file.
 * @tparam Traits Define types for points, normals triangles.
 */
template <typename Traits>
class STLWriter
{
public:
	/** @brief Point type.
	 * E.g., Vec3d from any library or a wrapper of it.
	 */
	using PointT   = typename Traits::PointT;
	/** @brief Vector type.
	 * It is derived from PointT, representing the difference between two points.
	 */
	using NormalT  = typename Traits::NormalT;
	/** @brief triangle type */
	using Triangle = typename Traits::Triangle;
	/** @brief Number type in PointT.
	 * We also expect that PointT provides x(), y() and z().
	 */
	using NT     = std::remove_reference_t<decltype(std::declval<PointT>().x())>;
	/** @brief index used in triangle */
	using ti_t   = std::remove_reference_t<decltype(std::declval<Triangle>()[0])>;
	/** @brief An array that stores points for vertices.
	 * E.g., std::vector<PointT> or Eigen::VectorX<PointT>.
	 */
	using Points = typename Traits::Points;
	/** @brief An array that stores normals.
	 * E.g., std::vector<NormalT> or Eigen::VectorX<NormalT>.
	 */
	using Normals   = typename Traits::Normals;
	/** @brief An array that stores indices of three vertices for all faces.
	 * E.g., std::vector<std::array<index_t,3>> or
	 * Eigen::VectorX<Eigen::Vector3i>.
	 */
	using Triangles = typename Traits::Triangles;

public:
	AMCAXMeshing_API STLWriter();
	AMCAXMeshing_API ~STLWriter() noexcept;

	/**
	 * @brief Write mesh to file with given options and precison.
	 * @param opt Options to control which parts of mesh are written to file.
	 * @param precision precision of floating point numbers.
	 * @return true if succeed to write the mesh.
	 */
	AMCAXMeshing_API bool write(const std::string &filename, IOOptions &opt,
	                            std::streamsize precision = 6);
	/**
	 * @brief Write mesh to file with given options and precison.
	 * @param opt Options to control which parts of mesh are written to stream.
	 * @param precision precision of floating point numbers.
	 * @return true if succeed to write the mesh.
	 */
	AMCAXMeshing_API bool write(std::ostream &os, IOOptions &opt,
	                            std::streamsize precision = 6);

	/** @brief Clear data stored in writer */
	AMCAXMeshing_API void clear();

	Points    m_points;    ///< vertex position
	Triangles m_triangles; ///< triangles
	Normals   m_normals;   ///< triangle normals

private:
	std::string get_description() const { return "Stereolithography Format"; }
	std::string get_extensions() const { return "stla stlb"; }

	bool save_mesh_to_stream(std::ostream &out, IOOptions &opt,
	                         std::streamsize precision = 6);

	bool write_stla(std::ostream &, AMCAXMeshing_UNUSED IOOptions &opt,
	                std::streamsize _precision = 6);
	bool write_stlb(std::ostream &, AMCAXMeshing_UNUSED IOOptions &opt,
	                std::streamsize _precision = 6);

private:
	std::string path, stl_name;

	IOOptions user_options;

	void    write_int(int _i, FILE *_out, bool _swap = false);
	void    write_float(float _f, FILE *_out, bool _swap = false);
	void    write_int(int _i, std::ostream &_out, bool _swap = false);
	void    write_float(float _f, std::ostream &_out, bool _swap = false);
	void    write_short(short int _i, FILE *_out, bool _swap = false);
	void    write_short(short int _i, std::ostream &_out, bool _swap = false);
	/** @brief Calculate normal of a triangle.  */
	NormalT calc_normal(const Triangle &t);
};

#ifdef AMCAXMeshing_Enable_StandardTraits
extern template class AMCAXMeshing_CLASS_API STLWriter<TriSoupTraits>;
#endif
#ifdef AMCAXMeshing_Enable_EigenTraits
extern template class AMCAXMeshing_CLASS_API STLWriter<TriSoupTraits_Eigen>;
#endif
#ifdef AMCAXMeshing_Enable_CommonTraits
extern template class AMCAXMeshing_CLASS_API STLWriter<TriSoupTraits_Coord>;
#endif

} // namespace Mesh
} // namespace Meshing
} // namespace AMCAX

#ifdef AMCAXMeshing_HAS_IMPL
	#include "STLWriter.inl"
#endif