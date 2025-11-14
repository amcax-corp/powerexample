
#ifndef GUI_SELECTION_H
#define GUI_SELECTION_H

#include <Base/Observer.h>
#include <Base/Type.h>
#include "App/Document.h"
#include "App/DocumentObject.h"
#include "Gui/Application.h"
#include "SelectionChanges.h"
#include "BoostSignalDefine.h"

#include <utility>
#include <vector>

#include <common/PointT.hpp>
#include <qcompilerdetection.h>

namespace app {
class Document;
class DocumentObject;
}  // namespace app

namespace gui {
class SelectionSingleton;
class SelectionBlocker;
class SelectionRelay;
struct SelectionSingletonData;

class EnhancedSelectionManager;
class SelectionGateManager;
class SelectionGate;
enum class BasicPickFilter;

/// 选择解析层级
enum class SelectionResolve
{
    Exact = 0,
    Contained = 1,      // 被包含，选择管理类中的对象包含指定参数，如体包含面
    Contains = 2        // 包含，指定参数包含选择管理类中的对象
};

/// 选择观察者
class PFC_GUI_API SelectionObserver : protected base::Observer<const SelectionChanges&>
{
public:
    explicit SelectionObserver(bool attach = true, SelectionResolve level = SelectionResolve::Exact);
    SelectionObserver(bool lazy, bool attach, SelectionResolve level = SelectionResolve::Exact);
    ~SelectionObserver() override;

    bool BlockSelection(bool block);
    bool IsSelectionBlocked() const;
    bool IsSelectionAttached() const;

    void AttachSelection();
    void DetachSelection();

    /// @brief 选择过滤前过滤
    /// @note 避免大量无用事件触发 OnSelectionChanged
    virtual bool SelectionChangesPrefilter(const SelectionChanges& msg) const;

private:
    /// @brief 选择事件回调
    /// @note 重写该方法时尽可能优先过滤掉不需要处理的事件，提升整体选择效率
    virtual void OnSelectionChanged(const SelectionChanges& msg) {}
    void OnChange(base::Subject<MessageType>&, MessageType reason) override;
    void OnDestroy(base::Subject<MessageType>&) override;

private:
    SelectionResolve m_resolve;
    bool m_block{};
    bool m_lazy{};
};

/// 选择返回值
enum class SelectionResult
{
    Invalid,  // 未知结果
    Success,  // 成功

    InQueue,  // 已入队

    UnexpectedInput,  // 意外输入
    UndefinedStatus,  // 未定义状态
    Unsupported,      // 不支持
};

class PFC_GUI_API SelectionSingleton final : protected base::Subject<const SelectionChanges&>
{
public:
    SelectionSingleton();
    ~SelectionSingleton() override;

    using SelectionArray = std::vector<SelectionData>;

    static SelectionSingleton& GetInstance();

    /*
     *  数据相关
     */
    /// @brief 获取上次鼠标悬浮对象
    const SelectionData& GetLastHovered() const { return m_last_hovered; }
    /// @brief 获取当前鼠标悬浮对象
    const SelectionData& GetHovered() const { return m_hovered; }

    /// @brief 获取选择中的对象
    Q_DECL_DEPRECATED_X("Use GetSelectings()") auto GetAllSelection() const { return GetSelectings(); }
    const SelectionArray& GetSelectings() const { return m_selectings; }
    /// @brief 获取已选择的对象
    const SelectionArray& GetSelecteds() const { return m_selecteds; }
    /// @brief 获取选择中的数量
    int GetSelectingCount() const { return (int)m_selectings.size(); }
    /// @brief 获取已选择的数量
    int GetSelectedCount() const { return (int)m_selecteds.size(); }

    /// @brief 根据类型获取正在选择的对象
    /// @note 此函数兼容原功能，等价于 GetObjectsOfTypeInSelecting()
    template<typename T> Q_DECL_DEPRECATED_X("Use GetObjectsOfTypeInSelecting()") std::vector<T*> GetObjectsOfType(std::string_view doc_name = "") const { return GetObjectsOfTypeInSelecting<T>(doc_name); }
    template<typename T> std::vector<T*> GetObjectsOfTypeInSelecting(std::string_view doc_name = "") const;
    std::vector<app::DocumentObject*> GetObjectsOfTypeInSelecting(const base::Type& type_id, std::string_view doc_name = "") const;
    std::vector<app::DocumentObject*> GetObjectsOfTypeInSelecting(std::string_view type_name, std::string_view doc_name = "") const;

