/// @file      NMBlock.hpp
/// @brief     Class of NextMesh Block
/// @details   Operations related to generated block-structured mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
/// All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <nextmesh/BlockMacros.hpp>
#include <vector>

namespace AMCAX {
namespace NextMesh {

class HyperBlock;

/// @brief Class of Block in NextMesh
class NMBlock
{
private:
	NMBlock()                           = default;
	AMCAX_API ~NMBlock()                = default;
	NMBlock(const NMBlock &other)       = delete;
	NMBlock &operator=(const NMBlock &) = delete;

public:
	// Init

	/// @brief Initializes the NMBlock with bounding box from the geometric model.
	AMCAX_API void Init();

	// Edit

	/// @brief Splits an edge at specified ratios.
	/// @param[in] eid Index of the edge to split.
	/// @param[in] ratios Vector of ratio values (0.0 to 1.0) defining split
	/// positions along the edge.
	AMCAX_API void SplitEdge(const Indext eid, const std::vector<double> &ratios);

	/// @brief Splits an edge by projecting a point onto it.
	/// @param[in] eid Index of the edge to split.
	/// @param[in] pos 3D point whose projection determines the split location on
	/// the edge.
	/// @param[in] tol Tolerance for ratio value (0.0 to 1.0) defining the split
	/// position of projection point.
	AMCAX_API void SplitEdgeByProject(const Indext eid, const NMPoint3 &pos,
	                                  double tol = 1e-2);

	/// @brief Splits an edge into uniform segments.
	/// @param[in] eid Index of the edge to split.
	/// @param[in] segNum Number of uniform segments to create.
	AMCAX_API void SplitEdgeUniform(const Indext eid, const Indext segNum);

#ifdef INTERNAL_TEST
	/// @brief Cuts two edges in the same face at specified ratios.
	/// @param[in] eid1 Index of the first edge to cut.
	/// @param[in] ratioInEid1 Ratio along the first edge where the cut should be
	/// made.
	/// @param[in] eid2 Index of the second edge to cut.
	/// @param[in] ratioInEid2 Ratio along the second edge where the cut should be
	/// made.
	/// @return Returns true if the cut operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool CutTwoEdgeInSameFace(const Indext  eid1,
	                                    const double &ratioInEid1,
	                                    const Indext  eid2,
	                                    const double &ratioInEid2);
#endif

	/// @brief Performs offset split on specified hexes and faces.
	/// @param[in] hids Vector of hex element indices to split.
	/// @param[in] fids Vector of face indices to use for splitting.
	/// @param[in] offset Offset distance for the split operation.
	AMCAX_API void OSplit(const std::vector<Indext> &hids,
	                      const std::vector<Indext> &fids, const double &offset);

	/// @brief Joins hex elements along specified faces.
	/// @param[in] fids Vector of face indices where hex elements should be
	/// joined.
	/// @return Returns true if the join operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool JoinHex(const std::vector<Indext> &fids);

	/// @brief Deletes specified hex elements.
	/// @param[in] hids Vector of hex element indices to delete.
	AMCAX_API void DeleteHex(const std::vector<Indext> &hids);

	// Associate

	/// @brief Associates vertices with geometric entities.
	/// @param[in] vids Vector of vertex indices to associate.
	/// @param[in] dim Dimension of the geometric entities.
	/// @param[in] NMEnts Vector of geometric entities to associate with the
	/// vertices.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input vertices.
	/// @return Returns true if the association is successful; otherwise, returns
	/// false.
	AMCAX_API bool AssociateVertex(const std::vector<Indext> &vids, DimType dim,
	                               const std::vector<NMEntity> &NMEnts,
	                               bool translate = false);

    /// @brief Associates control nodes with geometric entities.
	/// @param[in] cids Vector of control node indices to associate.
	/// @param[in] dim Dimension of the geometric entities.
	/// @param[in] NMEnts Vector of geometric entities to associate with the
	/// control nodes.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes located on the same edge as the input control nodes.
	/// @return Returns true if the association is successful; otherwise, returns
	/// false.
	AMCAX_API bool AssociateCtrlNode(const std::vector<Indext> &cids, DimType dim,
	                                 const std::vector<NMEntity> &NMEnts,
	                                 bool translate = false);

