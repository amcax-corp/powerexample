/// @file      LabelIterator.hpp
/// @brief     The class of LabelIterator
/// @details   Supply methods of Next, More, Value of ChildIterator
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once

#include <af/label/Label.hpp>

#include <map>
namespace AMCAX
{

class LabelNode;

/// @brief The class of ChildIterator
/// @details Iterate a Label
class ChildIterator
{
public:
    /// @brief Construct a ChildIterator
    /// @param l The label need to be iteratered
    AMCAX_API ChildIterator(const Label& l);

    /// @brief Move to next child label
    /// @details The iterator plus one
    AMCAX_API void Next();

    /// @brief Check if has more child label
    /// @return True if it has more child label, otherwise return false
    AMCAX_API bool More();

    /// @brief Get current child label
    /// @return The current child label
    AMCAX_API Label Value();

private:
    Label _myLabel;
    std::map<LocalId, std::shared_ptr<LabelNode>>::iterator _current;
    std::map<LocalId, std::shared_ptr<LabelNode>>::iterator _end;
};
} // namespace AMCAX