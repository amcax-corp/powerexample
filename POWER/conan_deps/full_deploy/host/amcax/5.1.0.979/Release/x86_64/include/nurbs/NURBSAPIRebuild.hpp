/// @file      NURBSAPIRebuild.hpp
/// @brief     The class of NURBS curve or surface rebuilding
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom2BSplineCurve;
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of rebuilding curves and surfaces
/// @details This class computes the rebuilt curve or surface with given source geometry, target degree and target number of poles
class NURBSAPIRebuild
{
public:
	/// @brief Rebuild curve with target degree and target number of poles
	/// @param srcCurve Source curve
	/// @param targetDeg Target degree
	/// @param targetNPoles Target number of poles
	/// @return The rebuilt curve and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, double> RebuildCurve(const std::shared_ptr<Geom3BSplineCurve>& srcCurve, int targetDeg, int targetNPoles);

	/// @brief Rebuild curve with target degree, target knots and mults
	/// @param srcCurve Source curve
	/// @param targetDeg Target degree
	/// @param knots Target knots
	/// @param mults Target mults
	/// @return The rebuilt curve and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, double> RebuildCurve(const std::shared_ptr<Geom3BSplineCurve>& srcCurve, int targetDeg, const std::vector<double>& knots, const std::vector<int>& mults);

	/// @brief Rebuild curve with target degree and target tolerance.
	/// @param srcCurve Source curve
	/// @param targetDeg Target degree
	/// @param tol The tolerance of source curve and result curve. It is usally set over 1e-2 to guarantee the time performance
	/// @return The rebuilt curve and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, double> RebuildCurve(const std::shared_ptr<Geom3BSplineCurve>& srcCurve, int targetDeg, double tol);

	/// @brief Rebuild 2d curve with target degree and target tolerance.
	/// @param srcCurve Source curve
	/// @param targetDeg Target degree
	/// @param tol The tolerance of source curve and result curve. It is usally set over 1e-2 to guarantee the time performance
	/// @return The rebuilt curve and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom2BSplineCurve>, double> RebuildCurve(const std::shared_ptr<Geom2BSplineCurve>& srcCurve, int targetDeg, double tol);

	/// @brief Rebuild curve with target degree, target number of poles and the parameter to begin with
	/// @param srcCurve Source curve
	/// @param beginParameter The begin parameter such as
	/// if the source curve's parameter domain is [0.0, 1.0], the rebuilt curve's parameter domain is [t, 1.0 + t]
	/// @param isReverse Is the rebuilt curve parameter direction reversed
	/// @param targetDeg The target degree
	/// @param targetNPoles The target number of poles
	/// @return The rebuilt curve and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, double> RebuildPeriodicCurveFromParameter(const std::shared_ptr<Geom3BSplineCurve>& srcCurve, double beginParameter, bool isReverse, int targetDeg, int targetNPoles);

	/// @brief Rebuild curve with target degree, target tolerance and the parameter to begin with
	/// @param srcCurve Source curve
	/// @param beginParameter The begin parameter such as
	/// if the source curve's parameter domain is [0.0, 1.0], the rebuilt curve's parameter domain is [t, 1.0 + t]
	/// @param isReverse Is the rebuilt curve parameter direction reversed
	/// @param targetDeg The target degree
	/// @param tol The target tolerance of source curve and result curve. It is usally set over 1e-2 to guarantee the time performance
	/// @return The rebuilt curve and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, double> RebuildPeriodicCurveFromParameter(const std::shared_ptr<Geom3BSplineCurve>& srcCurve, double beginParameter, bool isReverse, int targetDeg, double tol);

	/// @brief Rebuild curve with target degree, knots, mults and the parameter to begin with
	/// @param srcCurve Source curve
	/// @param beginParameter The begin parameter such as
	/// if the source curve's parameter domain is [0.0, 1.0], the rebuilt curve's parameter domain is [t, 1.0 + t]
	/// @param isReverse Is the rebuilt curve parameter direction reversed
	/// @param targetDeg The target degree
	/// @param knots The given knots
	/// @param mults The given mults
	/// @return The rebuilt curve and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineCurve>, double> RebuildPeriodicCurveFromParameter(const std::shared_ptr<Geom3BSplineCurve>& srcCurve, double beginParameter, bool isReverse, int targetDeg, const std::vector<double>& knots, const std::vector<int>& mults);

