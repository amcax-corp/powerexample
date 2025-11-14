/// @file      TopoBuilder.hpp
/// @brief     Class of a tool for building B-Rep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <memory>

#include <common/PointT.hpp>
#include <math/GeometryMacros.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class CurveRepresentation;
class Geom2Curve;
class Geom3Curve;
class Geom3Surface;
class PointRepresentation;
class Polygon2;
class Polygon3;
class PolygonOnTriangularMesh;
class TopoCompound;
class TopoCompSolid;
class TopoEdge;
class TopoFace;
class TopoLocation;
class TopoShape;
class TopoShell;
class TopoSolid;
class TopoTShape;
class TopoVertex;
class TopoWire;
class TriangularMesh;
#endif

/// @brief Class of a tool for building B-Rep structure
class TopoBuilder
{
public:
	/// @brief Make an empty wire
	/// @param[in,out] w The wire
	AMCAX_API void MakeWire(TopoWire& w) const;

	/// @brief Make an empty shell
	/// @param[in,out] s The shell
	AMCAX_API void MakeShell(TopoShell& s) const;

	/// @brief Make an empty solid
	/// @param[in,out] s The solid
	AMCAX_API void MakeSolid(TopoSolid& s) const;

	/// @brief Make an empty composite solid
	/// @param[in,out] c The composite solid
	AMCAX_API void MakeCompSolid(TopoCompSolid& c) const;

	/// @brief Make an empty compound
	/// @param[in,out] c The compound
	AMCAX_API void MakeCompound(TopoCompound& c) const;

	/// @brief Make an empty face
	/// @param[in,out] f The face
	AMCAX_API void MakeFace(TopoFace& f) const;

	/// @brief Make a face with a surface
	/// @param[in,out] f The face
	/// @param[in] s The surface
	/// @param[in] tol The tolerance
	AMCAX_API void MakeFace(TopoFace& f, const std::shared_ptr<Geom3Surface>& s, double tol) const;

	/// @brief Make a face with a surface and a location
	/// @param[in,out] f The face
	/// @param[in] s The surface
	/// @param[in] l The location
	/// @param[in] tol The tolerance
	AMCAX_API void MakeFace(TopoFace& f, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double tol) const;

	/// @brief Make a face with a triangular mesh
	/// @param[in,out] f The face
	/// @param[in] t The triangular mesh
	AMCAX_API void MakeFace(TopoFace& f, const std::shared_ptr<TriangularMesh>& t) const;

	/// @brief Make a face with a list of triangular meshes and set the active mesh
	/// @details If the active mesh is null, the first mesh in the list is set to be the active one
	/// @param[in,out] f The face
	/// @param[in] ts The list of triangular meshes
	/// @param[in] activeT The active triangular mesh
	AMCAX_API void MakeFace(TopoFace& f, const std::list<std::shared_ptr<TriangularMesh>>& ts, const std::shared_ptr<TriangularMesh>& activeT = std::shared_ptr<TriangularMesh>()) const;

	/// @brief Update the surface, location and tolerance of a face
	/// @param f The face
	/// @param s The surface
	/// @param l The location
	/// @param tol The tolerance
	AMCAX_API void UpdateFace(const TopoFace& f, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double tol) const;

	/// @brief Update the triangular mesh of a face
	/// @details If the reset flag is true, then the triangular mesh list is updated by the new triangular mesh.
	///          If the reset flag is false, then if the triangular mesh is in the list, just set it to be the active; otherwise, the active triangular mesh is replaced.
	/// @param f The face
	/// @param t The triangular mesh
	/// @param toReset Whether reset the active mesh
	AMCAX_API void UpdateFace(const TopoFace& f, const std::shared_ptr<TriangularMesh>& t, bool toReset = true) const;

	/// @brief Update the tolerance of a face
	/// @param f The face
	/// @param tol The tolerance
	AMCAX_API void UpdateFace(const TopoFace& f, double tol) const;

	/// @brief Update the natural restriction flag of a face
	/// @param f The face
	/// @param n The natural restriction flag
	AMCAX_API void NaturalRestriction(const TopoFace& f, bool n) const;

	/// @brief Make an empty edge
	/// @param[in,out] e The edge
	AMCAX_API void MakeEdge(TopoEdge& e) const;

	/// @brief Make an edge with a curve
	/// @param[in,out] e The edge
	/// @param[in] c The curve
	/// @param[in] tol The tolerance
	AMCAX_API void MakeEdge(TopoEdge& e, const std::shared_ptr<Geom3Curve>& c, double tol) const;

