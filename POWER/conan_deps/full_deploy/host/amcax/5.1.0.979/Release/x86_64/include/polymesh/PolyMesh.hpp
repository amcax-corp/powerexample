/// @file      PolyMesh.hpp
/// @brief     Class of PolyMesh structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/PointT.hpp>

namespace AMCAX
{
namespace SubD
{
class MVert;
class MEdge;
class MPolyFace;
class MHalfedge;
class PMeshImage;

/// @brief Class of PolyMesh structure
/// The Low Level API functions are not exported for this version
class PolyMesh
{
public:
	typedef typename std::vector<MVert*>::iterator VertexIter;
	typedef typename std::vector<MEdge*>::iterator EdgeIter;
	typedef typename std::vector<MHalfedge*>::iterator HalfEdgeIter;
	typedef typename std::vector<MPolyFace*>::iterator FaceIter;
	typedef typename std::vector<MVert*>::const_iterator CVertexIter;
	typedef typename std::vector<MEdge*>::const_iterator CEdgeIter;
	typedef typename std::vector<MHalfedge*>::const_iterator CHalfEdgeIter;
	typedef typename std::vector<MPolyFace*>::const_iterator CFaceIter;

public:
	AMCAX_API PolyMesh();
	AMCAX_API ~PolyMesh();

public:
	//=====================================================================
	// Get Method
	//=====================================================================
	AMCAX_API size_t numVertices() const;
	AMCAX_API size_t numEdges() const;
	AMCAX_API size_t numPolygons() const;
	AMCAX_API size_t numHalfEdges() const;

	AMCAX_API bool isEmpty() const;

	AMCAX_API void clear();

#ifndef DOXYGEN_SKIP

	//=====================================================================
	// Low Level API - Base and Iterators
	//=====================================================================
	MVert* vert(const size_t id);
	MEdge* edge(const size_t id);
	MPolyFace* polyface(const size_t id);
	MHalfedge* halfedge(const size_t id);

	const MVert* vert(const size_t id) const;
	const MEdge* edge(const size_t id) const;
	const MPolyFace* polyface(const size_t id) const;
	const MHalfedge* halfedge(const size_t id) const;

	VertexIter vertices_begin();
	VertexIter vertices_end();
	EdgeIter edges_begin();
	EdgeIter edges_end();
	HalfEdgeIter halfedge_begin();
	HalfEdgeIter halfedge_end();
	FaceIter polyfaces_begin();
	FaceIter polyfaces_end();

	CVertexIter const_vertices_begin() const;
	CVertexIter const_vertices_end() const;
	CEdgeIter const_edges_begin() const;
	CEdgeIter const_edges_end() const;
	CHalfEdgeIter const_halfedge_begin() const;
	CHalfEdgeIter const_halfedge_end() const;
	CFaceIter const_polyfaces_begin() const;
	CFaceIter const_polyfaces_end() const;

	//=====================================================================
	// Low Level API - Traverse Method
	//=====================================================================
	/// return the mesh one boundary vertices in order, with input edge;
	std::vector<MVert*> boundaryVertices(MEdge* edge);

	bool isBoundary(const MVert* vert) const;
	bool isBoundary(const MEdge* edge) const;
	bool isBoundary(const MHalfedge* halfedge) const;

	std::vector<MVert*> vertAdjacentVertices(MVert* vert) const;
	std::vector<MEdge*> vertAdjacentEdge(MVert* vert) const;
	std::vector<MHalfedge*> vertAdjacentHalfEdge(MVert* vert) const;
	std::vector<MPolyFace*> vertAdjacentPolygon(MVert* vert) const;
	std::vector<MPolyFace*> edgeAdjacentPolygon(MEdge* edge) const;
	std::vector<MPolyFace*> polygonAdjacentPolygon(MPolyFace* face) const;
	std::vector<MVert*> polygonVertices(MPolyFace* face) const;
	std::vector<MHalfedge*> polygonHalfedges(MPolyFace* face) const;
	std::vector<MEdge*> polygonEdges(MPolyFace* face) const;

	MEdge* edgeBetween(MVert* v0, MVert* v1);

	bool isConnected(MVert* v0, MVert* v1);

	MHalfedge* faceHalfEdgeFromVert(MPolyFace* face, MVert* vert);

	size_t valence(MVert* vert) const;

	bool isIsolated(MVert* vert) const;
	bool isIsolated(MEdge* edge) const;
	bool isIsolated(MPolyFace* face) const;

	bool isTriangleMesh() const;

