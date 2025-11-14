#pragma once
#include <QColor>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdint.h>
#include <Widgets/PowerWidgetsConfig.h>

class PW_API DisplayColorTable
{
public:
    struct ColorTableItem {
        uint32_t id{};
        std::string color{};
        ColorTableItem(uint32_t id, const std::string& color)
            : id(id), color(color) {}
    };

private:
    std::vector<ColorTableItem> m_items;
    std::unordered_map<uint32_t, size_t> m_idIndex;
    std::unordered_map<std::string, size_t> m_colorIndex;

public:
    DisplayColorTable();
    ~DisplayColorTable() = default;

    QColor GetColorById(uint32_t id) const;
    uint32_t GetIdOfColor(const QColor& color) const;

    size_t GetColorCount() const { return m_items.size(); }
    QColor GetColor(size_t index) const;
    uint32_t GetColorId(size_t index) const;
};