	/// @brief Make an edge with a curve and a location
	/// @param[in,out] e The edge
	/// @param[in] c The curve
	/// @param[in] l The location
	/// @param[in] tol The tolerance
	AMCAX_API void MakeEdge(TopoEdge& e, const std::shared_ptr<Geom3Curve>& c, const TopoLocation& l, double tol) const;

	/// @brief Make an edge with a polygon
	/// @param[in,out] e The edge
	/// @param[in] p The polygon
	AMCAX_API void MakeEdge(TopoEdge& e, const std::shared_ptr<Polygon3>& p) const;

	/// @brief Make an edge with a polygon on triangular mesh
	/// @param[in,out] e The edge
	/// @param[in] p The polygon on triangular mesh
	/// @param[in] t The reference triangular mesh
	AMCAX_API void MakeEdge(TopoEdge& e, const std::shared_ptr<PolygonOnTriangularMesh>& p, const std::shared_ptr<TriangularMesh>& t) const;

	/// @brief Make an edge with a polygon on triangular mesh and a location
	/// @param[in,out] e The edge
	/// @param[in] p The polygon on triangular mesh
	/// @param[in] t The reference triangular mesh
	/// @param[in] l The location
	AMCAX_API void MakeEdge(TopoEdge& e, const std::shared_ptr<PolygonOnTriangularMesh>& p, const std::shared_ptr<TriangularMesh>& t, const TopoLocation& l) const;

