/// @file      TopoFace.hpp
/// @brief     Class of face
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of face
class TopoFace : public TopoShape
{
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoFace used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoFace> : std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a face
	/// @param f The face
	/// @return The hash value
	[[nodiscard]] size_t operator()(const AMCAX::TopoFace& f) const noexcept
	{
		return std::hash<AMCAX::TopoShape>::operator()(f);
	}
};

/// @brief Specialization of equal function of TopoFace used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoFace> : std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two faces are the same
	/// @param left The first face
	/// @param right The second face
	/// @return True if two faces are the same
	[[nodiscard]] bool operator()(const AMCAX::TopoFace& left, const AMCAX::TopoFace& right) const noexcept
	{
		return std::equal_to<AMCAX::TopoShape>::operator()(left, right);
	}
};
