/// @file      TopoTool.hpp
/// @brief     Class of tools for B-Rep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <memory>

#include <common/PointT.hpp>
#include <math/GeometryMacros.hpp>
#include <topology/TopologyMacros.hpp>

namespace AMCAX
{
class Geom2Curve;
class Geom3Curve;
class Geom3Surface;
class Polygon2;
class Polygon3;
class PolygonOnTriangularMesh;
class TopoEdge;
class TopoFace;
class TopoLocation;
class TopoShape;
class TopoVertex;
class TriangularMesh;

/// @brief Class of access tools for B-Rep structure
class TopoTool
{
public:
	/// @brief Get the surface and the location of the surface from a face
	/// @param[in] f The face
	/// @param[out] l The location
	/// @return The surface, or null if the face has no surface
	[[nodiscard]] AMCAX_API static const std::shared_ptr<Geom3Surface>& Surface(const TopoFace& f, TopoLocation& l);

	/// @brief Get the surface of a face, if the face has a location, the surface is copied and transformed
	/// @param f The face
	/// @return The surface, or null if the face has no surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Surface> Surface(const TopoFace& f);

	/// @brief Get the triangular mesh from a face and the location of the face under a given purpose
	/// @param[in] f The face
	/// @param[out] l The location
	/// @param[in] purpose The purpose of the mesh, default value is 0 (TriangularMesh::MeshPurpose::None)
	/// @return The triangular mesh, or null if the face has no mesh
	[[nodiscard]] AMCAX_API static const std::shared_ptr<TriangularMesh>& Triangulation(const TopoFace& f, TopoLocation& l, unsigned char purpose = 0);

	/// @brief Get all the triangular meshes from a face and the location of the face
	/// @param[in] f The face
	/// @param[out] l The location
	/// @return The list of triangular meshes
	[[nodiscard]] AMCAX_API static const std::list<std::shared_ptr<TriangularMesh>>& Triangulations(const TopoFace& f, TopoLocation& l);

	/// @brief Get the tolerance of the face
	/// @param f The face
	/// @return The tolerance
	[[nodiscard]] AMCAX_API static double Tolerance(const TopoFace& f);

	/// @brief Does the face have a natural restriction
	/// @param f The face
	/// @return True if the face has a natural restriction
	[[nodiscard]] AMCAX_API static bool NaturalRestriction(const TopoFace& f);

	/// @brief Is the face geometric
	/// @param f The face
	/// @return True if the face has a surface
	[[nodiscard]] AMCAX_API static bool IsGeometric(const TopoFace& f);

	/// @brief Is the edge geometric
	/// @param e The edge
	/// @return True if the edge has a 3D curve or a curve on surface
	[[nodiscard]] AMCAX_API static bool IsGeometric(const TopoEdge& e);

	/// @brief Get the curve of an edge with its location and bounds
	/// @param[in] e The edge
	/// @param[out] l The location
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	/// @return The curve
	[[nodiscard]] AMCAX_API static const std::shared_ptr<Geom3Curve>& Curve(const TopoEdge& e, TopoLocation& l, double& first, double& last);

	/// @brief Get the transformed curve of an edge with bounds.
	/// @param[in] e The edge
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	/// @return The transformed curve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom3Curve> Curve(const TopoEdge& e, double& first, double& last);

	/// @brief Get the polygon of an edge
	/// @param[in] e The edge
	/// @param[out] l The location
	/// @return The polygon
	[[nodiscard]] AMCAX_API static const std::shared_ptr<Polygon3>& Polygon3D(const TopoEdge& e, TopoLocation& l);

	/// @brief Get the pcurve of an edge on a given face
	/// @param[in] e The edge
	/// @param[in] f The face
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	/// @param[in,out] isStored If the pointer is not null, get the status whether the pcurve is stored or computed
	/// @return The pcurve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom2Curve> CurveOnSurface(const TopoEdge& e, const TopoFace& f, double& first, double& last, const std::shared_ptr<bool>& isStored = nullptr);

	/// @brief Get the pcurve of an edge on a given surface
	/// @param[in] e The edge
	/// @param[in] s The surface
	/// @param[in] l The location
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	/// @param[in,out] isStored If the pointer is not null, get the status whether the pcurve is stored or computed
	/// @return The pcurve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom2Curve> CurveOnSurface(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double& first, double& last, const std::shared_ptr<bool>& isStored = nullptr);

