/// @file      ChamferFilletMacros.hpp
/// @brief     The enum classes used in fillet and chamfer algorithm
/// @details   The enum classes including types of fillet shape, chamfer modes, type of concavity, states of fillet point, error status.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief The type of fillet shapes
enum class FilletShapeType
{
	/// @brief The standard NURBS representation of circles
	Rational,

	/// @brief A NURBS representation of circles where the parameters match those of the circles
	QuasiAngular,

	/// @brief A polynomial approximation of circles
	Polynomial
};

/// @brief Type of chamfer method
enum class ChamferMethod
{
	/// @brief The chamfer is symmetric
	Symmetric,

	/// @brief The chamfer has two distances away from each side of edge
	TwoDist,

	/// @brief The chamfer has a distance from the top and the oblique angle
	DistAngle
};

/// @brief Mode of chamfer
enum class ChamferMode
{
	/// @brief Chamfer with constant distance from spine to one of the two surfaces
	ClassicChamfer,

	/// @brief Symmetric chamfer with constant throat that is the height of isosceles triangle in section
	ConstThroatChamfer,

	/// @brief Chamfer with constant throat: the section of chamfer is a right-angled triangle, the first of two surfaces (where is the top of the chamfer) is virtually moved inside the solid by offset operation, the apex of the section is on the intersection curve between the moved surface and the second surface, right angle is at the top of the chamfer, the length of the leg from apex to top is constant - it is throat
	ConstThroatWithPenetrationChamfer
};

#ifndef DOXYGEN_SKIP

/// @internal
/// @brief Type of concavity
enum class ConcavityType
{
	Concave,
	Convex,
	Tangential,
	FreeBound,
	Other
};

/// @internal
/// @brief The state of extremities of a fillet
enum class FilletState
{
	/// @brief The edge of the fillet has a concave side different than one of the two other edges and identical to the third edge
	OnSame,

	/// @brief The edge of the fillet has a concave side different than the two other edges
	OnDiff,

	/// @brief The three concavities are on the same side of the shape
	AllSame,

	/// @brief Including all the three states, OnSame, OnDiff, and AllSame
	BreakPoint,

	FreeBoundary,
	Closed,
	Tangent
};

#endif

/// @brief Type of error status
enum class ChamferFilletErrorStatus
{
	OK,
	Error,
	WalkingFailure,
	StartsolFailure,
	TwistedSurface
};

/// @brief Type of error status in 2d fillet construction
enum class Fillet2dConstructionError
{
	/// @brief The face is not planar
	NotPlanar,

	/// @brief The face is null
	NoFace,

	/// @brief The two faces used for the initialization are uncompatible
	InitialisationError,

	/// @brief The parameters as distances or angle for chamfer are less or equal to zero
	ParametersError,

	/// @brief The initialization has been successful
	Ready,

	IsDone,

	/// @brief The algorithm could not find a solution
	ComputationError,

	/// @brief The vertex given to locate the fillet or the chamfer is not connected to 2 edges
	ConnexionError,

	/// @brief The two edges connected to the vertex are tangent
	TangencyError,

	/// @brief The first edge is degenerated
	FirstEdgeDegenerated,

	/// @brief The last edge is degenerated
	LastEdgeDegenerated,

	/// @brief The two edges are degenerated
	BothEdgesDegenerated,

	/// @brief One or the two edges connected to the vertex is a fillet or a chamfer; one or the two edges connected to the vertex is not a line or a circle
	NotAuthorized
};
} // namespace AMCAX
