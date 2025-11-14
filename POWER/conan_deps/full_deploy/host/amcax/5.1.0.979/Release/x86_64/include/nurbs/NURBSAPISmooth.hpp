/// @file      NURBSAPISmooth.hpp
/// @brief     The class of NURBS curve smoothing
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;

/// @brief Class of smoothing curve
/// @details This class computes the smoothed curve
class NURBSAPISmooth
{
public:
	/// @brief Smooth curve
	/// @param curve The source curve
	/// @param angularCorrection The smooth sweeping angular correction of the guide curve in radians.
	/// If the angular difference of the left derivative and the right derivative of
	/// the guide curve C0 points is below the parameter value,
	/// the C0 points will be smoothed; Else it will return failure.
	/// @param deviation The tolerance of smoothing
	/// @return The first is whether the curve C0 tangent angular is below the angularCorrection;
	///  The second is whether the smoothing operation succeeded;
	///  The third is the smoothed curve.
	[[nodiscard]] AMCAX_API static std::tuple<bool, bool, std::shared_ptr<Geom3BSplineCurve>> SmoothCurve(const std::shared_ptr<Geom3BSplineCurve>& curve, double angularCorrection, double deviation);
};
} // namespace AMCAX
