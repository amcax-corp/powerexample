/// @file      VertexEditor.hpp
/// @brief     Class of Vertex Editor
/// @details   Operations related to Vertex
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/IndexSet.hpp>
#include <common/PointT.hpp>
#include <iostream>
#include <shapeEdit/EditShape.hpp>
#include <topology/TopoVertex.hpp>
#include <vector>

namespace AMCAX {

namespace GeomE {
/// @brief Class of Vertex Editor
class AMCAX_CLASS_API VertexEditor : public EditShape
{
public:
	/// @brief Default constructor
	AMCAX_API VertexEditor();

	/// @brief Sew a set of vertices into a single vertex
	/// @details Use the average point of the sewn vertices as the point of the
	/// sewing vertex
	/// @param[in,out] shape The shape
	/// @param[in] vertexvec The set of vertices to be sewn
	/// @return The sewing vertex
	AMCAX_API TopoVertex SewVertices(AMCAX::TopoShape          &shape,
	                                 const IndexSet<TopoShape> &vertexvec);

	/// @brief Sew two vertices into a single vertex
	/// @details Use v2 as the sewing vertex
	/// @param[in,out] shape The shape
	/// @param[in] v1 The first vertex
	/// @param[in,out] v2 The second vertex
	AMCAX_API void SewVertices(AMCAX::TopoShape        &shape,
	                           const AMCAX::TopoVertex &v1,
	                           AMCAX::TopoVertex       &v2);

	/// @brief Automatically sew the vertices that are within the tolerance in the
	/// shape
	/// @param[in,out] shape The shape
	/// @param[in] tol The tolerance
	AMCAX_API void AutoSewVertices(AMCAX::TopoShape &shape, double tol);

	/// @brief Delete vertex on the edge
	/// @param[in,out] shape The shape
	/// @param[in] vertex The vertex
	AMCAX_API void RemoveVertex(TopoShape &shape, const TopoVertex &vertex);

	/// @brief Release vertex onto each edge
	/// @param[in,out] shape The shape
	/// @param[in] vertex The vertex
	AMCAX_API void ReleaseVertex(TopoShape &shape, const TopoVertex &vertex);

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
};

} // namespace GeomE

} // namespace AMCAX