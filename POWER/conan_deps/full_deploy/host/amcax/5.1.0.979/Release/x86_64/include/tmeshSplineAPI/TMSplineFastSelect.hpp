/// @file      TMSplineFastSelect.hpp
/// @brief     Class of TMSpline useful select Tool
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of TMSpline useful select Tool
class TMSplineFastSelect
{
public:
	/// @brief find the vector of boundary edges where the input edge is located
	/// @param tsp a TMSpline
	/// @param inputEdgeId input edge id
	/// @param boundaryEdgeId indices of the boundary edges
	AMCAX_API void FindBoundaryEdge(const TMSpline* tsp, size_t inputEdgeId, std::vector<int>& boundaryEdgeId);

	/// @brief find a loop of edges that are connected in a line end-to-end and contains input edges.
	/// @param tsp TMSpline
	/// @param inputEdgeId input edge id
	/// @param loopEdgeId indices of the edges in edge loop
	AMCAX_API void FindLoopEdge(const TMSpline* tsp, size_t inputEdgeId, std::vector<int>& loopEdgeId);

private:
	void FindBoundaryEdge(const TMSpline* tsp, const TEdge* edge, std::vector<int>& boundaryEdgeid);

	void FindLoopEdge(const TMSpline* tsp, TEdge* edge, std::vector<int>& loopEdgeId);

	bool IsLoopVertex(const TMSpline* tsp, TVert* v, TLink* he);

	void PushLoopEdge(const TMSpline* tsp, TLink*& heCurr, std::vector<int>& loopEdgeId, TLink* heBegin);
};

} // namespace TMS
} // namespace AMCAX