	/// @brief Associates edges with geometric entities.
	/// @param[in] eids Vector of edge indices to associate.
	/// @param[in] dim Dimension of the geometric entities.
	/// @param[in] NMEnts Vector of geometric entities to associate with the
	/// edges.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input edges.
	/// @return Returns true if the association is successful; otherwise, returns
	/// false.
	AMCAX_API bool AssociateEdge(const std::vector<Indext> &eids, DimType dim,
	                             const std::vector<NMEntity> &NMEnts,
	                             bool                         translate = false);

	/// @brief Associates faces with geometric entities.
	/// @param[in] fids Vector of face indices to associate.
	/// @param[in] NMEnts Vector of geometric entities to associate with the
	/// faces.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input faces.
	/// @return Returns true if the association is successful; otherwise, returns
	/// false.
	AMCAX_API bool AssociateFace(const std::vector<Indext>   &fids,
	                             const std::vector<NMEntity> &NMEnts,
	                             bool                         translate = false);

	// Disassociate

	/// @brief Disassociates specified vertices from geometric entities.
	/// @param[in] vids Vector of vertex indices to disassociate.
	/// @return Returns true if the disassociation is successful; otherwise,
	/// returns false.
	AMCAX_API bool DisassociateVertex(const std::vector<Indext> &vids);

	/// @brief Disassociates specified edges from geometric entities.
	/// @param[in] eids Vector of edge indices to disassociate.
	/// @return Returns true if the disassociation is successful; otherwise,
	/// returns false.
	AMCAX_API bool DisassociateEdge(const std::vector<Indext> &eids);

	/// @brief Disassociates specified faces from geometric entities.
	/// @param[in] fids Vector of face indices to disassociate.
	/// @return Returns true if the disassociation is successful; otherwise,
	/// returns false.
	AMCAX_API bool DisassociateFace(const std::vector<Indext> &fids);

    // Control Node

	/// @brief Preview the generated control node at a given position.
	/// @param[in] pos 3D position where the control node should be generated.
	/// @param[out] cNode The generated control node.
	/// @return Returns true if the preview is successful; otherwise, returns
	/// false.
	AMCAX_API bool PreviewSingleCtrlNode(const NMPoint3 &pos, CtrlNode &cNode);

	/// @brief Preview the control nodes generated from the projection point of
	/// the geometric point on the edge.
	/// @param eid Edge index where control nodes should be generated.
	/// @param NMEnts Vector of geometric entities used for projection.
	/// @param cNodes Vector of generated control nodes.
	/// @return Returns true if the preview is successful; otherwise, returns
	/// false.
	AMCAX_API bool PreviewProjectCtrlNode(const Indext                 eid,
	                                      const std::vector<NMEntity> &NMEnts,
	                                      std::vector<CtrlNode>       &cNodes);

	/// @brief Preview the specified number of control nodes generated on the
	/// edge.
	/// @param eid Edge index where control nodes should be generated.
	/// @param num Number of control nodes to preview.
	/// @param cNodes Vector of generated control nodes.
	/// @return Returns true if the preview is successful; otherwise, returns
	/// false.
	AMCAX_API bool PreviewNumberCtrlNode(const Indext eid, const unsigned num,
	                                     std::vector<CtrlNode> &cNodes);

	/// @brief Preview the control nodes generated with isometric spacing on the
	/// edge.
	/// @param eid Edge index where control nodes should be generated.
	/// @param cNodes Vector of generated control nodes.
	/// @return Returns true if the preview is successful; otherwise, returns
	/// false.
	AMCAX_API bool PreviewIsoSpaceCtrlNode(const Indext           eid,
	                                       std::vector<CtrlNode> &cNodes);

	/// @brief Adds control nodes to an edge.
	/// @param eid Edge index where control nodes should be added.
	/// @param cNodes Vector of control nodes to add.
	/// @return Returns true if the control nodes are successfully added;
	/// otherwise, returns false.
	AMCAX_API bool AddCtrlNodesToEdge(const Indext                 eid,
	                                  const std::vector<CtrlNode> &cNodes);

	/// @brief Replace control nodes on an edge.
	/// @param eid Edge index where control nodes should be modified.
	/// @param cNodes Vector of control nodes to replace the old control nodes.
	/// @return Returns true if the control nodes are successfully modified;
	/// otherwise, returns false.
	AMCAX_API bool ReplaceEdgeCtrlNodes(const Indext                 eid,
	                                    const std::vector<CtrlNode> &cNodes);

	/// @brief Removes specified control nodes.
	/// @param[in] cids Vector of control node indices to erase.
	/// @return Returns true if the control nodes are successfully erased;
	/// otherwise, returns false.
	AMCAX_API bool EraseCtrlNodes(const std::vector<Indext> &cids);

