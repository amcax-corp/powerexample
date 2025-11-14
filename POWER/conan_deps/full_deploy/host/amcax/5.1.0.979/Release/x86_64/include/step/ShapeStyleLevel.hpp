/// @file       ShapeStyleLevel.hpp
/// @brief		Controls the level of style information provided by styled STEP readers.
/// @copyright  Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

namespace AMCAX
{
namespace STEP
{

/// @brief Controls the level of style information provided by styled STEP readers.
enum class ShapeStyleLevel : int
{
	NONE = 0, ///< Do not provide any style data. The styled reader behaves like the basic reader.

	SOLID,	///< Provide style data for solids (if available).
	SHELL,	///< Provide style data for solids and shells (if available).
	FACE,	///< (default) Provide style data for solids, shells, and faces (if available).
	WIRE,	///< Provide style data for solids, shells, faces, and wires (if available).
	EDGE,	///< Provide style data for solids, shells, faces, wires, and edges (if available).
	VERTEX, ///< Provide style data down to the vertex level (if available).
};

} // namespace STEP
} // namespace AMCAX
