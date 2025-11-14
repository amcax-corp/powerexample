#ifndef HIGHLIGHTMANAGER_H
#define HIGHLIGHTMANAGER_H
#include "Gui/Selection/Selection.h"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace AMCAXRender {
enum class PickType;
}
namespace app {
class DocumentObject;
class Color;
}
namespace gui {
class PFC_GUI_API HighlightManager final : public SelectionObserver
{
public:
    static HighlightManager& Instance()
    {
        static HighlightManager instance;
        return instance;
    }

    enum class Identity
    {
        None = 0,
        Selection = 1 << 0,
        Custom = 1 << 1,

        All = (1 << 2) - 1
    };
    friend Identity operator|(Identity lhs, Identity rhs);
    friend Identity operator-(Identity lhs, Identity rhs);
    friend bool operator&(Identity lhs, Identity rhs);

    /*
     *  连续事务
     */
    struct Blocker
    {
        ~Blocker();
    };
    std::shared_ptr<Blocker> StartRelayWithBlocker();
    void StartRelay();
    void StopRelay();

    /*
     *  设置高亮
     */
    /// @brief 设置预选高亮
    void SetPreselectHighlight(bool highlight, app::DocumentObject* doc_obj, Identity identity = Identity::Custom);
    void SetPreselectHighlight(bool highlight, std::string_view doc_name, std::string_view obj_name, std::string_view sub_name = {}, Identity identity = Identity::Custom);;

    /// @brief 设置已选高亮
    void SetSelectingHighlight(bool highlight, app::DocumentObject* doc_obj, Identity identity = Identity::Custom);
    void SetSelectingHighlight(bool highlight, std::string_view doc_name, std::string_view obj_name, std::string_view sub_name = {}, Identity identity = Identity::Custom);;

    /// @brief 设置备选高亮
    void SetAlternativeHighlight(bool highlight, app::DocumentObject* doc_obj, Identity identity = Identity::Custom);
    void SetAlternativeHighlight(bool highlight, std::string_view doc_name, std::string_view obj_name, std::string_view sub_name = {}, Identity identity = Identity::Custom);;

    /// @brief 设置提示高亮
    void SetAttentionHighlight(bool highlight, app::DocumentObject* doc_obj, Identity identity = Identity::Custom);
    void SetAttentionHighlight(bool highlight, std::string_view doc_name, std::string_view obj_name, std::string_view sub_name = {}, Identity identity = Identity::Custom);;

    /// @brief 清除高亮
    void ClearHighlight(Identity identity = Identity::Custom);

    /// @brief 清除所有高亮
    void ClearAllHighlight() { ClearHighlight(Identity::All); }

    /// @brief 刷新
    void Refresh();

    HighlightManager(const HighlightManager&) = delete;
    HighlightManager& operator=(const HighlightManager&) = delete;
    HighlightManager(HighlightManager&&) = delete;
    HighlightManager& operator=(HighlightManager&&) = delete;
    ~HighlightManager() override = default;
private:
    HighlightManager();
    struct HighlightInfo
    {
        std::string obj_name;
        AMCAXRender::PickType pick_type;
        int sub_index;
        struct Data
        {
            Identity preselect_highlight_identities { Identity::None };
            Identity selecting_highlight_identities { Identity::None };
            Identity alternative_highlight_identities { Identity::None };
            Identity attention_highlight_identities { Identity::None };
        } origin, value;
    };

    void UpdateIdentities(Identity& origin, bool highlight, Identity input);
    static std::string MakeName(std::string_view doc_name, std::string_view obj_name, std::string_view sub_name);
    [[nodiscard]] HighlightInfo& InitInfo(std::string&& full_name, std::string_view doc_name, std::string_view obj_name, std::string_view sub_name);

    void UpdateHighlight();
    void UpdateHighlightNoCheck();

    bool SelectionChangesPrefilter(const SelectionChanges& msg) const override;
    void OnSelectionChanged(const SelectionChanges& msg) override;

private:
    std::unordered_map<std::string, HighlightInfo> m_highlight_info;

    bool m_relay { false };
    bool m_dirty { false };

    app::Document* m_document { nullptr };
    boost::signals2::scoped_connection
    m_connection_activate_document,
    m_connection_new_object,
    m_connection_remove_object;
    std::map<const ViewProviderDocumentObject*, boost::signals2::scoped_connection>
    m_map_view_provider_connection;
};

inline HighlightManager& HighlightManager()
{
    return HighlightManager::Instance();
}
}


#endif //HIGHLIGHTMANAGER_H