    /// @brief 根据类型获取已选择的对象
    template<typename T> std::vector<T*> GetObjectsOfTypeInSelected(std::string_view doc_name = "") const;
    std::vector<app::DocumentObject*> GetObjectsOfTypeInSelected(const base::Type& type_id, std::string_view doc_name = "") const;
    std::vector<app::DocumentObject*> GetObjectsOfTypeInSelected(std::string_view type_name, std::string_view doc_name = "") const;

    /// @brief 根据对象获取正在选择的子对象
    std::vector<std::string_view> GetSubNamesOfObjectInSelecting(std::string_view obj_name, std::string_view doc_name = "") const;

    /// @brief 根据对象获取已选择的子对象
    std::vector<std::string_view> GetSubNamesOfObjectInSelected(std::string_view obj_name, std::string_view doc_name = "") const;

    /// @brief 返回当前正在选择对象中指定type的数量
    template<typename T> Q_DECL_DEPRECATED_X("Use CountObjectsOfTypeInSelecting()") unsigned int CountObjectsOfType(std::string_view doc_name = "") const { return CountObjectsOfTypeInSelecting<T>(doc_name); }
    Q_DECL_DEPRECATED_X("Use CountObjectsOfTypeInSelecting()") unsigned int CountObjectsOfType(std::string_view type_name, std::string_view doc_name = "") const { return CountObjectsOfTypeInSelecting(type_name, doc_name); }
    Q_DECL_DEPRECATED_X("Use CountObjectsOfTypeInSelecting()") unsigned int CountObjectsOfType(const base::Type& type_id, std::string_view doc_name = "") const { return CountObjectsOfTypeInSelecting(type_id, doc_name);}
    template<typename T> unsigned int CountObjectsOfTypeInSelecting(std::string_view doc_name = "") const;
    unsigned int CountObjectsOfTypeInSelecting(const base::Type& type_id, std::string_view doc_name = "") const;
    unsigned int CountObjectsOfTypeInSelecting(std::string_view type_name, std::string_view doc_name = "") const;

    /// @brief 返回当前已选择对象中指定type的数量
    template<typename T> unsigned int CountObjectsOfTypeInSelected(std::string_view doc_name = "") const;
    unsigned int CountObjectsOfTypeInSelected(const base::Type& type_id, std::string_view doc_name = "") const;
    unsigned int CountObjectsOfTypeInSelected(std::string_view type_name, std::string_view doc_name = "") const;

    /// @brief 当前是否有正在选择的对象
    Q_DECL_DEPRECATED_X("Use HasSelecting()") bool HasSelection() const { return HasSelecting(); }
    bool HasSelecting() const { return !m_selectings.empty(); }
    /// @brief 当前是否由已选择的对象
    bool HasSelected() const { return !m_selecteds.empty(); }

    /*
     *  状态相关
     */
    /// @brief 当前鼠标是否处于悬浮状态
    /// @brief 此状态说明鼠标悬浮在了某个对象上
    bool IsHovered() const;
    /// @brief 当前鼠标是否处于空闲状态
    /// @note 此状态说明鼠标没有悬浮在任何对象上
    bool IsIdle() const;

    /*
     *  基本过滤
     *  BasicPickFilter 用于控制用户当前鼠标可以选择的基本过滤
     *  BasicPickRange 为用户允许的基本过滤的集合
     */
    /// @brief 阻塞当前基本过滤、基本过滤允许范围，并返回一个临时阻塞器
    /// @note 若当前已经阻塞，则返回为 std::nullopt
    std::optional<SelectionBlocker> BlockBasicPickFilterWithBlocker();
    /// @brief 阻塞当前基本过滤、基本过滤允许范围
    /// @return true - 阻塞成功; false - 已阻塞
    /// @note 调用该函数后，需要手动调用 RestoreBasicPickFilter() 恢复原状态
    bool BlockBasicPickFilter();
    /// @brief 恢复阻塞前的基本过滤、基本过滤允许范围
    /// @return true - 恢复成功; false - 未阻塞
    bool RestoreBasicPickFilter();
    /// @brief 设置基本过滤
    /// @return 之前设置的基本过滤
    BasicPickFilter SetBasicPickFilter(BasicPickFilter filter);
    BasicPickFilter SetBasicPickFilter(BasicPickFilter filter, bool on);
    /// @brief 获取当前基本过滤
    [[nodiscard]] BasicPickFilter GetBasicPickFilter() const;
    /// @brief 判断当前指定基本过滤是否生效
    bool TestBasicPickFilter(BasicPickFilter filter) const;
    /// @brief 基本过滤变更
    BoostSignal<void(BasicPickFilter)> SignalBasicPickFilterChanged{};
    /// @brief 设置基本过滤的允许范围
    /// @return 之前设置的基本过滤允许范围
    BasicPickFilter SetBasicPickRange(BasicPickFilter range);
    BasicPickFilter SetBasicPickRange(BasicPickFilter range, bool on);
    /// @brief 获取当前基本过滤允许范围
    [[nodiscard]] BasicPickFilter GetBasicPickRange() const;
    /// @brief 判断当前指定基本过滤是否允许
    bool TestBasicPickRange(BasicPickFilter range) const;
    /// @brief 基本过滤范围变更
    BoostSignal<void(BasicPickFilter)> SignalBasicPickRangeChanged{};

