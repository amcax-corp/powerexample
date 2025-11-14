/// @file      FaceEditor.hpp
/// @brief     Class of Face Editor
/// @details   Operations related to Face
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/IndexSet.hpp>
#include <common/PointT.hpp>
#include <common/Precision.hpp>
#include <iostream>
#include <map>
#include <shapeEdit/EditShape.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoVertex.hpp>
#include <vector>

namespace AMCAX {
class Plane;

namespace GeomE {
/// @brief Class of Face Editor
class AMCAX_CLASS_API FaceEditor : public EditShape
{
public:
	/// @brief Default constructor
	AMCAX_API FaceEditor();

	/// @brief Remove a face from the shape
	/// @param[in,out] shape The shape
	/// @param[in] face The face to be removed
	AMCAX_API void DeleteFace(AMCAX::TopoShape      &shape,
	                          const AMCAX::TopoFace &face);

	/// @brief Parametrically cut the given face using the specified pair of
	/// vertices
	/// @param[in,out] shape The shape
	/// @param[in] face The face to be cut
	/// @param[in] vertex1 The first vertex
	/// @param[in] vertex2 The last vertex
	AMCAX_API void ParameterFaceCut(AMCAX::TopoShape        &shape,
	                                const AMCAX::TopoFace   &face,
	                                const AMCAX::TopoVertex &vertex1,
	                                const AMCAX::TopoVertex &vertex2);

	/// @brief Reverse the orientation of a face
	/// @param[in,out] shape The shape
	/// @param[in] face The face to be reversed
	AMCAX_API void ReverseOrientation(AMCAX::TopoShape      &shape,
	                                  const AMCAX::TopoFace &face);

	/// @brief Project edges onto a face
	/// @param[in,out] shape The shape
	/// @param[in] edges The edges
	/// @param[in, out] face The face
	/// @param[out] replaceshape The shape of the face after projection
	AMCAX_API void EdgesProjectFace(TopoShape                 &shape,
	                                const IndexSet<TopoShape> &edges,
	                                TopoFace &face, TopoShape &replaceshape);

	/// @brief Fill the holes formed by free boundaries
	/// @param[in,out] shape The shape
	/// @param[in] freeboundaries Free boundaries that form holes
	AMCAX_API void FillHole(TopoShape                 &shape,
	                        const IndexSet<TopoShape> &freeboundaries);

	/// @brief Project vertices onto a surface
	/// @param[in,out] shape The shape
	/// @param[in] vertices The vertices
	/// @param[in, out] face The face
	/// @param[out] replaceshape The shape of the face after the projection
	AMCAX_API void VerticesProjectFace(TopoShape                 &shape,
	                                   const IndexSet<TopoShape> &vertices,
	                                   TopoFace &face, TopoShape &replaceshape);

	/// @brief Construct a new plane face based on the given set of edges
	/// @param[in,out] shape The shape
	/// @param[in] edges The given set of edges
	/// @return The new face
	AMCAX_API TopoFace BuildPlane(TopoShape                 &shape,
	                              const IndexSet<TopoShape> &edges);

	/// @brief Construct a new coons face based on the given set of edges
	/// @param[in,out] shape The shape
	/// @param[in] edges The given set of edges
	/// @return The new face
	AMCAX_API TopoFace BuildCoons(TopoShape                 &shape,
	                              const IndexSet<TopoShape> &edges);

	/// @brief Construct a new face based on the given set of edges and an
	/// existing face
	/// @param[in,out] shape The shape
	/// @param[in] edges The given set of edges
	/// @param[in] face The existing face
	/// @return The new face
	AMCAX_API TopoFace BuildFaceFromSurface(TopoShape                 &shape,
	                                        const IndexSet<TopoShape> &edges,
	                                        const TopoFace            &face);

	/// @brief Ensure consistent orientation of all faces in a shape without
	/// non-manifold edges
	/// @param[in,out] shape The shape
	AMCAX_API void AlignFaceOrientations(TopoShape &shape);

	/// @brief Given an edge, if it is shared by two faces, the faces are merged
	/// within the specified tolerance and normal angle threshold, and the edge is
	/// removed. If it is an internal edge of a single face, the edge is removed
	/// within the given tolerance
	/// @param[in,out] shape The shape
	/// @param[in] edge The edge
	/// @param[in] removevertices Whether to remove the edge's vertices from the
	/// shape after the edge is removed
	/// @param[in] tolerance The tolerance
	/// @param[in] continuitylimit The normal angle threshold
	/// @return Whether the merge was successful
	AMCAX_API bool MergeFace(TopoShape &shape, const TopoEdge &edge,
	                         bool   removevertices  = true,
	                         double tolerance       = Precision::Confusion(),
	                         double continuitylimit = Precision::Angular());

	/// @brief Cut the selected set of faces in the shape using the given plane
	/// @param[in,out] shape The shape
	/// @param[in] faces The set of faces
	/// @param[in] plane The given plane
	/// @param[in] tolerance The tolerance
	/// @return Whether at least one face was cut
	AMCAX_API bool CutFacesByPlane(TopoShape                  &shape,
	                               const std::list<TopoShape> &faces,
	                               const Plane                &plane,
	                               double tolerance = Precision::Confusion());

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
	static void RebuildFace(AMCAX::TopoShape &shape, AMCAX::TopoFace &face,
	                        const std::vector<IndexSet<TopoShape>> boundedges);

	static void RebuildFaceInterior(AMCAX::TopoShape                   &shape,
	                                AMCAX::TopoFace                    &face,
	                                const std::vector<AMCAX::TopoEdge> &edges);
};

} // namespace GeomE

} // namespace AMCAX