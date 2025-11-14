#pragma once

// 如果包含头文件异常，请检查是否在Make(CMake/QMake)中添加了依赖库
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Base/Object/BoxObject.h>

namespace Ui
{
    class BoxDialog;
}
namespace Dev
{
class BoxDialog : public BlockDialog
{
    Q_OBJECT

public:
    BoxDialog(Dev::BoxObject *obj, QWidget *parent = nullptr);
    ~BoxDialog();

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
    void OnValueChanged(BlockBase *block, QString key);

private:
    void ConnectPropertyData(BlockBase *block, std::string property);
    void UpdataBoxTopoShape();
    void SetSelectionPointSize(int size);

private:
    Ui::BoxDialog *ui;
    Dev::BoxObject *m_object;
};
}