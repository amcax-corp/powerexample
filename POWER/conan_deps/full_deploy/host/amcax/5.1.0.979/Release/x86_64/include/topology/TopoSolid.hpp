/// @file      TopoSolid.hpp
/// @brief     Class of solid
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of solid
class TopoSolid : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoSolid used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoSolid> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a solid
	/// @param s The solid
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoSolid& s) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(s);
	}
};

/// @brief Specialization of equal function of TopoSolid used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoSolid> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two solids are the same
	/// @param left The first solid
	/// @param right The second solid
	/// @return True if two solids are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoSolid& left, const AMCAX::TopoSolid& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