	/// @brief Get the pcurve of an edge on a plane
	/// @param[in] e The edge
	/// @param[in] s The plane
	/// @param[in] l The location
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	/// @return The pcurve
	[[nodiscard]] AMCAX_API static std::shared_ptr<Geom2Curve> CurveOnPlane(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double& first, double& last);

	/// @brief Get the pcurve of an edge
	/// @param[in] e The edge
	/// @param[out] pc The pcurve
	/// @param[out] s The surface
	/// @param[out] l The location
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	AMCAX_API static void CurveOnSurface(const TopoEdge& e, std::shared_ptr<Geom2Curve>& pc, std::shared_ptr<Geom3Surface>& s, TopoLocation& l, double& first, double& last);

	/// @brief Get the pcurve of an edge at a given index
	/// @details The index starts from 1
	/// @param[in] e The edge
	/// @param[out] pc The pcurve
	/// @param[out] s The surface
	/// @param[out] l The location
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	/// @param[in] index The index of pcurve
	AMCAX_API static void CurveOnSurface(const TopoEdge& e, std::shared_ptr<Geom2Curve>& pc, std::shared_ptr<Geom3Surface>& s, TopoLocation& l, double& first, double& last, int index);

	/// @brief Get the polygon on a given face of an edge
	/// @param e The edge
	/// @param f The face
	/// @return The polygon on face
	[[nodiscard]] AMCAX_API static std::shared_ptr<Polygon2> PolygonOnSurface(const TopoEdge& e, const TopoFace& f);

	/// @brief Get the polygon on a given surface of an edge
	/// @param e The edge
	/// @param s The surface
	/// @param l The location
	/// @return The polygon on surface
	[[nodiscard]] AMCAX_API static std::shared_ptr<Polygon2> PolygonOnSurface(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l);

	/// @brief Get the polygon on surface of an edge
	/// @param[in] e The edge
	/// @param[out] p The polygon on surface
	/// @param[out] s The surface
	/// @param[out] l The location
	AMCAX_API static void PolygonOnSurface(const TopoEdge& e, std::shared_ptr<Polygon2>& p, std::shared_ptr<Geom3Surface>& s, TopoLocation& l);

	/// @brief Get the polygon on surface of an edge at a given index
	/// @details The index starts from 1
	/// @param[in] e The edge
	/// @param[out] p The polygon on surface
	/// @param[out] s The surface
	/// @param[out] l The location
	/// @param[in] index The index of polygon
	AMCAX_API static void PolygonOnSurface(const TopoEdge& e, std::shared_ptr<Polygon2>& p, std::shared_ptr<Geom3Surface>& s, TopoLocation& l, int index);

	/// @brief Get the polygon on a given triangular mesh of an edge
	/// @param e The edge
	/// @param t The triangular mesh
	/// @param l The location
	/// @return The polygon on triangular mesh
	[[nodiscard]] AMCAX_API static const std::shared_ptr<PolygonOnTriangularMesh>& PolygonOnTriangulation(const TopoEdge& e, const std::shared_ptr<TriangularMesh>& t, const TopoLocation& l);

	/// @brief Get the polygon on triangular mesh of an edge
	/// @param[in] e The edge
	/// @param[out] p The polygon on triangular mesh
	/// @param[out] t The reference triangular mesh
	/// @param[out] l The location
	AMCAX_API static void PolygonOnTriangulation(const TopoEdge& e, std::shared_ptr<PolygonOnTriangularMesh>& p, std::shared_ptr<TriangularMesh>& t, TopoLocation& l);

	/// @brief Get the polygon on triangular mesh of an edge at a given index
	/// @param[in] e The edge
	/// @param[out] p The polygon on triangular mesh
	/// @param[out] t The triangular mesh
	/// @param[out] l The location
	/// @param[in] index The index of polygon
	AMCAX_API static void PolygonOnTriangulation(const TopoEdge& e, std::shared_ptr<PolygonOnTriangularMesh>& p, std::shared_ptr<TriangularMesh>& t, TopoLocation& l, int index);

	/// @brief Is the shape closed
	/// @details If the shape is a shell, then return true if the shell has no boundary edge.
	///          If the shape is a wire, then return true if the wire has no boundary vertex.
	///          If the shape is an edge, then return true if the edge has two coincide vertices.
	/// @param s The shape
	/// @return True if the shape is closed
	[[nodiscard]] AMCAX_API static bool IsClosed(const TopoShape& s);

