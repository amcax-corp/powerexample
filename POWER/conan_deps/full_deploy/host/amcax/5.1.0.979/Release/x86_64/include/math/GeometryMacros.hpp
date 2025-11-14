/// @file      GeometryMacros.hpp
/// @brief     Geometry macros
/// @details   Geometry macros including curve type, surface type, join type, isoparametric type, continuity type, transformation type, and B spline knot distribution.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
namespace AMCAX
{
/// @brief Type of curve
enum class CurveType
{
	Undefined,
	Line,
	Circle,
	Ellipse,
	Parabola,
	Hyperbola,
	BezierCurve,
	BSplineCurve,
	TrimmedCurve,
	OffsetCurve,
	OtherCurve
};

/// @brief Type of surface
enum class SurfaceType
{
	Undefined,
	Plane,
	Cylinder,
	Cone,
	Sphere,
	Torus,
	SurfaceOfExtrusion,
	SurfaceOfRevolution,
	BezierSurface,
	BSplineSurface,
	TrimmedSurface,
	OffsetSurface,
	OtherSurface
};

/// @brief Type of knot distribution in B splines
enum class BSplineKnotDistribution
{
	NonUniform,
	Uniform,
	QuasiUniform,
	PiecewiseBezier
};

#ifndef DOXYGEN_SKIP
/// @internal
/// @brief Type of multiplicity distribution in B splines
enum class BSplineMultDistribution
{
	NonConstant,
	Constant,
	QuasiConstant
};

/// @internal
/// @brief Type of isoparametric curves
enum class IsoparametricType
{
	IsoU,
	IsoV,
	NoneIso
};
#endif

/// @brief Type of join
enum class JoinType
{
	/// @brief Build arc blend
	Arc,

	/// @brief Build two tangent lines at the end of the edges and intersect the lines
	Intersection
};

/// @brief Type of continuity
enum class ContinuityType
{
	C0,
	G1,
	C1,
	G2,
	C2,
	C3,
	CN
};

/// @brief Status used in local property
enum class LocalPropertyStatus
{
	Undecided,
	Undefined,
	Defined,
	Computed
};
} // namespace AMCAX
