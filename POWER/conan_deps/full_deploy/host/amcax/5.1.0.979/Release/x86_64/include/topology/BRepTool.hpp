/// @file      BRepTool.hpp
/// @brief     Class of tool for B-Rep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <memory>

#include <common/IndexSet.hpp>
#include <common/Macros.hpp>
#include <topology/TopologyMacros.hpp>

namespace AMCAX
{
class BoundingBox2;
class Geom2Curve;
class Geom3Curve;
class Geom3Surface;
class TopoBuilder;
class TopoCompound;
class TopoCompSolid;
class TopoEdge;
class TopoFace;
class TopoShape;
class TopoShell;
class TopoSolid;
class TopoVertex;
class TopoWire;

/// @brief Class of tool for B-Rep structure
class BRepTool
{
public:
	/// @brief Compute the UV bounds of a face
	/// @param[in] f The face
	/// @param[out] uMin The u lower bound
	/// @param[out] uMax The u upper bound
	/// @param[out] vMin The v lower bound
	/// @param[out] vMax The v upper bound
	AMCAX_API static void UVBounds(const TopoFace& f, double& uMin, double& uMax, double& vMin, double& vMax);

	/// @brief Compute the UV bounds of a wire on a face
	/// @param[in] f The face
	/// @param[in] w The wire
	/// @param[out] uMin The u lower bound
	/// @param[out] uMax The u upper bound
	/// @param[out] vMin The v lower bound
	/// @param[out] vMax The v upper bound
	AMCAX_API static void UVBounds(const TopoFace& f, const TopoWire& w, double& uMin, double& uMax, double& vMin, double& vMax);

	/// @brief Compute the UV bounds of an edge on a face
	/// @param[in] f The face
	/// @param[in] e The edge
	/// @param[out] uMin The u lower bound
	/// @param[out] uMax The u upper bound
	/// @param[out] vMin The v lower bound
	/// @param[out] vMax The v upper bound
	AMCAX_API static void UVBounds(const TopoFace& f, const TopoEdge& e, double& uMin, double& uMax, double& vMin, double& vMax);

	/// @brief Add the UV bounds of a face to a bounding box
	/// @param[in] f The face
	/// @param[in,out] b The bounding box
	AMCAX_API static void AddUVBounds(const TopoFace& f, BoundingBox2& b);

	/// @brief Add the UV bounds of a wire on a face to a bounding box
	/// @param[in] f The face
	/// @param[in] w The wire
	/// @param[in,out] b The bounding box
	AMCAX_API static void AddUVBounds(const TopoFace& f, const TopoWire& w, BoundingBox2& b);

	/// @brief Add the UV bounds of an edge on a face to a bounding box
	/// @param[in] f The face
	/// @param[in] e The edge
	/// @param[in,out] b The bounding box
	AMCAX_API static void AddUVBounds(const TopoFace& f, const TopoEdge& e, BoundingBox2& b);

	/// @brief Update a vertex
	/// @param v The vertex
	AMCAX_API static void Update(const TopoVertex& v) noexcept;

	/// @brief Update an edge
	/// @param e The edge
	AMCAX_API static void Update(const TopoEdge& e) noexcept;

	/// @brief Update a wire
	/// @param w The wire
	AMCAX_API static void Update(const TopoWire& w) noexcept;

	/// @brief Update a face
	/// @param f The face
	AMCAX_API static void Update(const TopoFace& f);

	/// @brief Update a shell
	/// @param s The shell
	AMCAX_API static void Update(const TopoShell& s);

	/// @brief Update a solid
	/// @param s The solid
	AMCAX_API static void Update(const TopoSolid& s);

	/// @brief Update a composite solid
	/// @param c The composite solid
	AMCAX_API static void Update(const TopoCompSolid& c);

	/// @brief Update a compound
	/// @param c The compound
	AMCAX_API static void Update(const TopoCompound& c);

	/// @brief Update a shape
	/// @param s The shape
	AMCAX_API static void Update(const TopoShape& s);

	/// @brief Update the UV points for all edges in a face
	/// @param f The face
	AMCAX_API static void UpdateFaceUVPoints(const TopoFace& f);

	/// @brief Remove the polygon and mesh representation of the shape
	/// @param s The shape
	/// @param force Whether to remove polygon on triangulations irrelevant for the face of the shape
	AMCAX_API static void Clean(const TopoShape& s, bool force = false);

