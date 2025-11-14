/// @file      TopoCompSolid.hpp
/// @brief     Class of composite solid
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of composite solid
class TopoCompSolid : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoCompSolid used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoCompSolid> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a composite solid
	/// @param c The composite solid
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoCompSolid& c) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(c);
	}
};

/// @brief Specialization of equal function of TopoCompSolid used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoCompSolid> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two composite solids are the same
	/// @param left The first composite solid
	/// @param right The second composite solid
	/// @return True if two composite solids are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoCompSolid& left, const AMCAX::TopoCompSolid& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
