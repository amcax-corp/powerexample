/// @file      NURBSAPILinearSweep.hpp
/// @brief     The class of linear sweeping operation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/DirectionT.hpp>
#include <nurbs/NURBSMacros.hpp>

namespace AMCAX
{
struct NURBSLinearSweepWithDraftDirectionLength;
class Geom3BSplineCurve;
class Geom3BSplineSurface;
class Geom3Surface;
class LawFunction;

/// @brief Class of sweeping an implicit linear profile along guides
/// @details This class computes the resulting surface by means of linear profile sweeping
class NURBSAPILinearSweep
{
public:
	/// @brief Sweep with two guide curves as surface limit boundaries
	/// @param guide1 The first guide curve
	/// @param guide2 The second guide curve
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @param length1Law The first guide additional length law function. The domain of defination is [0.0, 1.0]
	/// @param length2Law The second guide additional length law function. The domain of defination is [0.0, 1.0]
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>>
	SweepWithTwoLimits(const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound,
		const LawFunction& length1Law,
		const LawFunction& length2Law);

	/// @brief Sweep with a guide curve as surface limit boundary and another guide curve as surface middle curve
	/// @param guide1 The first guide curve
	/// @param guide2 The second guide curve
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>>
	SweepWithLimitAndMiddle(const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with a guide curve on the reference surface
	/// @param guide The guide curve on the reference surface
	/// @param reference The reference surface
	/// @param angleLaw The angle (in radians) law function of section rotation around the guide. The domain of defination is [0.0, 1.0]
	/// @param length1Law The additional length law function along the surface normal. The domain of defination is [0.0, 1.0]
	/// @param length2Law The additional length law function against the surface normal. The domain of defination is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the four result surfaces constructed by four rotation directions
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithReferenceSurface(const std::shared_ptr<Geom3BSplineCurve>& guide,
		const std::shared_ptr<Geom3BSplineSurface>& reference,
		const LawFunction& angleLaw,
		const LawFunction& length1Law,
		const LawFunction& length2Law,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with a guide curve and a reference curve.
	/// The swept surface boundary is on the guide curve and
	/// the section curve of the surface is a line
	/// with the direction from the guide curve to the reference curve
	/// @param guide The guide curve
	/// @param reference The reference curve
	/// @param angleLaw The angle (in radians) law function of section rotation around the guide. The domain of defination is [0.0, 1.0]
	/// @param length1Law The additional length law function with the direction from the reference to the guide. The domain of defination is [0.0, 1.0]
	/// @param length2Law The additional length law function with the direction from the guide to the reference. The domain of defination is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the four result surfaces constructed by four rotation directions
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithReferenceCurve(const std::shared_ptr<Geom3BSplineCurve>& guide,
		const std::shared_ptr<Geom3BSplineCurve>& reference,
		const LawFunction& angleLaw,
		const LawFunction& length1Law,
		const LawFunction& length2Law,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with a guide curve and a surface with which the swept surface is tangent
	/// @param guide The guide curve
	/// @param tangencySurface The tangency surface
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the one or more solutions depending on the geometry
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithTangencySurface(const std::shared_ptr<Geom3BSplineCurve>& guide,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with a guide curve and a draft direction.
	/// @param guide The guide curve
	/// @param draftDirection The draft direction
	/// @param angleLaw The angle (in radians) law function of section rotation around the guide. The domain of defination is [0.0, 1.0]
	/// @param length1 The draft length against the draft direction
	/// @param length2 The draft length along the draft direction
	/// @return The first is the sweep status and the second is the four results constructed by four rotation angles
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithDraftDirection(const std::shared_ptr<Geom3BSplineCurve>& guide,
		const Direction3& draftDirection,
		const LawFunction& angleLaw,
		const NURBSLinearSweepWithDraftDirectionLength& length1,
		const NURBSLinearSweepWithDraftDirectionLength& length2);

	/// @brief Build a swept surface tangency to two surfaces
	/// @param spine The spine
	/// @param tangencySurface1 The first tangency surface
	/// @param tangencySurface2 The second tangency surface
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the one or more solutions depending on the geometry
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::vector<std::shared_ptr<Geom3BSplineSurface>>>
	SweepWithTwoTangencySurfaces(const std::shared_ptr<Geom3BSplineCurve>& spine,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface1,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface2,
		double spineLeftBound,
		double spineRightBound);
};
} // namespace AMCAX
