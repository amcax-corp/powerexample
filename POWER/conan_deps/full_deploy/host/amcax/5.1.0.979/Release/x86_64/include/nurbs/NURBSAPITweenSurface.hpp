/// @file      NURBSAPITweenSurface.hpp
/// @brief     The class of Tween surface
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3BSplineSurface;

/// @brief Class of Creating tween surfaces
class NURBSAPITweenSurface
{
public:
	/// @brief Create middle surface of two surfaces
	/// @details The alignment rule is described as follows. The four corner points of a surface is sorted as {u0v0, u0v1, u1v0, u1v1}.
	/// If isReverse = false, the first surface's corner point i will match the second surface's corner point (i + offset2) % 4.
	/// If isReverse = true, the first surface's corner point i will match the second surface's corner point (3 - i + offset2) % 4.
	/// @param surf1 The first surface
	/// @param surf2 The second surface
	/// @param proportion The proportion of the middle surface of the first surface. For example, 0.5 is the exact middle surface, 1/3 is the one-third middle surface.
	/// @param[in, out] isReverse Whether the boundary of the second surface is required to be reversed
	/// @param[in, out] offset2 The offset number of the boundary of the second surface
	/// @param isAutoAlign Whether to automatically make alignment between the input surfaces. If true, the parameter isReverse and offset2 will be changed
	/// @return The middle surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> CreateMidSurface(
		const std::shared_ptr<Geom3BSplineSurface>& surf1,
		const std::shared_ptr<Geom3BSplineSurface>& surf2,
		double proportion,
		bool& isReverse,
		int& offset2,
		bool isAutoAlign = true);
};
} // namespace AMCAX
