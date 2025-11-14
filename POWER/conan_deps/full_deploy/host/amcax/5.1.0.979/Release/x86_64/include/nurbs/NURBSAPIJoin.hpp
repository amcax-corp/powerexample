/// @file      NURBSAPIJoin.hpp
/// @brief     Class of NURBS join operation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <memory>
#include <vector>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom2BSplineCurve;
class Geom3BSplineCurve;
class Geom3BSplineSurface;
class Geom3Surface;

/// @brief Class of combining two or more curves/surfaces end-to-end into one curve/surface
/// @details This class computes the result curve or surface by joining connected curves or surfaces
class NURBSAPIJoin
{
public:
	/// @brief Prepare for joining curves to several curves
	/// @details The unsorted and unclassified curves are classified into several groups by tolerance,
	/// each group which contains sorted curves and curve orientations will create a curve.
	/// @param inputCurves The given curves;
	/// @param tol Tolerance to judge connection
	/// @return {sorted curves, each curve is reverse, is result periodic}
	[[nodiscard]] AMCAX_API static std::tuple<std::vector<std::vector<std::shared_ptr<Geom3BSplineCurve>>>, std::vector<std::vector<bool>>, std::vector<bool>>
	JoinCurvePrepare(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& inputCurves, double tol);

	/// @brief Prepare for joining curves
	/// @details The unsorted and unclassified curves are classified into several groups by tolerance,
	/// each group which contains sorted curves and curve orientations will create a curve.
	/// @param inputCurves  The given curves;
	/// @param inputCurve2ds  The given curve2ds;
	/// @param tol Tolerance to judge 3d connection
	/// @param tol2d Tolerance to judge 2d connection
	/// @return {sorted curves, sorted curve2ds, each curve is reverse, is result periodic}
	[[nodiscard]] AMCAX_API static std::tuple<std::vector<std::vector<std::shared_ptr<Geom3BSplineCurve>>>, std::vector<std::vector<std::shared_ptr<Geom2BSplineCurve>>>, std::vector<std::vector<bool>>, std::vector<bool>>
	JoinCurvePrepare(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& inputCurves, const std::vector<std::shared_ptr<Geom2BSplineCurve>>& inputCurve2ds, double tol, double tol2d);

	/// @brief Prepare for joining curves to a curve
	/// @details The unsorted curves are forced to classified into one group,
	/// the group which contains the sorted curves and the curve orientations will create one curve.
	/// @param inputCurves The given curves;
	/// @return {sorted curves, each curve is reverse, is result periodic}
	[[nodiscard]] AMCAX_API static std::tuple<std::vector<std::shared_ptr<Geom3BSplineCurve>>, std::vector<bool>, bool>
	JoinCurvePrepare(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& inputCurves);

	/// @brief Prepare for join curves to a curve
	/// @details The unsorted curves are forced to classified into one group,
	/// the group which contains the sorted curves and the curve orientations will create one curve.
	/// @param inputCurves  The given curves;
	/// @param inputCurve2ds  The given curve2ds;
	/// @return {sorted curves, sorted curve2ds, each curve is reverse, is result periodic}
	[[nodiscard]] AMCAX_API static std::tuple<std::vector<std::shared_ptr<Geom3BSplineCurve>>, std::vector<std::shared_ptr<Geom2BSplineCurve>>, std::vector<bool>, bool>
	JoinCurvePrepare(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& inputCurves, const std::vector<std::shared_ptr<Geom2BSplineCurve>>& inputCurve2ds);

	/// @brief Curves and curve2ds are combined to a curve
	/// @param curves The given curves
	/// @param curve2ds The given curve2ds
	/// @param isReverse Whether curves should get reversed
	/// @param isPeriodic Is result curve periodic
	/// @return The joint curves and curve2ds
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, std::shared_ptr<Geom2BSplineCurve>> JoinCurves(
		const std::vector<std::shared_ptr<Geom3BSplineCurve>>& curves,
		const std::vector<std::shared_ptr<Geom2BSplineCurve>>& curve2ds,
		const std::vector<bool>& isReverse, bool isPeriodic);

	/// @brief Curves and curve2ds are combined to several curves
	/// @param curves The given curves, each group will make a curve
	/// @param curve2ds The given curve2ds, each group will make a curve
	/// @param isReverse Whether curves should get reversed
	/// @param isPeriodic Is result curve periodic
	/// @return The joint curves and curve2ds
	[[nodiscard]] AMCAX_API static std::pair<std::vector<std::shared_ptr<Geom3BSplineCurve>>, std::vector<std::shared_ptr<Geom2BSplineCurve>>> JoinCurves(
		const std::vector<std::vector<std::shared_ptr<Geom3BSplineCurve>>>& curves,
		const std::vector<std::vector<std::shared_ptr<Geom2BSplineCurve>>>& curve2ds,
		const std::vector<std::vector<bool>>& isReverse, const std::vector<bool>& isPeriodic);