	/// @brief Update the curve and tolerance of an edge
	/// @param e The edge
	/// @param c The curve
	/// @param tol The tolerance
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom3Curve>& c, double tol) const;

	/// @brief Update the curve, location and tolerance of an edge
	/// @param e The edge
	/// @param c The curve
	/// @param l The location
	/// @param tol The tolerance
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom3Curve>& c, const TopoLocation& l, double tol) const;

	/// @brief Update the pcurve of an edge on a face
	/// @param e The edge
	/// @param c The pcurve
	/// @param f The face
	/// @param tol The tolerance
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom2Curve>& c, const TopoFace& f, double tol) const;

	/// @brief Update the pcurves of an edge on a closed face
	/// @param e The edge
	/// @param c1 The first pcurve
	/// @param c2 The second pcurve
	/// @param f The face
	/// @param tol The tolerance
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom2Curve>& c1, const std::shared_ptr<Geom2Curve>& c2, const TopoFace& f, double tol) const;

	/// @brief Update the pcurve of an edge on a surface
	/// @param e The edge
	/// @param c The pcurve
	/// @param s The surface
	/// @param l The location of surface
	/// @param tol The tolerance
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom2Curve>& c, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double tol) const;

	/// @brief Update the pcurve of an edge on a surface with UV bounds
	/// @param e The edge
	/// @param c The pcurve
	/// @param s The surface
	/// @param l The location of surface
	/// @param tol The tolerance
	/// @param pf The first uv point
	/// @param pl The last uv point
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom2Curve>& c, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double tol, const Point2& pf, const Point2& pl) const;

	/// @brief Update the pcurves of an edge on a closed surface
	/// @param e The edge
	/// @param c1 The first pcurve
	/// @param c2 The second pcurve
	/// @param s The surface
	/// @param l The location of surface
	/// @param tol The tolerance
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom2Curve>& c1, const std::shared_ptr<Geom2Curve>& c2, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double tol) const;

	/// @brief Update the pcurves of an edge on a closed surface with UV bounds
	/// @param e The edge
	/// @param c1 The first pcurve
	/// @param c2 The second pcurve
	/// @param s The surface
	/// @param l The location of surface
	/// @param tol The tolerance
	/// @param pf The first uv point
	/// @param pl The last uv point
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Geom2Curve>& c1, const std::shared_ptr<Geom2Curve>& c2, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double tol, const Point2& pf, const Point2& pl) const;

	/// @brief Update the polygon of an edge
	/// @param e The edge
	/// @param p The polygon
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Polygon3>& p) const;

	/// @brief Update the polygon and location of an edge
	/// @param e The edge
	/// @param p The polygon
	/// @param l The location
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Polygon3>& p, const TopoLocation& l) const;

	/// @brief Update the polygon on triangular mesh of an edge
	/// @param e The edge
	/// @param p The polygon on triangular mesh
	/// @param t The reference triangular mesh
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<PolygonOnTriangularMesh>& p, const std::shared_ptr<TriangularMesh>& t) const;

	/// @brief Update the polygon on triangular mesh and location of an edge
	/// @param e The edge
	/// @param p The polygon on triangular mesh
	/// @param t The reference triangular mesh
	/// @param l The location
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<PolygonOnTriangularMesh>& p, const std::shared_ptr<TriangularMesh>& t, const TopoLocation& l) const;

	/// @brief Update the polygons on closed triangular mesh of an edge
	/// @param e The edge
	/// @param p1 The first polygon on triangular mesh
	/// @param p2 The second polygon on triangular mesh
	/// @param t The reference closed triangular mesh
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<PolygonOnTriangularMesh>& p1, const std::shared_ptr<PolygonOnTriangularMesh>& p2, const std::shared_ptr<TriangularMesh>& t) const;

	/// @brief Update the polygons on closed triangular mesh and location of an edge
	/// @param e The edge
	/// @param p1 The first polygon on triangular mesh
	/// @param p2 The second polygon on triangular mesh
	/// @param t The reference closed triangular mesh
	/// @param l The location
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<PolygonOnTriangularMesh>& p1, const std::shared_ptr<PolygonOnTriangularMesh>& p2, const std::shared_ptr<TriangularMesh>& t, const TopoLocation& l) const;

	/// @brief Update the polygon on face of an edge
	/// @param e The edge
	/// @param p The polygon
	/// @param f The face
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Polygon2>& p, const TopoFace& f) const;

	/// @brief Update the polygon on surface of an edge
	/// @param e The edge
	/// @param p The polygon
	/// @param s The surface
	/// @param l The location
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Polygon2>& p, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l) const;

	/// @brief Update the polygons on a closed face of an edge
	/// @param e The edge
	/// @param p1 The first polygon
	/// @param p2 The second polygon
	/// @param f The closed face
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Polygon2>& p1, const std::shared_ptr<Polygon2>& p2, const TopoFace& f) const;

	/// @brief Update the polygons on a closed surface of an edge
	/// @param e The edge
	/// @param p1 The first polygon
	/// @param p2 The second polygon
	/// @param s The closed surface
	/// @param l The location
	AMCAX_API void UpdateEdge(const TopoEdge& e, const std::shared_ptr<Polygon2>& p1, const std::shared_ptr<Polygon2>& p2, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l) const;

	/// @brief Update the tolerance of an edge
	/// @param e The edge
	/// @param tol The tolerance
	AMCAX_API void UpdateEdge(const TopoEdge& e, double tol) const;

	/// @brief Set the continuity of an edge between two faces
	/// @param e The edge
	/// @param f1 The first face
	/// @param f2 The second face
	/// @param c The continuity
	AMCAX_API void Continuity(const TopoEdge& e, const TopoFace& f1, const TopoFace& f2, ContinuityType c) const;

	/// @brief Set the continuity of an edge between two surfaces
	/// @param e The edge
	/// @param s1 The first surface
	/// @param s2 The second surface
	/// @param l1 The location of the first surface
	/// @param l2 The location of the second surface
	/// @param c The continuity
	AMCAX_API void Continuity(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, const TopoLocation& l1, const TopoLocation& l2, ContinuityType c) const;

	/// @brief Set the same parameter flag of an edge
	/// @param e The edge
	/// @param s The same parameter flag
	AMCAX_API void SameParameter(const TopoEdge& e, bool s) const;

	/// @brief Set the same range flag of an edge
	/// @param e The edge
	/// @param s The same range flag
	AMCAX_API void SameRange(const TopoEdge& e, bool s) const;

	/// @brief Set the degenerate flag of an edge
	/// @param e The edge
	/// @param d The degenerate flag
	AMCAX_API void Degenerated(const TopoEdge& e, bool d) const;

	/// @brief Set the range of parameter of an edge
	/// @param e The edge
	/// @param first The first parameter
	/// @param last The last parameter
	/// @param only3d Whether the range is only applied to 3D curve
	AMCAX_API void Range(const TopoEdge& e, double first, double last, bool only3d = false) const;

	/// @brief Set the range of parameter of the pcurve on a surface of an edge
	/// @param e The edge
	/// @param s The reference surface
	/// @param l The location
	/// @param first The first parameter
	/// @param last The last parameter
	AMCAX_API void Range(const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double first, double last) const;

	/// @brief Set the range of parameter of the pcurve on a face of an edge
	/// @param e The edge
	/// @param f The reference face
	/// @param first The first parameter
	/// @param last The last parameter
	AMCAX_API void Range(const TopoEdge& e, const TopoFace& f, double first, double last) const;

	/// @brief Transfer the representations from an edge to another edge
	/// @param ein The source edge
	/// @param eout The target edge
	AMCAX_API void Transfer(const TopoEdge& ein, const TopoEdge& eout) const;

	/// @brief Make an empty vertex
	/// @param[in,out] v The vertex
	AMCAX_API void MakeVertex(TopoVertex& v) const;

	/// @brief Make a vertex with a point
	/// @param[in,out] v The vertex
	/// @param[in] p The point
	/// @param[in] tol The tolerance
	AMCAX_API void MakeVertex(TopoVertex& v, const Point3& p, double tol) const;

	/// @brief Update the point of a vertex
	/// @param v The vertex
	/// @param p The point
	/// @param tol The tolerance
	AMCAX_API void UpdateVertex(const TopoVertex& v, const Point3& p, double tol) const;

	/// @brief Update the point on edge of a vertex
	/// @param v The vertex
	/// @param p The parameter of point on edge
	/// @param e The edge
	/// @param tol The tolerace
	AMCAX_API void UpdateVertex(const TopoVertex& v, double p, const TopoEdge& e, double tol) const;

	/// @brief Update the point on edge on face of a vertex
	/// @param v The vertex
	/// @param p The parameter of point on edge on face
	/// @param e The edge
	/// @param f The face
	/// @param tol The tolerance
	AMCAX_API void UpdateVertex(const TopoVertex& v, double p, const TopoEdge& e, const TopoFace& f, double tol) const;

	/// @brief Update the point on edge on surface of a vertex
	/// @param v The vertex
	/// @param p The parameter of point on edge on surface
	/// @param e The edge
	/// @param s The surface
	/// @param l The location of surface
	/// @param tol The tolerance
	AMCAX_API void UpdateVertex(const TopoVertex& v, double p, const TopoEdge& e, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, double tol) const;

	/// @brief Update the point on face of a vertex
	/// @param vert The vertex
	/// @param u The u parameter of point on face
	/// @param v The v parameter of point on face
	/// @param f The face
	/// @param tol The tolerance
	AMCAX_API void UpdateVertex(const TopoVertex& vert, double u, double v, const TopoFace& f, double tol) const;

	/// @brief Update the tolerance of a vertex
	/// @param v The vertex
	/// @param tol The tolerance
	AMCAX_API void UpdateVertex(const TopoVertex& v, double tol) const;

	/// @brief Transfer the parameters of a vertex on edge to another vertex on edge
	/// @param ein The source edge
	/// @param eout The target edge
	/// @param vin The source vertex
	/// @param vout The target vertex
	AMCAX_API void Transfer(const TopoEdge& ein, const TopoEdge& eout, const TopoVertex& vin, const TopoVertex& vout) const;

	/// @brief Add a sub-shape to a shape
	/// @param[in,out] s The parent shape
	/// @param[in] c The sub-shape to be added
	AMCAX_API void Add(TopoShape& s, const TopoShape& c) const;

	/// @brief Remove a sub-shape from a shape
	/// @param[in,out] s The parent shape
	/// @param[in] c The sub-shape to be removed
	AMCAX_API void Remove(TopoShape& s, const TopoShape& c) const;

