/// @file      TopologyMacros.hpp
/// @brief     Enumerations on topology, including type of orientation, type of shape, type of state, type of point representation, and type of curve representation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once

namespace AMCAX
{
/// @brief Type of orientations
enum class OrientationType
{
	Forward,
	Reversed,
	Internal,
	External
};

/// @brief Type of shape
enum class ShapeType
{
	Shape,
	Compound,
	CompSolid,
	Solid,
	Shell,
	Face,
	Wire,
	Edge,
	Vertex
};

/// @brief Type of relative position state
enum class StateType
{
	In,
	Out,
	On,
	Unknown
};

#ifndef DOXYGEN_SKIP
/// @internal
/// @brief Type of point representation
enum class PointRepType
{
	Undefined,
	PointOnCurve,
	PointOnCurveOnSurface,
	PointOnSurface
};

/// @internal
/// @brief Type of curve representation
enum class CurveRepType
{
	Undefined,
	Curve3D,
	CurveOnSurface,
	CurveOnClosedSurface,
	CurveOn2Surfaces,
	Polygon3D,
	PolygonOnTriangularMesh,
	PolygonOnClosedTriangularMesh,
	PolygonOnSurface,
	PolygonOnClosedSurface
};
#endif
} // namespace AMCAX
