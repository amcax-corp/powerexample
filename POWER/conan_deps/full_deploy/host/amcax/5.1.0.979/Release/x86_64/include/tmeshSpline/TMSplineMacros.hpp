/// @file      TMSplineMacros.hpp
/// @brief     Enumerator class used for TMSpline structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>

namespace AMCAX
{
typedef Point2 TParam;

enum class TMTransType
{
	R0,
	R1,
	R2,
	R3
};
enum class TMDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	ErrorDirection
};
enum class TMVType
{
	TJunction,
	IJunction,
	LJunction,
	Extraordinary,
	Normal
};
enum class TMLType
{
	TJunction,
	Normal,
	LJunction
};

} // namespace AMCAX
