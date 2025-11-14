/// @file      TopoWire.hpp
/// @brief     Class of wire
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of wire
class TopoWire : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoWire used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoWire> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a wire
	/// @param w The wire
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoWire& w) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(w);
	}
};

/// @brief Specialization of equal function of TopoWire used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoWire> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two wires are the same
	/// @param left The first wire
	/// @param right The second wire
	/// @return True if two wires are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoWire& left, const AMCAX::TopoWire& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
