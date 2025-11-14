/// @file      BRepOrientedBoundingBox.hpp
/// @brief     Class of tool for computing an oriented bounding box of BRep structure
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/OrientedBoundingBox.hpp>

namespace AMCAX
{
class TopoShape;

/// @brief Class of tool for computing an oriented bounding box of BRep structure
class BRepOrientedBoundingBox
{
public:
	/// @brief Add a shape to a oriented bounding box. Does not support infinite shape
	/// @param[in] S The shape
	/// @param[in,out] B The oriented bounding box
	/// @param[in] useTriangulation Does the computation use triangulation
	AMCAX_API static void AddToBox(const TopoShape& S, OrientedBoundingBox& B, bool useTriangulation = true);

	/// @brief Add a shape to a oriented bounding box. Does not support infinite shape
	/// @details The algorithm to find optimal oriented bounding box, which is more tight but has more computational cost
	/// @param[in] S The shape
	/// @param[in,out] B The oriented bounding box
	/// @param[in] useTriangulation Does the computation use triangulation
	/// @param[in] useShapeTolerance Does the computation use the tolerance of shape
	AMCAX_API static void AddOptimal(const TopoShape& S, OrientedBoundingBox& B, bool useTriangulation = true, bool useShapeTolerance = false);
};
} // namespace AMCAX
