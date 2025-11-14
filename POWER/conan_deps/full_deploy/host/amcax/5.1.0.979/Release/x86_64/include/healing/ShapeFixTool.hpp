/// @file      ShapeFixTool.hpp
/// @brief     Some useful tool for fixing shapes
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <topology/TopoEdge.hpp>

namespace AMCAX
{
class TopoFace;
class TopoWire;
class Geom2Curve;

/// @brief Some useful tool for fixing shapes
class ShapeFixTool
{
public:
	/// @brief Make edge to same Parameter(i.e. All curves of edge correspond one-to-one with parameters)
	/// @param edge The edge
	/// @return True if the edge is fix to same parameter;
	AMCAX_API static bool FixEdgeSameParameter(const TopoEdge& edge);

	/// @brief Build a 3d curve if the edge has no 3d curve
	/// @param edge The edge
	/// @return True if the 3d curve is added
	AMCAX_API static bool FixEdgeAddCurve(const TopoEdge& edge);

	/// @brief Build pcurves for the edge if the edge has missing pcurves
	/// @param edge The edge
	/// @param face The face where the pcurves lies
	/// @param isSeam If the edge is a seam
	/// @param prec The precision tolerance
	/// @return True if the pcurves are added
	AMCAX_API static bool FixEdgeAddPCurve(const TopoEdge& edge, const TopoFace& face, bool isSeam, double prec = 0.0);

	/// @brief Connect wire edges and make adjacent edges share one vertex
	/// @param wire The wire
	/// @param prec The precision of determining whether two edges are connected, if this value < 0, use the default value Precision::Confusion()
	/// @return Connected wire
	[[nodiscard]] AMCAX_API static TopoWire FixWireConnected(const TopoWire& wire, double prec = -1.0);

	/// @brief Connect input edges to a wire and make adjacent edges share one vertex
	/// @param edges Vector of interconnected edges
	/// @param closedMode Identify whether input edges form a closed wire
	/// @param prec The precision of determining whether two edges are connected, if this value < 0, use the default value Precision::Confusion()
	/// @return Connected wire
	[[nodiscard]] AMCAX_API static TopoWire FixWireConnected(const std::vector<TopoEdge>& edges, bool closedMode, double prec = -1.0);

	/// @brief Try to repair the shape to a valid shape
	/// @param shape Input shape
	/// @param prec The global precision used when the algorithm needs to check the precision
	/// @param maxTol The global max tolerance used when the algorithm needs to check the tolerance
	/// @return Fixed Shape
	[[nodiscard]] AMCAX_API static TopoShape FixShape(const TopoShape& shape, double prec, double maxTol);

	/// @brief Transform and single direction scaling a 2d curve
	/// @param[in] inputCurve input 2d curve
	/// @param[in] trans The Transformation
	/// @param[in] uFact The scale in u direction
	/// @param[in,out] firstParam The curve first param
	/// @param[in,out] lastParam The curve last param
	/// @return Transformed 2d curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom2Curve> FixTransformPCurve(const std::shared_ptr<Geom2Curve>& inputCurve, const Transformation2& trans, double uFact, double& firstParam, double& lastParam);

	/// @brief Try to unify faces and edges of the shape which lie on the same geometry.
	/// @param shape Input shape
	/// @param isUnifyEdges The flag of whether to unify all possible edges
	/// @param isUnifyFaces The flag of whether to unify all possible faces
	/// @param isConcatBsplines The flag of whether to attempt to merge C1 continuous spline edges with common vertices to one edge.
	/// @return Unified shape
	[[nodiscard]] AMCAX_API static TopoShape UpgradeUnifySameDomain(const TopoShape& shape, bool isUnifyEdges = true, bool isUnifyFaces = true, bool isConcatBsplines = false);
};
} // namespace AMCAX
