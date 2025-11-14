/// @file      TMSplineBridgeEdge.hpp
/// @brief     Class of TMSpline API for bridge edge
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of TMSpline API for bridge edge
class TMSplineBridgeEdge
{
public:
	/// @brief return true if it can bridge two edge in TMSpline
	/// @param tsp the TMSpline
	/// @param e1index the first edge
	/// @param e2index the second edge
	AMCAX_API bool CanBridgeEdge(TMSpline* tsp, int e1index, int e2index);

	/// @brief Bridge two edge and creat one face in TMSpline  
	/// @param tsp The TMSpline
	/// @param e1index the first edge
	/// @param e2index the second edge
	/// @return true if the process is succeed
	AMCAX_API bool BridgeEdge(TMSpline* tsp, int e1index, int e2index);

private:
	bool BridgeEdgesImp(TMSpline* tsp, const std::vector<size_t>& e1_index_list, const std::vector<size_t>& e2_index_list,
		size_t v1_index, size_t v2_index, bool direction1, bool direction2);

	bool BridgeEdgesImp(TMSpline* tsp, std::vector<TEdge*>& e1_list, std::vector<TEdge*>& e2_list,
		TVert* v1_index, TVert* v2_index, bool direction1, bool direction2);

	void SortBridgeEdgesRingLink(std::vector<TCLink*>& he_list, TVert* v, bool direction);

	bool ReorderEdgeList(TMSpline* mesh, std::vector<TEdge*>& edge_list, std::vector<TLink*>& he_list);
};

} // namespace TMS
} // namespace AMCAX
