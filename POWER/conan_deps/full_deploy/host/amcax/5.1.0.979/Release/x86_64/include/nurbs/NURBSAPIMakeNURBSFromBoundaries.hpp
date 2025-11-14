/// @file      NURBSAPIMakeNURBSFromBoundaries.hpp
/// @brief     The class of NURBS patch building from boundaries
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of making a surface from given 2, 3 or 4 boundary curves
/// @details This class computes the NURBS surface from two, three or four boundary curves which are connected end by end.
class NURBSAPIMakeNURBSFromBoundaries
{
public:
	/// @brief Given 2 or 3 or 4 boundaries, make a surface
	/// @param boundCurves The boundary curves
	/// @param isParallel Are the result surface isocurves parallel to boundary curves
	/// @return The surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> MakeSurf(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& boundCurves, bool isParallel);
};
} // namespace AMCAX
