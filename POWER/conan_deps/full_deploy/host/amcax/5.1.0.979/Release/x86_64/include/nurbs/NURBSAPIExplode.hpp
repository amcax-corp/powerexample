/// @file      NURBSAPIExplode.hpp
/// @brief     Class of NURBS explosion
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Array2.hpp>
#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of NURBS explosion
/// @details This class divides a B spline curve/surface into pieces by inner C0 points/isocurves
class NURBSAPIExplode
{
public:
	/// @brief Explode a curve into curves at C0 points
	/// @param curve The given curve
	/// @return The result curves
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineCurve>> ExplodeCurve(const std::shared_ptr<Geom3BSplineCurve>& curve);

	/// @brief Explode a surface into patches at C0 isocurves
	/// @param surface The given surface
	/// @return The result surfaces
	[[nodiscard]] AMCAX_API static Array2<std::shared_ptr<Geom3BSplineSurface>> ExplodeSurface(const std::shared_ptr<Geom3BSplineSurface>& surface);
};
} // namespace AMCAX
