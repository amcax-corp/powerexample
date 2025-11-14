/// @file      NURBSAPIConicalSweep.hpp
/// @brief     The class of NURBS sweeping with conical profile
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

/// @brief Class of conical sweeping
/// @details This class computes the sweeping result surfaces with conical profile
class NURBSAPIConicalSweep
{
public:
	/// @brief Sweep with two guides lie on two tangency surfaces
	/// @param guide1 The first guide
	/// @param tangencySurface1 The first tangency surface which the first guide lies on
	/// @param angleLaw1 The angle (in radians) law function of section rotation of the first tangency direction. The domain of defination is [0.0, 1.0]
	/// @param guide2 The second guide
	/// @param tangencySurface2 The second tangency surface which the second guide lies on
	/// @param angleLaw2 The angle (in radians) law function of section rotation of the second tangency direction. The domain of defination is [0.0, 1.0]
	/// @param parameter The law function of parameter belongs to (0, 1) is used to define a passing point of the section conic.
	/// The larger the value, the more curved the conic curve.
	/// For not parallel vectors,
	/// if parameter = 0.5, the resulting curve is an arc of parabola;
	/// if parameter < 0.5, the resulting curve is an arc of ellipse;
	/// if parameter > 0.5, the resulting curve is an arc of hyperbola.
	/// For parallel vectors,
	/// if parameter = 0.5, the resulting curve is an arc of circle;
	/// else the resulting curve is an arc of ellipse.
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>> SweepWithTwoGuides(
		const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface1,
		const LawFunction& angleLaw1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface2,
		const LawFunction& angleLaw2,
		const LawFunction& parameter,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with three guides. The first and the last guide lie on two tangency surfaces
	/// @param guide1 The first guide
	/// @param tangencySurface1 The first tangency surface which the first guide lies on
	/// @param angleLaw1 The angle (in radians) law function of section rotation of the first tangency direction. The domain of defination is [0.0, 1.0]
	/// @param guide2 The second guide
	/// @param guide3 The last guide
	/// @param tangencySurface3 The last tangency surface which the last guide lies on
	/// @param angleLaw3 The angle (in radians) law function of section rotation of the last tangency direction. The domain of defination is [0.0, 1.0]
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>> SweepWithThreeGuides(
		const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface1,
		const LawFunction& angleLaw1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const std::shared_ptr<Geom3BSplineCurve>& guide3,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface3,
		const LawFunction& angleLaw3,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with four guides. The first guide lies on the tangency surface
	/// @param guide1 The first guide
	/// @param tangencySurface The first tangency surface which the first guide lies on
	/// @param angleLaw The angle (in radians) law function of section rotation of the first tangency direction. The domain of defination is [0.0, 1.0]
	/// @param guide2 The second guide
	/// @param guide3 The third guide
	/// @param guide4 The last guide
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>> SweepWithFourGuides(
		const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineSurface>& tangencySurface,
		const LawFunction& angleLaw,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const std::shared_ptr<Geom3BSplineCurve>& guide3,
		const std::shared_ptr<Geom3BSplineCurve>& guide4,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);

	/// @brief Sweep with five guides
	/// @param guide1 The first guide
	/// @param guide2 The second guide
	/// @param guide3 The third guide
	/// @param guide4 The fourth guide
	/// @param guide5 The last guide
	/// @param spine The spine
	/// @param spineLeftBound The left boundary parameter of the spine
	/// @param spineRightBound The right boundary parameter of the spine
	/// @return The first is the sweep status and the second is the result surface
	[[nodiscard]] AMCAX_API static std::pair<NURBSSweepStatus, std::shared_ptr<Geom3BSplineSurface>> SweepWithFiveGuides(
		const std::shared_ptr<Geom3BSplineCurve>& guide1,
		const std::shared_ptr<Geom3BSplineCurve>& guide2,
		const std::shared_ptr<Geom3BSplineCurve>& guide3,
		const std::shared_ptr<Geom3BSplineCurve>& guide4,
		const std::shared_ptr<Geom3BSplineCurve>& guide5,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineLeftBound,
		double spineRightBound);
};
} // namespace AMCAX