	/// @brief Remove all the curves and surfaces from all edges and faces in the shape
	/// @param s The shape
	AMCAX_API static void CleanGeometry(const TopoShape& s);

	/// @brief Check if the shape contains geometry (points, curves, or surfaces)
	/// @param s The shape
	[[nodiscard]] AMCAX_API static bool HasGeometry(const TopoShape& s);

	/// @brief Remove the pcurves of the edges in the shape, which has a reference surface not belonging to any face of the shape
	/// @param s The shape
	AMCAX_API static void RemoveUnusedPCurves(const TopoShape& s);

	/// @brief Check that the deflection of triangular mesh is smaller than a tolerance for faces in a shape
	/// @param s The shape
	/// @param linDefl The deflection tolerance
	/// @param checkFreeEdges Whether check the polygons on free edges
	/// @return True if the faces and edges have polygons and meshes with deflection lower than the tolerance
	[[nodiscard]] AMCAX_API static bool Triangulation(const TopoShape& s, double linDefl, bool checkFreeEdges = false);

	/// @brief Check the distance between two vertices is lower than their tolerance
	/// @param v1 The first vertex
	/// @param v2 The second vertex
	/// @return True if the distance between two vertices is lower than their tolerance
	[[nodiscard]] AMCAX_API static bool Compare(const TopoVertex& v1, const TopoVertex& v2);

	/// @brief Check the distance between two edges is lower than their tolerance
	/// @param e1 The first edge
	/// @param e2 The second edge
	/// @return True if the distance between two edges is lower than their tolerance
	[[nodiscard]] AMCAX_API static bool Compare(const TopoEdge& e1, const TopoEdge& e2) noexcept;

	/// @brief Get the outer wire of a face
	/// @param f The face
	/// @return The outer wire
	[[nodiscard]] AMCAX_API static TopoWire OuterWire(const TopoFace& f);

	/// @brief Get all the topology edges in a shape, i.e. not degenerated
	/// @param[in] s The shape
	/// @param[out] m The set of edges
	AMCAX_API static void Map3DEdges(const TopoShape& s, IndexSet<TopoShape>& m);

	/// @brief Check the edge appears twice in a face
	/// @param e The edge
	/// @param f The face
	/// @return True if the edge appears twice in a face
	[[nodiscard]] AMCAX_API static bool IsReallyClosed(const TopoEdge& e, const TopoFace& f);

	/// @brief Detect closedness of face in U and V directions
	/// @param[in] f The face
	/// @param[out] uClosed True if the face is closed in u direction
	/// @param[out] vClosed True if the face is closed in v direction
	AMCAX_API static void DetectClosedness(const TopoFace& f, bool& uClosed, bool& vClosed);

	/// @brief Compute the actual tolerance of the edge and update the tolerance if it is more than the current edge tolerance
	/// @param e The edge
	/// @param c3d The 3D curve
	/// @param c2d The pcurve
	/// @param s The reference surface
	/// @param first The first parameter
	/// @param last The last parameter
	/// @return The actual tolerance
	[[nodiscard]] AMCAX_API static double EvalAndUpdateTol(const TopoEdge& e, const std::shared_ptr<Geom3Curve>& c3d, const std::shared_ptr<Geom2Curve>& c2d, const std::shared_ptr<Geom3Surface>& s, double first, double last);

	/// @brief Get the cumulative orientation of an edge in a face
	/// @param e The edge
	/// @param f The face
	/// @return The cumulative orientation
	[[nodiscard]] AMCAX_API static OrientationType OriEdgeInFace(const TopoEdge& e, const TopoFace& f);

	/// @brief Remove the internal sub-shapes of a shape
	/// @param[in,out] s The shape
	/// @param[in] force If force is true, connection check is disabled
	AMCAX_API static void RemoveInternals(TopoShape& s, bool force = false);

	/// @brief Check the location of shape, and find all the problematic sub-shapes
	/// @details If the transformation contains mirroring or scaling, then the sub-shape is problematic
	/// @param[in] s The shape
	/// @param[out] problemShapes The list of problematic sub-shapes
	AMCAX_API static void CheckLocations(const TopoShape& s, std::list<TopoShape>& problemShapes);
};
} // namespace AMCAX
