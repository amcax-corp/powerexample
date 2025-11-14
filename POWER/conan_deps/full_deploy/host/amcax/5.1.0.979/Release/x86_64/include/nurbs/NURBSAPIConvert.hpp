/// @file      NURBSAPIConvert.hpp
/// @brief     The class of NURBS conversion from other type
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Array2.hpp>
#include <common/Macros.hpp>

namespace AMCAX
{
class Geom2Curve;
class Geom3Curve;
class Geom3Surface;
class Geom2BezierCurve;
class Geom3BezierCurve;
class Geom3BezierSurface;
class Geom2BSplineCurve;
class Geom3BSplineCurve;
class Geom3BSplineSurface;

/// @brief Class of converting a common curve/surface to a B spline curve/surface
/// @details This class converts other type curve or surface to NURBS.
class NURBSAPIConvert
{
public:
	/// @brief Convert a common curve to a BSpline curve
	/// @param curve The given curve
	/// @return Result BSpline curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineCurve> ToBSpline(const std::shared_ptr<Geom3Curve>& curve);

	/// @brief Convert a common 2d curve to a 2d BSpline curve
	/// @param curve The given curve
	/// @return Result BSpline curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom2BSplineCurve> ToBSpline(const std::shared_ptr<Geom2Curve>& curve);

	/// @brief Convert a common surface to a BSpline surface
	/// @param surface The given surface
	/// @return BSpline surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3BSplineSurface> ToBSpline(const std::shared_ptr<Geom3Surface>& surface);

	/// @brief Convert a BSpline curve to Bezier curves
	/// @param curve The BSpline curve
	/// @return Result Bezier curves
	[[nodiscard]] AMCAX_API static std::vector<std::shared_ptr<Geom3BezierCurve>> ToBezier(const std::shared_ptr<Geom3BSplineCurve>& curve);

#ifndef DOXYGEN_SKIP
	[[nodiscard]] AMCAX_TEST_API static std::vector<std::shared_ptr<Geom2BezierCurve>> ToBezier(const std::shared_ptr<Geom2BSplineCurve>& curve);
	[[nodiscard]] AMCAX_TEST_API static Array2<std::shared_ptr<Geom3BezierSurface>> ToBezier(const std::shared_ptr<Geom3BSplineSurface>& surf);
#endif
};
} // namespace AMCAX
