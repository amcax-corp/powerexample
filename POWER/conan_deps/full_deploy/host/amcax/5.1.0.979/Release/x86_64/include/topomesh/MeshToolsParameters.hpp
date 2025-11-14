/// @file      MeshToolsParameters.hpp
/// @brief     Struct of parameters used in the meshing process
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of algorithm used for meshing
enum class MeshAlgoType
{
	/// @brief The default algorithm is Watson
	Default = -1,

	/// @brief Watson algorithm
	Watson = 0,

	/// @brief Delabella algorithm (not available)
	Delabella = 1
};

/// @brief Struct of parameters used in the meshing process
struct MeshToolsParameters
{
	/// @brief Default relative factor of minimum size
	static constexpr double relMinSize = 0.1;

	/// @brief The triangulation algorithm
	MeshAlgoType meshAlgo = MeshAlgoType::Default;

	/// @brief Angular deflection used to tessellate the boundary edges
	double angle = 0.5;

	/// @brief Linear deflection used to tessellate the boundary edges
	double deflection = 0.001;

	/// @brief Angular deflection used to tessellate the face interior
	double angleInterior = -1.0;

	/// @brief Linear deflection used to tessellate the face interior
	double deflectionInterior = -1.0;

	/// @brief Minimum size parameter limiting size of edge to prevent generating too much vertices in case of distorted curves and surfaces
	double minSize = -1.0;

	/// @brief The deflection used for the tessellation of each edge is relative to the size of the edge. The deflection used for faces is the maximum deflection of their edges.
	bool relative = false;

	/// @brief Mode to take internal face vertices into account in triangulation process
	bool internalVerticesMode = true;

	/// @brief Enable check the surface deflection for all types of surfaces.
	bool controlSurfaceDeflection = true;

	/// @brief Clean temporary data model when algorithm is finished
	bool cleanModel = true;

	/// @brief Enable local adjustment of minimum size depending on edge size
	bool adjustMinSize = false;

	/// @brief Enable usage of shape tolerances for computing face deflection.
	bool forceFaceDeflection = false;

	/// @brief Allow the decrease of the quality of the generated mesh over the existing mesh
	bool allowQualityDecrease = false;
};
} // namespace AMCAX
