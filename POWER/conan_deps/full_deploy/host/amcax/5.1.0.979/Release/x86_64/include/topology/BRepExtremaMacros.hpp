/// @file      BRepExtremaMacros.hpp
/// @brief     Enumerate classes used in extrema computation of BRep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of extrema in a BRep structure
enum class BRepExtremaSupportType
{
	/// @brief The extrema is a vertex
	IsVertex,

	/// @brief The extrema is on an edge
	IsOnEdge,

	/// @brief The extrema is in a face
	IsInFace,
};
} // namespace AMCAX
