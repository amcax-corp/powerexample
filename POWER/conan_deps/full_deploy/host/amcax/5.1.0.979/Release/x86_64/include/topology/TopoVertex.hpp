/// @file      TopoVertex.hpp
/// @brief     Class of vertex
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of vertex
class TopoVertex : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoVertex used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoVertex> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a vertex
	/// @param v The vertex
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoVertex& v) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(v);
	}
};

/// @brief Specialization of equal function of TopoVertex used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoVertex> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two vertices are the same
	/// @param left The first vertex
	/// @param right The second vertex
	/// @return True if two vertices are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoVertex& left, const AMCAX::TopoVertex& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
