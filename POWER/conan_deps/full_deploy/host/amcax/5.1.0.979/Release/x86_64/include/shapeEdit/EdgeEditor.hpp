/// @file      EdgeEditor.hpp
/// @brief     Class of Edge Editor
/// @details   Operations related to Edge
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/IndexMap.hpp>
#include <common/IndexSet.hpp>
#include <common/PointT.hpp>
#include <iostream>
#include <shapeEdit/EditShape.hpp>
#include <topology/TopoEdge.hpp>
#include <vector>

namespace AMCAX {
namespace GeomE {
/// @brief Class of Edge Editor
class AMCAX_CLASS_API EdgeEditor : public EditShape
{
public:
	/// @brief Default constructor
	AMCAX_API EdgeEditor();

	/// @brief Insert vertices on the edge based on the parameters
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to insert vertices
	/// @param[in] ts The parameters
	AMCAX_API void TrimEdgeWithParameter(TopoShape &shape, const TopoEdge &edge,
	                                     const std::vector<double> &ts);

	/// @brief Project points onto an edge
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to project points
	/// @param[in] points The points to be projected
	AMCAX_API void TrimEdgeWithPoint(TopoShape &shape, const TopoEdge &edge,
	                                 const std::vector<Point3> &points);

	/// @brief Insert vertices on the edge based on the given lengths
	/// @details If the orientation of the edge is forward, then start
	/// from the starting point of the curve; if the orientation of the edge is
	/// reversed, then start from the end point of the curve
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to insert vertices
	/// @param[in] lens The given lengths
	AMCAX_API void TrimEdgeWithLength(TopoShape &shape, const TopoEdge &edge,
	                                  const std::vector<double> &lens);

	/// @brief Insert vertices on the edge based on the given ratios
	/// @details If the orientation of the edge is forward, then start
	/// from the starting point of the curve; if the orientation of the edge is
	/// reversed, then start from the end point of the curve
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to insert vertices
	/// @param[in] ratios The given ratios
	AMCAX_API void TrimEdgeWithRatio(TopoShape &shape, const TopoEdge &edge,
	                                 const std::vector<double> &ratios);

	/// @brief Insert a vertex on the edge based on the parameters
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to insert a vertex
	/// @param[in] t The parameters
	AMCAX_API void TrimEdgeWithParameter(TopoShape &shape, const TopoEdge &edge,
	                                     const double t);

	/// @brief Project a point onto an edge
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to project a point
	/// @param[in] point The point to be projected
	AMCAX_API void TrimEdgeWithPoint(TopoShape &shape, const TopoEdge &edge,
	                                 const Point3 &point);

	/// @brief Insert a vertex on the edge based on the given length
	/// @details If the orientation of the edge is forward, then start
	/// from the starting point of the curve; if the orientation of the edge is
	/// reversed, then start from the end point of the curve
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to insert a vertex
	/// @param[in] len The given length
	AMCAX_API void TrimEdgeWithLength(TopoShape &shape, const TopoEdge &edge,
	                                  const double len);

	/// @brief Insert a vertex on the edge based on the given ratio
	/// @details If the orientation of the edge is forward, then start
	/// from the starting point of the curve; if the orientation of the edge is
	/// reversed, then start from the end point of the curve
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge to insert a vertex
	/// @param[in] ratio The given ratio
	AMCAX_API void TrimEdgeWithRatio(TopoShape &shape, const TopoEdge &edge,
	                                 const double ratio);

	/// @brief Resample the curve of an edge and update it
	/// @param[in,out] shape The shape
	/// @param[in] edge The resampled edge
	/// @return The new edge
	AMCAX_API TopoEdge RebuildAndUpdateEdge(TopoShape      &shape,
	                                        const TopoEdge &edge);

	/// @brief Join edges into one edge
	/// @param[in,out] shape The shape
	/// @param[in] edges The edges to be joined
	/// @return The joined edge
	AMCAX_API TopoEdge JoinEdgesAndUpdate(AMCAX::TopoShape          &shape,
	                                      const IndexSet<TopoShape> &edges);

	/// @brief Join edges into one edge
	/// @param[in] edges The edges to be joined
	/// @return The joined edge
	AMCAX_API TopoEdge JoinEdges(const IndexSet<TopoShape> &edges);

	/// @brief Sew two edges with nearby vertices, using the second edge as the
	/// resulting edge
	/// @details The distances between the corresponding vertices of
	/// the two edges should be within the given tolerance. If setting tolerance
	/// as 0.0, only sew two edges with common vertices
	/// @param[in,out] shape The shape
	/// @param[in] edge1 The first edge
	/// @param[in,out] edge2 The second edge
	/// @param[in] tol The given tolerance
	AMCAX_API void SewEdges(AMCAX::TopoShape &shape, const AMCAX::TopoEdge &edge1,
	                        AMCAX::TopoEdge &edge2, double tol);

	/// @brief Automatically sew all free edges of the shape to the edges within
	/// the given tolerance
	/// @param[in,out] shape The shape
	/// @param[in] tol The given tolerance
	AMCAX_API void AutoSewFreeEdges(AMCAX::TopoShape &shape, double tol);

	/// @brief Automatically sew all edges of the shape to the edges within the
	/// given tolerance
	/// @param[in,out] shape The shape
	/// @param[in] tol The given tolerance
	AMCAX_API void AutoSewEdges(AMCAX::TopoShape &shape, double tol);

	/// @brief Release the common edge of several faces to their respective faces
	/// @param[in,out] shape The shape
	/// @param[in] edge The common edge to be released
	AMCAX_API void ReleaseEdge(AMCAX::TopoShape      &shape,
	                           const AMCAX::TopoEdge &edge);

	/// @brief Compute the shape modified from a given shape s
	/// @details If any, the list will contain only those splits of the given
	/// shape
	/// @param[in] s The given shape
	/// @return The list of modified shapes
	AMCAX_API const std::list<TopoShape> &Modified(const TopoShape &s) override;

	/// @brief Compute the shape generated from a given shape s
	/// @details Only edges and faces could have generated shapes, i.e. edges
	/// generate new vertices, and faces generate new edges and vertices
	/// @param[in] s The given shape
	/// @return The list of generated shapes
	AMCAX_API const std::list<TopoShape> &Generated(const TopoShape &s) override;

	/// @brief Check if the shape s has been deleted during the operation
	/// @param[in] s The given shape
	/// @return Whether the shape is deleted
	AMCAX_API bool IsDeleted(const TopoShape &s) override;

private:
	static void SewEdgesWithCommonVertex(AMCAX::TopoShape      &shape,
	                                     const AMCAX::TopoEdge &edge1,
	                                     const AMCAX::TopoEdge &edge2);

	bool
	PreSewEdges(AMCAX::TopoShape &shape, const AMCAX::TopoEdge &edge1,
	            AMCAX::TopoEdge &edge2, double tol,
	            const IndexMap<TopoShape, std::list<TopoShape>> &mapedgetoface);

	void
	SewTwoEdges(AMCAX::TopoShape &shape, const AMCAX::TopoEdge &edge1,
	            AMCAX::TopoEdge &edge2, double tol,
	            const IndexMap<TopoShape, std::list<TopoShape>> &mapedgetoface);
};

} // namespace GeomE

} // namespace AMCAX