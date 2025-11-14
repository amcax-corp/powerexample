/// @file      TopoCast.hpp
/// @brief     Class of casting tool
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Macros.hpp>

namespace AMCAX
{
class TopoCompound;
class TopoCompSolid;
class TopoEdge;
class TopoFace;
class TopoShape;
class TopoShell;
class TopoSolid;
class TopoVertex;
class TopoWire;

/// @brief Class of tool that casts TopoShape objects to specific sub-classes
class TopoCast
{
public:
	/// @brief Cast shape to vertex
	/// @param s The shape
	/// @return The constant reference of vertex
	[[nodiscard]] AMCAX_API static const TopoVertex& Vertex(const TopoShape& s);

	/// @brief Cast shape to vertex
	/// @param s The shape
	/// @return The reference of vertex
	[[nodiscard]] AMCAX_API static TopoVertex& Vertex(TopoShape& s);

	/// @brief Cast shape to vertex
	/// @param s The shape
	/// @return The rvalue reference of vertex
	[[nodiscard]] AMCAX_API static TopoVertex&& Vertex(TopoShape&& s);

	/// @brief Cast shape to edge
	/// @param s The shape
	/// @return The constant reference of edge
	[[nodiscard]] AMCAX_API static const TopoEdge& Edge(const TopoShape& s);

	/// @brief Cast shape to edge
	/// @param s The shape
	/// @return The reference of edge
	[[nodiscard]] AMCAX_API static TopoEdge& Edge(TopoShape& s);

	/// @brief Cast shape to edge
	/// @param s The shape
	/// @return The rvalue reference of edge
	[[nodiscard]] AMCAX_API static TopoEdge&& Edge(TopoShape&& s);

	/// @brief Cast shape to wire
	/// @param s The shape
	/// @return The constant reference of wire
	[[nodiscard]] AMCAX_API static const TopoWire& Wire(const TopoShape& s);

	/// @brief Cast shape to wire
	/// @param s The shape
	/// @return The reference of wire
	[[nodiscard]] AMCAX_API static TopoWire& Wire(TopoShape& s);

	/// @brief Cast shape to wire
	/// @param s The shape
	/// @return The rvalue reference of wire
	[[nodiscard]] AMCAX_API static TopoWire&& Wire(TopoShape&& s);

	/// @brief Cast shape to face
	/// @param s The shape
	/// @return The constant reference of face
	[[nodiscard]] AMCAX_API static const TopoFace& Face(const TopoShape& s);

	/// @brief Cast shape to face
	/// @param s The shape
	/// @return The reference of face
	[[nodiscard]] AMCAX_API static TopoFace& Face(TopoShape& s);

	/// @brief Cast shape to face
	/// @param s The shape
	/// @return The rvalue reference of face
	[[nodiscard]] AMCAX_API static TopoFace&& Face(TopoShape&& s);

	/// @brief Cast shape to shell
	/// @param s The shape
	/// @return The constant reference of shell
	[[nodiscard]] AMCAX_API static const TopoShell& Shell(const TopoShape& s);

	/// @brief Cast shape to shell
	/// @param s The shape
	/// @return The reference of shell
	[[nodiscard]] AMCAX_API static TopoShell& Shell(TopoShape& s);

	/// @brief Cast shape to shell
	/// @param s The shape
	/// @return The rvalue reference of shell
	[[nodiscard]] AMCAX_API static TopoShell&& Shell(TopoShape&& s);

	/// @brief Cast shape to solid
	/// @param s The shape
	/// @return The constant reference of solid
	[[nodiscard]] AMCAX_API static const TopoSolid& Solid(const TopoShape& s);

	/// @brief Cast shape to solid
	/// @param s The shape
	/// @return The reference of solid
	[[nodiscard]] AMCAX_API static TopoSolid& Solid(TopoShape& s);

	/// @brief Cast shape to solid
	/// @param s The shape
	/// @return The rvalue reference of solid
	[[nodiscard]] AMCAX_API static TopoSolid&& Solid(TopoShape&& s);

	/// @brief Cast shape to composite solid
	/// @param s The shape
	/// @return The constant reference of composite solid
	[[nodiscard]] AMCAX_API static const TopoCompSolid& CompSolid(const TopoShape& s);

	/// @brief Cast shape to composite solid
	/// @param s The shape
	/// @return The reference of composite solid
	[[nodiscard]] AMCAX_API static TopoCompSolid& CompSolid(TopoShape& s);

	/// @brief Cast shape to composite solid
	/// @param s The shape
	/// @return The rvalue reference of composite solid
	[[nodiscard]] AMCAX_API static TopoCompSolid&& CompSolid(TopoShape&& s);

	/// @brief Cast shape to compound
	/// @param s The shape
	/// @return The constant reference of compound
	[[nodiscard]] AMCAX_API static const TopoCompound& Compound(const TopoShape& s);

	/// @brief Cast shape to compound
	/// @param s The shape
	/// @return The reference of compound
	[[nodiscard]] AMCAX_API static TopoCompound& Compound(TopoShape& s);

	/// @brief Cast shape to compound
	/// @param s The shape
	/// @return The rvalue reference of compound
	[[nodiscard]] AMCAX_API static TopoCompound&& Compound(TopoShape&& s);
};
} // namespace AMCAX
