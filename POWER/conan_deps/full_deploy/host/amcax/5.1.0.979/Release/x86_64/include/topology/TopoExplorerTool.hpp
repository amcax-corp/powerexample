/// @file      TopoExplorerTool.hpp
/// @brief     Class of tool for explorer
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <unordered_set>

#include <common/IndexMap.hpp>
#include <common/IndexSet.hpp>
#include <common/Macros.hpp>
#include <topology/TopologyMacros.hpp>

namespace AMCAX
{
class TopoEdge;
class TopoShape;
class TopoVertex;
class TopoWire;

/// @brief Class of tool for explorer
class TopoExplorerTool
{
public:
	/// @brief Construct a set of sub-shapes of given type
	/// @details The input set is not cleared
	/// @param[in] s The parent shape
	/// @param[in] t The required type
	/// @param[in,out] shapeSet The set of sub-shapes
	AMCAX_API static void MapShapes(const TopoShape& s, ShapeType t, IndexSet<TopoShape>& shapeSet);

	/// @brief Construct a set of all sub-shapes of a parent shape
	/// @details The parent shape itself is also inserted into the set. The input set is not cleared.
	/// @param[in] s The parent shape
	/// @param[in,out] shapeSet The set of sub-shapes
	/// @param[in] cumOri Determine whether computing cumulative orientation
	/// @param[in] cumLoc Determine whether computing cumulative location
	AMCAX_API static void MapShapes(const TopoShape& s, IndexSet<TopoShape>& shapeSet, bool cumOri = true, bool cumLoc = true);

	/// @brief Construct a set of all sub-shapes of a parent shape
	/// @details The parent shape itself is also inserted into the set. The input set is not cleared.
	/// @param[in] s The parent shape
	/// @param[in,out] shapeSet The set of sub-shapes
	/// @param[in] cumOri Determine whether computing cumulative orientation
	/// @param[in] cumLoc Determine whether computing cumulative location
	AMCAX_API static void MapShapes(const TopoShape& s, std::unordered_set<TopoShape>& shapeSet, bool cumOri = true, bool cumLoc = true);

	/// @brief Construct a map from sub-shapes of given type to all the ancestor shapes of given type
	/// @details For example, find a map from all edges in a shape to the list of faces. The input map is not cleared.
	/// @param[in] s The parent shape
	/// @param[in] ts The type of sub-shape
	/// @param[in] ta The type of ancester of sub-shape
	/// @param[in,out] shapeMap The shape map
	AMCAX_API static void MapShapesAndAncestors(const TopoShape& s, ShapeType ts, ShapeType ta, IndexMap<TopoShape, std::list<TopoShape>>& shapeMap);

	/// @brief Construct a map from sub-shapes of given type to all the unique ancestor shapes of given type
	/// @details For example, find a map from all edges in a shape to the list of faces. The input map is not cleared.
	/// @param[in] s The parent shape
	/// @param[in] ts The type of sub-shape
	/// @param[in] ta The type of ancester of sub-shape
	/// @param[in,out] shapeMap The shape map
	/// @param[in] useOrientation Determine whether considering the orientation of ancestor shapes
	AMCAX_API static void MapShapesAndUniqueAncestors(const TopoShape& s, ShapeType ts, ShapeType ta, IndexMap<TopoShape, std::list<TopoShape>>& shapeMap, bool useOrientation = false);

	/// @brief Get the forward vertex of the edge
	/// @param e The edge
	/// @param cumOri Determine whether computing cumulative orientations
	/// @return The forward vertex
	[[nodiscard]] AMCAX_API static TopoVertex FirstVertex(const TopoEdge& e, bool cumOri = false);

	/// @brief Get the reverse vertex of the edge
	/// @param e The edge
	/// @param cumOri Determine whether computing cumulative orientations
	/// @return The reverse vertex
	[[nodiscard]] AMCAX_API static TopoVertex LastVertex(const TopoEdge& e, bool cumOri = false);

	/// @brief Get the two vertices of an edge
	/// @details If the edge has the same vertices, the second vertex will be null
	/// @param[in] e The edge
	/// @param[out] vfirst The first vertex
	/// @param[out] vlast The last vertex
	/// @param[in] cumOri Determine whether computing cumulative orientations
	AMCAX_API static void Vertices(const TopoEdge& e, TopoVertex& vfirst, TopoVertex& vlast, bool cumOri = false);

	/// @brief Get the start and end vertices of a wire
	/// @details If the wire is closed, two vertices will be the same
	/// @param[in] w The wire
	/// @param[out] vfirst The first vertex
	/// @param[out] vlast The last vertex
	AMCAX_API static void Vertices(const TopoWire& w, TopoVertex& vfirst, TopoVertex& vlast);

	/// @brief Find the common vertex of two edges
	/// @param[in] e1 The first edge
	/// @param[in] e2 The second edge
	/// @param[out] v The common vertex
	/// @return True if the edges share the same vertex
	AMCAX_API static bool CommonVertex(const TopoEdge& e1, const TopoEdge& e2, TopoVertex& v);
};
} // namespace AMCAX
