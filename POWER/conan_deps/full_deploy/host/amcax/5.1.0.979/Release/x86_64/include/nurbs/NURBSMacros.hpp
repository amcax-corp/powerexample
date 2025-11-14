/// @file      NURBSMacros.hpp
/// @brief     The basic enum classes used in NURBS algorithm
/// @details   Some useful options used in NURBS algorithm, including the type of constraints, link, etc.
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
/// @internal
/// @brief Type of the curve modifying constraint
enum class NURBSCurveConstraintType
{
	Undefined,
	DN,
	D0ToDN,
	HomoDN
};

/// @internal
/// @brief Type of the surface modifying constraint
enum class NURBSSurfaceConstraintType
{
	Undefined,
	Position,
	Du,
	Dv,
	Normal,
	Duu,
	Duv,
	Dvv,
	MeanCurvature,
	GaussCurvature
};

/// @internal
/// @brief Type of the curve modifying regularization term
enum class NURBSRegularizationTermType
{
	ARAP,
	D1,
	D2,
	D3
};
#endif

/// @brief Type of the surface lofting
/// @details Strict is to build a surface which interpolate the sections;
/// Relax is to build a high deviation and low twist result;
///  Standard is to build a lower deviation result than Relax;
/// Ruled is to build a ruled surface
enum class NURBSLoftSurfaceStype
{
	Standard,
	Strict,
	Relax,
	Ruled
};

/// @brief Type of the lofting algorithm
/// @details Basic is the traditional way of lofting; Sweep is to sweep the profiles along two interpolation curves
enum class NURBSLoftAlgorithm
{
	Basic,
	Sweep
};

/// @brief The sweeping status
enum class NURBSSweepStatus
{
	Undefined,
	Success,

	/// @brief There is no intersection between spine normal plane and the guide curve
	InvalidSpine,

	/// @brief There is no intersection between the profile plane and the spine normal plane
	InvalidSpineBoundary,

	/// @brief Not all the spine normal planes intersect with the guide
	SpineNormalPlaneNotAlwaysIntersectWithGuide,

	/// @brief There is no intersection between te guide and the profile plane
	InvalidGuide,

	/// @brief The guide cannot be projected on the support surface
	InvalidSurface,

	SpineGuidePeriodicIncompatible,

	/// @brief The guide curve is parallel to the pulling direction
	InvalidPullingDirection,

	/// @brief The length relimiter used by LinearSweep is invalid
	InvalidLengthRelimiter,

	/// @brief There is no solution of solving a 3D circle under given constraints including the radius
	InvalidRadius,

	/// @brief There is no solution of solving the section under given constraints including the angle
	InvalidAngle
};

#ifndef DOXYGEN_SKIP
/// @internal
/// @brief The status of multi-sections surface modeling
/// 1. Undefined, the algorithm is not performed
/// 2. Success, the algorithm is succeeded
/// 3. SectionNotMatchContinuityConstraint, the section cannot match support surface continuity constraints
/// 4. GuideNotMatchContinuityConstraint, the guide cannot match support surface continuity constraints
/// 5. SpineNormalPlaneNotAlwaysIntersectWithGuide, the spine normal plane cannot always intersect with the guide
enum class NURBSMultiSectionStatus
{
	Undefined,
	Success,

	/// @brief The section cannot satisfy support surface continuity constraints
	SectionNotMatchContinuityConstraint,

	/// @brief The guide cannot satisfy support surface continuity constraints
	GuideNotMatchContinuityConstraint,

	/// @brief The spine normal plane cannot always intersect with the guide
	SpineNormalPlaneNotAlwaysIntersectWithGuide
};

/// @internal
/// @brief Coupling strategy of multi-sections surface modeling
enum class NURBSMultiSectionCouplingStrategy
{
	/// @brief Strictly obey the rule of the curvilinear abscissa ratio
	Ratio,

	/// @brief Match tangency discontinuity points
	Tangency,

	/// @brief Match tangency discontinuity points and then match the curvature discontinuity points
	TangencyThenCurvature
};
#endif

/// @brief Four length types are supported:
enum class NURBSLinearSweepWithDraftDirectionLengthType
{
	/// @brief The swept surface starts from the curve;
	FromCurve,

	/// @brief The length is computed in sweeping planes (defining 0 is similar as choosing From curve)
	Standard,

	/// @brief the length is computed by intersecting a plane or a surface; a point can be selected: a plane parallel to the draft plane would be computed
	FromTo,

	/// @brief the lengths are defined along the draft direction from an extremum plane; L1 corresponds to the maximum plane in the draft direction, L2 corresponds to the minimum plane in the draft direction
	FromExtremum
};
} // namespace AMCAX