	/// @brief Curves are combined to several curves
	/// @param curves The given curves, each group will make a curve
	/// @param isReverse Whether curves should get reversed
	/// @param isPeriodic Is result curve periodic
	/// @return The joint curves
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BSplineCurve>> JoinCurves(
		const std::vector<std::vector<std::shared_ptr<Geom3BSplineCurve>>>& curves,
		const std::vector<std::vector<bool>>& isReverse, const std::vector<bool>& isPeriodic);

	/// @brief Curves are combined to a curve
	/// @param curves The given curves
	/// @param isReverse Whether curves should get reversed
	/// @param isPeriodic Is result curve periodic
	/// @return The joint curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> JoinCurves(
		const std::vector<std::shared_ptr<Geom3BSplineCurve>>& curves,
		const std::vector<bool>& isReverse, bool isPeriodic);

	/// @brief Prepare for joining surfaces to a surface
	/// @param surfaces The given surfaces
	/// @param tol Tolerance to judge connection
	/// @return {sorted surfaces, is surface connection boundary a u isocurve, is surface front back reverse, is surface iso reverse, is result uperiodic, isresult vperiodic}
	[[nodiscard]] AMCAX_API static std::tuple<std::vector<std::shared_ptr<Geom3BSplineSurface>>, std::vector<bool>, std::vector<bool>, std::vector<bool>, bool, bool>
	JoinSurfacesPrepare(const std::vector<std::shared_ptr<Geom3BSplineSurface>>& surfaces, double tol);

	/// @brief Surfaces are combined to one surface
	/// @param surface1 Surface 1
	/// @param surface2 Surface 2
	/// @param isSurface1UIso Is surface 1 connection boundary a u isocurve
	/// @param isSurface2UIso Is surface 2 connection boundary a u isocurve
	/// @param isSurface1FrontBackReverse Whether surface1 follows the rule that surface 1 back boundary is connected to surface 2 front boundary
	/// @param isSurface2FrontBackReverse Whether surface2 follows the rule that surface 1 back boundary is connected to surface 2 front boundary
	/// @param isSurface1IsoReverse Is surface 1 connection boundary isocurve need to be reversed
	/// @param isSurface2IsoReverse Is surface 2 connection boundary isocurve need to be reversed
	/// @param isUPeriodic Is final surface UPeriodic
	/// @param isVPeriodic Is final surface VPeriodic
	/// @return [isSucceed, sirface]. When surfaces don't coincide at end, return false.
	[[nodiscard]] AMCAX_API static std::pair<bool, std::shared_ptr<Geom3BSplineSurface>> JoinSurfaces(
		const std::shared_ptr<Geom3BSplineSurface>& surface1,
		const std::shared_ptr<Geom3BSplineSurface>& surface2,
		bool isSurface1UIso, bool isSurface2UIso,
		bool isSurface1FrontBackReverse, bool isSurface2FrontBackReverse,
		bool isSurface1IsoReverse, bool isSurface2IsoReverse,
		bool isUPeriodic, bool isVPeriodic);

	/// @brief Surfaces are combined to one surface.
	/// Make sure all surfaces are connected with the same direction isocurves, such as u front iso and u back iso
	/// , which means that it is not allowed that one surface is connected to other surfaces on a u iso and a v iso.
	/// @param surfaces Surfaces
	/// @param isUIso Is surface i connection boundary a u isocurve
	/// @param isFrontBackReverse Whether surface i follows the rule that surface i back boundary is connected to the next surface boundary
	/// @param isIsoReverse Is surface i connection boundary isocurve need to be reversed
	/// @param isUPeriodic Is final surface UPeriodic
	/// @param isVPeriodic Is final surface VPeriodic
	/// @return [isSucceed, surface]. When surfaces don't coincide at end, return false.
	[[nodiscard]] AMCAX_API static std::pair<bool, std::shared_ptr<Geom3BSplineSurface>> JoinSurfaces(
		const std::vector<std::shared_ptr<Geom3BSplineSurface>>& surfaces,
		const std::vector<bool>& isUIso, const std::vector<bool>& isFrontBackReverse,
		const std::vector<bool>& isIsoReverse, bool isUPeriodic, bool isVPeriodic);

#ifndef DOXYGEN_SKIP
	[[nodiscard]] AMCAX_TEST_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, std::shared_ptr<Geom2BSplineCurve>>
	JoinCurveOnSurface(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& inputCurves,
		const std::vector<std::shared_ptr<Geom2BSplineCurve>>& inputCurve2ds,
		const std::shared_ptr<Geom3Surface> surface);

	[[nodiscard]] AMCAX_TEST_API static std::pair<std::vector<std::shared_ptr<Geom3BSplineCurve>>, std::vector<std::shared_ptr<Geom2BSplineCurve>>>
	JoinCurveOnSurface(const std::vector<std::shared_ptr<Geom3BSplineCurve>>& inputCurves,
		const std::vector<std::shared_ptr<Geom2BSplineCurve>>& inputCurve2ds,
		const std::shared_ptr<Geom3Surface> surface, double tol3d, double tol2d);
#endif
};
} // namespace AMCAX
