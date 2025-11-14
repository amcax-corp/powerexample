/// @file      TopoEdge.hpp
/// @brief     Class of edge
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of edge
class TopoEdge : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoEdge used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoEdge> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for an edge
	/// @param e The edge
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoEdge& e) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(e);
	}
};

/// @brief Specialization of equal function of TopoEdge used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoEdge> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two edges are the same
	/// @param left The first edge
	/// @param right The second edge
	/// @return True if two edges are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoEdge& left, const AMCAX::TopoEdge& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
