/// @file      NURBSAPICorrespondence.hpp
/// @brief     Class of building NURBS curves parameter correspondence
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3Curve;

/// @brief Class of building NURBS curves parameter correspondence
/// @details This class computes the correspondence parameters and orientations of the curves
class NURBSAPICorrespondence
{
public:
	/// @brief Find the correspondence parameter and orientation of curves
	/// @param curves Input curves
	/// @param isPeriodic Whether curves are periodic which means the first curve and the last curve are neighbours
	/// @param isConsiderReverse Whether curve orientation is under consideration
	/// @return Array of curve correspondence parameter and orientation
	[[nodiscard]] AMCAX_API static std::vector<std::pair<double, bool>> CalcParamCorrespondence(
		const std::vector<std::shared_ptr<Geom3Curve>>& curves,
		bool isPeriodic,
		bool isConsiderReverse);
};
} // namespace AMCAX
