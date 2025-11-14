/// @file      BOAlgoMacros.hpp
/// @brief     The basic enum classes used in boolean algorithm
/// @details   Some useful options used in boolean algorithm, including the type of gluing, the status, and the type of boolean operation.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief The gluing operation is the option of the basic operations such as general fuse, splitting, boolean, section, operations.
/// @details The gluing options are used to speed the computation of the interferences among arguments of the operations on special cases,
///         in which the arguments may be overlapping but do not have real intersections between their sub-shapes.
enum class BOAlgoGlueType
{
	/// @brief Default value for the algorithms, gluing is switched off
	GlueOff,

	/// @brief Gluing option for shapes with partial coincidence
	GlueShift,

	/// @brief Gluing option for shapes with full coincidence
	GlueFull
};

/// @brief Type of boolean operation
enum class BOAlgoOperation
{
	/// @brief Common operation (intersection)
	Common,

	/// @brief Fuse operation (union)
	Fuse,

	/// @brief Cut operation, A - B (difference)
	Cut,

	/// @brief Cut operation, B - A
	Cut21,

	/// @brief Section operation
	Section,

	/// @brief Unknown operation
	Unknown
};
} // namespace AMCAX
