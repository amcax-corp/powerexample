#ifndef SELECTIONCHANGES_H
#define SELECTIONCHANGES_H

#include "PFCGlobal.h"
#include <optional>
#include <string>
#include <vector>

namespace AMCAX {
class TopoShape;
}
namespace app {
class Document;
class DocumentObject;
}
namespace gui {

/// 选择身份标识
enum class SelectionIdentity
{
    Undefined,              // 未定义

    MouseHovered,           // 鼠标悬浮
    MouseLeaved,            // 鼠标离开

    MouseLeftClicked,       // 鼠标左键单击
    MouseRightClicked,      // 鼠标右键单击
    MouseMiddleClicked,     // 鼠标中键单击
    MouseDoubleClicked,     // 鼠标双击
    MouseRubberBand,        // 鼠标框选

    BlockSelectObjectInitialized,   // 选择控件初始化
    NavigatorChanged,       // 导航栏变更
    DocumentSwitched,       // 文档切换
    DocumentNotify,         // 文档通知

    Custom                  // 自定义
};

/// 选择数据包
class PFC_GUI_API SelectionData
{
public:
    bool IsEmpty() const;
    void Set(std::string_view doc_name, std::string_view obj_name, std::string_view sub_name);
    void Set(std::string_view doc_name, std::string_view obj_name, std::string_view sub_name, double x, double y, double z);
    void Clear();

    app::Document* GetDocument() const;
    std::optional<app::DocumentObject*> GetDocumentObject() const;
    AMCAX::TopoShape GetTopoShape() const;
    bool operator==(const SelectionData& other) const;
    bool operator!=(const SelectionData& other) const { return !(*this == other); }

    bool IsScatter() const;
    bool IsVertex() const;
    bool IsPoint() const;
    bool IsFace() const;
    bool IsEdge() const;
    bool IsBody() const;

    void SetMainAccepted(bool accpeted = true) const;

    std::string document_name {};
    std::string object_name {};
    std::string sub_name {};
    double x {};
    double y {};
    double z {};
    mutable bool accepted { true };
};

/// 选择变更数据包
class PFC_GUI_API SelectionChanges : public SelectionData
{
public:
    enum MsgType
    {
        // 为兼容事件保留以下枚举
        AddSelection,
        RemoveSelection,
        SetSelection,
        ClearSelection,
        SetPreselect,  // to signal observer the preselect has changed
        RemovePreselect,
        SetPreselectSignal,  // to request 3D view to change preselect
        PickedListChanged,
        ShowSelection,          // to show a selection
        HideSelection,          // to hide a selection
        RemovePreselectSignal,  // to request 3D view to remove preselect
        MovePreselect,          // to signal observer the mouse movement when preselect
        GetSelection,          // to get the current selection
        CustomSelection,

        // 新事件机制
        AddSelecting = AddSelection,                // 添加选择中的对象
        RemoveSelecting = RemoveSelection,          // 移除选择中对象
        ClearSelecting = ClearSelection,            // 清空选择中的对象

        Unknown = CustomSelection + 1,              // 无效事件
        HoverChanged,                               // 鼠标悬浮变更
        Start,                                      // 某一事务开始执行
        IgnoreSelection,                            // 忽略选择
        AdvancedResult,                             // 进阶计算结果
        AddSelected,                                // 添加已选择的对象
        RemoveSelected,                             // 移除已选择的对象
        ClearSelected,                              // 清空已选择的对象

        BeforeLoopStop,                             // 事务循环结束前
        NotifyBlockDialog,                          // 通知 BlockDialog 更新，由焦点控件代监听
        BeforeFinish,                               // 事务结束前
    };

    enum class SelectionSource
    {
        Unknown,            // 无效来源
        HoverChanged,       // 鼠标悬浮变更
        AddSelecting,       // 添加选择中的对象
        AddSelected,        // 添加已选择的对象
        RemoveSelecting,    // 移除选择中对象
        RemoveSelected,     // 移除已选择的对象
        ClearSelecting,     // 清空选择中的对象
        ClearSelected,      // 清空已选择的对象
        ClearAll,           // 清空全部选择对象
    };

    enum class SelectionEventReason
    {
        NoReason,

        Unknown_Source,         // 未知来源

        MultiSelect_Cancel,    // 多选状态下取消选中
        SingleSelect_Clear,    // 单选状态下清空原选中项
        SingleSelect_SelectBody,  // 单选状态下选中相同对象将转为体
        SingleSelect_RubberBand,    // 单选状态下框选忽略第二个及以后的对象
        GateFiltered,           // 不满足门
        AdvancedFailure,        // 增强失败
        NoAccepted,            // 无已接受的对象
        ReachedMaxLimit,        // 超出范围
        ObjectRemoved,          // 对象已移除
        ObjectNotFound,         // 对象未找到

        ObjectExisted,          // 对象在选择管理类中已存在
        ObjectNotExist,         // 对象在选择管理类中不存在
        ObjectContained,        // 对象在选择管理类中已被包含
    };

    bool IsValid() const { return source != SelectionSource::Unknown && identity != SelectionIdentity::Undefined; }
    void Init(std::string_view doc_name, std::string_view obj_name, std::string_view sub_name,
        double x, double y, double z, SelectionSource source, SelectionIdentity identity);
    void Init(std::string_view doc_name, std::string_view obj_name, std::string_view sub_name,
        SelectionSource source, SelectionIdentity identity);
    void Init(const SelectionData& data, SelectionSource source, SelectionIdentity identity);
    void Init(const SelectionChanges& change, MsgType event);
    void Reset();

    void SetAccepted(int index, bool accpted = true) const;
    std::vector<SelectionData> advanced_result{};

    MsgType m_type{ Unknown };
    SelectionEventReason reason { SelectionEventReason::NoReason };
    SelectionSource source { SelectionSource::Unknown };
    SelectionIdentity identity { SelectionIdentity::Undefined };
    bool finished { false };
};
}



#endif //SELECTIONCHANGES_H
