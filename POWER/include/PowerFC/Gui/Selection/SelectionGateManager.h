#ifndef SELECTIONGATEMANAGER_H
#define SELECTIONGATEMANAGER_H

#include "PFCGlobal.h"
#include <string>
#include <vector>
#include <memory>

namespace app {
class Document;
class DocumentObject;
}
namespace gui {

/// 选择基本过滤
enum class BasicPickFilter
{
    Unknown = 0,

    Scatter = 1 << 0,
    Vertex = 1 << 1,
    Point = Scatter | Vertex,

    Edge = 1 << 2,

    Face = 1 << 3,

    GeomOnShape = Vertex | Edge | Face,
    AllGeom = Point | Edge | Face,

    Body = 1 << 4,

    All = AllGeom | Body,
};
PFC_GUI_API BasicPickFilter operator|(BasicPickFilter lhs, BasicPickFilter rhs);
PFC_GUI_API BasicPickFilter operator-(BasicPickFilter lhs, BasicPickFilter rhs);
PFC_GUI_API bool operator&(BasicPickFilter lhs, BasicPickFilter rhs);

class PFC_GUI_API SelectionGate
{
public:
    virtual ~SelectionGate() = default;

    [[nodiscard]] virtual std::string GetName() const { return {}; }
    virtual bool Allow(app::Document*, app::DocumentObject*, std::string) = 0;

    /// @brief 将基本过滤条件封装成门
    /// @note 包含多个过滤条件时，均以或运算连接
    static std::unique_ptr<SelectionGate> MakeGate(BasicPickFilter filter);
};

/// 选择过滤器管理
class PFC_GUI_API SelectionGateManager
{
public:
    SelectionGateManager() = default;
    SelectionGateManager(const SelectionGateManager&) = delete;
    SelectionGateManager& operator=(const SelectionGateManager&) = delete;
    SelectionGateManager(SelectionGateManager&&) = default;
    SelectionGateManager& operator=(SelectionGateManager&&) = default;
    virtual ~SelectionGateManager() = default;

    using AndGates = std::vector<std::unique_ptr<SelectionGate>>;      // 行内的门执行与操作
    using GateMatrix = std::vector<AndGates>;   // 行间的门执行或操作

    /// @brief 获取或门数量
    int GetOrGateCount() const;
    /// @brief 获取与门数量
    int GetAndGateCount(int row) const;

    /// @brief 追加一个与门
    /// @param row 指定行（0为第一行），-1或其他无效值则视为追加至最后一行
    /// @return 受影响的行号
    int AppendAndGate(std::unique_ptr<SelectionGate>&& gate, int row = -1);
    int AppendAndGate(SelectionGate* gate, int row = -1) { return AppendAndGate(std::unique_ptr<SelectionGate>(gate), row); }

    /// @brief 追加一个或门
    /// @return 行号
    int AppendOrGate(std::unique_ptr<SelectionGate>&& gate);
    int AppendOrGate(SelectionGate* gate) { return AppendOrGate(std::unique_ptr<SelectionGate>(gate)); }

    void Clear();

    /// @brief 执行
    bool Execute(app::Document* doc, app::DocumentObject* obj, std::string sub) const;

private:
    GateMatrix m_gate_matrix;
};

}



#endif //SELECTIONGATEMANAGER_H