	/// @brief Rebuild surface with target degree and target number of poles
	/// @param srcSurf Source surface
	/// @param targetUDeg Target u degree
	/// @param targetVDeg Target v degree
	/// @param targetNUPoles Target number of u poles
	/// @param targetNVPoles Target number of v poles
	/// @return The rebuit surface and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineSurface>, double> RebuildSurface(const std::shared_ptr<Geom3BSplineSurface>& srcSurf, int targetUDeg, int targetVDeg, int targetNUPoles, int targetNVPoles);

	/// @brief Rebuild surface with target degree, target uv knots and mults
	/// @param srcSurf Source surface
	/// @param targetUDeg Target u degree
	/// @param targetVDeg Target v degree
	/// @param uknots Target u knots
	/// @param vknots Target v knots
	/// @param umults Target u multipicities
	/// @param vmults Target v multipicities
	/// @return The rebuit surface and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineSurface>, double> RebuildSurface(const std::shared_ptr<Geom3BSplineSurface>& srcSurf, int targetUDeg, int targetVDeg, const std::vector<double>& uknots, const std::vector<double>& vknots, const std::vector<int>& umults, const std::vector<int>& vmults);

	/// @brief Rebuild surface with target degree and target tolerance
	/// @param srcSurf Source surface
	/// @param targetUDeg Target u degree
	/// @param targetVDeg Target v degree
	/// @param tol Target tolerance between source surface and result surface. It is usally set over 1e-2 to guarantee the time performance
	/// @return The rebuit surface and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineSurface>, double> RebuildSurface(const std::shared_ptr<Geom3BSplineSurface>& srcSurf, int targetUDeg, int targetVDeg, double tol);

	/// @brief Rebuild surface with target degree, target number of poles and the parameter to begin with
	/// @param srcSurface Source surface
	/// @param isU Is u parameter
	/// @param beginParameter The begin parameter such as
	/// if the source surface's parameter domain is [0.0, 1.0], the rebuilt surface's parameter domain is [t, 1.0 + t]
	/// @param isReverse Is the rebuilt surface parameter direction reversed
	/// @param targetDeg The target degree
	/// @param targetNPoles The target number of poles
	/// @return The rebuilt surface and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineSurface>, double> RebuildPeriodicSurfaceFromParameter(const std::shared_ptr<Geom3BSplineSurface>& srcSurface, bool isU, double beginParameter, bool isReverse, int targetDeg, int targetNPoles);

	/// @brief Rebuild surface with target degree, target tolerance and the parameter to begin with
	/// @param srcSurface Source surface
	/// @param isU Is u parameter
	/// @param beginParameter The begin parameter such as
	/// if the source surface's parameter domain is [0.0, 1.0], the rebuilt surface's parameter domain is [t, 1.0 + t]
	/// @param isReverse Is the rebuilt surface parameter direction reversed
	/// @param targetDeg The target degree
	/// @param tol The target tolerance of source surface and result surface. It is usally set over 1e-2 to guarantee the time performance
	/// @return The rebuilt surface and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineSurface>, double> RebuildPeriodicSurfaceFromParameter(const std::shared_ptr<Geom3BSplineSurface>& srcSurface, bool isU, double beginParameter, bool isReverse, int targetDeg, double tol);

	/// @brief Rebuild surface with target degree, knots, mults and the parameter to begin with
	/// @param srcSurface Source surface
	/// @param isU Is u parameter
	/// @param beginParameter The begin parameter such as
	/// if the source surface's parameter domain is [0.0, 1.0], the rebuilt surface's parameter domain is [t, 1.0 + t]
	/// @param isReverse Is the rebuilt surface parameter direction reversed
	/// @param targetDeg The target degree
	/// @param knots The given knots
	/// @param mults The given mults
	/// @return The rebuilt surface and the error
	[[nodiscard]] AMCAX_API static std::pair<std::shared_ptr<Geom3BSplineSurface>, double> RebuildPeriodicSurfaceFromParameter(const std::shared_ptr<Geom3BSplineSurface>& srcSurface, bool isU, double beginParameter, bool isReverse, int targetDeg, const std::vector<double>& knots, const std::vector<int>& mults);
};
} // namespace AMCAX
