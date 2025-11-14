/// @file      NURBSAPITrim.hpp
/// @brief     The class of trim operation
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>
#include <vector>

#include <common/CoordT.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of trimming a shape with cutters
/// @details This class computes the trimmed shape with cutter shapes and parameters to find which part is desired.
class NURBSAPITrim
{
public:
	/// @brief Trim a shape with cutters
	/// @param cutter The cutters consist of TopoEdges and TopoFaces
	/// @param srcShape The source shape which can be a TopoEdge or a TopoFace
	/// @param param The parameter to determin which part of the srcShape is deleted.
	/// If the srcShape is a TopoEdge, param.size = 1.  If the srcShape is a TopoFace, param.size = 2
	/// @param isViewPortIntersection Point projection or parallel projection
	/// @param eyeOrDir if isViewPortIntersection, it is the position of the camera (or eye), else it is the direction of parallel projection
	/// @return The trimmed shape
	[[nodiscard]] AMCAX_API static TopoShape Trim(const std::list<TopoShape>& cutter, const TopoShape& srcShape, const std::vector<double>& param, bool isViewPortIntersection, const Coord3& eyeOrDir);
};
} // namespace AMCAX