    /*
     *  过滤门
     */
    /// @brief 获取门管理器
    [[nodiscard]] std::shared_ptr<SelectionGateManager> GetSelectionGateManager() const { return m_gate_manager; }
    /// @brief 取出门管理器
    [[nodiscard]] std::shared_ptr<SelectionGateManager> TakeSelectionGateManager();
    /// @brief 设置门管理器
    void SetSelectionGateManager(const std::shared_ptr<SelectionGateManager>& gate_manager);
    /// @brief 设置门
    /// @note 该函数兼容原功能，等价于 SetSelectionGate()
    void AddSelectionGate(SelectionGate* gate) { SetSelectionGate(gate); }
    void SetSelectionGate(SelectionGate* gate);
    /// @brief 移除门
    /// @note 该函数兼容原功能，等价于 ClearSelectionGate()
    void RemoveSelectionGate() { ClearSelectionGate(); }
    void ClearSelectionGate();

    /*
     *  选择模式/选择数量限制
     */
    /// @brief 设置模式为单选
    /// @note 该函数将取消默认多选，并设置选择数量为 1
    void SetSingleSelectionMode();

    enum { NO_LIMIT = -1 };
    /// @brief 设置模式为多选
    /// @note 该函数将开启默认多选，并设置选择数量
    void SetMultiSelectionMode(int limit = NO_LIMIT);
    /// @brief 设置可选数量
    /// @note 有效参数为 NO_LIMIT 和正整数，其他值将被忽略
    void SetSelectionLimit(int limit = NO_LIMIT);
    /// @brief 重置可选数量至初始状态
    /// @note 当模态窗关闭时调用该函数以恢复默认状态
    void ResetSelectionLimit();
    /// @brief 是否为单选模式
    bool IsSingleSelectionMode() const;
    /// @brief 是否为多选模式
    bool IsMultiSelectionMode() const;
    /// @brief 获取选择数量限制
    int GetSelectionLimit() const;

    /*
     *  选择增强
     *  选择模块中自带一个增强器，默认不可用
     */
    /// @brief 获取选择增强器
    [[nodiscard]] auto GetEnhandedSelectionManager() const { return m_enhanced_selection_manager;}
    /// @brief 设置选择增强器
    void SetEnhancedSelectionManager(std::shared_ptr<EnhancedSelectionManager> enhanced_selection_manager);
    /// @brief 取出选择增强器
    std::shared_ptr<EnhancedSelectionManager> TakeEnhancedSelectionManager();
    /// @brief 重置选择增强器
    void ResetEnhancedSelectionManager();
    /// @brief 选择增强其变更
    BoostSignal<void()> SignalEnhancedSelecionManagerChanged{};

    /*
     *  自动清空
     */
    /// @brief 阻塞当前自动清空状态，指定一个自动清空状态，并返回一个临时阻塞器
    /// @note 若当前已经阻塞，则返回为 std::nullopt
    std::optional<SelectionBlocker> BlockAutoClearWithBlocker(bool auto_clear = false);
    /// @brief 阻塞当前自动清空状态，指定一个自动清空状态
    /// @return true - 阻塞成功; false - 已阻塞
    /// @note 调用该函数后，需要手动调用 RestoreAutoClear() 恢复原状态
    bool BlockAutoClear(bool auto_clear = false);
    /// @brief 恢复阻塞前的自动清空状态
    /// @return true - 恢复成功; false - 未阻塞
    bool RestoreAutoClear();
    /// @brief 设置当前自动清空状态
    /// @return 返回设置前的自动清空状态
    bool SetAutoClear(bool auto_clear);
    /// @brief 获取当前自动清空状态
    bool GetAutoClear() const;
    /// @brief 自动清空状态变更信号
    BoostSignal<void(bool)> SignalAutoClearChanged{};

