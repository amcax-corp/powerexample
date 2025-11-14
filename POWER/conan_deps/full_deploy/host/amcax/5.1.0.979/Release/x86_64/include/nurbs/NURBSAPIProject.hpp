/// @file      NURBSAPIProject.hpp
/// @brief     The class of projecting curve onto surface
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/DirectionT.hpp>
#include <common/PointT.hpp>

namespace AMCAX
{
class Geom2Curve;
class Geom3Curve;
class Geom2BSplineCurve;
class Geom3BSplineCurve;
class Geom3Surface;

/// @brief Project curve on surface
class NURBSAPIProject
{
public:
	/// @brief Project the curve on the surface by point light projection
	/// @param curve Curve
	/// @param surf Surface
	/// @param pt The point light source
	/// @return Projected 3D curves and their 2D parameter curves, 3D points and their 2D parameter points
	[[nodiscard]] AMCAX_API static std::pair<std::vector<std::pair<std::shared_ptr<Geom3Curve>, std::shared_ptr<Geom2Curve>>>, std::vector<std::pair<Point3, Point2>>>
	NURBSProjectCurveOnSurface(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Surface>& surf, const Point3& pt);

	/// @brief Project the curve on the surface by parallel light projection
	/// @param curve Curve
	/// @param surf Surface
	/// @param dir Projection direction
	/// @return Projected 3D curves and their 2D parameter curves, 3D points and their 2D parameter points
	[[nodiscard]] AMCAX_API static std::pair<std::vector<std::pair<std::shared_ptr<Geom3Curve>, std::shared_ptr<Geom2Curve>>>, std::vector<std::pair<Point3, Point2>>>
	NURBSProjectCurveOnSurface(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Surface>& surf, const Direction3& dir);

	/// @brief Project the curve on the surface along the surface normal
	/// @param curve The curve to project
	/// @param surf The surface
	/// @return {isSucceeded, curve3d, pcurve}
	[[nodiscard]] AMCAX_API static std::tuple<bool, std::shared_ptr<AMCAX::Geom3BSplineCurve>, std::shared_ptr<AMCAX::Geom2BSplineCurve>>
	ProjectAlongSurfaceNormal(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Surface>& surf);
};
} // namespace AMCAX
