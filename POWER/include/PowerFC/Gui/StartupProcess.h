#ifndef POWERFC_GUI_STARTUPPROCESS_H
#define POWERFC_GUI_STARTUPPROCESS_H
#pragma once
#include <PFCGlobal.h>
#include <QStringList>

class QApplication;

namespace gui {
class Application;
class MainWindow;
}  // namespace gui

namespace gui {
class PFC_GUI_API StartupProcess
{
  public:
    StartupProcess();

    void Execute();

    static void SetupApplication();

  private:
    void SetLibraryPath();
    void SetStyleSheetPaths();
    void SetImagePaths();
    void RegisterEventType();
    void SetThemePaths();
    void SetupFileDialog();
};

class PFC_GUI_API StartupPostProcess
{
  public:
    StartupPostProcess(MainWindow* main_window, gui::Application* gui_app, QApplication* qt_app);

    void Execute();

  private:
    void SetWindowTitle();
    void SetProcessMessages();
    void SetAutoSaving();
    void SetToolbarIconSize();
    void SetWheelEventFilter();
    void SetLocale();
    void SetCursorFlashing();
    void SetQtStyle();
    void CheckOpenGL();
    void SetBranding();
    void SetStyleSheet();

    void AutoLoadModules(QStringList const& work_benches);

    void SetImportImageFormats();
    bool HiddenMainWindow() const;
    void ShowMainWindow();
    void ActivateWorkbench();
    void CheckParameters();

  private:
    bool m_is_load_from_python_module{false};
    gui::MainWindow* m_main_window{nullptr};
    gui::Application* m_gui_app{nullptr};
    QApplication* m_qt_app{nullptr};
};
}  // namespace gui

#endif
