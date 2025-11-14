/// @file      NURBSAPICircularSweep.hpp
/// @brief     The class of NURBS sweeping with circular profile
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <nurbs/NURBSMacros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;
class LawFunction;

/// @brief Class of circular sweeping
/// @details This class computes the sweeping result surfaces with circular profile
class NURBSAPICircularSweep
{
public:
	/// @brief Sweep with circular profile defined by three guide curves, the first guide and the last guide are the swept surface boundaries
	/// @param guide1 The first guide
	/// @param guide2 The second guide
	/// @param guide3 The third guide
	/// @param spine The spine
	/// @param spineLeftBound The spine left boundary
	/// @param spineRightBound The spine right boundary
	/// @return The status and the swept surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>>
	SweepWithThreeGuides(const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const std::shared_ptr<Geom3BSplineCurve>& guide3,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with circular profile defined by two guide curves and the radius, the guides are the swept surface boundaries
	/// @param guide1 The first guide
	/// @param guide2 The second guide
	/// @param radiusLaw The law function of the radius, defination domain is [0.0, 1.0]. If the circle with the given radius cannot pass the guides, the status is InvalidRadius the result surfaces are empty
	/// @param spine The spine
	/// @param spineLeftBound The spine left boundary
	/// @param spineRightBound The spine right boundary
	/// @return The status and the swept surfaces
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithTwoGuidesAndRadius(const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const LawFunction& radiusLaw,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with circular profile defined by a center curve, a reference curve to determine the radius and two angles to determine swept surface span
	/// @param centerCurve The center curve
	/// @param referenceCurve The reference curve
	/// @param angleLaw1 The beginning angle (in radians) of the circular profile. The defination domain is [0.0, 1.0]
	/// @param angleLaw2 The ending angle (in radians) of the circular profile. The defination domain is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The spine left boundary
	/// @param spineRightBound The spine right boundary
	/// @return The status and the swept surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>>
	SweepWithCenterAndTwoAngles(const std::shared_ptr<Geom3BSplineCurve>& centerCurve,
		const std::shared_ptr<Geom3BSplineCurve>& referenceCurve,
		const LawFunction& angleLaw1,
		const LawFunction& angleLaw2,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with circular profile defined by a center curve and a radius
	/// @param centerCurve The center curve
	/// @param radiusLaw The law function of the radius. The defination domain is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The spine left boundary
	/// @param spineRightBound The spine right boundary
	/// @return The status and the swept surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>>
	SweepWithCenterAndRadius(const std::shared_ptr<Geom3BSplineCurve>& centerCurve,
		const LawFunction& radiusLaw,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with circular profile defined by two guide (or limit) curves and a tangency surface. The first guide curve is required to locate on the given tangency surface
	/// @param limitCurveWithTangency The guide curve on the tangency surface
	/// @param tangencySurface The tangency surface
	/// @param limitCurve The guide curve not on the tangency surface
	/// @param spine The spine
	/// @param spineLeftBound The spine left boundary
	/// @param spineRightBound The spine right boundary
	/// @return The status and the swept surfaces
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithTwoGuidesAndTangencySurface(const std::shared_ptr<Geom3BSplineCurve>& limitCurveWithTangency,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface,
		const std::shared_ptr<Geom3BSplineCurve>& limitCurve,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with circular profile defined by a guide (or limit) curve and a tangency surface. The guide curve is not on the given tangency surface
	/// @param guide The guide curve
	/// @param tangencySurface The tangency surface
	/// @param radiusLaw The law function of the radius. The defination domain is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The spine left boundary
	/// @param spineRightBound The spine right boundary
	/// @return The status and the swept surfaces
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithOneGuideAndTangencySurface(const std::shared_ptr<Geom3BSplineCurve>& guide,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface,
		const LawFunction& radiusLaw,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with circular profile defined by a guide (or limit) curve on a tangency surface
	/// @param guide The guide curve
	/// @param tangencySurface The tangency surface
	/// @param radiusLaw The law function of the radius. The defination domain is [0.0, 1.0]
	/// @param angleLaw1 The beginning angle (in radians) of the circular profile. The defination domain is [0.0, 1.0]
	/// @param angleLaw2 The ending angle (in radians) of the circular profile. The defination domain is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The spine left boundary
	/// @param spineRightBound The spine right boundary
	/// @return The status and the swept surfaces
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithCurveOnTangencySurface(const std::shared_ptr<Geom3BSplineCurve>& guide,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface,
		const LawFunction& radiusLaw,
		const LawFunction& angleLaw1,
		const LawFunction& angleLaw2,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);
};
} // namespace AMCAX