private:
	void MakeShape(TopoShape& s, const std::shared_ptr<TopoTShape>& t) const;
	static void UpdateCurves(std::list<std::shared_ptr<CurveRepresentation>>& cs, const std::shared_ptr<Geom3Curve>& c, const TopoLocation& l);
	static void UpdateCurves(std::list<std::shared_ptr<CurveRepresentation>>& cs, const std::shared_ptr<Geom2Curve>& c, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l);
	static void UpdateCurves(std::list<std::shared_ptr<CurveRepresentation>>& cs, const std::shared_ptr<Geom2Curve>& c, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, const Point2& pf, const Point2& pl);
	static void UpdateCurves(std::list<std::shared_ptr<CurveRepresentation>>& cs, const std::shared_ptr<Geom2Curve>& c1, const std::shared_ptr<Geom2Curve>& c2, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l);
	static void UpdateCurves(std::list<std::shared_ptr<CurveRepresentation>>& cs, const std::shared_ptr<Geom2Curve>& c1, const std::shared_ptr<Geom2Curve>& c2, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l, const Point2& pf, const Point2& pl);
	static void UpdateCurves(std::list<std::shared_ptr<CurveRepresentation>>& cs, const std::shared_ptr<Geom3Surface>& s1, const std::shared_ptr<Geom3Surface>& s2, const TopoLocation& l1, const TopoLocation& l2, ContinuityType c);
	static void UpdatePoints(std::list<std::shared_ptr<PointRepresentation>>& ps, double p, const std::shared_ptr<Geom3Curve>& c, const TopoLocation& l);
	static void UpdatePoints(std::list<std::shared_ptr<PointRepresentation>>& ps, double p, const std::shared_ptr<Geom2Curve>& pc, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l);
	static void UpdatePoints(std::list<std::shared_ptr<PointRepresentation>>& ps, double p1, double p2, const std::shared_ptr<Geom3Surface>& s, const TopoLocation& l);
};
} // namespace AMCAX
