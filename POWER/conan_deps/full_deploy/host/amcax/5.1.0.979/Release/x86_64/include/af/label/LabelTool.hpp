/// @file      LabelTool.hpp
/// @brief     The class of LabelTool
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.

#pragma once
#include "af/attribute/Attribute.hpp"
#include <af/label/Label.hpp>
#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief The class LabelTool
class LabelTool
{
#ifndef DOXYGEN_SKIP
    friend class WithAttrBase;
    friend class Label;
#endif

public:
    /// @brief Deep copy the label
    /// @param label The label be copied
    /// @return A new label copied by given label
    AMCAX_API static Label CopyLabel(const Label& label);

    /// @brief Serialize the label to a file
    /// @param label The label to write
    /// @param file The path of the file to save the label
    /// @return True if the writing is success, otherwise return false
    AMCAX_API static bool Write(const Label& label, const std::string& file);

    /// @brief Deserialize the label from a file
    /// @param[out] label The result label
    /// @param file The path of the file
    /// @return True if the reading is success, otherwise return false
    AMCAX_API static bool Read(Label& label, const std::string& file);

private:
    /// @brief Copy labels from srcLabel to targetLabel
    /// @param srcLabel The source label
    /// @param targetLabel The target label
    static void CopyLabelAttribute(const Label& srcLabel, Label& targetLabel);

    /// @brief Clear all child labels of given label
    /// @param label The label needed to be cleared
    static void ClearLabel(Label& label);
};
} // namespace AMCAX