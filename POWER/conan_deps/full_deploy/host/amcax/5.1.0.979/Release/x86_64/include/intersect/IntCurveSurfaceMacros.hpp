/// @file      IntCurveSurfaceMacros.hpp
/// @brief     The basic enum classes used in the interserction between a curve and a surface.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Transition Type of an interserction point between a curve and a surface.
enum class IntCurveSurfaceTransOnCurveType
{
	/// @brief The curve and the surface are tangent at the intersection point
	Tangent,

	/// @brief At the intersection point, the direction of the curve is opposite to the normal direction of the surface
	In,

	/// @brief At the intersection point, the direction of the curve is the same as the normal direction of the surface
	Out
};
} // namespace AMCAX
