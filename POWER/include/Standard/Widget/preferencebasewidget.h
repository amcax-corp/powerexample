#ifndef PREFERENCEBASEWIDGET_H
#define PREFERENCEBASEWIDGET_H

// 如果包含头文件异常，请检查是否在Make(CMake/QMake)中添加了依赖库
#include "Widgets/ContainerBlock/BlockWorkbenchPreferenceWidget.h"

namespace Ui {
class PreferenceBaseWidget;
}

class PreferenceBaseWidget : public BlockWorkbenchPreferenceWidget
{
    Q_OBJECT

  public:
    PreferenceBaseWidget(QWidget* parent = nullptr);
    ~PreferenceBaseWidget();

    void InitBackgroundColor();
    void InitGeometryColor();
    void InitLogLevel();

  public slots:
    void SetParameterNode() override;
    void RestoreDefaultParameter() override;

  protected:
    virtual void UpdateUI() override;

  private:
    Ui::PreferenceBaseWidget* ui;

};
#endif  // PREFERENCEBASEWIDGET_H
