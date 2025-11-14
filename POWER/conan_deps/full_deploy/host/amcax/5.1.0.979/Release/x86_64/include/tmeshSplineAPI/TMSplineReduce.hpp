/// @file      TMSplineReduce.hpp
/// @brief     Class of TMSpline API for delete and remove element
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for delete and remove element
///		   Deleting an element will leave a hole, while removing an element will fill the removed part
class TMSplineReduce
{
public:
	/// @brief return true if it can delete faces in a TMSpline
	/// @param tsp The TMSpline
	/// @param flist The faces that need to be deleted
	AMCAX_API bool CanDeleteFaces(TMSpline* tsp, const std::vector<int>& flist);

	/// @brief return true if it can remove vertices in a TMSpline
	/// @param tsp The TMSpline
	/// @param vlist The vertices that need to be remove
	AMCAX_API bool CanRemoveVertices(TMSpline* tsp, const std::vector<int>& vlist);

	/// @brief return true if it can remove edges in a TMSpline
	/// @param tsp The TMSpline
	/// @param elist The edges that need to be remove
	AMCAX_API bool CanRemoveEdges(TMSpline* tsp, const std::vector<int>& elist);

	/// @brief Delete faces in a TMSpline
	/// @param tsp The TMSpline
	/// @param flist The faces that need to be deleted
	AMCAX_API void DeleteFaces(TMSpline* tsp, const std::vector<int>& flist);

	/// @brief Remove vertices in a TMSpline, it will also remove edges which connect to vertices
	/// @param tsp The TMSpline
	/// @param vlist The vertices that need to be remove
	AMCAX_API void RemoveVertices(TMSpline* tsp, const std::vector<int>& vlist);

	/// @brief Remove edges in a TMSpline
	/// @param tsp The TMSpline
	/// @param elist The edges that need to be remove
	AMCAX_API void RemoveEdges(TMSpline* tsp, const std::vector<int>& elist);

	/// @brief Delete all isolated vertices in a TMSpline
	/// @param tsp The TMSpline
	AMCAX_API void DeleteIsolatedVertices(TMSpline* tsp);

private:
	void ComputeEdgeConnectedComponents(TMSpline* tsp, const std::vector<TEdge*>& edge_list,
		std::vector<std::vector<TEdge*>>& edge_list_part);

	void ComputeEdgeFaceList(TMSpline* tsp, const std::vector<std::vector<TEdge*>>& edge_list,
		std::vector<std::vector<TFace*>>& face_list, std::vector<bool>& is_need_fillhole);

	void UpdateFaceEdgeList(TMSpline* tsp, const std::vector<std::vector<TFace*>>& face_list,
		std::vector<std::vector<TEdge*>>& edge_list);

	TLink* GetFaceHoleInformation(TMSpline* tsp, std::vector<TFace*>& face_list);

	TFace* InsertWithBoundaryType(TMSpline* tsp, TLink* he);

	bool IsFaceListSingalConnected(TMSpline* tsp, const std::vector<TFace*>& f_list);
};

} // namespace TMS
} // namespace AMCAX
