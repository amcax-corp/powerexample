#ifndef POWERFC_GUI_MESSAGEWINDOW_H
#define POWERFC_GUI_MESSAGEWINDOW_H
#pragma once
#include <PFCGlobal.h>
#include <QMessageBox>

class QGridLayout;

namespace gui {

class PFC_GUI_API MessageWindow : public QMessageBox
{
    Q_OBJECT

  public:
    enum DialogType
    {
        DialogTypeError /** Error */,
        DialogTypeWarning /** Warning */,
        DialogTypeInformation /** Informattion */,
        DialogTypeQuestion /** Question */
    };

  public:
    explicit MessageWindow(QWidget* parent = nullptr);
    void setWindowTitle(const QString& title);

    static int Show(DialogType type, const QString& title, const QString& message);
    static bool Question(const QString& title, const QString& message);
    static bool Question(const QString& title, const QString& message, const QString& yes, const QString& no);
    static void Information(const QString& title, const QString& message);
    static void Warning(const QString& title, const QString& message);
    static void Error(const QString& title, const QString& message);
    static void LicenseInformation(const QString& title, const QString& message);


  protected:
    //在此重载中调整buttons的长度统一，并将TitleBar加入到布局中
    void showEvent(QShowEvent* e) override;

  private:
    void SetupUI();
    void AdjustLayout();
};
}  // namespace gui

#endif
