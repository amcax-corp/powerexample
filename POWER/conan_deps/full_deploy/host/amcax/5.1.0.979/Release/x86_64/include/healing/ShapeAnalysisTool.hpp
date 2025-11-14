/// @file      ShapeAnalysisTool.hpp
/// @brief     Some useful tool for analysis shapes information
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Macros.hpp>
#include <common/Precision.hpp>

namespace AMCAX
{
class TopoFace;
class TopoShape;
class TopoVertex;
class TopoWire;
class TopoSolid;
class TopoShell;

/// @brief Some useful tool for analysis shapes information
class ShapeAnalysisTool
{
public:
	/// @brief Get the outer wire of a face
	/// @param face The face
	/// @return The outer wire
	[[nodiscard]] AMCAX_API static TopoWire OuterWire(const TopoFace& face);

	/// @brief Get the outer shell of a solid
	/// @param solid The solid
	/// @return The outer shell
	[[nodiscard]] AMCAX_API static TopoShell OuterShell(const TopoSolid& solid);

	/// @brief Does a face have an outer bound
	/// @param face The face
	/// @return True if the face has an outer bound
	[[nodiscard]] AMCAX_API static bool IsOuterBound(const TopoFace& face);

	/// @brief Get a shift value to move a value into a range [toVal - period / 2, toVal + period / 2]
	/// @param val The value
	/// @param toVal The middle value
	/// @param period The period
	/// @return The shift value
	[[nodiscard]] AMCAX_API static double AdjustByPeriod(double val, double toVal, double period);

	/// @brief Get a shift value to move a value into a range [valMin, valMax]
	/// @param val The value
	/// @param valMin The lower bound of the range
	/// @param valMax The upper bound of the range
	/// @return The shift value
	[[nodiscard]] AMCAX_API static double AdjustToPeriod(double val, double valMin, double valMax);

	/// @brief Get the start and end vertices of a shape
	/// @details The input shape can be a vertex, an edge or a wire
	/// @param[in] shape The input shape
	/// @param[out] c1 The start vertex
	/// @param[out] c2 The end vertex
	AMCAX_API static void FindBounds(const TopoShape& shape, TopoVertex& c1, TopoVertex& c2);

	/// @brief Get the UV bounds of a face
	/// @param[in] f The face
	/// @param[out] umin The u first parameter
	/// @param[out] umax The u last parameter
	/// @param[out] vmin The v first parameter
	/// @param[out] vmax The v last parameter
	AMCAX_API static void GetFaceUVBounds(const TopoFace& f, double& umin, double& umax, double& vmin, double& vmax);

	/// @brief Check if the input wire is self-intersection in the face's parameter domain.
	/// @details It is based on the self-intersection check of edge Pcurves
	/// @param w The input wire
	/// @param f The input face
	/// @param isCheckCoincide The flag for checking whether vertices and edges coincide
	/// @return true if the wire is self-intersection
	[[nodiscard]] AMCAX_API static bool CheckWireSelfIntersection(const TopoWire& w, const TopoFace& f, bool isCheckCoincide = true);
};
} // namespace AMCAX
