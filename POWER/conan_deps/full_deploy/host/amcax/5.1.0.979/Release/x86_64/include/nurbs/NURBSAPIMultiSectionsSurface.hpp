/// @file      NURBSAPIMultiSectionsSurface.hpp
/// @brief     Class of NURBS multi-section surface
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class Geom3BSplineSurface;
class Geom2BSplineCurve;
class Geom3BSplineCurve;
class Geom3Surface;

/// @brief Struct of SectionCurve
/// @details The SectionCurve contains curve, pCurve, surface and continuity type
struct SectionCurve
{
	std::shared_ptr<AMCAX::Geom3BSplineCurve> curve;
	std::shared_ptr<AMCAX::Geom2BSplineCurve> pCurve;
	std::shared_ptr<AMCAX::Geom3Surface> surface;
	ContinuityType Continuity;
};

/// @brief Class of muti-section surface
/// @details Create a multi-section surface from at least two section curves and any guide curve
class NURBSAPIMultiSectionsSurface
{
public:
	/// @brief Constructor
	AMCAX_API NURBSAPIMultiSectionsSurface();

	/// @brief Create a multi-section surface
	/// @details Create a surface requires at least two sections
	/// @details Curves must have the same orientation and parameter domain as pCurves
	/// @details Guide curves must intersect each section curve and must be continuous in point
	/// The u periodicity of the result surface is same as the periodicity of sections
	/// The v periodicity of the result surface is same as the periodicity of guides
	/// @param sections The sections contains section curves, pCurves and surfaces in the u direction
	/// @param guides The guides contains guide curves, pCurves and surfaces in the v direction (the guide may be cut by the section)
	/// @param nsample The nsample is the number of samples in the u direction and v direction on the result surface
	/// @param nupoles The nupoles is the number of control points in the u direction npoles on the result surface
	/// @param nvpoles The nvpoles is the number of control points in the v direction npoles on the result surface
	/// @param tol The intersection tolerance of section curves and guides
	/// @param isClosed Is surface closed
	/// @return The result surface
	AMCAX_API std::shared_ptr<AMCAX::Geom3BSplineSurface> Perform(
		const std::vector<SectionCurve>& sections,
		const std::vector<SectionCurve>& guides,
		int nsample,
		int nupoles,
		int nvpoles,
		double tol = 1e-3,
		bool isClosed = false);

	/// @brief Get the parameter of isoparametric curve on the result surface
	/// @param isU The u direction or v direction
	/// @param id The index of section or guide
	/// @return The parameter
	AMCAX_API double IsoParam(bool isU, int id) const;

private:
	std::vector<double> uiso;
	std::vector<double> viso;
};
} // namespace AMCAX
