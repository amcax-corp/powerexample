/// @file      TMSplineWeld.hpp
/// @brief     Class of TMSpline API for weld edges
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for weld edges
class TMSplineWeld
{
public:
	/// @brief return true if two edge in a TMSpline can be weld
	/// @param tsp The TMSpline
	/// @param e1 The first edge
	/// @param e2 The second edge
	AMCAX_API bool CanWeldTwoEdge(TMSpline* tsp, int e1, int e2);

	/// @brief Weld two edges in a TMSpline to one inner edge
	/// @param tsp The TMSpline
	/// @param e1 The first edge
	/// @param e2 The second edge
	AMCAX_API bool WeldTwoEdge(TMSpline* tsp, int e1, int e2);

	/// @brief return true if edges in a TMSpline can be weld
	/// @param tsp The TMSpline
	/// @param elist The edges that need to be weld
	AMCAX_API bool CanWeldEdges(TMSpline* tsp, const std::vector<int>& elist);

	/// @brief find all edges in a TMSpline by input edges with tolerance and Weld them to inner edges
	/// @param tsp The TMSpline
	/// @param elist The edges that need to be weld
	/// @param tolerance The tolerance used to find additional edges
	/// @return true if process succeeded
	AMCAX_API bool WeldEdges(TMSpline* tsp, const std::vector<int>& elist, double tolerance = 0.01);

	/// @brief filter input edges and remove edges which can not be weld, use it when CanWeldEdges return false;
	/// @param tsp The TMSpline
	/// @param elist The edges that need to be checked
	AMCAX_API bool FilterVoidWeldEdges(TMSpline* tsp, std::vector<int>& elist);

private:
	void FindEdgePairWeldEdge(TMSpline* tsp, std::vector<TEdge*>& edges, std::vector<TEdge*>& edges_pair, double tolerance);
};

} // namespace TMS
} // namespace AMCAX
