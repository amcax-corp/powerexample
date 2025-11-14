/// @file      NURBSAPIOffsetCurveOnSurface.hpp
/// @brief     The class of NURBS curve on surface offset operation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/PointT.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
class Geom3Curve;

/// @brief Class of offset curve on surface
/// @details This class computes the offset result which is still on the surface
class NURBSAPIOffsetCurveOnSurface
{
public:
	/// @brief Offset curve on surface to a distance
	/// @param edge The curve which should lie on surface
	/// @param face The surface
	/// @param offset Offset distance
	/// @param reverse Whether offset the curve to right side of the curve D1 on parameter domain
	/// @return The result curves or points. The result can degenerated to a point or break into curve segments.
	[[nodiscard]] AMCAX_API static std::pair<std::vector<std::shared_ptr<Geom3Curve>>, std::vector<Point3>> OffsetCurveOnSurface(
		const TopoEdge& edge, const TopoFace& face, double offset, bool reverse);

	/// @brief Offset curve on surface to a point
	/// @param edge The curve which should lie on surface
	/// @param face The surface
	/// @param point The target point
	/// @return The result curves or points. The result can degenerated to a point or break into curve segments.
	[[nodiscard]] AMCAX_API static std::pair<std::vector<std::shared_ptr<Geom3Curve>>, std::vector<Point3>> OffsetCurveOnSurfaceToPoint(
		const TopoEdge& edge, const TopoFace& face, const Point2& point);
};
} // namespace AMCAX
