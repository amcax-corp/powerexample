/// @file      TMSplineSampleChamfer.hpp
/// @brief     Class of TMSpline API for Sample Chamfer
/// @details   Only supports the simplest chamfering function
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for Sample Chamfer
class TMSplineSampleChamfer
{
public:
	/// @brief Build chamfers with the same scale to both sides of the edge
	/// @param scale The ratio of the distance of the chamfer to the length of the edge, must in (0,1)
	AMCAX_API explicit TMSplineSampleChamfer(double scale);

	/// @brief return true if the edges in TMSpline can be chemferd
	/// @param tsp The TMSpline
	/// @param elist The edges used to build chamfers
	AMCAX_API bool CanEdgesSampleChamfer(TMSpline* tsp, const std::vector<int>& elist);

	/// @brief Perform the chamfer algorithm with edges in TMSpline
	/// @param tsp The TMSpline
	/// @param elist The edges used to build chamfers
	/// @return true if process succeeded
	AMCAX_API bool SampleChamfer(TMSpline* tsp, const std::vector<int>& elist);

private:
	bool ReorderEdgeList(TMSpline* mesh, std::vector<TEdge*>& edge_list, std::vector<TLink*>& he_list);

	bool BevelConnectedEdges(TMSpline* mesh, std::vector<TEdge*> edge_list, std::vector<TLink*> he_list,
		bool is_keep_sharp_edge);

	bool BevelRingEdges(TMSpline* mesh, std::vector<TEdge*> edge_list, std::vector<TLink*> he_list,
		bool is_keep_sharp_edge);

	bool CheckEdgeListVertDegree(std::vector<TEdge*> edge_list);

	// set the information with begin vertex, only for the connectedEdges;
	bool SetBevelBothEndPoint(TMSpline* tsp, TVert* v, TLink* he_prev, TLink* he_next, std::vector<TCLink*>& fhe_list);

	void FindVertexNeighborPrev(std::vector<Point3>& v_neighbor, TLink* he_begin, TLink* he_end);

	void FindVertexNeighborNext(std::vector<Point3>& v_neighbor, TLink* he_begin, TLink* he_end);

	void GetEdgeVertexDirection(std::vector<Point3>& v_neighbor, std::vector<Vector3>& v_direction,
		const Vector3& v_direction_begin, const Vector3& v_direction_end, const Point3& vp);

	void RepairVertexDirection(const size_t& vert_num, std::vector<bool>& v_type0, std::vector<Vector3>& v_direction0,
		std::vector<bool>& v_type1, std::vector<Vector3>& v_direction1);

	void AddFaceUsingTwoVector(TMSpline* mesh, std::vector<TCVert*>& v_list0, std::vector<TCVert*>& v_list1,
		std::vector<double>& edge_length, double& edge_length_parallel);

	void AddFaceBothEnd(TMSpline* tsp, std::vector<TLink*>& he_list);

	Point3 ComputerNewPosition(const Point3&, const Point3& p0, const Point3& p1, size_t segment, size_t i);

	Point3 ComputerLinePosition(const Point3& p0, const Point3& p1, size_t segment, size_t i);

private:
	size_t segment_num_;
	double scale_;
};

} // namespace TMS
} // namespace AMCAX
