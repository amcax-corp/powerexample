/// @file      NURBSAPISweep2.hpp
/// @brief     The class of two-rail sweeping
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <nurbs/NURBSCurveSection.hpp>

namespace AMCAX
{
class Geom3BSplineSurface;
class Geom3BSplineCurve;

/// @brief Class of sweeping profiles along two spines
/// @details This class computes the swept surface with one or more profiles and two spine curves
class NURBSAPISweep2
{
public:
	/// @brief Sweep a profile along two spines
	/// @param profile The profile
	/// @param spine1 The spine
	/// @param spine2 The spine
	/// @return Swept surfaces
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineSurface>> SweepTwoRails(
		const std::shared_ptr<Geom3BSplineCurve>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& spine1,
		const std::shared_ptr<Geom3BSplineCurve>& spine2);

	/// @brief Sweep profiles along two spines.
	/// @param profile If only one profile, open spine will get surface between spine first parameter (or last parameter which depends on the chosen spineRefParam) and profile correspondece parameter
	/// but closed spine will get the whole surface even though the whole surface is consist of severial sub-surfaces which is segmented by init profile and spine C0 params.
	/// If num of profile is more than one, only the surface between the profiles (spineRefParam is not used to judge which part is left, only the sequence of profiles is considered)
	/// will be generated and the surface is segmented whose rule is same as above unless isClosedSweep is true.
	/// @param spine1 Spine1, closed or open, C0 or not. If multiple end-to-end spines are needed, concat them into one spine before sweeping.
	/// @param spine2 Spine2, closed or open, C0 or not. If multiple end-to-end spines are needed, concat them into one spine before sweeping.
	/// @param spine1RefParam It is the param on spine1 which is verified when the user chooses the spine (click one point on spine) to judge which part of curve is deman
	/// @param spine1CorrParams Params of spine1 which profile is located on. Correspondece parameters can be automatically computed so params can be missing.
	/// @param spine2CorrParams Params of spine2 which profile is located on. Correspondece parameters can be automatically computed so params can be missing.
	/// @param isClosedSweep If the spine is closed and sweep can be closed or open, do closed sweep or not. If the spine is open, make it closed.
	/// @param isAutoTwist Whether automatically lower the surface twist.
	/// @return Swept surfaces divided by c0. U is rail direction and v is profile direction.
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineSurface>> SweepTwoRails(
		const std::vector<NURBSCurveSection>& profile,
		const std::shared_ptr<Geom3BSplineCurve>& spine1,
		const std::shared_ptr<Geom3BSplineCurve>& spine2,
		double spine1RefParam,
		const std::vector<std::pair<int, double>>& spine1CorrParams,
		const std::vector<std::pair<int, double>>& spine2CorrParams,
		bool isClosedSweep,
		bool isAutoTwist);
};
} // namespace AMCAX
