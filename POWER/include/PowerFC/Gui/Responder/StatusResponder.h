#ifndef STATUSRESPONDER_H
#define STATUSRESPONDER_H

#include <QBitArray>
#include <QMetaEnum>
#include <QObject>
#include "PFCGlobal.h"

class QDialog;
namespace gui {
class MainWindow;

struct PFC_GUI_API ResponderPredicateWrapper
{
    ResponderPredicateWrapper() = default;
    template<typename Predicate>
    explicit ResponderPredicateWrapper(Predicate&& predicate) : m_predicate { predicate } {}
    ResponderPredicateWrapper(const ResponderPredicateWrapper&) = default;
    ResponderPredicateWrapper(ResponderPredicateWrapper&&) = default;
    ResponderPredicateWrapper& operator=(const ResponderPredicateWrapper&) = default;
    ResponderPredicateWrapper& operator=(ResponderPredicateWrapper&&) = default;
    ~ResponderPredicateWrapper() = default;

    auto operator() (const QString& param) const
    {
        return m_predicate(param);
    }

private:
    std::function<bool(const QString&)> m_predicate{};
};
Q_DECLARE_METATYPE(ResponderPredicateWrapper)

enum class ResponderRuleType
{
    Group = 0,
    BaseName,
    RegExp,
    Predicate,
    DirectName
};

struct ResponderRuleNode
{
    enum : unsigned int { MUST_DO_FIRST = 0,
        MUST_DO_LAST = (std::numeric_limits<unsigned int>::max)(),
        DEFAULT_PRIORITY = (std::numeric_limits<unsigned int>::max)() / 2
    };
    // 规则
    QVariant value{};

    // 规则类型
    ResponderRuleType type{ ResponderRuleType::DirectName };

    // 填 MUST_DO_FIRST 则一定先执行，填 MUST_DO_LAST 则一定最后执行
    unsigned int priority{ DEFAULT_PRIORITY };  // 从小到大排序

    // 使用 QMultiMap 存储规则，会按 operator < 进行排序，此排序对规则作用的先后顺序有影响
    bool operator< (const ResponderRuleNode& other) const {
        // 按优先级排序
        if (priority != other.priority)
        {
            return priority < other.priority;
        }
        // 按类型排序，颗粒度越小规则越靠后
        return type < other.type;
        // 不考虑为 QVariant 排序，若插入的优先级和类型完全一致，则按插入顺序的逆序存储
    }

    friend QDebug operator<<(QDebug debug, const ResponderRuleNode& node)
    {
        debug << "ResponderRuleNode value: " << node.value << " type: " << (int)node.type << "priority: " << node.priority;
        return debug;
    }
};
struct ResponderEffectNode
{
    QVariant value{};
    ResponderRuleType type{ ResponderRuleType::DirectName };

    bool enable{};
    bool clear_dialog_stack{ false };

    friend QDebug operator<<(QDebug stream, const ResponderEffectNode& node)
    {
        stream << "ResponderEffectNode value: " << node.value << " type: " << (int)node.type << " enable: " << node.enable << " clear_dialog: " << node.clear_dialog_stack;
        return stream;
    }
};

class PFC_GUI_API StatusResponder : public QObject {
    Q_OBJECT
public:
    explicit StatusResponder(QObject* parent = Q_NULLPTR);
    StatusResponder(const StatusResponder& other) = delete;
    StatusResponder& operator=(const StatusResponder& other) = delete;
    StatusResponder(StatusResponder&& other) = delete;
    StatusResponder& operator=(StatusResponder&& other) = delete;
    ~StatusResponder() override = default;

    /// @brief 设置命令响应
    /// @param rule 命令过滤条件
    /// @param effect 满足后的响应内容
    /// @example
    /// 执行任何命令都会使所有命令不可用
    /// AddCommandResponder({ "*", ResponderRuleType::RegExp }, { { "*", ResponderRuleType::RegExp }, false });
    /// @note 当执行命令后存在弹窗时，DialogResponder 总会先于 CommandResponder 执行
    void AddCommandResponder(ResponderRuleNode rule, ResponderEffectNode effect);

    /// @brief 设置弹窗响应
    /// @param rule 命令过滤条件
    /// @param effect 满足后的响应内容
    /// @note 仅当对话框的 modal_type 设置为 3 时可用
    void AddDialogResponder(ResponderRuleNode rule, ResponderEffectNode effect);

    bool TestIfClearDialogStack(QDialog* root, const QString& command) const;
    [[nodiscard]] std::optional<bool> TestIfCommandEnabled(const QString& command) const;

    enum class EventType
    {
        Ribbon_TabBar_Changed,
        Block_Dialog_Changed,   // Block_Dialog_Changed会在窗口全部关闭时触发一次
        Command_Invoked,        // 当 Command_Invoked 需要弹窗时，总是会晚于 Block_Dialog_Changed

        Refresh,
    };
    Q_FLAG(EventType);

    void Refresh() { emit EventOccurred(EventType::Refresh); }

    /// @brief 注册事件回调
    /// @param event 监听的事件类型
    /// @param callback 回调函数，类型为 void()
    template<typename Callback>
    QMetaObject::Connection RegisterCallback(EventType event, Callback&& callback)
    {
        return QObject::connect(this, &StatusResponder::EventOccurred,
            [require_event { event }, callback { std::forward<Callback>(callback) }] (EventType event) {
                if (require_event == event || event == EventType::Refresh) [[likely]] {
                    callback();
                }
        });
    }

    /// @brief 取消注册回调
    void UnregisterCallback(QMetaObject::Connection connection)
    {
        QObject::disconnect(connection);
    }

    /// @brief 获取缓存的状态数据
    /// @note 事件回调触发时，通过该接口获取的数据总是更新后的数据
    const auto& GetStatusData() const { return m_data; }

Q_SIGNALS:
    void EventOccurred(EventType);

public:
    enum { INVALID_VALUE = -1 };
    struct StoredStatusData
    {
        int ribbon_tab_bar_index { INVALID_VALUE };
        QDialog* showing_block_dialog {};

        QString preselected_command{};
        QString executed_command{};
    };
private:
    void InitConnections();
    void InitResponders();

    auto FindCommandEffects() const -> std::vector<std::reference_wrapper<const ResponderEffectNode>>;
    auto FindDialogEffects() const -> std::vector<std::reference_wrapper<const ResponderEffectNode>>;

    std::optional<std::reference_wrapper<const ResponderEffectNode>> FindEffect(const QString& command, const std::vector<std::reference_wrapper<const ResponderEffectNode>>& effects) const;
    void ExecuteEffects(std::vector<std::reference_wrapper<const ResponderEffectNode>>&& effects) const;
    bool TestIfClearDialogStack(const QString& command, std::vector<std::reference_wrapper<const ResponderEffectNode>>&& effects) const;

private:
    static QStringList ExtractQStringList(const QVariant& container);
    static bool Contains(const QVariant& container, const QString& value);

    gui::MainWindow* m_parent;
    StoredStatusData m_data;

    QMultiMap<ResponderRuleNode, ResponderEffectNode> m_command_rules{};
    QMultiMap<ResponderRuleNode, ResponderEffectNode> m_dialog_rules{};
};
}

#endif //STATUSRESPONDER_H