	// Projection

	/// @brief Projects nodes onto geometric entities.
	/// @param[in] nids Vector of node indices to project.
	/// @param[in] type Type of the nodes to project.
	/// @param[in] dim Dimension of the geometric entities.
	/// @param[in] NMEnts Vector of geometric entities to project the nodes onto.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes located on the same edge as the input control nodes.
	/// @return Returns true if the projection is successful; otherwise, returns
	/// false.
	AMCAX_API bool ProjectNode(const std::vector<Indext> &nids, NodeType type,
	                           DimType dim, const std::vector<NMEntity> &NMEnts,
	                           bool translate = false);

	/// @brief Projects edges onto geometric entities.
	/// @param[in] eids Vector of edge indices to project.
	/// @param[in] dim Dimension of the geometric entities.
	/// @param[in] NMEnts Vector of geometric entities to project the edges onto.
	/// @param[in] translate Flag indicating whether to translate the control nodes 
	/// on the edges adjacent to input edges.
	/// @return Returns true if the projection is successful; otherwise, returns
	/// false.
	AMCAX_API bool ProjectEdge(const std::vector<Indext> &eids, DimType dim,
	                           const std::vector<NMEntity> &NMEnts,
	                           bool                         translate = false);

	// Move

	/// @brief Moves nodes in a specified direction.
	/// @param[in] nids Vector of node indices to move.
	/// @param[in] type Type of the nodes to move.
	/// @param[in] dir Direction vector for moving the nodes.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input vertices.
	/// @return Returns true if the nodes are successfully moved; otherwise,
	/// returns false.
	AMCAX_API bool MoveNodes(const std::vector<Indext> &nids, NodeType type,
	                         const NMVector3 &dir, bool translate = false);

	/// @brief Moves edges in a specified direction.
	/// @param[in] eids Vector of edge indices to move.
	/// @param[in] dir Direction vector for moving the edges.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input edges.
	/// @return Returns true if the edges are successfully moved; otherwise,
	/// returns false.
	AMCAX_API bool MoveEdges(const std::vector<Indext> &eids,
	                         const NMVector3 &dir, bool translate = false);

	/// @brief Moves faces in a specified direction.
	/// @param[in] fids Vector of face indices to move.
	/// @param[in] dir Direction vector for moving the faces.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input faces.
	/// @return Returns true if the faces are successfully moved; otherwise,
	/// returns false.
	AMCAX_API bool MoveFaces(const std::vector<Indext> &fids,
	                         const NMVector3 &dir, bool translate = false);

	// Edge match

	/// @brief Matches source edges to target edges.
	/// @param[in] sourceEIds Vector of source edge indices to match.
	/// @param[in] targetEIds Vector of target edge indices to match against.
	/// @param[in] matchFactor Factor controlling the degree of matching.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input edges.
	/// @return Returns true if the edge matching is successful; otherwise,
	/// returns false.
	AMCAX_API bool MatchEdgeToEdge(const std::vector<Indext> &sourceEIds,
	                               const std::vector<Indext> &targetEIds,
	                               double matchFactor, bool translate = false);

	/// @brief Matches edges to curves.
	/// @param[in] sourceEIds Vector of edge indices to match.
	/// @param[in] NMEnts Vector of curve entities to match against.
	/// @param[in] matchFactor Factor controlling the degree of matching.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input edges.
	/// @return Returns true if the edge-to-curve matching is successful;
	/// otherwise, returns false.
	AMCAX_API bool MatchEdgeToCurve(const std::vector<Indext>   &sourceEIds,
	                                const std::vector<NMEntity> &NMEnts,
	                                double matchFactor, bool translate = false);

	/// @brief Matches edges to points.
	/// @param[in] sourceEIds Vector of edge indices to match.
	/// @param[in] NMEnts Vector of point entities to match against.
	/// @param[in] matchFactor Factor controlling the degree of matching.
	/// @param[in] translate Flag indicating whether to translate the control
	/// nodes on the edges adjacent to input edges.
	/// @return Returns true if the edge-to-point matching is successful;
	/// otherwise, returns false.
	AMCAX_API bool MatchEdgeToPoints(const std::vector<Indext>   &sourceEIds,
	                                 const std::vector<NMEntity> &NMEnts,
	                                 double matchFactor, bool translate = false);

	// Distribution

