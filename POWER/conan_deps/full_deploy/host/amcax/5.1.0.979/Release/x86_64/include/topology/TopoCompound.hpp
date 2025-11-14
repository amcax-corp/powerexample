/// @file      TopoCompound.hpp
/// @brief     Class of compound
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of compound
class TopoCompound : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoCompound used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoCompound> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a compound
	/// @param c The compound
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoCompound& c) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(c);
	}
};

/// @brief Specialization of equal function of TopoCompound used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoCompound> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two compounds are the same
	/// @param left The first compound
	/// @param right The second compound
	/// @return True if two compounds are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoCompound& left, const AMCAX::TopoCompound& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