    /*
     *  多选状态
     */
    /// @brief 阻塞当前默认多选状态，指定是否默认多选状态，并返回一个临时阻塞器
    /// @note 若当前已经阻塞，则返回为 std::nullopt
    std::optional<SelectionBlocker> BlockMultiSelectWithBlocker(bool multi_select = false);
    /// @brief 阻塞当前默认多选状态，指定是否默认多选状态
    /// @return true - 阻塞成功; false - 已阻塞
    /// @note 调用该函数后，需要手动调用 RestoreMultiSelect() 恢复原状态
    bool BlockMultiSelect(bool multi_select = false);
    /// @brief 恢复阻塞前的默认多选状态
    /// @return true - 恢复成功; false - 未阻塞
    bool RestoreMultiSelect();
    /// @brief 设置当前是否默认多选
    /// @return 返回设置前的默认多选状态
    bool SetMultiSelect(bool multi_select);
    /// @brief 获取当前默认多选状态
    bool GetMultiSelect() const;
    /// @brief 默认多选状态变更信号
    BoostSignal<void(bool)> SignalMultiSelectChanged{};
    /// @brief 当前是否按下多选建
    static bool IsMultiSelectKeyDown();
    /// @brief 当前是否处于多选状态
    bool IsMultiSelecting() const;

    /*
     *  取消选择操作
     */
    /// @brief 当前是否按下取消选择键
    static bool IsDeselectKeyDown();

    /*
     *  是否允许框选
     */
    /// @brief 阻塞当前框选状态，指定是否允许框选状态，并返回一个临时阻塞器
    /// @note 若当前已经阻塞，则返回为 std::nullopt
    std::optional<SelectionBlocker> BlockRubberBandWithBlocker(bool enable_rubber_band = false);
    /// @brief 阻塞当前框选状态，指定是否允许框选状态
    /// @return true - 阻塞成功; false - 已阻塞
    /// @note 调用该函数后，需要手动调用 RestoreAutoClear() 恢复原状态
    bool BlockRubberBand(bool enable_rubber_band = false);
    /// @brief 恢复阻塞前的框选状态
    /// @return true - 恢复成功; false - 未阻塞
    bool RestoreRubberBand();
    /// @brief 设置是否允许框选状态
    /// @return 返回设置前的自动清空状态
    bool SetRubberBand(bool enable_rubber_band);
    /// @brief 获取是否允许框选状态
    bool GetRubberBand() const;
    /// @brief 是否允许框选状态变更信号
    BoostSignal<void(bool)> SignalRubberBandChanged{};

    /*
     *  操作相关
     */
    /// @brief 开启连续操作事务，使多次操作后仅发送一次 BeforeFinish 事件
    /// @note 需要调用 RestoreSeparating() 取消事务
    void StartRelay();
    std::unique_ptr<SelectionRelay> StartRelayWithBlocker();
    /// @brief 取消连续操作事务
    void StopRelay();

    /// @brief 设置鼠标悬浮对象
    /// @param doc_name object_name sub_name 描述对象的信息
    /// @param x y z 进入位置
    /// @param identity 调用者身份
    /// @event HoverChanged 更新 m_last_hovered、m_hovered 后发送
    /// @return
    ///     Success - 设置成功
    ///     UnexpectedInput - 输入无效
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件：Start、HoverChanged
    SelectionResult SetHovered(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        double x = 0., double y = 0., double z = 0., SelectionIdentity identity = SelectionIdentity::Custom);
    /// @brief 设置鼠标离开对象
    /// @param doc_name object_name sub_name 离开对象的信息
    /// @param x y z 离开位置
    /// @param identity 调用者身份
    /// @event HoverChanged 更新 m_last_hovered、m_hovered 后发送
    /// @return
    ///     Success - 设置成功
    ///     UnexpectedInput - 输入无效
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件：Start、HoverChanged
    SelectionResult SetLeaved(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        double x = 0., double y = 0., double z = 0., SelectionIdentity identity = SelectionIdentity::Custom);

