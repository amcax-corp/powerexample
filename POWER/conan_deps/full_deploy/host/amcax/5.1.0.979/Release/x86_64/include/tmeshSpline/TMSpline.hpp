/// @file      TMSpline.hpp
/// @brief     Class of TMSpline structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/VectorT.hpp>
#include <tmeshSpline/TMSplineMacros.hpp>

namespace AMCAX
{
namespace TMS
{
class TCVert;
class TCEdge;
class TCLink;
class TCFace;
typedef TCVert TVert;
typedef TCEdge TEdge;
typedef TCLink TLink;
typedef TCFace TFace;

class TControl;
class TSplineUnstructured;

/// @brief Class of TMSpline structure
/// The Low Level API functions are not exported for this version
class TMSpline
{
public:
	typedef typename std::vector<TVert*>::iterator VertexIter;
	typedef typename std::vector<TEdge*>::iterator EdgeIter;
	typedef typename std::vector<TLink*>::iterator LinkIter;
	typedef typename std::vector<TFace*>::iterator FaceIter;
	typedef typename std::vector<TVert*>::const_iterator CVertexIter;
	typedef typename std::vector<TEdge*>::const_iterator CEdgeIter;
	typedef typename std::vector<TLink*>::const_iterator CLinkIter;
	typedef typename std::vector<TFace*>::const_iterator CFaceIter;

public:
	/// @brief Empty Constructor
	AMCAX_API TMSpline();

	AMCAX_API ~TMSpline();

	/// @brief Return The number of control mesh vertices
	AMCAX_API size_t numVertices() const;
	/// @brief Return The number of control mesh edges
	AMCAX_API size_t numEdges() const;
	/// @brief Return The number of control mesh Faces
	AMCAX_API size_t numFaces() const;
	/// @brief Return The number of control mesh HalfEdges
	AMCAX_API size_t numHalfEdges() const;

	/// @brief Return True if The TMSpline is empty
	AMCAX_API bool isEmpty() const;

	/// @brief Clear the TMSpline
	AMCAX_API void clear();

#ifndef DOXYGEN_SKIP

	//=====================================================================
	// Low Level API - Base
	//=====================================================================
	TVert* vert(const size_t id);
	TEdge* edge(const size_t id);
	TFace* polyface(const size_t id);
	TLink* halfedge(const size_t id);

	const TVert* vert(const size_t id) const;
	const TEdge* edge(const size_t id) const;
	const TFace* polyface(const size_t id) const;
	const TLink* halfedge(const size_t id) const;

	VertexIter vertices_begin();
	VertexIter vertices_end();
	EdgeIter edges_begin();
	EdgeIter edges_end();
	LinkIter halfedge_begin();
	LinkIter halfedge_end();
	FaceIter faces_begin();
	FaceIter faces_end();

	CVertexIter const_vertices_begin() const;
	CVertexIter const_vertices_end() const;
	CEdgeIter const_edges_begin() const;
	CEdgeIter const_edges_end() const;
	CLinkIter const_halfedge_begin() const;
	CLinkIter const_halfedge_end() const;
	CFaceIter const_faces_begin() const;
	CFaceIter const_faces_end() const;

public:
	//=====================================================================
	// Low Level API - Check
	//=====================================================================
	bool isBoundary(const TVert* vert) const;
	bool isBoundary(const TEdge* edge) const;
	bool isBoundary(const TLink* halfedge) const;

	bool isConnected(TVert* v0, TVert* v1);
	bool isConnected(TEdge* e0, TEdge* e1);

	bool isFaceContainsVertices(TFace* face, TVert* vert);
	bool isFaceContainsEdges(TFace* face, TEdge* edge);

	bool isIsolated(TVert* vert) const;
	bool isIsolated(TEdge* edge) const;
	bool isIsolated(TFace* face) const;

	//=====================================================================
	// Low Level API - Traveling
	//=====================================================================
	/// return the mesh one boundary vertices in order, with input edge;
	std::vector<TVert*> boundaryVertices(TEdge* edge);

	std::vector<TVert*> vertAdjacentVertices(TVert* vert) const;
	std::vector<TEdge*> vertAdjacentEdge(TVert* vert) const;
	std::vector<TLink*> vertAdjacentHalfEdge(TVert* vert) const;
	std::vector<TFace*> vertAdjacentPolygon(TVert* vert) const;

	std::vector<TFace*> edgeAdjacentPolygon(TEdge* edge) const;

	std::vector<TFace*> polygonAdjacentPolygon(TFace* face) const;
	std::vector<TVert*> polygonVertices(TFace* face) const;
	std::vector<TLink*> polygonHalfedges(TFace* face) const;
	std::vector<TEdge*> polygonEdges(TFace* face) const;

	//=====================================================================
	// Low Level API - Base Topology add Method, Only change the topology, not compute the spline
	//=====================================================================
	void reserveMemory(size_t nv, size_t nf = -1);

	TVert* addVertex(const TParam& param);
	TVert* addVertex(const Point3& point);
	TVert* addVertex(const TParam& param, const Point3& point);
	TVert* addVertex(double x, double y)
	{
		return addVertex(TParam(x, y));
	}
	TVert* addVertex(double x, double y, double z)
	{
		return addVertex(Point3(x, y, z));
	}

	/// Juat add an edge and two opposite halfedges. The two halfedge are connected end to end.
	/// it will set the halfedge vertex but it will not set vert halfedge.
	/// Be careful when using this function
	TEdge* addEdge(TVert* v_begin, TVert* v_end);

