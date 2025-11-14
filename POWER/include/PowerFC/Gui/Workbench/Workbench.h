
#ifndef GUI_WORKBENCH_H
#define GUI_WORKBENCH_H

#pragma once
#include <Base/IPlugin.h>
#include <Base/Parameter.h>
#include <Gui/Workbench/Menu/MenuManager.h>
#include <Gui/Workbench/Navigator/Navigator.h>
#include <Gui/Workbench/ToolBar/ToolBarManager.h>
#include <QList>
#include <QStringList>
#include <list>
#include <string>

class SARibbonCategory;

namespace app {
class Document;
}

namespace gui {
class MenuItem;
class ToolBarItem;
class WorkbenchManager;

class PFC_GUI_API Workbench : public base::IPlugin
{
public:
    Workbench();
    virtual ~Workbench();

    virtual std::string ToolTip() const;

    virtual std::string Version() const override;

    virtual std::string PluginName() const override;

    virtual int BaseIndex();

    virtual int BaseNavIndex();

    virtual QString Label() const;

    virtual QString Pixmap() const;

    virtual QString GroupName() const;

    virtual QMap<QString, QWidget*> CreatePreferrenceWidgetList() const = 0;

    virtual void CreateMainWindowPopupMenu(MenuItem*) const;
    /**
     * 激活工作台，并更新GUI界面
     */
    bool Activate();

    /** 工作台激活时执行的操作 */
    virtual void Activated();
    /** 停止工作台时执行的操作. */
    virtual void Deactivated();
    /** 返回工作台 对应Preferrence的界面Tab控件名称. */
    virtual std::string GetPreferrenceWidgetName();
    /** 返回工作台 对应配置项. */
    base::ParameterGroup* GetPreferrenceParameters();

    void RegistWorkbenchCommand();

    //// toolbars列表
    std::list<std::string> ListToolBars() const;
    std::list<std::pair<std::string, std::list<std::string>>> GetToolbarItems() const;
    //// menus列表
    std::list<std::string> ListMenus() const;
    /** 返回导航栏列表 */
    virtual std::vector<Navigator*> GetNavigatorList() const;
    /** 注册相关模块命令 */
    virtual void RegistCommand() = 0;
    /** 加载Workbench初始化内容 */
    virtual void StartUp();
    /** 初始化相关数据 */
    virtual void InitData(app::Document* doc);

    QList<SARibbonCategory*> SetupCategory(ToolBarItem* item) const;
    void SetupPage(ToolBarItem* item, SARibbonCategory* page) const;

    /** 返回菜单栏列表 */
    virtual MenuItem* SetupMenuBar() const = 0;
    /** 返回工具栏列表 */
    virtual ToolBarItem* SetupToolBars() const = 0;
    /** 返回工具栏 */
    virtual QList<SARibbonCategory*> GetCategoryList() const = 0;

    /** 注册规则 **/
    virtual void RegistRules() const {}
  private:
    /**
     * 创建工具栏树结构
     */
    void SetupCustomToolbars(ToolBarItem* root, std::string const& toolbar) const;
    void SetupCustomToolbars(ToolBarItem* root, base::ParameterGroup* group) const;
    void SetupCustomShortcuts() const;
};

}  // namespace gui

#endif  // GUI_WORKBENCH_H
