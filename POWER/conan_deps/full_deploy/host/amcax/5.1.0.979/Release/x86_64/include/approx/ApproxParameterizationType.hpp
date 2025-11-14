/// @file      ApproxParameterizationType.hpp
/// @brief     The enum class of parameterization type
/// @details   The enum class of parameterization type used in curve approximation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of the parameterization used in curve approximation
enum class ApproxParameterizationType
{
	/// @brief Parameters of points are proportional to distances between them
	ChordLength,

	/// @brief Parameters of points are proportional to square roots of distances between them
	Centripetal,

	/// @brief Parameters of points are distributed uniformly
	IsoParametric
};
} // namespace AMCAX
