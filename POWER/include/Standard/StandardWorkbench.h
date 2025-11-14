#pragma once
#include <Gui/Workbench/Workbench.h>

class SARibbonCategory;

namespace gui {

class StandardWorkbench : public Workbench
{
  public:
    StandardWorkbench();
    virtual ~StandardWorkbench();
    std::string ToolTip() const override
    {
        return "显示基础功能";
    }

    std::string Version() const override
    {
        return "1.0";
    }

    std::string PluginName() const override
    {
        return "StandardWorkbench";
    }

    virtual QString Label() const override
    {
        return QObject::tr("标准");
    }
    virtual QString Pixmap() const override
    {
        return ":icon/workbench/StandardWorkbench.png";
    }

    virtual QMap<QString, QWidget*> CreatePreferrenceWidgetList() const override;
    virtual void RegistCommand() override;
    virtual void StartUp() override;

    virtual std::vector<Navigator*> GetNavigatorList() const override;

    virtual MenuItem* SetupMenuBar() const override;
    virtual ToolBarItem* SetupToolBars() const override;
    virtual QList<SARibbonCategory*> GetCategoryList() const override;

    void RegistRules() const override;
};

}  // namespace gui