	/// @brief Sets the point distribution along edges.
	/// @param[in] eids Vector of edge indices to configure.
	/// @param[in] param Spacing parameters defining the distribution.
	/// @return Returns true if the distribution is successfully set; otherwise,
	/// returns false.
	AMCAX_API bool SetEdgesDistribution(const std::vector<Indext> &eids,
	                                    const SpacingParam        &param);

	/// @brief Reverts edges to their original distribution.
	/// @param[in] eids Vector of edge indices to revert.
	/// @param[in] parallel Flag indicating whether to process edges in parallel.
	/// @return Returns true if the distribution is successfully reverted;
	/// otherwise, returns false.
	AMCAX_API bool RevertEdgesDistribution(const std::vector<Indext> &eids,
	                                       bool parallel = false);

	// Discrete

	/// @brief Discretizes all hyper faces into mesh elements.
	/// @return Returns true if the discretization is successful; otherwise,
	/// returns false.
	AMCAX_API bool DiscreteHyperFaces();

	/// @brief Discretizes specified faces.
	/// @param[in] fids Vector of face indices to discretize.
	/// @return Returns true if the discretization is successful; otherwise,
	/// returns false.
	AMCAX_API bool DiscreteFace(const std::vector<Indext> &fids);

	/// @brief Discretizes the entire hyper block.
	/// @return Returns true if the discretization is successful; otherwise,
	/// returns false.
	AMCAX_API bool DiscreteHyperBlock();

	/// @brief Discretizes specified blocks.
	/// @param[in] hids Vector of block indices to discretize.
	/// @return Returns true if the discretization is successful; otherwise,
	/// returns false.
	AMCAX_API bool DiscreteBlock(const std::vector<Indext> &hids);

	// Smooth

	/// @brief Smooths faces according to specified parameters.
	/// @param[in,out] param Smoothing parameters controlling the smoothing
	/// process.
	/// @return Returns true if the smoothing is successful; otherwise, returns
	/// false.
	AMCAX_API bool SmoothFaces(SmoothParam &param);

	/// @brief Smooths blocks according to specified parameters.
	/// @param[in,out] param Smoothing parameters controlling the smoothing
	/// process.
	/// @return Returns true if the smoothing is successful; otherwise, returns
	/// false.
	AMCAX_API bool SmoothBlocks(SmoothParam &param);

	// Query Data

	/// @brief Gets the total number of vertices.
	/// @return Number of vertices.
	AMCAX_API Indext GetVertexCount();

	/// @brief Gets the total number of edges.
	/// @return Number of edges.
	AMCAX_API Indext GetEdgeCount();

	/// @brief Gets the total number of faces.
	/// @return Number of faces.
	AMCAX_API Indext GetFaceCount();

	/// @brief Gets the total number of blocks.
	/// @return Number of blocks.
	AMCAX_API Indext GetBlockCount();

	// Topology connectivity queries

	/// @brief Gets vertices of an edge.
	/// @param[in] eid Index of the edge.
	/// @param[out] vids Vector to store the vertex indices.
	AMCAX_API void GetEdgeVertexs(Indext eid, std::vector<Indext> &vids);

	/// @brief Gets vertices of a face.
	/// @param[in] fid Index of the face.
	/// @param[out] vids Vector to store the vertex indices.
	AMCAX_API void GetFaceVertexs(Indext fid, std::vector<Indext> &vids);

	/// @brief Gets vertices of a block.
	/// @param[in] hid Index of the block.
	/// @param[out] vids Vector to store the vertex indices.
	AMCAX_API void GetBlockVertexs(Indext hid, std::vector<Indext> &vids);

	/// @brief Gets edges of a face.
	/// @param[in] fid Index of the face.
	/// @param[out] eids Vector to store the edge indices.
	AMCAX_API void GetFaceEdges(Indext fid, std::vector<Indext> &eids);

	/// @brief Gets edges of a block.
	/// @param[in] hid Index of the block.
	/// @param[out] eids Vector to store the edge indices.
	AMCAX_API void GetBlockEdges(Indext hid, std::vector<Indext> &eids);

	/// @brief Gets faces of a block.
	/// @param[in] hid Index of the block.
	/// @param[out] fids Vector to store the face indices.
	AMCAX_API void GetBlockFaces(Indext hid, std::vector<Indext> &fids);

	// Geometric representation queries

	/// @brief Gets the geometric position of a vertex.
	/// @param[in] vid Index of the vertex.
	/// @param[out] pos 3D position of the vertex.
	AMCAX_API void GetVertexRepresentation(Indext vid, NMPoint3 &pos);

