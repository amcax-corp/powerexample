/// @file      NURBSMatchSurfConfig.hpp
/// @brief     Struct of NURBS matching configuration
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Struct of NURBS matching configuration
/// @details Some useful options used in NURBS matching algorithm, including the boundary begin parameter, orientation and nearest matching.
struct NURBSMatchSurfConfig
{
	/// @brief The begining parameter of the periodic iso curve of the surface
	double beginParam = 0.0;

	/// @brief Whether the begin parameter is chosen by the user or automatically computed
	bool isBeginParamFixed = false;

	/// @brief Whether the orientation of the periodic iso curve of the surface is chosen by the user or automatically computed
	bool isOrientationFixed = false;

	/// @brief The orientaion of the periodic iso curve of the surface is reversed or not
	bool isReverse = false;

	/// @brief Whether match at the nearest point
	bool isNearestMatch = false;
};
} // namespace AMCAX
