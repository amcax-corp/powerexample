#pragma once

#include <Widgets/Block/BlockBase.h>
#include <QListWidget>
#include <QStackedWidget>
#include <QButtonGroup>
#include <Widgets/PowerWidgetsConfig.h>
class PowerToolTip;
class PW_API BlockExplorer : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText DESIGNABLE false)
    Q_PROPERTY(bool LabelTextVisibility READ IsLabelTextVisibility WRITE SetLabelTextVisibility DESIGNABLE false)
    Q_PROPERTY(QPixmap LabelBitmap READ GetLabelBitmap WRITE SetLabelBitmap DESIGNABLE false)
    Q_PROPERTY(bool LabelBitmapVisibility READ IsLabelBitmapVisibility WRITE SetLabelBitmapVisibility DESIGNABLE false)
    Q_PROPERTY(bool LabelVisibility READ IsLabelVisibility WRITE SetLabelVisibility FINAL DESIGNABLE false)
    Q_PROPERTY(QString TooltipTitle READ GetTooltipTitle WRITE SetTooltipTitle DESIGNABLE false)
    Q_PROPERTY(QString TooltipText READ GetTooltipText WRITE SetTooltipText DESIGNABLE false)
    Q_PROPERTY(QPixmap TooltipImage READ GetTooltipImage WRITE SetTooltipImage DESIGNABLE false)
    Q_PROPERTY(TooltipLayout TooltipLayout READ GetTooltipLayout WRITE SetTooltipLayout DESIGNABLE false)

    Q_PROPERTY(int CurrentPage READ GetCurrentPage WRITE SetCurrentPage)
    Q_PROPERTY(QString CurrentPageToolTip READ GetCurrentPageToolTipTitle WRITE SetCurrentPageToolTipTitle)
    Q_PROPERTY(QString CurrentPageToolTipText READ GetCurrentPageToolTipText WRITE SetCurrentPageToolTipText)
    Q_PROPERTY(QPixmap CurrentPageToolTipImage READ GetCurrentPageToolTipImage WRITE SetCurrentPageToolTipImage)
    Q_PROPERTY(BlockBase::TooltipLayout CurrentPageToolTipLayout READ GetCurrentPageToolTipLayout WRITE SetCurrentPageToolTipLayout)
    Q_PROPERTY(int ActivePage READ ActivePage WRITE SetActivePage)
    Q_PROPERTY(bool CurrentPageVisible READ IsCurrentPageVisible WRITE SetCurrentPageVisible)
    Q_PROPERTY(bool CurrentPageEnabled READ IsCurrentPageEnabled WRITE SetCurrentPageEnabled)
    Q_PROPERTY(QString CurrentPageTitle READ GetCurrentPageTitle WRITE SetCurrentPageTitle)
    Q_PROPERTY(int ListWidth READ GetListWidth WRITE SetListWidth FINAL)

public:
    explicit BlockExplorer(QWidget *parent = nullptr);

public:
    // READ
    int GetCurrentPage() const;
    QString GetCurrentPageToolTipTitle() const;
    QString GetCurrentPageToolTipText() const;
    QPixmap GetCurrentPageToolTipImage() const;
    BlockBase::TooltipLayout GetCurrentPageToolTipLayout() const;
    int ActivePage() const;
    bool IsCurrentPageVisible() const;
    bool IsCurrentPageEnabled() const;
    QString GetCurrentPageTitle() const;
    int GetListWidth() const;

    // WRITE
    void SetCurrentPage(int index);
    void SetCurrentPageToolTipTitle(const QString &text);
    void SetCurrentPageToolTipText(const QString &text);
    void SetCurrentPageToolTipImage(const QPixmap &image);
    void SetCurrentPageToolTipLayout(BlockBase::TooltipLayout layout);
    void SetActivePage(int index);
    void SetCurrentPageVisible(bool visible);
    void SetCurrentPageEnabled(bool enabled);
    void SetCurrentPageTitle(const QString &title);
    void SetListWidth(int width);

    QSize sizeHint() const override;

public:
    // Container
    int count() const;
    int currentIndex() const;
    QWidget *widget(int index);

    void addPage(QWidget *page);
    void insertPage(int index, QWidget *page);
    void removePage(int index);
    void setCurrentIndex(int index);

Q_SIGNALS:
    void CurrentPageChanged(int index);

private:
    void InitStyle();

private:
    QListWidget *m_listWidget;
    QStackedWidget *m_content;
    QList<PowerToolTip *> m_pageToolTipList;
    QButtonGroup m_buttonGroup;
    int m_activeIndex = -1;
    int m_listWidth;
};