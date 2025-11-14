/// @file      TMSplineTool.hpp
/// @brief     Class of TMSpline Tool
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>
#include <common/BoundingBox3.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline Tool
class TMSplineTool
{
public:
	/// @brief Return the vert index in input TMSpline
	/// @param tsp The TMSpline
	/// @param vert  One pointer of vertex
	/// @return The index of vertex, -1 indicates it is not in input TMSpline
	AMCAX_API static int VertIndex(TMSpline* tsp, const TVert* vert);

	/// @brief Return the edge index in input TMSpline
	/// @param tsp The TMSpline
	/// @param edge One pointer of edge
	/// @return The index of edge, -1 indicates it is not in input TMSpline
	AMCAX_API static int EdgeIndex(TMSpline* tsp, const TEdge* edge);

	/// @brief Return the face index in input TMSpline
	/// @param tsp The TMSpline
	/// @param One pointer of face
	/// @return The index of face, -1 indicates it is not in input TMSpline
	AMCAX_API static int FaceIndex(TMSpline* tsp, const TFace* face);

	/// @brief Return the control position of vert in TMSpline
	/// @param tsp The TMSpline
	/// @param vert The index of vertex
	/// @return The position of vertex
	AMCAX_API static Point3 ControlPosition(TMSpline* tsp, int vert);

	/// @brief Return the weight of vert in TMSpline
	/// @param tsp The TMSpline
	/// @param vert The index of vertex
	/// @return The weight of vertex
	AMCAX_API static double Weight(TMSpline* tsp, int vert);

	/// @brief Return the normal of face in TMSpline control net
	/// @param tsp The TMSpline
	/// @param face The index of face
	/// @return a unit vector of face normal
	AMCAX_API static Vector3 ControlFaceNormal(TMSpline* tsp, int face);

	/// @brief Update all normal of the TMSpline control net
	/// @param tsp The TMSpline
	AMCAX_API static void UpdateNormal(TMSpline* tsp);

	/// @brief Reverse all normal of the TMSpline
	/// @param tsp The TMSpline
	AMCAX_API static void ReverseTMSNormal(TMSpline* tsp);

	/// @brief Return the vertices of the face in TMSpline
	/// @param tsp The TMSpline
	/// @param face The index of face
	/// @return The indices of vertices
	AMCAX_API static std::vector<int> FaceVertexIndexs(TMSpline* tsp, int face);

	/// @brief Return the edge of the face in TMSpline
	/// @param tsp The TMSpline
	/// @param face The index of face
	/// @return The indices of edges
	AMCAX_API static std::vector<int> FaceEdgeIndexs(TMSpline* tsp, int face);

	/// @brief Get the vertices of the edge in TMSpline
	/// @param tsp The TMSpline
	/// @param edge The index of edge
	/// @param vfirst The index of edge first vertex
	/// @param vlast The index of edge last vertex
	AMCAX_API static void EdgeVertexIndexs(TMSpline* tsp, int edge, int& vfirst, int& vlast);

	/// @brief Return the faces adjacent to edge in TMSpline
	/// @param tsp The input TMSpline
	/// @param edge The index of edge
	/// @return the indices of faces adjacent to edge
	AMCAX_API static std::vector<int> EdgeFaceIndexs(TMSpline* tsp, int edge);

	/// @brief Compute the Bounding box of TMSpline
	/// @param tsp The TMSpline
	/// @param box The bounding box
	AMCAX_API static void UpdateTMSplineBndBox(TMSpline* tsp, BoundingBox3& box);

	/// @brief Compute a Line form a edge in T-mesh spline control net
	/// @param tsp The TMSpline
	/// @param eId The edge
	/// @param p The result line position
	/// @param dir The result line direction
	AMCAX_API static void TMSControlEdgeToLine(TMSpline* tsp, int eId, Point3& p, Vector3& dir);
};

} // namespace TMS
} // namespace AMCAX
