
/// @file       ShapeRepresentationType.hpp
/// @brief		Enumeration of STEP shape representation types.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

namespace AMCAX::STEP
{
/// @brief Enumeration of STEP shape representation types.
/// @details These values correspond to standard STEP schema entity names
///          and define how shape geometry is represented in the file.
enum class ShapeRepresentationType
{
	/// @brief Unspecified or unknown representation type.
	UNSPECIFIED,

	/// @brief Generic SHAPE_REPRESENTATION.
	SHAPE_REPRESENTATION,

	/// @brief ADVANCED_BREP_SHAPE_REPRESENTATION (advanced B-Rep with topology and geometry).
	ADVANCED_BREP_SHAPE_REPRESENTATION,

	/// @brief FACETED_BREP_SHAPE_REPRESENTATION (faceted boundary representation).
	FACETED_BREP_SHAPE_REPRESENTATION,

	/// @brief MANIFOLD_SURFACE_SHAPE_REPRESENTATION (manifold surfaces without volume).
	MANIFOLD_SURFACE_SHAPE_REPRESENTATION,

	/// @brief GEOMETRICALLY_BOUNDED_WIREFRAME_SHAPE_REPRESENTATION (wireframe models).
	GEOMETRICALLY_BOUNDED_WIREFRAME_SHAPE_REPRESENTATION,

	/// @brief GEOMETRICALLY_BOUNDED_SURFACE_SHAPE_REPRESENTATION (surface-only models).
	GEOMETRICALLY_BOUNDED_SURFACE_SHAPE_REPRESENTATION,

	/// @brief TESSELLATED_SHAPE_REPRESENTATION (tessellated or mesh representation).
	TESSELLATED_SHAPE_REPRESENTATION,

	/// @brief CONSTRUCTIVE_GEOMETRY_REPRESENTATION (CSG-based representation).
	CONSTRUCTIVE_GEOMETRY_REPRESENTATION,

	/// @brief Other non-standard representation type.
	OTHER,
};

} // namespace AMCAX::STEP
