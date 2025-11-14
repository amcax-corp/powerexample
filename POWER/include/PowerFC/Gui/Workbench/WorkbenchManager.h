#ifndef GUI_WORKBENCHMANAGER_H
#define GUI_WORKBENCHMANAGER_H

#pragma once
#include <Base/IPluginManager.h>
#include <PFCGlobal.h>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace gui {

class Workbench;

class PFC_GUI_API WorkbenchManager : public base::IPluginManager
{
  public:
    static WorkbenchManager& GetInstance();
    WorkbenchManager(const WorkbenchManager&) = delete;
    WorkbenchManager& operator=(const WorkbenchManager&) = delete;

    /**       搜索并返回带有指定名称的现有工作台对象。     */
    std::shared_ptr<Workbench> CreateWorkbench(const std::string& name, const std::string& className);
    /** 返回指定名称的工作台实例     */
    std::shared_ptr<Workbench> GetWorkbench(const std::string& name) const;
    /** 激活指定名称的工作台 */
    bool Activate(const std::string& name, const std::string& className);
    /** 返回当前激活的工作台 */
    std::shared_ptr<Workbench> Active() const;

    QString GetWorkbenchPath(const std::string& name);

    std::set<QString> FixTabNames();

  protected:
    WorkbenchManager();
    ~WorkbenchManager() override;

  private:
    std::shared_ptr<Workbench> m_active_workbench;
    std::set<QString> m_fix_tab_names;
};

}  // namespace gui

#endif
