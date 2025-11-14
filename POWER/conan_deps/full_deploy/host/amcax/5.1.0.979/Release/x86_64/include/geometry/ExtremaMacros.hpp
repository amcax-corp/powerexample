/// @file      ExtremaMacros.hpp
/// @brief     Enumerations used in extrema computation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief The algorithm used to find extrema between point and surface
enum class ExtremaAlgorithm
{
	Grad,
	Tree
};

/// @brief Flags for finding specific type of extrema
enum class ExtremaFlag
{
	Min,
	Max,
	MinMax
};
} // namespace AMCAX
