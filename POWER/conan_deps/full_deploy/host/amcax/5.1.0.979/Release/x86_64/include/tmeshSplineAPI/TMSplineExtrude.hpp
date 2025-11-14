/// @file      TMSplineExtrude.hpp
/// @brief     Class of TMSpline API for extrude method
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for extrude method
/// only change the topology, the new result is coincide the old result, and use TMSplineTransform to move the new result.
class TMSplineExtrude
{
public:
	/// @brief check if it can extrude input edges in TMSpline
	/// @param tsp a TMSpline
	/// @param edges indices of the edge to be extrude
	/// @return true if the edges can extrude
	AMCAX_API bool CanExtrudeEdges(TMSpline* tsp, const std::vector<int>& edges);

	/// @brief check if it can extrude input faces in TMSpline
	/// @param tsp a TMSpline
	/// @param faces indices of the face to be extrude
	/// @return true if the faces can extrude
	AMCAX_API bool CanExtrudeFaces(TMSpline* tsp, const std::vector<int>& faces);

	/// @brief extrude the edges in TMSpline
	/// @param tsp a TMSpline
	/// @param edges indices of the edges to be extrude
	/// @param edgesNew indices of the edges after extrude
	/// @return true if the process successfed
	AMCAX_API bool ExtrudeEdges(TMSpline* tsp, const std::vector<int>& edges, std::vector<int>& edgesNew);

	/// @brief extrude the faces in TMSpline
	/// @param tsp a TMSpline
	/// @param faces indices of the faces to be extrude
	/// @param facesNew indices of the faces after extrude
	/// @return true if the process successfed
	AMCAX_API bool ExtrudeFaces(TMSpline* tsp, const std::vector<int>& faces, std::vector<int>& facesNew);

private:
	bool ExtrudeEdges(TMSpline* tsp, const std::vector<TEdge*>& edges_list, std::vector<TEdge*>& edges_new);

	bool ExtrudeFaces(TMSpline* tsp, const std::vector<TFace*>& faces, std::vector<TFace*>& faces_new);

	bool ExtrudeFacesMultPatch(TMSpline* tsp, const std::vector<TFace*>& faces, std::vector<TFace*>& faces_new);

	bool ExtrudeSingleEdge(TMSpline* tsp, TEdge* edge, TEdge*& edge_new);

	bool ExtrudeConnectedEdge(TMSpline* tsp, const std::vector<TLink*>& he_list, std::vector<TEdge*>& edge_list_new);

	bool ExtrudeConnectedEdge(TMSpline* tsp, const std::vector<TEdge*>& edge_list, std::vector<TEdge*>& edge_list_new);

	void FacesRepeatEdgeTime(TMSpline* tsp, const std::vector<TFace*>& faces, std::vector<int>& face_edges_time);

	bool IsTowFaceEdgeConnected(TMSpline* tsp, TFace* f1, TFace* f2);
};

} // namespace TMS
} // namespace AMCAX
