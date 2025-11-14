#pragma once

// 如果包含头文件异常，请检查是否在Make(CMake/QMake)中添加了依赖库
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Base/Object/RenderDistanceObject.h>
#include <Gui/View/View3DInventor.h>
#include <Base/ViewProvider/ViewProviderRenderDistance.h>

namespace Ui
{
    class RenderDistanceDialog;
}
namespace Dev
{
class RenderDistanceDialog : public BlockDialog
{
    Q_OBJECT

public:
    RenderDistanceDialog(Dev::RenderDistanceObject *obj, QWidget *parent = nullptr);
    ~RenderDistanceDialog();

public slots:
    // 点击确定时触发
    bool OnConfirmed() override;
    // 点击应用时触发
    bool OnApplied() override;
    // 点击重置时触发
    void OnResetted() override;
    // 点击取消时触发
    void OnCanceled() override;

private slots:
    void OnValueChanged(BlockBase *block, QString property);

private:
    void SetSelectionPointSize(int size);
    void ConnectPropertyData(BlockBase *block, std::string property);
    void RefreshRenderWindow();
private:
    Ui::RenderDistanceDialog *ui;
    Dev::RenderDistanceObject *m_object;

    gui::View3DInventor *m_view = nullptr;
};
}