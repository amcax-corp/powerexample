/// @file      NURBSAPIExplicitSweep.hpp
/// @brief     Class of explicit sweeping operation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <nurbs/NURBSMacros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;
class LawFunction;

/// @brief Class of explicit sweeping operation
/// @details This class computes the result surface by means of explict profile sweeping
class NURBSAPIExplicitSweep
{
public:
	/// @brief Sweep the profile along a guide on the reference surface
	/// @param profile The profile
	/// @param guide The guide curve which is on the reference surface
	/// @param reference The reference surface
	/// @param angleLawFunc The angle (in radians) law function of section rotation. The defination domain is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surfaces of four rotation direction
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>> SweepWithReferenceSurface(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& guide,
		const std::shared_ptr<Geom3BSplineSurface>& reference,
		const LawFunction& angleLawFunc,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep the profile along two guides with two anchor points
	/// @param profile The profile
	/// @param guide1 The first guide curve
	/// @param guide2 The second guide curve
	/// @param anchorPoint1 The first anchor point on the profile that will be matched to the first guide curve. The point must belong to the sweeping plane of the profile.
	/// @param anchorPoint2 The second anchor point on the profile that will be matched to the second cuide curve. The point must belong to the sweeping plane of the profile.
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>> SweepWithTwoGuideCurves(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		Point3 anchorPoint1,
		Point3 anchorPoint2,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep the profile along two guides with two anchor points
	/// @param profile The profile
	/// @param guide1 The first guide curve
	/// @param guide2 The second guide curve
	/// @param anchorPoint The anchor point on the profile that will be matched to the first guide curve. The point must belong to the sweeping plane of the profile.
	/// @param anchorDirection The anchor direction. In each sweeping plane, the profile is rotated around the anchor point so that the anchor direction (linked to this profile) is aligned with the two guide curves, from the first guide curve to the second guide curve.
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>> SweepWithTwoGuideCurves(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		Point3 anchorPoint,
		const Direction3& anchorDirection,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep the profile along one guide curve with one pulling direction which is used to control the final shape of the swept surface.
	///  The result is quivalent to the With reference surface subtype with a reference plane normal to the pulling direction.
	/// @param profile The profile
	/// @param guide The guide curve which is on the reference surface
	/// @param direction The pulling direction
	/// @param angleLawFunc The angle (in radians) law function of section rotation. The defination domain is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surfaces of four rotation direction
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>> SweepWithPullingDirection(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& guide,
		const Direction3& direction,
		const LawFunction& angleLawFunc,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);
};
} // namespace AMCAX
