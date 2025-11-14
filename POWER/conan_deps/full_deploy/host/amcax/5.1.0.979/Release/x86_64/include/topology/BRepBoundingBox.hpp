/// @file      BRepBoundingBox.hpp
/// @brief     Class of tool for computing a bounding box of BRep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/BoundingBox3.hpp>

namespace AMCAX
{
class TopoShape;

/// @brief Class of tool for computing a bounding box of BRep structure
class BRepBoundingBox
{
public:
	/// @brief Add a shape to a bounding box
	/// @param[in] S The shape
	/// @param[in,out] B The bounding box
	/// @param[in] useTriangulation Does the computation use triangulation
	AMCAX_API static void AddToBox(const TopoShape& S, BoundingBox3& B, bool useTriangulation = true);

	/// @brief Add a shape to a bounding box
	/// @details The fast algorithm to compute an approximate bounding box.
	///          The result is not larger than the precise bounding box.
	/// @param[in] S The shape
	/// @param[in,out] B The bounding box
	AMCAX_API static void AddClose(const TopoShape& S, BoundingBox3& B);

	/// @brief Add a shape to a bounding box
	/// @details The algorithm to find optimal bounding box
	/// @param[in] S The shape
	/// @param[in,out] B The bounding box
	/// @param[in] useTriangulation Does the computation use triangulation
	/// @param[in] useShapeTolerance Does the computation use the tolerance of shape
	AMCAX_API static void AddOptimal(const TopoShape& S, BoundingBox3& B, bool useTriangulation = true, bool useShapeTolerance = false);
};
} // namespace AMCAX
