#pragma once

#include <Widgets/Block/BlockString.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/PowerWidgetsConfig.h>

class PW_API BlockTextDialog : public BlockDialog
{
    Q_OBJECT

  public:
    BlockTextDialog(QString title, QString base_text = "");
    static QString message(QString title, QString text = "", std::function<bool(QString currentText)> callback = nullptr, QString ErrorInfo = "");
    void SetCallBack(std::function<bool(QString currentText)> callback);
    void SetErrorInfo(QString ErrorInfo);

  protected:
    void showEvent(QShowEvent* event) override;
    bool OnConfirmed() override;
    void OnCanceled() override;

  signals:
    void SignaltextChanged(const QString& text);

  public slots:
    void accept() override;
    

  private:
    BlockString* m_text;
    std::function<bool(QString currentText)> m_callback = nullptr;
    QString m_errorInfo;
};