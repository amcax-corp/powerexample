
#ifndef GUI_APPLICATION_H
#define GUI_APPLICATION_H

#pragma once
#include <QApplication>
#include <QList>
#include <QScopedPointer>
#include <QSessionManager>

namespace gui {

class GUISingleApplication : public QApplication
{
    Q_OBJECT

  public:
    explicit GUISingleApplication(int& argc, char** argv);
    virtual ~GUISingleApplication() override;

    bool isRunning() const;
    bool sendMessage(const QByteArray& message, int timeout = 5000);

  private Q_SLOTS:
    void receiveConnection();
    void processMessages();
    bool notify(QObject* receiver, QEvent* event) override;
    void commitData(QSessionManager& manager);

  Q_SIGNALS:
    void messageReceived(const QList<QByteArray>&);

  protected:
    bool event(QEvent* event) override;

  private:
    class Private;
    QScopedPointer<Private> d_ptr;
};

class WheelEventFilter : public QObject
{
    Q_OBJECT

  public:
    WheelEventFilter(QObject* parent);
    bool eventFilter(QObject* obj, QEvent* ev);
};

}  // namespace gui

#endif  // GUI_APPLICATION_H
