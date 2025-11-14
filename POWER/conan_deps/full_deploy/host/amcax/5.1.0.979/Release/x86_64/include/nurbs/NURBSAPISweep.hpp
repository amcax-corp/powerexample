/// @file      NURBSAPISweep.hpp
/// @brief     The class of one-rail sweeping
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <nurbs/NURBSCurveSection.hpp>

namespace AMCAX
{
class Geom3BSplineSurface;
class Geom3BSplineCurve;

/// @brief Class of sweeping profiles along one spine
/// @details This class computes the swept surface with one or more profiles and one spine curve
class NURBSAPISweep
{
public:
	/// @brief Sweep a profile along a spine
	/// @param profile Profile
	/// @param spine Spine
	/// @param isParallel Parallel sweep or frenet sweep
	/// @return The swept surface
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineSurface>> SweepOneRail(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		bool isParallel);

	/// @brief Sweep a profile along a spine
	/// @param profile Profile
	/// @param spine Spine
	/// @param spineParam Spine parameter to determine which part is desired
	/// @param isParallel Parallel sweep or frenet sweep
	/// @return The swept surface
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineSurface>> SweepOneRail(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineParam,
		bool isParallel);

	/// @brief Sweep profile along spine. The correspondence between profile and spine is stored in spineCorrParams.
	/// @param profile If only one profile, open spine will get surface between spine first parameter (or last parameter which depends on the chosen spineRefParam) and profile correspondece parameter
	/// but closed spine will get the whole surface even though the whole surface is consist of severial sub-surfaces which is segmented by init profile and spine C0 params.
	/// If num of profile is more than one, only the surface between the profiles (spineRefParam is not used to judge which part is left, only the sequence of profiles is considered)
	/// will be generated and the surface is segmented whose rule is same as above.
	/// @param spine Spine, closed or open, C0 or not. If multiple end-to-end spines are needed, concat them into one spine before sweeping.
	/// @param spineRefParam It is the param on spine which is verified when the user chooses the spine (click one point on spine) to judge which part of curve is needed
	/// @param spineCorrParams Params of spine which profile is located on. Correspondece parameters can be automatically computed and some params can be missing.
	/// @param isClosedSweep If the spine is closed and sweep can be closed or open, do closed sweep or not. If the spine is open, make it closed.
	/// @param isAutoTwist Whether or not to automatically adjust periodic profile origin parameter to lower the twist of sweep surface.
	/// @return Swept surfaces.
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineSurface>> SweepOneRail(
		const std::vector<NURBSCurveSection>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& spine,
		double spineRefParam,
		const std::vector<std::pair<int, double>>& spineCorrParams,
		bool isClosedSweep,
		bool isAutoTwist);
};
} // namespace AMCAX
