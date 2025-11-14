

#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include "Frame/FrameHost.h"
#include "Responder/StatusResponder.h"

#include <string>
#include <vector>

#include <Gui/Workbench/Navigator/Navigator.h>
#include <PFCGlobal.h>
#include <QEvent>
#include <QMainWindow>
#include <QMdiArea>
#include <QTabWidget>
#include <SARibbonBar.h>
#include <SARibbonMainWindow.h>

class QMimeData;
class QUrl;
class QMdiSubWindow;
namespace app {
class Document;
}

namespace gui {
class FrameHost;
class BaseView;
class Document;
class MacroManager;
class MdiView;
class Navigator;
class NavigatorTabWidget;
class BasicSelectionFilterDelegate;

class PFC_GUI_API MainWindow : public SARibbonMainWindow
{
    Q_OBJECT


  public:
    MainWindow(QWidget* parent = 0);

    void InitBase();                    //基本配置
    void CreateUI();                    //创建UI
    void CreateRightBar();              //创建右侧边栏
    void CreateNavigator();             //创建导航栏
    void CreateRibbonBar();             //创建ribbonbar
    void CreateWindowButtonGroupBar();  //创建右上角window栏
    void InitCentralWidget();           //centralWidget
    void CreateStatusBar();             //状态栏

    QWidget* GetNavigator() const;
    QWidget* GetRibbonBar() const;
    QWidget* GetWindowBar() const;
    QWidget* GetMdiTabBar() const;
    QWidget* GetRightBar() const;

    void InitUI();                //初始化UI
    void InitRightButtonGroup();  //初始化右边按钮组
    void InitQuickAccessBar();    //初始化左上角快捷栏

    void SetNavigatorPosition(Qt::DockWidgetArea area);
    void Show();

    ~MainWindow();

    void AddWelcomePage();

    /**
     * 将MDI窗口视图添加到主窗口的工作区，并添加一个新选项卡到标签栏。
     */
    void AddWindow(MdiView* view);
    /**
     * 从主窗口的工作区及其关联的选项卡中删除MDI窗口
     */
    void RemoveWindow(MdiView* view, bool close = true);
    /**
     * 返回当前所有子窗体
     */
    QList<QWidget*> Windows(QMdiArea::WindowOrder order = QMdiArea::CreationOrder) const;

    /**
     * 添加一个Dock窗体
     */
    QDockWidget* AddDockWidget(QWidget* widget, Qt::DockWidgetArea pos);
    /**
     * MdiView更改后触发
     */
    void TabChanged(MdiView* view);
    void SlotTabChanged(int index);
    /**
     * 返回当前活动的MDI窗口
     */
    MdiView* ActiveWindow() const;
    /**
     * 设置当前活动的MDI窗口
     */
    void SetActiveWindow(MdiView* view);

    QMenu* CreatePopupMenu();

    static MainWindow* GetInstance();

    BasicSelectionFilterDelegate* GetPreFilterDelegate() const;
    NavigatorTabWidget* NavigatorTab();
    Navigator* GetNavigator(int index);
    void SetupNavigator(std::vector<Navigator*> list);

    void StartSplasher();
    void StopSplasher();
    QPixmap SplashImage() const;
    void ShowDocumentation(const QString& help);
    void LoadWindowSettings();
    void SaveWindowSettings();
    void LoadStyleFile();

    int GetCurrentDialogCount() const;
    FrameHost* GetFrameHost() const;
    StatusResponder* GetStatusResponder() const;

    void ClearRightBar();
    QAction* AddToRightBar(const std::string& commandName);
    void AddSeparatorToRightBar();

    void UpdateActions(bool delay = false);
    QAction* GetAction(const std::string& commandName);

    enum StatusType
    {
        None,
        Err,
        Wrn,
        Pane,
        Msg,
        Log,
        Tmp
    };
    // void showStatus(int type, const QString& message);

    //添加一个最近打开目录
    void AppendRecentFile(QString);

  public slots:
    void UpdateEditorActions();
    void SetPaneText(int i, QString text);
    void ArrangeIcons();
    void Tile();
    void Cascade();
    void CloseActiveWindow();
    
    bool CloseAllDocuments(bool close = true);
    void ActivateNextWindow();
    void ActivatePreviousWindow();
    void ActivateWorkbench(const QString&);
    void WhatsThis();

    void setWindowTitle(const QString& string);

    // void StatusMessageChanged();

    void SlotSetActiveSubWindow(QWidget* window);
    void SlotWindowActivated(QMdiSubWindow*);
    void SlotTabCloseRequested(int index);
    void SlotUpdateActions();
    void SlotShowMainWindow();
    void SlotDelayedStartup();
    void SlotProcessMessages(const QList<QByteArray>&);
    void SlotStatusMessageChanged(const QString& text);
    void ShowMessage(const QString& message, int timeout = 0);

  protected:
    bool eventFilter(QObject* o, QEvent* e) override;
    void closeEvent(QCloseEvent* e) override;
    void showEvent(QShowEvent* e) override;
    void hideEvent(QHideEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;
    void timerEvent(QTimerEvent*) override
    {
        emit SignalTimeEvent();
    }
    void customEvent(QEvent* e) override;
    bool event(QEvent* e) override;
    void dropEvent(QDropEvent* e) override;
    void dragEnterEvent(QDragEnterEvent* e) override;
    void changeEvent(QEvent* e) override;
    // void childEvent(QChildEvent* e) override;
    void moveEvent(QMoveEvent* event) override;

  signals:
    void SignalTimeEvent();
    void SignalWindowStateChanged(MdiView*);
    void SignalWorkbenchActivated(const QString&);
    void SignalMainWindowClosed();

    // void SignalDialogAdded(QDialog* child);

  private slots:
    void ProcessMessages(const QList<QString> &);

    void OnWindowActivated(QMdiSubWindow*);

  private:
    /// some kind of singleton
    static MainWindow* s_instance;
    struct MainWindowPrivate* d;
};

inline MainWindow* GetMainWindow()
{
    return MainWindow::GetInstance();
}

// -------------------------------------------------------------

// class StatusBarObserver: public WindowParameter
// {
// public:
//     StatusBarObserver();
//     virtual ~StatusBarObserver();

//     /** Observes its parameter group. */
//     void OnChange(base::Subject<std::string const&> &rCaller, const char * sReason) override;

//     void SendLog(const std::string& msg, base::LogStyle level) override;

//     /// name of the observer
//     const char *Name() override {return "StatusBar";}

//     friend class MainWindow;
// private:
//     QString msg, wrn, err;
// };

}  // namespace gui

#endif  // GUI_MAINWINDOW_H