	/// @brief Is the edge on a closing curve of a face
	/// @param e The edge
	/// @param f The closed face
	/// @return True if the edge has two pcurves on the face
	[[nodiscard]] AMCAX_API static bool IsClosed(const TopoEdge& e, const TopoFace& f);

	/// @brief Is the edge on a closing curve of a surface
	/// @param e The edge
	/// @param s The closed surface
	/// @param l The location
	/// @return True if the edge has two pcurves on the surface
	[[nodiscard]] AMCAX_API static bool IsClosed(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l);

	/// @brief Is the edge on a closing polygon of a triangular mesh
	/// @param e The edge
	/// @param t The closed triangular mesh
	/// @param l The location
	/// @return True if the edge has two polygons on the triangular mesh
	[[nodiscard]] AMCAX_API static bool IsClosed(const TopoEdge& e, const std::shared_ptr<TriangularMesh>& t, const TopoLocation& l);

	/// @brief Get the tolerance of an edge
	/// @param e The edge
	/// @return The tolerance
	[[nodiscard]] AMCAX_API static double Tolerance(const TopoEdge& e);

	/// @brief Get the same parameter flag of an edge
	/// @param e The edge
	/// @return True if the edge is same parameter
	[[nodiscard]] AMCAX_API static bool SameParameter(const TopoEdge& e);

	/// @brief Get the same range flag of an edge
	/// @param e The edge
	/// @return True if the edge is same range
	[[nodiscard]] AMCAX_API static bool SameRange(const TopoEdge& e);

	/// @brief Get the degenerated flag of an edge
	/// @param e The edge
	/// @return True if the edge is degenerated
	[[nodiscard]] AMCAX_API static bool Degenerated(const TopoEdge& e);

	/// @brief Get the parameter range of the 3D curve of an edge
	/// @param[in] e The edge
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	AMCAX_API static void Range(const TopoEdge& e, double& first, double& last);

	/// @brief Get the parameter range of the pcurve on a surface of an edge
	/// @param[in] e The edge
	/// @param[in] s The surface
	/// @param[in] l The location
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	AMCAX_API static void Range(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double& first, double& last);

	/// @brief Get the parameter range of the pcurve on a face of an edge
	/// @param[in] e The edge
	/// @param[in] f The face
	/// @param[out] first The first parameter
	/// @param[out] last The last parameter
	AMCAX_API static void Range(const TopoEdge& e, const TopoFace& f, double& first, double& last);

	/// @brief Get the UV points on a surface of an edge
	/// @param[in] e The edge
	/// @param[in] s The surface
	/// @param[in] l The location
	/// @param[out] pFirst The first point
	/// @param[out] pLast The last point
	AMCAX_API static void UVPoints(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, Point2& pFirst, Point2& pLast);

	/// @brief Get the UV points on a face of an edge
	/// @param[in] e The edge
	/// @param[in] f The face
	/// @param[out] pFirst The first point
	/// @param[out] pLast The last point
	AMCAX_API static void UVPoints(const TopoEdge& e, const TopoFace& f, Point2& pFirst, Point2& pLast);

	/// @brief Set the UV points on a surface of an edge
	/// @param e The edge
	/// @param s The surface
	/// @param l The location
	/// @param pFirst The first point
	/// @param pLast The last point
	AMCAX_API static void SetUVPoints(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, const Point2& pFirst, const Point2& pLast);

	/// @brief Set the UV points on a face of an edge
	/// @param e The edge
	/// @param f The face
	/// @param pFirst The first point
	/// @param pLast The last point
	AMCAX_API static void SetUVPoints(const TopoEdge& e, const TopoFace& f, const Point2& pFirst, const Point2& pLast);

	/// @brief Is the edge on two faces
	/// @param e The edge
	/// @param f1 The first face
	/// @param f2 The second face
	/// @return True if the edge has a continuity between two faces
	[[nodiscard]] AMCAX_API static bool HasContinuity(const TopoEdge& e, const TopoFace& f1, const TopoFace& f2);

	/// @brief Get the type of continuity of an edge on two faces
	/// @param e The edge
	/// @param f1 The first face
	/// @param f2 The second face
	/// @return The type of continuity
	[[nodiscard]] AMCAX_API static ContinuityType Continuity(const TopoEdge& e, const TopoFace& f1, const TopoFace& f2);

