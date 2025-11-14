
#ifndef GUI_MENUMANAGER_H
#define GUI_MENUMANAGER_H

#pragma once
#include <PFCGlobal.h>
#include <QStringList>
#include <string>

class QAction;
class QMenu;
class SARibbonMenu;

namespace gui {

class MainWindow;

class PFC_GUI_API MenuItem
{
  public:
    MenuItem();
    MenuItem(MenuItem*);
    ~MenuItem();

    void SetName(const std::string&);
    std::string Name() const;

    bool HasItems() const;
    MenuItem* FindItem(const std::string&);
    MenuItem* Copy() const;
    uint Count() const;

    void AppendItem(MenuItem*);
    bool InsertItem(MenuItem*, MenuItem*);
    MenuItem* AfterItem(MenuItem*) const;
    void RemoveItem(MenuItem*);
    void Clear();

    MenuItem& operator<<(MenuItem* item);
    MenuItem& operator<<(const std::string& command);
    QList<MenuItem*> GetItems() const;

  private:
    std::string m_name;
    QList<MenuItem*> m_items;
};

class PFC_GUI_API MenuManager
{
  public:
    void Setup(MenuItem* items);
    void Setup(MenuItem* items, SARibbonMenu* menu);
    static MenuManager* GetInstance();
    static void Destruct();

  protected:
    MenuManager();
    ~MenuManager();

  private:
    static MenuManager* s_instance;

    friend class MainWindow;
};

}  // namespace gui

#endif
