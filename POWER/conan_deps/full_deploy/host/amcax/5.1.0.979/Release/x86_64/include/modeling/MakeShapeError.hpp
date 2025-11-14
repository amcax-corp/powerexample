/// @file      MakeShapeError.hpp
/// @brief     Enumerations used for construction of shapes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Error types in edge construction
enum class EdgeError
{
	/// @brief No error
	EdgeDone,

	/// @brief The projection of point on the curve is failed.
	PointProjectionFailed,

	/// @brief The parameters are not in the parameter range
	ParameterOutOfRange,

	/// @brief The end points of a closed curve are not at the same position
	DifferentPointsOnClosedCurve,

	/// @brief The parameter of a point is infinite with respect to the precision
	PointWithInfiniteParameter,

	/// @brief The distance between the 3D point and the point at the parameter on the curve is greater than the precision
	DifferentsPointAndParameter,

	/// @brief The two points defining a line are coincide
	LineThroughIdenticPoints
};

/// @brief Error types in wire construction
enum class WireError
{
	/// @brief No error
	WireDone,

	/// @brief No initial wire
	EmptyWire,

	/// @brief The added edge is not connected to the wire
	DisconnectedWire,

	/// @brief The wire has singularities
	NonManifoldWire
};

/// @brief Error types in face construction
enum class FaceError
{
	/// @brief No error
	FaceDone,

	/// @brief No initial face
	EmptyFace,

	/// @brief No given surface and the wire is not planar
	NotPlanar,

	/// @brief The parameters are out of range of the surface
	ParametersOutOfRange
};

/// @brief Error types in shell construction
enum class ShellError
{
	/// @brief No error
	ShellDone,

	/// @brief No initial shell
	EmptyShell,
};
} // namespace AMCAX
