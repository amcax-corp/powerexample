/// @file      TopoShell.hpp
/// @brief     Class of shell
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of shell
class TopoShell : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoShell used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoShell> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a shell
	/// @param s The shell
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoShell& s) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(s);
	}
};

/// @brief Specialization of equal function of TopoShell used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoShell> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two shells are the same
	/// @param left The first shell
	/// @param right The second shell
	/// @return True if two shells are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoShell& left, const AMCAX::TopoShell& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