	//=====================================================================
	// Low Level API - Base Topology
	//=====================================================================
	void reserveMemory(size_t nv, size_t nf);

	MVert* newVertex();
	MEdge* newEdge();
	MEdge* newEdge(MVert* v1, MVert* v2);
	MHalfedge* newHalfEdge();
	MPolyFace* newPolyFace();

	MVert* addVertex(const Point3& point);

	/// Juat add an edge and two opposite halfedges. The two halfedge are connected end to end.
	/// it will set the halfedge vertex but it will not set vert halfedge.
	/// Be careful when using this function
	MEdge* addEdge(MVert* v_begin, MVert* v_end);

	/// add a face by given vertices, it will not detect duplicate face
	MPolyFace* addPolyFace(std::vector<size_t>& v_loop_id);
	MPolyFace* addPolyFace(std::vector<MVert*>& v_loop);

	void deleteVertex(MVert* vert);
	void deleteEdges(MEdge* edge);
	void deletePolyFace(MPolyFace* face);

	size_t delete_isolated_vertices();
	size_t delete_isolated_edges();

	void deleteMultipleVerttex(std::vector<MVert*>& vert_list);
	void deleteMultipleEdge(std::vector<MEdge*> edge_list);
	void deleteMultiplePolyFace(std::vector<MPolyFace*> face_list);

	void deleteMultiplePolyFaceOnly(std::vector<MPolyFace*> face_list);

	//=====================================================================
	// Low Level API - MeshBasedMethod
	//=====================================================================
	/// Reverse all halfedge of a mesh
	void reverse_mesh();

	void updateMeshNormal();

	/// Insert a point in the middle of an edge, only split the edge into two edges
	MVert* splitEdgeMakeVertex(MEdge* edge);

	/// Delete the vertex with a degree of 2 that is not a boundary, leaving an edge connecting the two neighbors of the vertex.
	MEdge* jointEdgeRemoveVertex(MVert* vert);

	/// connect two unconnected vertices v0/v1 in face, creat a edge divide face into two polygonal faces
	MEdge* splitFaceMakeEdge(MPolyFace* face, MVert* v0, MVert* v1);

	/// split a polygon completely into triangles
	void splitNGonTriangle(MPolyFace* face);

	/// Split an edge and divide the adjacent faces into multiple triangles
	MVert* splitEdgeSplitPolygon(MEdge* edge);

	bool is_collapse_ok(MHalfedge* he);

	/// the collapse function for polygon mesh, the from vert will be delete
	void collapse(MHalfedge* he);

	/// Combine two adjacent faces of an edge into one face
	/// The input edge is the only intersection edge of two adjacent faces. No vertices will be deleted
	/// +-----+        +-----+
	/// |     |        |     |
	/// +-----+   ->   +     +
	/// |     |        |     |
	/// +-----+        +-----+
	MPolyFace* jointFaceRemoveEdge(MEdge* edge);

	/// Merge two edges into one edge, use jointEdgeRemoveVertex
	MEdge* mergeEdge(MEdge* edge0, MEdge* edge1);

	/// Merge two faces into one face, use jointFaceRemoveEdge
	MPolyFace* mergeFace(MPolyFace* f0, MPolyFace* f1);

	/// weld two vertex to one vertex
	bool weldVertex(MVert* v_ori, MVert* v_tar, double tolerance = 1e-2);

	/// weld two edge to one edge
	bool weldEdge(MEdge* e0, MEdge* e1, double tolerance = 1e-2); // it will deleat e0;

	/// separate a single vert, Add vertex the number of manifold subregions -1
	bool separateSingleVert(MVert* vert);

	/// separate a single edge, it will add a new edge
	bool separateSingleEdge(MEdge* edge);

	Point3 calculatFaceCenter(MPolyFace* face);

	Point3 calculatEdgeCenter(MEdge* edge);

	//=====================================================================
	// Low Level API - Triangle Mesh API
	//=====================================================================
	bool is_flip_ok_Triangle(MEdge* edge);

	void flipEdgeTriangle(MEdge* edge);

	bool is_collapse_ok_Triangle(MHalfedge* he);

	/// collapse edge from vertex to edge to vertex, the from vertex will be delete
	void collapseTriangle(MHalfedge* he);

	MVert* splitEdgeTriangle(MEdge* edge);

public:
	PMeshImage* GetBaseMesh() const;

#endif

private:
	PMeshImage* baseMesh_ = nullptr;
};

} // namespace SubD
} // namespace AMCAX