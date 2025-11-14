/// @file      TMSplineCheck.hpp
/// @brief     Class of TMSpline check Tool
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline Check Tool
class TMSplineCheck
{
public:
	/// @brief check if the input index is valid vert
	/// @param tsp a TMSpline
	/// @param vid input index
	/// @return return true if the input index is valid vert
	AMCAX_API static bool IsVertValid(TMSpline* tsp, int vid);

	/// @brief check if the vert is boundary vert
	/// @param tsp a TMSpline
	/// @param vid input vert index
	/// @return true if vert is boudary
	AMCAX_API static bool IsVertBoundary(TMSpline* tsp, int vid);

	/// @brief check if the vert is inner vert
	/// @param tsp a TMSpline
	/// @param vid input vert index
	/// @return true if vert is inner
	AMCAX_API static bool IsVertInner(TMSpline* tsp, int vid);

	/// @brief check if the input index is valid edge
	/// @param tsp a TMSpline
	/// @param eid input index
	/// @return return true if the input index is valid edge
	AMCAX_API static bool IsEdgeValid(TMSpline* tsp, int eid);

	/// @brief check if the edge is boundary edge
	/// @param tsp a TMSpline
	/// @param eid input edge index
	/// @return true if edge is boudary
	AMCAX_API static bool IsEdgeBoundary(TMSpline* tsp, int eid);

	/// @brief check if the edge is inner edge
	/// @param tsp a TMSpline
	/// @param eid input edge index
	/// @return true if edge is inner
	AMCAX_API static bool IsEdgeInner(TMSpline* tsp, int eid);

	/// @brief check if the edge is crease edge
	/// @param tsp a TMSpline
	/// @param eid input edge index
	/// @return true if edge is crease
	AMCAX_API static bool IsEdgeCrease(TMSpline* tsp, int eid);

	/// @brief check if the input index is valid face
	/// @param tsp a TMSpline
	/// @param fid input index
	/// @return return true if the input index is valid face
	AMCAX_API static bool IsFaceValid(TMSpline* tsp, int fid);
};

} // namespace TMS
} // namespace AMCAX
