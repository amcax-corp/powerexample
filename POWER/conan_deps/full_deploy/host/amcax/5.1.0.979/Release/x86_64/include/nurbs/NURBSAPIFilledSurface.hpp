/// @file      NURBSAPIFilledSurface.hpp
/// @brief     Class of NURBS filled surface
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <vector>

#include <common/Macros.hpp>
#include <nurbs/NURBSAPIMultiSectionsSurface.hpp>
namespace AMCAX
{
class TopoFace;
class NURBSAPIMultiSectionsSurface;
/// @brief Class of filled surface
/// @details This class computes the face from a closed region bounded by at least one boundary curve
class NURBSAPIFilledSurface
{
public:
	/// @brief When there are multiple boundary curves, they must be oriented in a clockwise or counterclockwise direction
	/// @param Target The Target contains boundary curves, pCurves and surfaces 
	/// @param npoles The npoles is the face nvpoles and nupoles
	/// @param nsample The nsample is the number of samples on the each boundary curve
	/// @return The face
	AMCAX_API static AMCAX::TopoFace Perform(const std::vector<AMCAX::SectionCurve>& Target, int npoles, int nsample);
};
} // namespace AMCAX