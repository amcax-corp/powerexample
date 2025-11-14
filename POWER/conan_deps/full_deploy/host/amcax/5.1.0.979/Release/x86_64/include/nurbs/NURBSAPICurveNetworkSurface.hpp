/// @file      NURBSAPICurveNetworkSurface.hpp
/// @brief     Class of building Coons-Gordon surface
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

/// @brief The class of building Coons-Gordon surface
/// @details This class computes the resulting Coons-Gordon surface which goes through the given curves
class NURBSAPICurveNetworkSurface
{
public:
	/// @brief Coons-Gordon surface
	/// @param verticalCurves Vertical network curves
	/// @param horizontalCurves Horizontal network curves
	/// @return The Gordon surface which go through the curves
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> CurveNetworkSurfaceGordon(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& verticalCurves, const std::vector<std::shared_ptr<Geom3BSplineCurve>>& horizontalCurves);
};
} // namespace AMCAX
