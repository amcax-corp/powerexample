#pragma once

#include <Gui/Selection/Selection.h>
#include <Widgets/Block/BlockAbstractGeometry.h>
#include <Widgets/Block/BlockToggle.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <topology/TopoShape.hpp>

class PW_API BlockGeometryEditDialog : public BlockDialog
{
    Q_OBJECT

  public:
    explicit BlockGeometryEditDialog(QWidget* parent = nullptr);
    ~BlockGeometryEditDialog() = default;

    /// @brief 刷新对话框，清除数据
    virtual void Refresh();

  Q_SIGNALS:
    void SignalRefresh();

  public Q_SLOTS:
    bool OnConfirmed() override;
    bool OnApplied() override;
    void OnCanceled() override;

    /// @brief 在预览按钮被点击时触发
    /// @param checked true表示预览勾选框被选中, false表示未选中
    void OnPreviewChecked(bool checked);
    /// @brief 在参数改变(注册的输入控件值改变、拾取对象改变)时触发
    void OnParameterChanged();

  protected:
    void showEvent(QShowEvent* event) override;

    /// @brief 当进入拾取模式时，即几何控件进入焦点时触发，配置拾取模式的表现
    virtual void EnterPickMode();
    /// @brief 当退出拾取模式时，即几何控件失去焦点时触发，配置退出拾取模式的表现
    virtual void ExitPickMode();

    /*
     *  预览渲染流程
     */
    /// @brief 恢复预览生成前的额外渲染(如高亮、箭头等)
    virtual void ResumeRender() {}
    /// @brief 核心功能实现，根据已有的输入条件，调用算法计算几何编辑结果
    /// @return 以图元对象形式传递的计算结果
    virtual auto ReCompute() -> QList<AMCAX::TopoShape> { return {}; }
    /// @brief 传入生成的预览图元，生成额外渲染(如高亮、箭头等)
    virtual void RenderPreview(const QList<AMCAX::TopoShape>& inputs) {}

    /// @brief 获取计算结果
    /// @return 图元列表形式的结果
    const QList<AMCAX::TopoShape>& GetResults() const { return m_results; }
    // model是PowerCAM中的概念，这里不一定需要了
    virtual QStringList GenerateModelImplement(const QList<AMCAX::TopoShape>& inputs) { return {}; }

    /// @brief 生成预览图元
    void UpdatePreview();
    /// @brief 清除预览图元
    virtual void ClearPreview();

    /*
     *  生成结果
     */
    /// @brief 非虚的应用函数，实现应用按钮的功能
    bool ApplyImplement();
    /// @brief 非虚的确认函数，实现确认按钮的功能
    bool AcceptImplement();

    /// @brief 设置预览勾选框是否被选中
    /// @param checked true表示被选中，false表示未选中
    void SetPreviewChecked(bool checked);
    /// @brief 设置预览勾选框是否可见
    /// @param visible true表示可见，false表示不可见
    void SetPreviewVisible(bool visible);

    /// @brief 注册参数输入控件，用于在参数改变时触发OnParameterChanged()
    /// @param input 指定的控件指针
    void RegisterParametersInput(QWidget* input) const;

    void RegisterFocusChain(BlockAbstractGeometry* widget) override;

  private:
    BlockToggle* m_preview_check = nullptr;

    QStringList m_model_names;
    QList<AMCAX::TopoShape> m_results;
};
