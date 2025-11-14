#ifndef POWERTOOLTIP_H
#define POWERTOOLTIP_H
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <Widgets/PowerWidgetsConfig.h>
#include <Widgets/Block/BlockBase.h>
class PW_API PowerToolTip : public QWidget
{
    Q_OBJECT
public:

    PowerToolTip(QWidget *parent = nullptr);
    ~PowerToolTip();

    void SetToolTipText(const QString &text);
    QString GetToolTipText() const {return m_text;}

    void SetToolTipImage(QPixmap image_path);
    QPixmap GetToolTipImage() const {return m_image;}

    void SetLayoutDirection(BlockBase::TooltipLayout direction);
    BlockBase::TooltipLayout GetLayoutDirection() const {return m_current_direction;}

    void SetIsDisplayTitle(bool is_display);
    bool GetIsDisplayTitle() const {return m_is_display_title;}

    void SetToolTipTitle(const QString &title);
    QString GetToolTipTitle() const {return m_title;}

    void ShowToolTip(const QPoint &pos);

    void SetMyStyleSheet();

    // 新增方法：为部件安装事件过滤器
    void InstallFilterForWidget(QWidget *widget);

    void CheckAndHideIfNeeded();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *m_text_label;
    QLabel *m_image_label;
    QLabel *m_title_label;
    BlockBase::TooltipLayout m_current_direction;
    bool m_is_display_title;
    QString m_text;
    QPixmap m_image;
    QString m_title;


};

#endif // POWERTOOLTIP_H