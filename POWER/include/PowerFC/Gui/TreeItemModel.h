#pragma once

namespace gui {
/// highlight modes for the tree items
enum class HighlightMode
{
    Underlined,
    Italic,
    Overlined,
    StrikeOut,
    Bold,
    Blue,
    LightBlue,
    UserDefined
};

/// highlight modes for the tree items
enum class TreeItemMode
{
    ExpandItem,
    ExpandPath,
    CollapseItem,
    ToggleItem
};
}  // namespace gui