	/// add a face by given vertices, it will not detect duplicate face
	/// the is_control_only = true, only add face to control polygon, must use rebulid to get final T-spline before use it.
	TFace* addPolyFace(std::vector<size_t>& v_loop_id, bool is_control_only = false);

	TEdge* edgeBetween(TVert* v0, TVert* v1);

	TLink* halfedgeBetween(TVert* v0, TVert* v1);

public:
	//=====================================================================
	// Low Level API - control delete, use for topology method, After use it, must call rebulit;
	//=====================================================================
	void deleteMultiplePolyFaceOnly_Control(std::vector<TFace*> face_list);

	void deleteMultipleEdges_Control(std::vector<TEdge*> edge_list);
	void deleteMultipleFaces_Control(std::vector<TFace*> face_list);

	bool can_removeVertexEasy_Control(TVert* v);
	bool removeVertexRedundancy_Control(TVert* v);
	void deleteIsolatedElement_Control();

	//=====================================================================
	// Low Level API - Really delete, must care topology and type;
	//=====================================================================
	void deleteVertex(TVert* vert);
	void deleteEdges(TEdge* edge);
	void deletePolyFace(TFace* face);

public:
	//=====================================================================
	// Low Level API - Base Set and ChangMethod
	//=====================================================================
	void setVertControl(TVert* v, const Point3& newControl, double widget = 1.0);

	void setVertType(TVert* v, const TMVType& type);
	void setLinktype(TLink* he, const TMLType& type);
	// only used set the edge paramlength = -1;
	void setEdgeParamLength(TEdge* e, double length);

	void updateVerticesType(bool only_update_control = false);

	TMVType getVertType(TVert* v) const;
	TMLType getLinkType(TLink* he) const;

	// used in TMSplineCopy
	void swapEdgeLink(TEdge* e);
	void swapFaceLink(TFace* f, TLink* he);

	// used in TO_Add
	bool isNeedRebuild(TFace* f);

	// crease, after set, must call rebulit
	void addEdgeCrease(TEdge* e);
	void removeEdgeCrease(TEdge* e);

	//=====================================================================
	// Low Level API - Base Information get Method
	//=====================================================================
	Point3 getFaceCenter(size_t s_id) const;
	Point3 getFaceCenterWithoutT(size_t s_id) const;
	Point3 getEdgeCenter(size_t s_id) const;

	void getFaceBoundingBox(Point3& bb_min, Point3& bb_max, size_t s_id) const;
	void getEdgeBoundingBox(Point3& bb_min, Point3& bb_max, size_t s_id) const;
	void getVertBoundingBox(Point3& bb_min, Point3& bb_max, size_t s_id) const;

	//=====================================================================
	// Low Level API - MeshBasedMethod
	//=====================================================================
	void updateNormals();
	/// Reverse all halfedge of a mesh
	void reverseNormal();

	//=====================================================================
	// Low Level API - Tspline Inline method
	//=====================================================================
public:
	void inlineParamLengthOne();
	void inlineParamLengthWithVertParam();

	void inlineTypeNormal();

	void inlineTSpline();
	void inlineTSplineAfterParamAndType();
	void inlineTSplineWithRepairTopology(); // it also need set param and type

	//=====================================================================
	// Low Level API - Update TMesh Infomation Method
	//=====================================================================
public:
	void updateTSplineCompute();

	void updateBoundaryType();
	void updateAllDirection();
	void updateFaceDirection(TFace* face);

	//=====================================================================
	//	Low Level API - Tspline Rebulid Method
	//=====================================================================
public:
	void reBulidTsplineWithControl();

	// repair the spline topology; only used in spline_ == control_;
	void updateTsplineTopology();

	// try to uniform all spline param;
	bool uniformTsplineParam();

	// only use in rebulid TMS, repair control param.
	bool repairTsplineParam();

	bool repairTsplineTJunction();

public:
	//=====================================================================
	// Low Level API - Topology API
	//=====================================================================
	void separateEdge(TEdge* edge);
	// only separate control edge, be care to use it;
	void separateEdgeControlOnly(TEdge* edge);

	void weldEdgeControl(TEdge* edge0, TEdge* edge1, double tolerance = 0.01);

	// split Method
	bool isFaceCanSplitWithLink(TFace* face);

	// not used method
	void SplitFaceCross(TFace* face, const Point3& new_control);
	void splitFaceWithLink(TFace* face, TLink* he0, TLink* he1, const TParam& param, const Point3& nc0, const Point3& nc1);
	void splitEdge(TEdge* edge, const Point3& new_control);

	//=====================================================================
	//	Low Level API -	Only Control Topology API
	//=====================================================================
	void splitFaceCrossOnlyControl(TFace* face, const Point3& new_control);
	void splitFaceWithLinkOnlyControl(TFace* face, TLink* he0, TLink* he1, const TParam& param, const Point3& nc0, const Point3& nc1);

	TVert* splitEdgeOnlyControl(TEdge* edge, const Point3& new_control);
	TEdge* splitFacewithVertexOnlyControl(TFace* face, TVert* v0, TVert* v1);

	void findUpperPairInFace(TFace* face, TLink* he, TLink*& he_upper, const double& t_curr, double& t_pair);

	bool isCollapseOK(TLink* he);
	void collapseLink(TLink* he);

	bool combineTriangle(TEdge* edge);
	void revokeEdgeSplitWitVertexControl(TEdge* e);

	TControl* GetControlMesh() const;
	TSplineUnstructured* GetUnstructedMesh() const;

#endif

private:
	TControl* control_;
	TSplineUnstructured* spline_;

private:
	void cloneControlToSpline();
	void copyControlToSpline();
};

} // namespace TMS
} // namespace AMCAX
