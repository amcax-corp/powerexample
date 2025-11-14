

#pragma once
#include <Gui/Workbench/Workbench.h>

namespace Dev {

class DevWorkbench : public gui::Workbench
{
  public:
    DevWorkbench();
    virtual ~DevWorkbench();

    std::string Version() const override
    {
        return "1.0";
    }

    std::string PluginName() const override
    {
        return "Dev";
    }

    virtual QString Label() const override
    {
        return QObject::tr("Dev");
    }

    virtual QString Pixmap() const override
    {
        return ":icon/CAMWorkbench.png";
    }

    virtual QString GroupName() const override
    {
        return QObject::tr("开发");
    }

    virtual int BaseIndex() override
    {
        return 0;
    }

    virtual int BaseNavIndex() override
    {
        return 1;
    }

    virtual QMap<QString, QWidget*> CreatePreferrenceWidgetList() const override;
    virtual void RegistCommand() override;
    virtual void StartUp() override;
    virtual void InitData(app::Document* doc) override;

  public:
    virtual void CreateMainWindowPopupMenu(gui::MenuItem*) const;
    virtual std::vector<gui::Navigator*> GetNavigatorList() const override;

    virtual gui::MenuItem* SetupMenuBar() const override;
    virtual gui::ToolBarItem* SetupToolBars() const override;
    virtual QList<SARibbonCategory*> GetCategoryList() const override;
};

}  // namespace cam