	/// @brief Is the edge on two surfaces
	/// @param e The edge
	/// @param s1 The first surface
	/// @param s2 The second surface
	/// @param l1 The first location
	/// @param l2 The second location
	/// @return True if the edge has a continuity between two surfaces
	[[nodiscard]] AMCAX_API static bool HasContinuity(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, const TopoLocation& l1, const TopoLocation& l2);

	/// @brief Get the type of continuity of an edge on two surfaces
	/// @param e The edge
	/// @param s1 The first surface
	/// @param s2 The second surface
	/// @param l1 The first location
	/// @param l2 The second location
	/// @return The type of continuity
	[[nodiscard]] AMCAX_API static ContinuityType Continuity(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, const TopoLocation& l1, const TopoLocation& l2);

	/// @brief Does the edge have regularity on two surfaces
	/// @param e The edge
	/// @return True if the edge has regularity
	[[nodiscard]] AMCAX_API static bool HasContinuity(const TopoEdge& e);

	/// @brief Get the maximum continuity type of an edge
	/// @param e The edge
	/// @return The maximum continuity type of an edge
	[[nodiscard]] AMCAX_API static ContinuityType MaxContinuity(const TopoEdge& e);

	/// @brief Get the point of a vertex
	/// @param v The vertex
	/// @return The point
	[[nodiscard]] AMCAX_API static Point3 Point(const TopoVertex& v);

	/// @brief Get the tolerance of a vertex
	/// @param v The vertex
	/// @return The tolerance of vertex
	[[nodiscard]] AMCAX_API static double Tolerance(const TopoVertex& v);

	/// @brief Get the parameter of a vertex on an edge
	/// @param[in] v The vertex
	/// @param[in] e The edge
	/// @param[out] param The parameter
	/// @return True if the vertex is on the edge
	AMCAX_API static bool Parameter(const TopoVertex& v, const TopoEdge& e, double& param);

	/// @brief Get the parameter of a vertex on an edge
	/// @details If the vertex is not on the edge, then throw an exception
	/// @param v The vertex
	/// @param e The edge
	/// @return The parameter
	[[nodiscard]] AMCAX_API static double Parameter(const TopoVertex& v, const TopoEdge& e);

	/// @brief Get the parameter of a vertex on a pcurve of an edge on a face
	/// @details If the vertex is not on a pcurve of the edge on face, then throw an exception
	/// @param v The vertex
	/// @param e The edge
	/// @param f The face
	/// @return The parameter
	[[nodiscard]] AMCAX_API static double Parameter(const TopoVertex& v, const TopoEdge& e, const TopoFace& f);

	/// @brief Get the parameter of a vertex on a pcurve of an edge on a surface
	/// @details If the vertex is not on a pcurve of the edge on surface, then throw an exception
	/// @param v The vertex
	/// @param e The edge
	/// @param s The surface
	/// @param l The location
	/// @return The parameter
	[[nodiscard]] AMCAX_API static double Parameter(const TopoVertex& v, const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l);

	/// @brief Get the parameters of a vertex on a face
	/// @details If the vertex is not on a face, then throw an exception
	/// @param v The vertex
	/// @param f The face
	/// @return The uv parameters
	[[nodiscard]] AMCAX_API static Point2 Parameters(const TopoVertex& v, const TopoFace& f);

	/// @brief Get the maximum tolerance of all the sub-shape of a given type in a shape
	/// @param s The parent shape
	/// @param type The type of sub-shape
	/// @return The maximum tolerance
	[[nodiscard]] AMCAX_API static double MaxTolerance(const TopoShape& s, ShapeType type);

	/// @brief Get the composition of two orientation
	/// @param o1 The first orientation
	/// @param o2 The second orientation
	/// @return The composed orientation
	[[nodiscard]] AMCAX_API static OrientationType Compose(const OrientationType& o1, const OrientationType& o2) noexcept;

	/// @brief Get the reverse of an orientation
	/// @param o The orientation
	/// @return The reversed orientation
	[[nodiscard]] AMCAX_API static OrientationType Reverse(const OrientationType& o) noexcept;

	/// @brief Get the complement of an orientation
	/// @param o The orientation
	/// @return The complemented orientation
	[[nodiscard]] AMCAX_API static OrientationType Complement(const OrientationType& o) noexcept;
};
} // namespace AMCAX