    /// @brief 添加选择对象（旧）
    /// @param doc_name object_name sub_name 添加对象的信息
    /// @param x y z 添加位置
    /// @param identity 调用者身份
    /// @note 该函数兼容原功能，等价于 AddSelecting()
    Q_DECL_DEPRECATED_X("Use AddSelecting()") SelectionResult AddSelection(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        double x = 0., double y = 0., double z = 0., SelectionIdentity identity = SelectionIdentity::Custom)
    {
        return AddSelecting(doc_name, object_name, sub_name, x, y, z, identity);
    }
    Q_DECL_DEPRECATED_X("Use AddSelecting()") SelectionResult AddSelection(const SelectionChanges& change, SelectionIdentity identity = SelectionIdentity::Custom)
    {
        return AddSelecting(change, identity);
    }
    Q_DECL_DEPRECATED_X("Use AddSelecting()") SelectionResult AddSelection(app::DocumentObject* pObject)
    {
        return pObject ? AddSelecting(pObject->GetDocument()->GetName(), pObject->GetNameInDocument()) : SelectionResult::UnexpectedInput;
    }
    Q_DECL_DEPRECATED_X("Use AddSelectings()") SelectionResult AddSelections(std::string_view doc_name, std::string_view object_name, const std::vector<std::string>& sub_names,
        SelectionIdentity identity = SelectionIdentity::Custom)
    {
        return AddSelectings(doc_name, object_name, sub_names, identity);
    }
    Q_DECL_DEPRECATED_X("Use AddSelectings()") SelectionResult ShowSelections(std::string_view doc_name, std::string_view object_name, const std::vector<std::string>& sub_names,
    SelectionIdentity identity = SelectionIdentity::Custom)
    {
        return AddSelectings(doc_name, object_name, sub_names, identity);
    }
    Q_DECL_DEPRECATED_X("Use AddSelectings()") SelectionResult ShowSelections(std::string_view doc_name, const std::vector<std::string>& object_names,
        SelectionIdentity identity = SelectionIdentity::Custom)
    {
        return AddSelectings(doc_name, object_names, identity);
    }
    /// @brief 添加正在选择的对象
    /// @param doc_name object_name sub_name 离开对象的信息
    /// @param x y z 离开位置
    /// @param identity 调用者身份
    /// @return
    ///     Success - 设置成功
    ///     InQueue - 已入队
    ///     UnexpectedInput - 输入无效
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件: Start、IgnoreSelection、RemoveSelection、AdvancedResult、ClearSelection、AddSelection
    ///     IgnoreSelection Reason: ObjectNotFound、ObjectRemoved、GateFiltered、GateFiltered、NoAccepted
    ///     RemoveSelection Reason: MultiSelect_Cancel
    ///     ClearSelection Reason: SingleSelect_Clear
    /// @note 当一次添加多个正在选择的对象时，优先使用 AddSelectings()
    SelectionResult AddSelecting(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        double x = 0., double y = 0., double z = 0., SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelecting(const SelectionData& change, SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelecting(const app::DocumentObject* doc_obj, double x = 0., double y = 0., double z = 0.,
        SelectionIdentity identity = SelectionIdentity::Custom);

    SelectionResult AddSelectings(std::string_view doc_name, std::string_view object_name, const std::vector<std::string>& sub_names,
        SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelectings(std::string_view doc_name, const std::vector<std::string>& object_name, SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelectings(std::span<SelectionData> selections, SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelectings(std::span<app::DocumentObject*> doc_objs, SelectionIdentity identity = SelectionIdentity::Custom);
    /// @brief 添加已选择对象
    /// @param doc_name object_name sub_name 离开对象的信息
    /// @param x y z 离开位置
    /// @param identity 调用者身份
    /// @return
    ///     Success - 设置成功
    ///     InQueue - 已入队
    ///     UnexpectedInput - 输入无效
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件：Start、IgnoreSelection、AddSelected
    ///     IgnoreSelection Reason: ObjectNotFound、ObjectRemoved、ObjectExisted
    /// @note 当一次添加多个正在选择的对象时，优先使用 AddSelecteds()
    SelectionResult AddSelected(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        double x = 0., double y = 0., double z = 0., SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelected(const SelectionData& change, SelectionIdentity identity = SelectionIdentity::Custom);

    SelectionResult AddSelecteds(std::string_view doc_name, std::string_view object_name, const std::vector<std::string>& sub_names,
        SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelecteds(std::string_view doc_name, const std::vector<std::string>& object_names,
        SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult AddSelecteds(std::span<SelectionData> selections,
                                 SelectionIdentity identity = SelectionIdentity::Custom);

    /// @brief 移除正在选择的对象（旧）
    /// @param doc_name object_name sub_name 移除指定对象的信息
    /// @param level 移除的匹配等级
    /// @param identity 调用者身份
    /// @note 该函数兼容原功能，等价于 RemoveSelecting
    Q_DECL_DEPRECATED_X("Use RemoveSelecting()") SelectionResult RemoveSelection(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        SelectionResolve level = SelectionResolve::Exact, SelectionIdentity identity = SelectionIdentity::Custom)
    { return RemoveSelecting(doc_name, object_name, sub_name, level, identity); }
    Q_DECL_DEPRECATED_X("Use RemoveSelectings()") SelectionResult HideSelections(std::string_view doc_name, const std::vector<std::string>& object_names,
    SelectionResolve level = SelectionResolve::Exact, SelectionIdentity identity = SelectionIdentity::Custom)
    { return RemoveSelectings(doc_name, object_names, identity); }
    /// @brief 移除正在选择的对象
    /// @param doc_name object_name sub_name 移除指定对象的信息
    /// @param level 移除的匹配等级
    /// @param identity 调用者身份
    /// @return
    ///     Success - 设置成功
    ///     InQueue - 已入队
    ///     UnexpectedInput - 输入无效
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件: Start、IgnoreSelection、RemoveSelection
    ///     IgnoreSelection Reason: ObjectNotFound、ObjectRemoved、ObjectNotExist
    SelectionResult RemoveSelecting(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        SelectionResolve level = SelectionResolve::Exact, SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult RemoveSelecting(const app::DocumentObject* doc_obj, SelectionResolve level = SelectionResolve::Exact, SelectionIdentity identity = SelectionIdentity::Custom);

    SelectionResult RemoveSelectings(std::string_view doc_name, std::string_view object_name, const std::vector<std::string>& sub_names, SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult RemoveSelectings(std::string_view doc_name, const std::vector<std::string>& object_names, SelectionIdentity identity = SelectionIdentity::Custom);
    /// @brief 移除已选择的对象
    /// @param doc_name object_name sub_name 移除指定对象的信息
    /// @param level 移除的匹配等级
    /// @param identity 调用者身份
    /// @return
    ///     Success - 设置成功
    ///     InQueue - 已入队
    ///     UnexpectedInput - 输入无效
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件: Start、IgnoreSelection、RemoveSelected
    ///     IgnoreSelection Reason: ObjectNotFound、ObjectRemoved、ObjectNotExist
    SelectionResult RemoveSelected(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        SelectionResolve level = SelectionResolve::Exact, SelectionIdentity identity = SelectionIdentity::Custom);
    SelectionResult RemoveSelected(const app::DocumentObject* doc_obj, SelectionResolve level = SelectionResolve::Exact, SelectionIdentity identity = SelectionIdentity::Custom);

    /// @brief 清空所有选中对象（旧）
    /// @param doc_name (已废弃)
    /// @param identity 调用者身份
    /// @note 该函数兼容原功能，等价于 ClearSelecting()
    SelectionResult ClearSelection(std::string_view doc_name = "", SelectionIdentity identity = SelectionIdentity::Custom)
    { return ClearAllSelection(identity); }
    /// @brief 清空所有正在选中对象
    /// @param identity 调用者身份
    /// @return
    ///     Success - 设置成功
    ///     InQueue - 已入队
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件: Start、ClearSelection
    SelectionResult ClearSelecting(SelectionIdentity identity = SelectionIdentity::Custom);
    /// @brief 清空所有已选中对象
    /// @param identity 调用者身份
    /// @return
    ///     Success - 设置成功
    ///     InQueue - 已入队
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件: Start、ClearSelected
    SelectionResult ClearSelected(SelectionIdentity identity = SelectionIdentity::Custom);
    /// @brief 清空所有正在选中及已选中的对象
    /// @param identity 调用者身份
    /// @return
    ///     Success - 设置成功
    ///     InQueue - 已入队
    ///     UndefinedStatus - 当前状态未定义
    ///     Unsupported - 不支持的身份
    /// @note 触发事件: Start、ClearSelected、ClearSelecting
    SelectionResult ClearAllSelection(SelectionIdentity identity = SelectionIdentity::Custom);
    /// @brief 判断指定对象是否在正在选中或已选中（旧）
    /// @param doc_name object_name sub_name 指定对象信息
    /// @param level 匹配等级
    /// @note 该函数兼容原功能，等价于 TestSelected().value_or(false) || TestSelecting().value_or(false)
    bool IsSelected(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        SelectionResolve level = SelectionResolve::Exact) const;
    // bool IsSelected(app::DocumentObject* obj, std::string_view sub_name = "", SelectionResolve level = SelectionResolve::Exact) const;
    /// @brief 判断指定对象是否正在选中
    /// @return
    ///     std::nullopt 意外情况无法判断
    ///     true 传入参数满足匹配条件
    ///     false 传入参数不满足匹配条件
    /// @note std::optional<>直接放进 if() 中等价于 {true} == {false} == true, std::nullopt == false
    ///     如果认为意外情况等价于 false，要使用 .value_or(false)，此时等价于 {true} == true, std::nullopt == {false} == false
    std::optional<bool> TestSelecting(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        SelectionResolve level = SelectionResolve::Exact) const;
    std::optional<bool> TestSelecting(const app::DocumentObject* document_object, SelectionResolve level = SelectionResolve::Exact) const;
    std::optional<bool> TestSelecting(const SelectionData& change, SelectionResolve level = SelectionResolve::Exact) const
    { return TestSelecting(change.document_name, change.object_name, change.sub_name, level); }
    /// @brief 判断指定对象是否已选中
    /// @return
    ///     std::nullopt 意外情况无法判断
    ///     true 传入参数满足匹配条件
    ///     false 传入参数不满足匹配条件
    /// @note std::optional<>直接放进 if() 中等价于 {true} == {false} == true, std::nullopt == false
    ///     如果认为意外情况等价于 false，要使用 .value_or(false)，此时等价于 {true} == true, std::nullopt == {false} == false
    std::optional<bool> TestSelected(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        SelectionResolve level = SelectionResolve::Exact) const;
    std::optional<bool> TestSelected(const app::DocumentObject* document_object, SelectionResolve level = SelectionResolve::Exact) const;
    std::optional<bool> TestSelected(const SelectionData& change, SelectionResolve level = SelectionResolve::Exact) const
    { return TestSelected(change.document_name, change.object_name, change.sub_name, level); }

    /// @brief 重置
    /// @note 恢复为初始状态
    void Reset();

    /*
     *  操作记录
     */
    /// @brief 获取初始事件
    const SelectionChanges& GetInitialEvent() const;
    ///@brief 获取已完成操作
    const std::list<SelectionChanges>& GetCompletedEvents() const;

    /*
     *  状态信号
     */
    /// @brief 选择操作完全结束
    /// @note 该信号在清空初始事件以及清空已完成操作列表后触发
    BoostSignal<void(const SelectionChanges&)> SignalFinished;

    SelectionSingleton(const SelectionSingleton&) = delete;
    SelectionSingleton& operator=(const SelectionSingleton&) = delete;
    SelectionSingleton(SelectionSingleton&&) = delete;
    SelectionSingleton& operator=(SelectionSingleton&&) = delete;

  private:
    friend class SelectionObserver;

    static app::Document* GetDocument(std::string_view doc_name);
    static std::optional<std::tuple<app::DocumentObject*, std::string_view>> GetObjectOfType(const SelectionData& object, const base::Type& type);

    SelectionResult StartUniversalProcess(std::string_view doc_name, std::string_view object_name, std::string_view sub_name,
        double x, double y, double z, SelectionIdentity identity, SelectionChanges::SelectionSource source);
    SelectionResult StartUniversalProcess(std::string_view doc_name, std::string_view object_name, const std::vector<std::string_view>& sub_names,
        SelectionIdentity identity, SelectionChanges::SelectionSource source);
    SelectionResult StartUniversalProcess(std::string_view doc_name, std::string_view object_name, const std::vector<std::string>& sub_names,
        SelectionIdentity identity, SelectionChanges::SelectionSource source);
    SelectionResult StartUniversalProcess(std::string_view doc_name, const std::vector<std::string>& object_names,
        SelectionIdentity identity, SelectionChanges::SelectionSource source);
    SelectionResult StartUniversalProcess(std::span<SelectionData> selection,
        SelectionIdentity identity, SelectionChanges::SelectionSource source);

    void StartEventLoop();
    SelectionChanges::SelectionEventReason Transact(const SelectionChanges& changes);
    SelectionChanges::SelectionEventReason TransactHoverChanged(SelectionChanges changes);
    SelectionChanges::SelectionEventReason TransactAddSelecting(SelectionChanges changes);
    SelectionChanges::SelectionEventReason TransactAddSelected(SelectionChanges changes);
    SelectionChanges::SelectionEventReason TransactRemoveSelecting(SelectionChanges changes);
    SelectionChanges::SelectionEventReason TransactRemoveSelected(SelectionChanges changes);
    SelectionChanges::SelectionEventReason TransactClearSelecting(SelectionChanges changes);
    SelectionChanges::SelectionEventReason TransactClearSelected(SelectionChanges changes);
    SelectionChanges::SelectionEventReason TransactClearAll(SelectionChanges changes);
    void TransactFinish();

    static bool TestSourceIdentityValid(SelectionChanges::SelectionSource event, SelectionIdentity identity);
    static bool CompareWithResolve(std::string_view sub_name_from_param, std::string_view sub_name_from_storage, SelectionResolve level);

    void RemoveFromSelecting(const SelectionData& data, SelectionResolve level = SelectionResolve::Exact);
    void RemoveFromSelected(const SelectionData& data, SelectionResolve level = SelectionResolve::Exact);

    std::optional<int> FindFromSelecting(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
        SelectionResolve level = SelectionResolve::Exact) const;
    std::optional<int> FindFromSelected(std::string_view doc_name, std::string_view object_name, std::string_view sub_name = "",
    SelectionResolve level = SelectionResolve::Exact) const;

private:
    SelectionSingletonData* m_data;
    bool m_relay { false };

    std::shared_ptr<SelectionGateManager> m_gate_manager;
    std::shared_ptr<EnhancedSelectionManager> m_enhanced_selection_manager;

    SelectionData m_last_hovered{}, m_hovered{};
    SelectionArray m_selectings{};
    SelectionArray m_selecteds{};
};

template<typename T>
std::vector<T*> SelectionSingleton::GetObjectsOfTypeInSelecting(std::string_view doc_name) const
{
    if (!doc_name.empty() && (!app::GetApplication().GetActiveDocument() || app::GetApplication().GetActiveDocument()->GetName() != doc_name)) return {};

    std::vector<T*> results;
    for (const auto& selecting : m_selectings)
    {
        if (selecting.GetDocument() != GetDocument(doc_name)) continue;
        if (auto opResult { GetObjectOfType(selecting, T::GetClassType())})
        {
            app::DocumentObject* result{};
            std::tie(result, std::ignore) = opResult.value();
            results.push_back(static_cast<T*>(result));
        }
    }
    return results;
}
template<typename T>
std::vector<T*> SelectionSingleton::GetObjectsOfTypeInSelected(std::string_view doc_name) const
{
    std::vector<T*> results;
    for (const auto& selected : m_selecteds)
    {
        if (selected.GetDocument() != GetDocument(doc_name))
            continue;
        if (auto opResult{GetObjectOfType(selected, T::GetClassType())})
        {
            app::DocumentObject* result{};
            std::tie(result, std::ignore) = opResult.value();
            results.push_back(static_cast<T*>(result));
        }
    }
    return results;
}
template<typename T>
unsigned int SelectionSingleton::CountObjectsOfTypeInSelecting(std::string_view doc_name) const
{
    return std::count_if(m_selectings.begin(), m_selectings.end(), [doc_name](const auto& selecting) {
        return selecting.GetDocument() == GetDocument(doc_name) && GetObjectOfType(selecting, T::GetClassType());
    });
}
template<typename T>
unsigned int SelectionSingleton::CountObjectsOfTypeInSelected(std::string_view doc_name) const
{
    return std::count_if(m_selecteds.begin(), m_selecteds.end(), [doc_name](const auto& selected) {
        return selected.GetDocument() == GetDocument(doc_name) && GetObjectOfType(selected, T::GetClassType());
    });
}
inline SelectionSingleton& Selection()
{
    return SelectionSingleton::GetInstance();
}
}

#endif  // GUI_SELECTION_H
