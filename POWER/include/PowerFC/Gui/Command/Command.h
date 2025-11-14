
#ifndef GUI_COMMAND_H
#define GUI_COMMAND_H

#include <QActionGroup>
#include <QList>
#include <SARibbonMenu.h>
#include <list>
#include <map>
#include <string>
#include <vector>

#include <Base/Type.h>

class QWidget;
class QByteArray;
class QString;

namespace app {
class Document;
class DocumentObject;
}  // namespace app

namespace gui {

class Action;
class Application;
class CommandManager;
class Command;
class ActionGroup;
class Document;
// class SelectionSingleton;
class MdiView;

class PFC_GUI_API CommandBase
{
  protected:
    CommandBase(std::string const& menu, std::string const& toolTip = "", std::string const& whatThis = "", std::string const& status = "", std::string const& pixmap = "", std::string const& accel = "");
    virtual ~CommandBase();

  public:
    Action* GetAction();

  protected:
    virtual Action* CreateAction();

  public:
    virtual void UpdateAction(int mode = 0) = 0;
    virtual std::string ClassName() const = 0;
    virtual std::string const& GetMenuText() const
    {
        return m_menuText;
    }
    virtual std::string const& GetToolTipText() const
    {
        return m_toolTipText;
    }
    virtual std::string const& GetStatusTip() const
    {
        return m_statusTip;
    }
    virtual std::string const& GetWhatsThis() const
    {
        return m_statusTip;
    }
    virtual std::string const& GetPixmap() const
    {
        return m_pixmap;
    }
    virtual std::string const& GetAccel() const
    {
        return m_accel;
    }
    virtual bool const& GetCheckable() const
    {
        return m_checkable;
    }

    virtual bool const& GetChecked() const
    {
        return m_checked;
    }

    void SetWhatsThis(std::string const&);
    void SetMenuText(std::string const&);
    void SetToolTipText(std::string const&);
    void SetStatusTip(std::string const&);
    void SetPixmap(std::string const&);
    void SetAccel(std::string const&);
    void SetCheckable(bool const&);

    void SetChecked(bool const&);

  protected:
    std::string m_whatsThis;
    std::string m_menuText;
    std::string m_toolTipText;
    std::string m_statusTip;
    std::string m_pixmap;
    std::string m_accel;
    bool m_checkable;
    bool m_checked;
    //@}
  protected:
    Action* m_action;
    std::string m_display_text;
};

class PFC_GUI_API Command : public CommandBase
{
  protected:
    Command(std::string const& name);
    virtual ~Command();

  protected:
    virtual void Activated(int index) = 0;
    virtual Action* CreateAction();
    /// 应用 menu text, tool , status tip 到action中
    void ApplyCommandData(const char* context, Action* action);
    std::string KeySequenceToAccel(int) const;

  public:
    friend class CommandManager;
    virtual bool IsActive()
    {
        return true;
    }
    void TestActive();
    void SetEnabled(bool);

    void Invoke(int index);
    void AddTo(QWidget* widget);
    void AddToGroup(ActionGroup* actionGroup, bool checkable = true);
    void AddToGroup(QActionGroup* actionGroup);

    void UpdateAction(int mode = 0);
    void SetupCheckable(int index);
    bool IsMenu();

    QString GenTipWithTitleAndImage(const std::string& image, const std::string& title, const std::string& text);

    std::string const& GetAppModuleName() const
    {
        return m_app_module;
    }

    void SetAppModuleName(std::string const&);

    std::string const& GetName() const
    {
        return m_name;
    }

    std::string const& GetGroupName() const
    {
        return m_group;
    }
    void SetGroupName(std::string const& s);

  protected:
    enum CmdType
    {
        AlterDoc = 1,       /**< Command change the Document */
        Alter3DView = 2,    /**< Command change the Gui */
        AlterSelection = 4, /**< Command change the Selection */
        ForEdit = 8,        /**< Command is in a special edit mode active */
        NoTransaction = 16, /**< Do not setup auto transaction */
    };

    std::string m_app_module;
    std::string m_group;
    std::string m_name;
    int m_type;
    bool isMenu;

  private:
    static int s_busy;
    bool m_enabled;
    static bool m_block_cmd;
};

class PFC_GUI_API GroupCommand : public Command
{
  public:
    /// Constructor
    GroupCommand(std::string const& name);

    int AddCommand(Command* cmd = 0, bool reg = true);

    Command* AddCommand(std::string const& cmd_name);

  protected:
    virtual void Activated(int index);
    virtual gui::Action* CreateAction();

    void Setup(Action*);

  protected:
    std::vector<std::pair<Command*, size_t>> m_commands;
};

class PFC_GUI_API MenuCommand : public Command
{
  public:
    /// Constructor
    MenuCommand(std::string const& name);

    Command* AddCommand(std::string const& cmd_name);

    void Activated(int index) override;

    SARibbonMenu* CreateMenu();

