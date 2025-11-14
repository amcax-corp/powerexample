/// @file      BRepOffsetMacros.hpp
/// @brief     Enumeration classes used in the offset algorithms
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of offset mode
enum class BRepOffsetMode
{
	Skin,
	Pipe,
	RectoVerso
};

#ifndef DOXYGEN_SKIP
/// @internal
/// @brief Type of offset status
enum class BRepOffsetStatus
{
	Good,
	Reversed,
	Degenerated,
	Unknown
};

/// @internal
/// @brief Type of offset error
enum class BRepOffsetErrorType
{
	NoError,
	UnknownError,
	BadNormalsOnGeometry,
	C0Geometry,
	NullOffset,
	NotConnectedShell,
	CannotTrimEdges,
	CannotFuseVertices,
	CannotExtentEdge,
	UserBreak
};
#endif
} // namespace AMCAX
