/// @file      NURBSAPISweepRotation.hpp
/// @brief     The class of rotation sweeping
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/AxisT.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of sweeping a profile curve along a spine curve and rotating and scaling around an axis
/// @details This class computes the swept surface with a profile, a spine curve and a rotation axis.
class NURBSAPISweepRotation
{
public:
	/// @brief Sweep the profile along the spine and rotate and scale around the axis
	/// @param profile The profile
	/// @param spine The spine
	/// @param axis The axis
	/// @return The swept surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> RotationSweep(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		const Axis3& axis);
};
} // namespace AMCAX
