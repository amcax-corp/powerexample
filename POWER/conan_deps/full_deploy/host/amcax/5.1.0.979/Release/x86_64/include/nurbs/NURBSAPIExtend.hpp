/// @file      NURBSAPIExtend.hpp
/// @brief     Class of NURBS extension
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <common/PointT.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
class TopoEdge;
class TopoFace;
class TopoShape;
class Geom3Plane;
class Geom3Curve;
class Geom3Surface;

/// @brief Class of extending a curve/surface without degree changes.
/// @details This class computes the result curve or surface by extending the source untrimmed NURBS curve or surface at boundary.
/// The original curve is part of new curve.
/// Functions include extend curve/surface toPoint/byLength/onPlane(G0)/perpendicularToPlane(G1)
class NURBSAPIExtend
{
public:
	/// @brief Extend curve to plane and the curve end which is closer to plane is on the plane, which can be used in mirror to fix the gap.
	/// The original curve is part of new curve.
	/// The degree, the size of knots and the number of poles are not changed.
	/// @param curve Curve
	/// @param plane Plane
	/// @return New curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> ExtendCurveOnPlane(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Extend curve to plane and the end of curve is on the plane, which can be used in mirror to fix the gap.
	/// The original curve is part of new curve.
	/// The degree, the size of knots and the number of poles are not changed.
	/// @param curve Curve
	/// @param isFront Extend front or back
	/// @param plane Plane
	/// @return New curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> ExtendCurveOnPlane(const std::shared_ptr<Geom3Curve>& curve, bool isFront, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Extend curve to plane and the curve end which is closer to plane is perpendicular to the plane, which can be used in mirror to fix the gap.
	/// The original curve is part of new curve.
	/// The degree of curve is not changed but the size of knots and poles increase 1.
	/// @param curve Curve
	/// @param plane Plane
	/// @return New curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> ExtendCurvePerpendicularToPlane(const std::shared_ptr<Geom3Curve>& curve, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Extend curve to plane and the end of curve is perpendicular to the plane, which can be used in mirror to fix the gap.
	/// The original curve is part of new curve.
	/// The degree of curve is not changed but the size of knots and poles increase 1.
	/// @param curve Curve
	/// @param isFront Extend front or back
	/// @param plane Plane
	/// @return New curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> ExtendCurvePerpendicularToPlane(const std::shared_ptr<Geom3Curve>& curve, bool isFront, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Extend surface to plane and the surface end which is closer to plane is always perpendicular to the plane, which can be used in mirror to fix the gap.
	/// The original surface is part of new surface.
	/// The degree of surface is not changed but the size of the extended direction (u or v) knots and poles increase 1.
	/// @param surf Surf
	/// @param plane Plane
	/// @return New surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Surface> ExtendSurfPerpendicularToPlane(const std::shared_ptr<Geom3Surface>& surf, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Extend surface to plane and the end of surface is always perpendicular to the plane, which can be used in mirror to fix the gap.
	/// The original surface is part of new surface.
	/// The degree of surface is not changed but the size of the extended direction (u or v) knots and poles increase 1.
	/// @param surf Surf
	/// @param isExtendU Extend u or v
	/// @param isFront Extend front or back
	/// @param plane Plane
	/// @return New surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Surface> ExtendSurfPerpendicularToPlane(const std::shared_ptr<Geom3Surface>& surf, bool isExtendU, bool isFront, const std::shared_ptr<Geom3Plane>& plane);

	/// @brief Extend curve to a point.
	/// The original curve is part of new curve.
	/// The degree is not changed but the number of poles and knots increase 1.
	/// @param curve Curve
	/// @param isFront Extend front or back
	/// @param pt Point
	/// @return New curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> ExtendCurveToDynamicPoint(const std::shared_ptr<Geom3Curve>& curve, bool isFront, const Point3& pt);

	/// @brief Extend curve to a point.
	/// The original curve is part of new curve.
	/// The degree and the number of poles and knots are not changed.
	/// @param curve Curve
	/// @param isFront Extend front or back
	/// @param pt Point
	/// @return New curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> ExtendCurveToPoint(const std::shared_ptr<Geom3Curve>& curve, bool isFront, const Point3& pt);

	/// @brief Extend curve with specified 3D length.
	/// The original curve is part of new curve.
	/// The degree and the number of poles and knots are not changed.
	/// If new patch needed, refer to GeometryTool.
	/// @param curve Curve
	/// @param isFront Extend front or back
	/// @param length The length of the extend part of curve
	/// @param tol Tolerance of length error
	/// @return New curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> ExtendCurveByLength(const std::shared_ptr<Geom3Curve>& curve, bool isFront, double length, double tol = 1e-3);

	/// @brief Extend surface to a point.
	/// The original surface is part of new surface.
	/// The degree of the surface, the size of the extended direction (u or v) knots and poles are not changed.
	/// @param surf Surface
	/// @param isU Extend u or v
	/// @param isFront Extend front or back
	/// @param pt Point
	/// @return New surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Surface> ExtendSurfToPoint(const std::shared_ptr<Geom3Surface>& surf, bool isU, bool isFront, const Point3& pt);

	/// @brief Extend surface with specified average 3D length.
	/// The original surface is part of new surface.
	/// The degree and the number of poles and knots are not changed.
	/// If new patch needed, refer to GeometryTool.
	/// @param surf Surface
	/// @param isExtendU Extend u direction or v direction
	/// @param isFront Extend front or back
	/// @param averageLength The average extend length
	/// @param tol The tolerance
	/// @return New surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Surface> ExtendSurfByAverageLength(const std::shared_ptr<Geom3Surface>& surf, bool isExtendU, bool isFront, double averageLength, double tol = 1e-3);

	/// @brief Extend surface with specified 3D length at an iso curve of the surface.
	/// The original surface is part of new surface.
	/// The degree and the number of poles and knots are not changed.
	/// If new patch needed, refer to GeometryTool.
	/// @param surf Surface
	/// @param isExtendU Extend u direction or v direction
	/// @param isFront Extend front or back
	/// @param t The iso parameter
	/// @param length The extend length
	/// @param tol The tolerance
	/// @return New surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Surface> ExtendSurfByLength(const std::shared_ptr<Geom3Surface>& surf, bool isExtendU, bool isFront, double t, double length, double tol = 1e-3);
};
} // namespace AMCAX
