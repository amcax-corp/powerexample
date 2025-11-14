/// @file      BRepFillMacros.hpp
/// @brief     Enumerate classes used in advanced modeling
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
///@internal
/// @brief The type of transition
enum class BRepFillTransitionType
{
	/// @brief Modified corner
	Modified,

	/// @brief Right corner
	Right,

	/// @brief Round corner
	Round
};

/// @internal
/// @brief The type of side on the graph
enum class BisectorGraphDataSide
{
	Left,
	Right
};
#endif

/// @brief The type of contact status
enum class BRepFillTypeOfContact
{
	NoContact,
	Contact,
	ContactOnBorder
};
} // namespace AMCAX
