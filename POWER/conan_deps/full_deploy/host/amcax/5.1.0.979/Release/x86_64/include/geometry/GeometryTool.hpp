/// @file      GeometryTool.hpp
/// @brief     Class of tools for geometry objects
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <math/GeometryMacros.hpp>
#include <math/Plane.hpp>

namespace AMCAX
{
class Adaptor3CurveOnSurface;
class Geom2Curve;
class Geom3Curve;
class Geom3Surface;
class Geom3BezierSurface;
class Geom3BSplineSurface;
class Geom3BoundedCurve;
class Geom3BoundedSurface;

/// @brief Class of tools for geometry objects
class GeometryTool
{
public:
	/// @brief Convert a 2D curve to 3D curve
	/// @param position The local coordinate system
	/// @param curve The 2D curve
	/// @return The 3D curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> To3d(const Frame3& position, const std::shared_ptr<Geom2Curve>& curve);

	/// @brief Extend a bounded surface by a given length and extension directions
	/// @details The input surface should not be periodic.
	///          In addition, this function converts the surface into a B spline surface
	///          if the input surface is out of its natural parameter domain.
	/// @param[in,out] surface The surface to be extended
	/// @param[in] length The extension length
	/// @param[in] continuity The continuity constraints, ranging among 1, 2, 3
	/// @param[in] inU Set whether extending along u direction
	/// @param[in] after Set extension direction is forward or reversed
	AMCAX_API static void ExtendSurfByLength(std::shared_ptr<Geom3BoundedSurface>& surface, double length, int continuity, bool inU, bool after);

	/// @brief Check if a surface is a planar surface, and if it is planar, find the plane
	/// @param[in] s The input surface
	/// @param[out] plane The plane found when the surface is planar surface
	/// @param[in] tol The tolerance
	/// @return True if the surface is a planar surface
	AMCAX_API static bool IsPlanarSurface(const std::shared_ptr<Geom3Surface>& s, Plane& plane, double tol = 1.0e-7);

	/// @brief Check if a 3D curve is a planar curve, and if it is planar, find the plane
	/// @details If the input curve, such as a line, is on more than one plane, it will return the plane in which any one is located
	/// @param[in] c The input curve
	/// @param[out] plane The plane found when the curve is planar curve
	/// @param[in] tol The tolerance
	/// @return True if the curve is a planar curve
	AMCAX_API static bool IsPlanarCurve(const std::shared_ptr<Geom3Curve>& c, Plane& plane, double tol = 1.0e-7);

	/// @brief Check if a list of 3D curves is in one plane, and if in one plane, find the plane
	/// @param[in] curves The input cuves
	/// @param[out] plane The plane found when the curves in one plane
	/// @param[in] tol The linear tolerance used to check whether the curve is coplanar
	/// @param[in] angelTol The angle tolerance used to check whether the curve is coplanar, range in [0, Pi]
	/// @return True if the curves in one plane
	AMCAX_API static bool IsPlanarCurves(const std::vector<std::shared_ptr<Geom3Curve>>& curves, Plane& plane, double tol = 1.0e-7, double angelTol = 1.0e-3);

#ifndef DOXYGEN_SKIP

	static void SameRange(double tolerance, const std::shared_ptr<Geom2Curve>& curve2d, double first, double last, double requestedFirst, double requestedLast, std::shared_ptr<Geom2Curve>& newCurve2d);
	static void BuildCurve3d(double tolerance, const Adaptor3CurveOnSurface& curve, double firstParameter, double lastParameter, std::shared_ptr<Geom3Curve>& newCurve, double& maxDeviation, double& averageDeviation, ContinuityType continuity = ContinuityType::C1, int maxDegree = 14, int maxSegment = 30);
	static void AdjustExtremity(std::shared_ptr<Geom3BoundedCurve>& curve, const Point3& p1, const Point3& p2, const Vector3& v1, const Vector3& v2);
	static void ExtendCurveToPoint(std::shared_ptr<Geom3BoundedCurve>& curve, const Point3& p, int cont, bool after);
	static void AxisOfInertia(const std::vector<Point3>& points, Frame3& axis, bool& isSingular, double tol = 1.0e-7);
	static void Inertia(const std::vector<Point3>& points, Point3& bary, Direction3& xDir, Direction3& yDir, double& xGap, double& yGap, double& zGap);
	static void FuseIntervals(const std::vector<double>& intervals1, const std::vector<double>& intervals2, std::vector<double>& nintervals, double eps = 1.e-9, bool isChooseFirstInterval = false);
	static int EstimateNormal(const std::shared_ptr<Geom3Surface>& s, const Point2& uv, double tol, Direction3& n);
	static void IsClosed(const std::shared_ptr<Geom3Surface>& s, double tol, bool& isUClosed, bool& isVClosed);
	static bool IsBSplineUClosed(const std::shared_ptr<Geom3BSplineSurface>& s, double u1, double u2, double tol);
	static bool IsBSplineVClosed(const std::shared_ptr<Geom3BSplineSurface>& s, double v1, double v2, double tol);
	static bool IsBezierUClosed(const std::shared_ptr<Geom3BezierSurface>& s, double u1, double u2, double tol);
	static bool IsBezierVClosed(const std::shared_ptr<Geom3BezierSurface>& s, double v1, double v2, double tol);
	static bool Parameter(const std::shared_ptr<Geom2Curve>& curve, const Point2& Point, double maxDist, double& u);
	static bool Parameter(const std::shared_ptr<Geom3Curve>& curve, const Point3& point, double maxDist, double& u);
	static bool Parameters(const std::shared_ptr<Geom3Surface>& surface, const Point3& Point, double maxDist, double& u, double& v);
	static bool IsCurveOnPlane(const std::shared_ptr<Geom3Curve>& curve, const Plane& plane, double tol = 1.0e-7);

#endif
};
} // namespace AMCAX
