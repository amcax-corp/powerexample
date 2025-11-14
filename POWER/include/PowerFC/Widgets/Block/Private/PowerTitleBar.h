#pragma once

#include <QDragMoveEvent>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPointF>
#include <QPushButton>

class PowerTitleBar : public QWidget
{
    Q_OBJECT
  public:
    explicit PowerTitleBar(QWidget* parent = nullptr);

    QString GetTitle() const;
    void SetTitle(const QString& title);

    void InitBarUi(QHBoxLayout* layout);
    void InitSize(QHBoxLayout* layout);

    void SetSetting(bool has_setting);
    void SetClose(bool has_close);
    void SetMinimize(bool has_minimize);
    void SetMaximize(bool has_maximize);
    void SetReset(bool has_reset);

  Q_SIGNALS:
    void SignalSettingClicked();
    void SignalCloseClicked();
    void SignalMinimizeClicked();
    void SignalMaximizeClicked();
    void SignalSesetClicked();

  private:
    QString m_title;
    QLabel* m_title_label;

    bool m_has_setting = true;
    bool m_has_close = true;
    bool m_has_minimize = false;
    bool m_has_maximize = false;
    bool m_has_reset = true;

    QPushButton* m_setting_button;
    QPushButton* m_close_button;
    QPushButton* m_minimize_button;
    QPushButton* m_maximize_button;
    QPushButton* m_reset_button;
};
