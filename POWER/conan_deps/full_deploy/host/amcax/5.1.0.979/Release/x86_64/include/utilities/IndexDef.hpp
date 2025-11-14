/**
 * @file IndexDef.hpp
 * @brief Defines index_t used in everywhere.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */
#pragma once

#include <cstddef>

namespace AMCAX {
namespace Meshing {

/// @brief Index unsed in mesh
using index_t = size_t;

/// @brief A value indicates invalid index. When index is unsigned type, `-1`
/// will be cast to the maximum unsigned value.
/// @todo Use type_traits for a safe initialization.
inline constexpr index_t InvalidIndex = index_t(-1);

/// @brief Make an index invalid.
inline void invalidate_idx(index_t &idx) { idx = InvalidIndex; }

/// @brief Check if an index is valid.
inline bool is_valid_idx(index_t idx) { return idx != InvalidIndex; }

/// @brief A value indicates invalid index. When index is integer type, `-1`
/// will be cast to the maximum unsigned value.
/// @todo Use type_traits for a safe initialization.
template <typename integer_type>
inline constexpr integer_type AnyInvalidIndex = integer_type(-1);

/// @brief Check if an index is valid.
template <typename integer_type>
inline bool is_valid_idx(integer_type idx)
{
	return idx != AnyInvalidIndex<integer_type>;
}

} // namespace Meshing
} // namespace AMCAX