  private:
    QList<QAction*> GetActions();

  protected:
    std::vector<Command*> m_commands;
};

class PFC_GUI_API CommandManager
{
  public:
    static CommandManager& GetInstance();
    /// Construction
    CommandManager();
    /// Destruction
    ~CommandManager();
    CommandManager(const CommandManager&) = delete;
    CommandManager& operator=(const CommandManager&) = delete;

    /// Insert a new command into the manager
    void AddCommand(Command* command);
    /// Remove a command from the manager
    void RemoveCommand(Command* command);

    /// Adds the given command to a given widget
    bool AddTo(std::string const& name, QWidget* parent);

    std::vector<Command*> GetModuleCommands(std::string const& moduleName) const;

    std::vector<Command*> GetAllCommands() const;

    std::vector<Command*> GetGroupCommands(std::string const& groupName) const;

    Command* GetCommandByName(std::string const& name) const;

    void RunCommandByName(std::string const& name) const;

    const std::map<std::string, Command*>& GetCommands() const
    {
        return m_commands;
    }
    void TestActive();

    void AddCommandMode(std::string const& context, std::string const& name);
    void UpdateCommands(std::string const& context, int mode);

  private:
    void ClearCommands();
    std::map<std::string, Command*> m_commands;
    std::map<std::string, std::list<std::string>> m_command_modes;
};

}  // namespace gui

// DEF_STD_CMD
// Activated - 实现函数
#define DEF_STD_CMD(X)                        \
    class X : public gui::Command             \
    {                                         \
      public:                                 \
        X();                                  \
        X(std::string const& name);           \
        virtual std::string ClassName() const \
        {                                     \
            return #X;                        \
        }                                     \
                                              \
      protected:                              \
        virtual void Activated(int iMsg);     \
    };

// DEF_STD_CMD_A
// Activated - 实现函数
// IsActive - 判断是否可执行
#define DEF_STD_CMD_A(X)                      \
    class X : public gui::Command             \
    {                                         \
      public:                                 \
        X();                                  \
        virtual ~X() {}                       \
        virtual std::string ClassName() const \
        {                                     \
            return #X;                        \
        }                                     \
                                              \
      protected:                              \
        virtual void Activated(int iMsg);     \
        virtual bool IsActive();              \
    };

// DEF_STD_CMD_C
// Activated - 实现函数
// CreateAction - 自定义Action
#define DEF_STD_CMD_C(X)                      \
    class X : public gui::Command             \
    {                                         \
      public:                                 \
        X();                                  \
        virtual ~X() {}                       \
        virtual std::string ClassName() const \
        {                                     \
            return #X;                        \
        }                                     \
                                              \
      protected:                              \
        virtual void Activated(int iMsg);     \
        virtual gui::Action* CreateAction();  \
    };

// DEF_STD_CMD_AC
// Activated - 实现函数
// CreateAction - 自定义Action
#define DEF_STD_CMD_AC(X)                     \
    class X : public gui::Command             \
    {                                         \
      public:                                 \
        X();                                  \
        virtual ~X() {}                       \
        virtual std::string ClassName() const \
        {                                     \
            return #X;                        \
        }                                     \
                                              \
      protected:                              \
        virtual void Activated(int iMsg);     \
        virtual bool IsActive();              \
        virtual gui::Action* CreateAction();  \
    };

#define DEF_STD_CMD_ACL(X)                    \
    class X : public gui::Command             \
    {                                         \
      public:                                 \
        X();                                  \
        virtual ~X() {}                       \
        virtual std::string ClassName() const \
        {                                     \
            return #X;                        \
        }                                     \
                                              \
      protected:                              \
        virtual void Activated(int iMsg);     \
        virtual bool IsActive();              \
        virtual gui::Action* CreateAction();  \
    };

#define DEF_STD_CMD_Menu(X)                   \
    class X : public gui::MenuCommand         \
    {                                         \
      public:                                 \
        X();                                  \
        virtual ~X() {}                       \
        virtual std::string ClassName() const \
        {                                     \
            return #X;                        \
        }                                     \
                                              \
      protected:                              \
        virtual bool IsActive();              \
    };

// DEF_3DV_CMD 3D渲染使用的Command
#define DEF_3DV_CMD(X)                                                                 \
    class X : public gui::Command                                                      \
    {                                                                                  \
      public:                                                                          \
        X();                                                                           \
        virtual ~X() {}                                                                \
        virtual std::string ClassName() const                                          \
        {                                                                              \
            return #X;                                                                 \
        }                                                                              \
                                                                                       \
      protected:                                                                       \
        virtual void Activated(int index);                                             \
        virtual bool IsActive()                                                        \
        {                                                                              \
            gui::MdiView* view = gui::GetGuiAppliaction()->ActiveWindow();             \
            return view && view->isDerivedFrom(gui::View3DInventor::getClassTypeId()); \
        }                                                                              \
    };

#endif  // GUI_COMMAND_H
