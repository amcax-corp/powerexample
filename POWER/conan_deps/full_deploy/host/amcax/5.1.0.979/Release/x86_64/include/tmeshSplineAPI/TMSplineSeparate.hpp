/// @file      TMSplineSeparate.hpp
/// @brief     Class of TMSpline API for separate edges
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tmeshSpline/TMSpline.hpp>

namespace AMCAX
{
namespace TMS
{
/// @brief Class of TMSpline API for separate edge, obtain new boundaries in the separated edges
class TMSplineSeparate
{
public:
	/// @brief Separate edges into each other, the result edges will remain on top of each other until they are moved
	/// @param tsp The TMSpline
	/// @param elist the edges that need to separate
	/// @return true if process succeed
	AMCAX_API bool SeparateEdges(TMSpline* tsp, const std::vector<int>& elist);
};
} // namespace TMS
} // namespace AMCAX
