
#ifndef GUI_TOOLBARMANAGER_H
#define GUI_TOOLBARMANAGER_H

#pragma once
#include <PFCGlobal.h>
#include <QFileSystemWatcher>
#include <QStringList>
#include <string>

class QAction;
class Command;
class QToolBar;
class SARibbonCategory;

namespace gui {

enum ToolBarStyle
{
    Large,
    Normal,
    Small
};

class PFC_GUI_API ToolBarItem
{
  public:
    ToolBarItem();
    ToolBarItem(ToolBarItem* item);
    ToolBarItem(ToolBarItem* item, std::string name);
    ~ToolBarItem();

    void SetName(const std::string&);
    std::string Name() const;

    void SetStyle(ToolBarStyle style);
    ToolBarStyle GetStyle();

    void SetSubStyle(int index, ToolBarStyle style);

    bool HasItems() const;
    ToolBarItem* FindItem(const std::string&);
    ToolBarItem* Copy() const;
    uint Count() const;

    void AppendItem(ToolBarItem* item);
    bool InsertItem(ToolBarItem*, ToolBarItem* item);
    void RemoveItem(ToolBarItem* item);
    void Clear();

    ToolBarItem& operator<<(ToolBarItem* item);
    ToolBarItem& operator<<(const std::string& command);
    QList<ToolBarItem*> GetItems() const;

  private:
    std::string m_name;
    ToolBarStyle m_style;
    QList<ToolBarItem*> m_items;
};

class PFC_GUI_API ToolBarManager : public QObject
{
    Q_OBJECT
  public:
    static ToolBarManager* GetInstance();
    static void Destruct();
    void Setup(ToolBarItem*);
    static void SetupWorkbenchToolbars();
    void Setup(QList<SARibbonCategory*> list);
    void SaveState() const;

    // public slots:
    //   void OnFileChanged(const QString& dir_name);

  protected:
    void SetupPage(ToolBarItem*, SARibbonCategory* page) const;
    ToolBarManager();
    ~ToolBarManager();

    // void LoadExtraPannelFromSharedLib();

  private:
    QStringList toolbar_page_names;
    QFileSystemWatcher file_watcher;
    static ToolBarManager* s_instance;

    // QString m_dll_dir;
    // QMap<QString, std::tuple<bool, bool>> m_dll_states;
};

}  // namespace gui

#endif  // GUI_TOOLBARMANAGER_H
