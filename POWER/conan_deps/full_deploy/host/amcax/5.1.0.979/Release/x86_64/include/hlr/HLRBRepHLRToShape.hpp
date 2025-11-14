/// @file      HLRBRepHLRToShape.hpp
/// @brief     Class of HLR shape generation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <hlr/HLRBRepAlgorithm.hpp>
#include <hlr/HLRBRepTypeOfResultingEdge.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class HLRBRepEdgeData;
class HLRTopoOutLiner;
#endif

/// @brief Class of HLR shape generation
/// @details Extract the shapes in HLRAlgo, including the visible and hidden lines considering the Continuous order of the line
class HLRBRepHLRToShape
{
public:
	/// @brief Create HLR to shape
	/// @param A HLRAlgo
	AMCAX_API explicit HLRBRepHLRToShape(const std::shared_ptr<HLRBRepAlgorithm>& A);

	/// @brief Visible C0 (<G1) edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> VCompound(bool is3d = false);

	/// @brief Add visible C0 (<G1) edges to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> VCompound(const TopoShape& S, bool is3d = false);

	/// @brief Visible G1 (<G2) edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> Rg1LineVCompound(bool is3d = false);

	/// @brief Add visible G1 (<G2) edges to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> Rg1LineVCompound(const TopoShape& S, bool is3d = false);

	/// @brief Visible C2 edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> RgNLineVCompound(bool is3d = false);

	/// @brief Add visible C2 edges to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> RgNLineVCompound(const TopoShape& S, bool is3d = false);

	/// @brief Visible edges of outlined shape
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> OutLineVCompound(bool is3d = false);

	/// @brief Add visible edges of outlined shape to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> OutLineVCompound(const TopoShape& S, bool is3d = false);

	/// @brief Visible iso parameter lines
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the lines
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> IsoLineVCompound(bool is3d = false);

	/// @brief Add visible iso parameter lines to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> IsoLineVCompound(const TopoShape& S, bool is3d = false);

	/// @brief Hidden C0 (<G1) edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> HCompound(bool is3d = false);

	/// @brief Add hidden C0 (<G1) edges to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> HCompound(const TopoShape& S, bool is3d = false);

	/// @brief Hidden G1 (<G2) edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> Rg1LineHCompound(bool is3d = false);

	/// @brief Add hidden G1 (<G2) edges to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> Rg1LineHCompound(const TopoShape& S, bool is3d = false);

	/// @brief Hidden C2 edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> RgNLineHCompound(bool is3d = false);

	/// @brief Add hidden C2 edges to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> RgNLineHCompound(const TopoShape& S, bool is3d = false);

	/// @brief Hidden edges of outlined shape
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the edges and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> OutLineHCompound(bool is3d = false);

	/// @brief Add hidden edges of outlined shape to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> OutLineHCompound(const TopoShape& S, bool is3d = false);

	/// @brief Hidden iso parameter lines
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of the lines
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> IsoLineHCompound(bool is3d = false);

	/// @brief Add hidden iso parameter lines to S
	/// @param S The shape to add edges
	/// @param is3d Require 3d edge or 2d edge
	/// @return New shape and edge map including 2d-3d and 3d-2d
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> IsoLineHCompound(const TopoShape& S, bool is3d = false);

	/// @brief Get all such type edges
	/// @param type Edge type, C0, G1, ...
	/// @param visible Are edges visible
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of edges
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> CompoundOfEdges(HLRBRepTypeOfResultingEdge type, bool visible, bool is3d);

	/// @brief Get all such type edges of the Shape
	/// @param S The shape
	/// @param type Edge type, C0, G1, ...
	/// @param visible Are edges visible
	/// @param is3d Require 3d edge or 2d edge
	/// @return Shape of edges
	AMCAX_API std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> CompoundOfEdges(const TopoShape& S, HLRBRepTypeOfResultingEdge type, bool visible, bool is3d);

private:
	std::pair<TopoShape, std::unordered_map<TopoShape, TopoShape>> InternalCompound(int typ, bool visible, const TopoShape& S, bool is3d = false);

	void DrawFace(bool visible, int typ, int iface, const std::shared_ptr<HLRBRepData>& DS, const std::vector<std::shared_ptr<HLRTopoOutLiner>>& outliners, TopoShape& Result, std::unordered_map<TopoShape, TopoShape>& shapeMap, bool& added, bool is3d = false) const;

	void DrawEdge(bool visible, bool inFace, int typ, HLRBRepEdgeData& ed, const std::vector<std::shared_ptr<HLRTopoOutLiner>>& outliners, TopoShape& Result, std::unordered_map<TopoShape, TopoShape>& shapeMap, bool& added, bool is3d = false) const;

private:
	std::shared_ptr<HLRBRepAlgorithm> algorithm;
};
} // namespace AMCAX
