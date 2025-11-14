#pragma once

#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>
class ParameterGroup;
class PW_API BlockWorkbenchPreferenceWidget : public QWidget
{
    Q_OBJECT
  public:
    BlockWorkbenchPreferenceWidget(QWidget* parent = nullptr);
    ~BlockWorkbenchPreferenceWidget();

  public slots:
    virtual void SetParameterNode(){}
    virtual void RestoreDefaultParameter(){}

  protected:
    virtual void UpdateUI(){};

  private:
    ParameterGroup* m_parameter_node{nullptr};
};
