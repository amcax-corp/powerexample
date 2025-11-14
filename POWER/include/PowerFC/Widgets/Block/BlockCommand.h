#pragma once

#include <QAction>
#include <QToolButton>
#include <Widgets/PowerWidgetsConfig.h>

class PowerToolTip;

class PW_API BlockCommand : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(QString ToolTipTitle READ GetTooltipTitle WRITE SetTooltipTitle)
    Q_PROPERTY(QString ToolTipText READ GetTooltipText WRITE SetTooltipText)
    Q_PROPERTY(QPixmap ToolTipImage READ GetTooltipImage WRITE SetTooltipImage)

  public:
    BlockCommand(QWidget *parent = nullptr);
    ~BlockCommand();
    
    QString GetTooltipTitle() const;
    void SetTooltipTitle(const QString &title);

    QString GetTooltipText() const;
    void SetTooltipText(const QString &text);

    QPixmap GetTooltipImage() const;
    void SetTooltipImage(const QPixmap &image);

    virtual void CallbackAction();

    void SetCommand(std::function<void()> callback);

private:
    std::function<void()> m_callback_activated {};
    QPixmap m_tooltip_image;
    QString m_tooltip_title;
    QString m_tooltip_text;

    PowerToolTip *m_tooltip;

private:
    class CommandWrapper;

    CommandWrapper* m_command_ptr;
};