/// @file      TMSplineSplit.hpp
/// @brief     Class of TMSpline API for split spline
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for split spline
class TMSplineSplit
{
public:
	/// @brief return true if faces in TMSpline can be 1-4 split
	/// @param tsp The TMSpline
	/// @param flist The faces that need to be split
	AMCAX_API bool CanSplitFacesCross(TMSpline* tsp, const std::vector<int>& flist);

	/// @brief return true if a loop faces generated from edge in TMSpline can be splited
	/// @param tsp The TMSpline
	/// @param eId The input edge
	/// @param t The ratio of the distance between the starting point and the dividing point of an edge to the length of the edge
	AMCAX_API bool CanSplitFaceLoop(TMSpline* tsp, size_t eId, double t = 0.5);

	/// @brief return true if can split faces by sequentially cross the point of the edges in TMSpline
	/// @param tsp The TMSpline
	/// @param elist The edges that need to be sequentially cross
	/// @param newControl The point in each edges
	AMCAX_API bool CanSplitFaceWithEdge(TMSpline* tsp, const std::vector<int>& elist, const std::vector<Point3>& newControl);

	/// @brief return true if can split faces by sequentially cross vertices in TMSpline
	/// @param tsp The TMSpline
	/// @param vlist The vertices that need to be sequentially cross
	AMCAX_API bool CanSplitFaceWithVertex(TMSpline* tsp, std::vector<int>& vlist);

	/// @brief Split faces by 1-4 split method
	/// @param tsp The TMSpline
	/// @param flist The faces that need to be split
	AMCAX_API void SplitFacesCross(TMSpline* tsp, std::vector<int>& flist);

	/// @brief Split a loop faces generated from edge
	/// @param tsp The TMSpline
	/// @param eId The input edge
	/// @param t The ratio of the distance between the starting point and the dividing point of an edge to the length of the edge
	AMCAX_API void SplitFaceLoop(TMSpline* tsp, size_t eId, double t = 0.5);

	/// @brief Split faces by sequentially cross the point of the edges in TMSpline
	/// @param tsp The TMSpline
	/// @param elist The edges that need to be sequentially cross
	/// @param newControl The point in each edges
	AMCAX_API void SplitFaceWithEdge(TMSpline* tsp, std::vector<int>& elist, const std::vector<Point3>& newControl);

	/// @brief Split faces by sequentially cross vertices in TMSpline
	/// @param tsp The TMSpline
	/// @param vlist The vertices that need to be sequentially cross
	AMCAX_API void SplitFaceWithVertex(TMSpline* tsp, std::vector<int>& vlist);

	/// @brief A practical tool for repairing segmented splines, will be removed in future versions
	/// @param tsp The TMSpline
	AMCAX_API void FixSplitedShape(TMSpline* tsp);

private:
	void SplitFaceCross(TMSpline* tsp, TFace* face, const Point3& new_control);

	void FindFaceLoopEdge(TMSpline* tsp, TLink* he0, double t, std::vector<TFace*>& loop_faces,
		std::vector<TParam>& loop_face_param, std::vector<TLink*>& loop_face_Link, std::vector<Point3>& loop_face_control);

	void FindFaceLoopEdgeOneFace(TMSpline* tsp, TFace*& face, TLink*& he_curr, double& t_curr,
		std::vector<TCFace*>& loop_faces, std::vector<TParam>& loop_face_param,
		std::vector<TCLink*>& loop_face_Link, std::vector<Point3>& loop_face_control);

	void SplitFaceWithEdges(TMSpline* tsp, std::vector<TEdge*>& edges, std::vector<int>& edge_type, const std::vector<Point3>& new_control);

	void SplitFaceWithVertex(TMSpline* tsp, std::vector<TVert*>& vertices);

	bool IsTwoEdgeInFace(TMSpline* tsp, TEdge* e0, TEdge* e1);
	bool IsTwoEdgeHalfedgeConnected(TMSpline* tsp, TEdge* e0, TEdge* e1);

	TFace* GetFaceByTwoVertex(TMSpline* mesh, TVert* vb, TVert* ve);
};

} // namespace TMS
} // namespace AMCAX
