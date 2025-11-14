/// @file      BRepProximityOperations.hpp
/// @brief     The class of BRepProximityOperations
/// @details   This class implements the BRepProximityOperations with attribute.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/label/Label.hpp>
#include <topology/BRepExtremaProximityTool.hpp>

namespace AMCAX
{
/// @brief The class of BRepProximityOperations
/// @details This class implements the BRepProximityOperations with attribute.
class BrepProximityOperations
{
public:
    /// @brief Find the touch face pairs between two labels
    /// @param label01 The first label
    /// @param label02 The second label
    /// @param tolerance The horizontal tolerance used for check overlaping
	/// @param isOpposite The flag only keep faces with opposite normal directions
    /// @return A vector of pairs of labels that are touching
    AMCAX_API static std::vector<std::pair<AMCAX::Label, AMCAX::Label>> FindOverlapFaces(const AMCAX::Label& label01, const AMCAX::Label& label02, double tolerance = Precision::Confusion(), bool isOpposite = false);

    /// @brief Find the intersect face pairs between two labels
    /// @param label01 The first label
    /// @param label02 The second label
    /// @param tolerance The tolerance used for check intersection
    /// @return A vector of pairs of labels that are intersecting
    AMCAX_API static std::vector<std::pair<AMCAX::Label, AMCAX::Label>> FindIntersectionFaces(const AMCAX::Label& label01, const AMCAX::Label& label02, double tolerance = Precision::Confusion());
};
}
