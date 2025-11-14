/// @file      TMSplineCreaseTool.hpp
/// @brief     Class of TMSpline API for make crease edge
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{

/// @brief Class of TMSpline API for make crease edge
class TMSplineCreaseTool
{
public:
	/// @brief creat crease edge in a TMSpline
	/// @param tsp input TMSpline
	/// @param eIds indices of the edge to be creat crease
	AMCAX_API static void AddCreaseEdge(TMSpline* tsp, const std::vector<int>& eIds);

	/// @brief remove crease edge in a TMSpline
	/// @param tsp input TMSpline
	/// @param eIds indices of the edge to be remove crease
	AMCAX_API static void RemoveCreaseEdge(TMSpline* tsp, const std::vector<int>& eIds);
};

} // namespace TMS
} // namespace AMCAX
