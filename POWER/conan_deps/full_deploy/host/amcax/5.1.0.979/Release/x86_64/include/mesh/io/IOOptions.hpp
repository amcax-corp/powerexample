/**
 * @file IOOptions.hpp
 * @brief Mesh IO options.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

namespace AMCAX {
namespace Meshing {
namespace Mesh {

/**
 * @brief Options about pre-described properties in mesh IO.
 */
class IOOptions
{
public:
	bool vertex_has_point;
	bool vertex_has_normal;
	bool vertex_has_tex2d;
	bool vertex_has_tex3d;
	bool vertex_has_color;

	bool face_has_normal;
	bool face_has_tex2d;
	bool face_has_tex3d;
	bool face_has_color;

	bool color_has_alpha;

	bool mesh_has_object;
	bool mesh_has_group;
	bool mesh_has_smooth;

	bool stl_binary;

	/// @brief Filename extension for material files when writing OBJs default is
	/// currently .mtl
	std::string material_file_extension;

	IOOptions()
	  : vertex_has_point(false)
	  , vertex_has_normal(false)
	  , vertex_has_tex2d(false)
	  , vertex_has_tex3d(false)
	  , vertex_has_color(false)
	  , face_has_normal(false)
	  , face_has_tex2d(false)
	  , face_has_tex3d(false)
	  , face_has_color(false)
	  , color_has_alpha(false)
	  , mesh_has_object(false)
	  , mesh_has_group(false)
	  , mesh_has_smooth(false)
	  , stl_binary(false)
	  , material_file_extension(".mtl")
	{
	}

	void clear()
	{
		vertex_has_point        = false;
		vertex_has_normal       = false;
		vertex_has_tex2d        = false;
		vertex_has_tex3d        = false;
		vertex_has_color        = false;
		face_has_normal         = false;
		face_has_tex2d          = false;
		face_has_tex3d          = false;
		face_has_color          = false;
		color_has_alpha         = false;
		mesh_has_object         = false;
		mesh_has_group          = false;
		mesh_has_smooth         = false;
		stl_binary              = false;
		material_file_extension = ".mtl";
	}

	IOOptions &intersection(const IOOptions &rhs)
	{
		vertex_has_point  = vertex_has_point && rhs.vertex_has_point;
		vertex_has_normal = vertex_has_normal && rhs.vertex_has_normal;
		vertex_has_tex2d  = vertex_has_tex2d && rhs.vertex_has_tex2d;
		vertex_has_tex3d  = vertex_has_tex3d && rhs.vertex_has_tex3d;
		vertex_has_color  = vertex_has_color && rhs.vertex_has_color;
		face_has_normal   = face_has_normal && rhs.face_has_normal;
		face_has_tex2d    = face_has_tex2d && rhs.face_has_tex2d;
		face_has_tex3d    = face_has_tex3d && rhs.face_has_tex3d;
		face_has_color    = face_has_color && rhs.face_has_color;
		color_has_alpha   = color_has_alpha && rhs.color_has_alpha;
		stl_binary        = stl_binary && rhs.stl_binary;

		return *this;
	}
};

} // namespace Mesh
} // namespace Meshing
} // namespace AMCAX