	/// @brief Gets the geometric representation of an edge.
	/// @param[in] eid Index of the edge.
	/// @param[out] edgesPnts Vector to store the edge points.
	AMCAX_API void GetEdgeRepresentation(Indext                 eid,
	                                     std::vector<NMPoint3> &edgesPnts);

	/// @brief Gets the geometric representation of a face.
	/// @param[in] fid Index of the face.
	/// @param[out] meshPnts Vector to store the mesh points.
	/// @param[out] meshfvs Vector to store the triangular face-vertex
	/// connectivity.
	AMCAX_API void
	GetFaceRepresentation(Indext fid, std::vector<NMPoint3> &meshPnts,
	                      std::vector<std::array<Indext, 3>> &meshfvs);

	// Mesh connectivity queries

	/// @brief Gets all mesh nodes.
	/// @param[out] meshPnts Vector to store all mesh node coordinates.
	AMCAX_API void GetAllMeshNodes(std::vector<NMPoint3> &meshPnts);

	/// @brief Gets mesh connectivity for an edge.
	/// @param[in] eid Index of the edge.
	/// @param[out] mlines Vector to store line element connectivity (node pairs).
	AMCAX_API void GetEdgeMesh(Indext                              eid,
	                           std::vector<std::array<Indext, 2>> &mlines);

	/// @brief Gets mesh connectivity for a face.
	/// @param[in] fid Index of the face.
	/// @param[out] mquads Vector to store quadrilateral element connectivity (4
	/// nodes per quad).
	AMCAX_API void GetFaceMesh(Indext                              fid,
	                           std::vector<std::array<Indext, 4>> &mquads);

	/// @brief Gets mesh connectivity for a block.
	/// @param[in] hid Index of the block.
	/// @param[out] mhexs Vector to store hexahedral element connectivity (8 nodes
	/// per hex).
	AMCAX_API void GetBlockMesh(Indext                              hid,
	                            std::vector<std::array<Indext, 8>> &mhexs);

	// Control nodes queries

	/// @brief Gets all control nodes.
	/// @param[out] cNodes Vector to store all control nodes.
	AMCAX_API void GetAllCtrlNodes(std::vector<CtrlNode> &cNodes);

	/// @brief Gets control nodes of an edge.
	/// @param[in] eid Index of the edge.
	/// @param[out] cNodes Vector to store control nodes.
	AMCAX_API void GetEdgeCtrlNodes(Indext eid, std::vector<CtrlNode> &cNodes);

#ifdef INTERNAL_TEST
	// Write Data

	/// @brief Writes edge data to VTK format.
	/// @param[in] filename Output VTK filename.
	/// @return Returns true if the write operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool WriteEdgeToVTK(const std::string &filename);

	/// @brief Writes mesh vertices to VTK format.
	/// @param[in] filename Output VTK filename.
	/// @return Returns true if the write operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool WriteMeshVertToVTK(const std::string &filename);

	/// @brief Writes mesh lines to VTK format.
	/// @param[in] filename Output VTK filename.
	/// @return Returns true if the write operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool WriteMeshLineToVTK(const std::string &filename);

	/// @brief Writes mesh quadrilaterals to VTK format.
	/// @param[in] filename Output VTK filename.
	/// @return Returns true if the write operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool WriteMeshQuadToVTK(const std::string &filename);

	/// @brief Writes mesh hexahedra to VTK format.
	/// @param[in] filename Output VTK filename.
	/// @return Returns true if the write operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool WriteMeshHexToVTK(const std::string &filename);

	/// @brief Writes the inner mesh of a specified block to VTK format.
	/// @param[in] hid The ID of the block from which to get mesh connectivity.
	/// @param[in] filename Output VTK filename.
	/// @return Returns true if the write operation is successful; otherwise,
	/// returns false.
	AMCAX_API bool WriteBlockInnerMeshHexToVTK(Indext             hid,
	                                           const std::string &filename);
#endif

private:
	/// @brief Gets the singleton instance of NMBlock.
	/// @param[in] model Pointer to the geometric model.
	/// @return Shared pointer to the NMBlock instance.
	AMCAX_API static NMBlock &GetInstance();

private:
	std::shared_ptr<HyperBlock> m_hb = nullptr;
	friend class NMAPIModel;
};

} // namespace NextMesh
} // namespace AMCAX
