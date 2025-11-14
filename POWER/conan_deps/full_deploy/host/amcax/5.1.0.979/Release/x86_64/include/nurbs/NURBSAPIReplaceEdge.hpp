/// @file      NURBSAPIReplaceEdge.hpp
/// @brief     The class of face boundary edge replacing
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <topology/TopoEdge.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
class Geom3BSplineCurve;

/// @brief Class of replacing edges on face with another curve
/// @details This class computes the result face with given edges replaced with new geometry
class NURBSAPIReplaceEdge
{
public:
	/// @brief Replace edges on face with a line
	/// @param face Face
	/// @param edges Edges to be replaced
	/// @return The new face
	[[nodiscard]] AMCAX_API static TopoFace ReplaceEdgeWithLine(const TopoFace& face, const std::vector<TopoEdge>& edges);

	/// @brief Replace edges on face with a curve
	/// @param face Face
	/// @param edges Edges to be replaced
	/// @param curve The curve whose end points are required to be at the endpoints of the edges.
	/// @return The new face
	[[nodiscard]] AMCAX_API static TopoFace ReplaceEdgeWithCurve(const TopoFace& face, const std::vector<TopoEdge>& edges, const std::shared_ptr<Geom3BSplineCurve>& curve);
};
} // namespace AMCAX
