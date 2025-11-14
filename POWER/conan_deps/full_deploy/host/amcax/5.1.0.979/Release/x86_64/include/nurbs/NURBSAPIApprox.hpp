/// @file      NURBSAPIApprox.hpp
/// @brief     Class of NURBS curve approximation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <approx/ApproxParameterizationType.hpp>
#include <common/PointT.hpp>
#include <nurbs/NURBSMacros.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of approximate points to a curve
/// @details This class computes the approximation result curve of data points.
class NURBSAPIApprox
{
public:
	/// @brief Approx points to a curve
	/// @param points Data points to be approximated
	/// @param degree Target degree
	/// @param npoles Target number of poles
	/// @param isClosed Is curve closed
	/// @param ptype The parameterization type of data points
	/// @return curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> ApproxPoints(const std::vector<Point3>& points, int degree, int npoles, bool isClosed = false, ApproxParameterizationType ptype = ApproxParameterizationType::ChordLength);

#ifndef DOXYGEN_SKIP
	/// @brief Approx curves to make a surface
	/// @param curves Compatible input curves
	/// @param npoles Target number of poles
	/// @param isClosed Is surface closed
	/// @param ptype The parameterization type of data curves
	/// @return surface
	[[nodiscard]] AMCAX_TEST_API static std::shared_ptr<Geom3BSplineSurface> ApproxCurves(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& curves, int npoles, bool isClosed = false, ApproxParameterizationType ptype = ApproxParameterizationType::ChordLength);

	/// @brief Approx weighted curves to make a surface
	/// @param curves Input curves, all periodic or all not periodic
	/// @param weights Weights of tolerance calculation
	/// @param npoles Target number of poles
	/// @param isClosed Is surface closed
	/// @param ptype The parameterization type of data curves
	/// @return surface
	[[nodiscard]] static std::shared_ptr<Geom3BSplineSurface> ApproxCurvesWithWeights(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& curves, const std::vector<double>& weights, int npoles, bool isClosed = false, ApproxParameterizationType ptype = ApproxParameterizationType::ChordLength);
#endif
};
} // namespace AMCAX
