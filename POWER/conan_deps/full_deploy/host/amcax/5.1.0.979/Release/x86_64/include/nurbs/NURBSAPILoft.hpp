/// @file      NURBSAPILoft.hpp
/// @brief     The class of NURBS lofting
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <approx/ApproxParameterizationType.hpp>
#include <nurbs/NURBSCurveSection.hpp>
#include <nurbs/NURBSMacros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of NURBS lofting
/// @details This class computes the lofting surface from the section curves and guide curves.
class NURBSAPILoft
{
public:
	/// @brief Make lofting (section curves -> a surface)
	/// @param sections Curves with begin parameter and is reverse flag
	/// @param isClosedLofting Is surface closed
	/// @param stype The type of surface building such as interpolate, approx. It determines the error between surface and curves.
	/// @param ptype Parameterization type
	/// @param algo The algorithm of lofting. Basic is the original lofting and Sweep is the swept type lofting
	/// @return The loft surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> MakeLoft(const std::vector<NURBSCurveSection>& sections, bool isClosedLofting = false, NURBSLoftSurfaceStype stype = NURBSLoftSurfaceStype::Standard, ApproxParameterizationType ptype = ApproxParameterizationType::Centripetal, NURBSLoftAlgorithm algo = NURBSLoftAlgorithm::Basic);

	/// @brief Make lofting (section curves -> a surface) along rails
	/// @param sections Curves with begin parameter and is reverse flag
	/// @param rails Rails
	/// @param isClosedLofting Is surface closed
	/// @param stype The type of surface building such as interpolate, approx. It determines the error between surface and curves.
	/// @param ptype Parameterization type
	/// @return The loft surface
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineSurface>> MakeLoftWithRails(const std::vector<NURBSCurveSection>& sections, const std::vector<std::shared_ptr<Geom3BSplineCurve>>& rails, bool isClosedLofting = false, NURBSLoftSurfaceStype stype = NURBSLoftSurfaceStype::Standard, ApproxParameterizationType ptype = ApproxParameterizationType::Centripetal);
};
} // namespace AMCAX
