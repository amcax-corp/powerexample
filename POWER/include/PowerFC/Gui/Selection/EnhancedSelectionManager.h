#ifndef ENHANCEDSELECTIONMANAGER_H
#define ENHANCEDSELECTIONMANAGER_H

#include "SelectionChanges.h"
#include "SelectionGateManager.h"
#include "BoostSignalDefine.h"

#include <PFCGlobal.h>
#include <array>
#include <common/DirectionT.hpp>
#include <common/IndexMap.hpp>
#include <common/IndexSet.hpp>
#include <topology/TopoShape.hpp>
#include <memory>
#include <string>

class QString;
namespace AMCAX {
class TopoEdge;
class TopoFace;
}
namespace gui {
using namespace std::string_literals;
enum class BasicPickFilter;
class PFC_GUI_API EnhancedRuleInterface
{
public:
    virtual ~EnhancedRuleInterface() = default;
    virtual void Activate(bool) {}
    virtual std::string GetName() const = 0;
    virtual QString GetShowName() const = 0;
    virtual BasicPickFilter GetPickFilter() const = 0;
    virtual bool Execute(const SelectionData& data) = 0;

    const std::vector<SelectionData>& GetResult() const { return m_result; }
    void SwapResult(std::vector<SelectionData>& container) { m_result.swap(container); }

protected:
    std::vector<SelectionData> m_result{};
};
class PFC_GUI_API EnhancedSelectionManager {
public:
    EnhancedSelectionManager();
    virtual ~EnhancedSelectionManager() = default;
    EnhancedSelectionManager(const EnhancedSelectionManager&) = delete;
    EnhancedSelectionManager(EnhancedSelectionManager&&) = default;
    EnhancedSelectionManager& operator=(const EnhancedSelectionManager&) = delete;
    EnhancedSelectionManager& operator=(EnhancedSelectionManager&&) = default;

    enum class ModeType
    {
        Face,
        Edge,
        Body
    };
    void RegisterEnhancedRule(EnhancedRuleInterface* mode, ModeType type);
    void RemoveEnhancedRule(std::string_view rule_name, ModeType type);

    /// @brief 设置增强器是否可用
    void SetEnabled(bool enabled);
    bool GetEnabled() const { return m_enabled; }
    BoostSignal<void()> SignalEnhancedEnableChanged {};

    /// @brief 设置增强类型是否可用
    void SetEnabled(ModeType type, bool enable);
    bool GetEnabled(ModeType type) const;
    BoostSignal<void(ModeType)> SignalModeEnableChanged{};

    /// @brief 屏蔽增强类型
    void BlockEnabled(ModeType type, bool block);
    bool IsBlockEnabled(ModeType type) const;
    BoostSignal<void(ModeType)> SignalBlockEnabledChanged{};

    /// @brief 设置当前选择的增强项
    void RefreshCurrentRule();
    void SetCurrentRule(int index, ModeType type);
    int GetCurrentRule(ModeType type) const;
    void ResetCurrentRule();
    BoostSignal<void(ModeType)> SignalCurrentModeChanged {};

    std::optional<EnhancedRuleInterface*> GetEnhancedSelection(ModeType type) const;

    const std::vector<std::shared_ptr<EnhancedRuleInterface>>& GetAllEnhancedSelection(ModeType type) const;

    static std::shared_ptr<EnhancedSelectionManager> CreateDefaultEnhancedSelectionManager();

private:
    enum { MAX_INDEX = static_cast<int>(ModeType::Body) + 1 };

    bool m_enabled { true };

    struct EnhancedModeInfo
    {
        bool enable { true };
        bool block { false };
        int cur_index { 0 };
        std::vector<std::shared_ptr<EnhancedRuleInterface>> modes{};
    };
    std::array<EnhancedModeInfo, MAX_INDEX> m_info{};
};

class PFC_GUI_API EnhancedFaceSelectionMode_SingleFace : public EnhancedRuleInterface
{
public:
    std::string GetName() const override { return "Single_Face"s; }
    QString GetShowName() const override;
    BasicPickFilter GetPickFilter() const override;
    bool Execute(const SelectionData& data) override;
};
class PFC_GUI_API EnhancedFaceSelectionMode_SingleBody : public EnhancedRuleInterface
{
public:
    std::string GetName() const override { return "Single_Body"s; }
    QString GetShowName() const override;
    BasicPickFilter GetPickFilter() const override;
    bool Execute(const SelectionData& data) override;
};
class PFC_GUI_API EnhancedFaceSelectionMode_SingleEdge : public EnhancedRuleInterface
{
public:
    std::string GetName() const override { return "Single_Edge"s; }
    QString GetShowName() const override;
    BasicPickFilter GetPickFilter() const override;
    bool Execute(const SelectionData& data) override;
};
class PFC_GUI_API EnhancedEdgeSelecionMode_EdgeInFace : public EnhancedRuleInterface
{
public:
    void Activate(bool activate) override;
    std::string GetName() const override { return "EdgeInFace"s; }
    QString GetShowName() const override;
    BasicPickFilter GetPickFilter() const override;
    bool Execute(const SelectionData& data) override;

private:
    void Restore();

private:
    std::optional<BasicPickFilter> m_temp_pick_range{};
    std::optional<BasicPickFilter> m_temp_current_pick_filter{};
};
class PFC_GUI_API EnhancedEdgeSelectionMode_SerialTangentEdge : public EnhancedRuleInterface
{
public:
    std::string GetName() const override { return "SerialTangentEdge"s; }
    QString GetShowName() const override;
    BasicPickFilter GetPickFilter() const override;
    bool Execute(const SelectionData& data) override;

private:
    void Execute(const AMCAX::TopoEdge& current_edge, std::function<void(const AMCAX::TopoEdge&, std::deque<AMCAX::TopoShape>&)> push_function, std::deque<AMCAX::TopoShape>& result);
    static bool IsG1Continuity(const AMCAX::TopoEdge& edge_1, const AMCAX::TopoEdge& edge_2);

    AMCAX::IndexMap<AMCAX::TopoShape, std::list<AMCAX::TopoShape>> m_vertex_edge_map{};
};
class PFC_GUI_API EnhancedFaceSelectionMode_SerialTangentFace : public EnhancedRuleInterface
{
public:
    std::string GetName() const override { return "SerialTangentFace"s; }
    QString GetShowName() const override;
    BasicPickFilter GetPickFilter() const override;
    bool Execute(const SelectionData& data) override;

private:
    void Execute(const AMCAX::TopoFace& current_face, AMCAX::IndexSet<AMCAX::TopoShape>& result);
    static void ComputeNormal(const AMCAX::TopoFace& face, const AMCAX::TopoEdge& edge, double param, AMCAX::Direction3& normal);

    AMCAX::IndexMap<AMCAX::TopoShape, std::list<AMCAX::TopoShape>> m_edge_face_map{};
};
class PFC_GUI_API EnhancedFaceSelectionMode_AdjacentFace : public EnhancedRuleInterface
{
public:
    std::string GetName() const override { return "AdjacentFace"s; }
    QString GetShowName() const override;
    BasicPickFilter GetPickFilter() const override;
    bool Execute(const SelectionData& data) override;
};
}


#endif //ENHANCEDSELECTIONMANAGER_H
