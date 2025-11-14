#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#pragma once

#include <QTabWidget>
#include <Widgets/Block/BlockBase.h>
#include <Widgets/Block/Private/PowerToolTip.h>
#include <Widgets/PowerWidgetsConfig.h>

class PowerToolTip;
class PW_API BlockTabControlToolTip : public PowerToolTip
{
    Q_OBJECT
  public:
    BlockTabControlToolTip(int index, QWidget* parent = nullptr)
      : PowerToolTip(parent)
      , m_index(index)
    {}

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

  private:
    int m_index;
};

class PW_API BlockTabControl : public BlockBase
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

    Q_PROPERTY(QString CurrentTabTitle READ GetCurrentTabTitle WRITE SetCurrentTabTitle NOTIFY SignalCurrentTabTitleChanged STORED false)

    Q_PROPERTY(QString CurrentTabToolTipTitle READ GetCurrentTabToolTipTitle WRITE SetCurrentTabToolTipTitle NOTIFY SignalCurrentTabToolTipTitleChanged STORED false)
    Q_PROPERTY(QString CurrentTabToolTipText READ GetCurrentTabToolTipText WRITE SetCurrentTabToolTipText NOTIFY SignalCurrentTabToolTipTextChanged STORED false)
    Q_PROPERTY(QPixmap CurrentTabToolTipImage READ GetCurrentTabToolTipImage WRITE SetCurrentTabToolTipImage NOTIFY SignalCurrentTabToolTipImageChanged STORED false)
    Q_PROPERTY(BlockBase::TooltipLayout CurrentTabToolTipLayout READ GetCurrentTabToolTipLayout WRITE SetCurrentTabToolTipLayout NOTIFY SignalCurrentTabToolTipLayoutChanged STORED false)

    Q_PROPERTY(QStringList TabToolTipTitles READ GetTabToolTipTitles WRITE SetTabToolTipTitles NOTIFY SignalTabToolTipTitlesChanged DESIGNABLE false)
    Q_PROPERTY(QStringList TabToolTipTexts READ GetTabToolTipTexts WRITE SetTabToolTipTexts NOTIFY SignalTabToolTipTextsChanged DESIGNABLE false)
    Q_PROPERTY(QString JsonSerialTabToolTipImages READ GetJsonSerialTabToolTipImages WRITE SetJsonSerialTabToolTipImages NOTIFY SignalJsonSerialTabToolTipImagesChanged DESIGNABLE false)
    Q_PROPERTY(QString JsonSerialTabToolTipLayouts READ GetJsonSerialTabToolTipLayouts WRITE SetJsonSerialTabToolTipLayouts NOTIFY SignalJsonSerialTabToolTipLayoutsChanged DESIGNABLE false)

  public:
    explicit BlockTabControl(QWidget* parent = nullptr);

  public:
    // READ
    QString GetCurrentTabToolTipTitle() const;
    QString GetCurrentTabToolTipText() const;
    QPixmap GetCurrentTabToolTipImage() const;
    BlockBase::TooltipLayout GetCurrentTabToolTipLayout() const;

    QString GetCurrentTabTitle() const;

    QStringList GetTabToolTipTitles() const;
    QStringList GetTabToolTipTexts() const;
    // 序列化
    QString GetJsonSerialTabToolTipImages() const;
    QString GetJsonSerialTabToolTipLayouts() const;

    // WRITE
    void SetCurrentTabToolTipTitle(const QString& title);
    void SetCurrentTabToolTipText(const QString& text);
    void SetCurrentTabToolTipImage(const QPixmap& image);
    void SetCurrentTabToolTipLayout(BlockBase::TooltipLayout layout);

    void SetCurrentTabTitle(const QString& title);

    void SetTabToolTipTitles(const QStringList& titles);
    void SetTabToolTipTexts(const QStringList& texts);
    // 反序列化
    void SetJsonSerialTabToolTipImages(const QString&);
    void SetJsonSerialTabToolTipLayouts(const QString&);

  Q_SIGNALS:
    void SignalCurrentTabChanged(int index);
    void SignalCurrentTabTitleChanged(const QString& title);

    void SignalCurrentTabToolTipTitleChanged(const QString& title);
    void SignalCurrentTabToolTipTextChanged(const QString& text);
    void SignalCurrentTabToolTipImageChanged(const QPixmap& image);
    void SignalCurrentTabToolTipLayoutChanged(BlockBase::TooltipLayout layout);

    void SignalTabToolTipTitlesChanged(const QStringList&);
    void SignalTabToolTipTextsChanged(const QStringList&);
    void SignalJsonSerialTabToolTipImagesChanged(const QString&);
    void SignalJsonSerialTabToolTipLayoutsChanged(const QString&);

  public:
    // Container
    int Count() const;
    int CurrentIndex() const;
    QWidget* Widget(int index);

    void AddPage(QWidget* page);
    void InsertPage(int index, QWidget* page);
    void RemovePage(int index);
    void SetCurrentIndex(int index);
    int GetCurrentIndex() const;

  private:
    void InitStyle();

    void UpdateAllTabTitles();

    // 恢复当前最新page的tip属性、由addPage调用
    void RestoreLastPageTabToolTipAttribute();
  private:
    QTabWidget* m_tab_widget;
    QList<BlockTabControlToolTip*> m_tab_tooltip_list;
    // 再次编辑时使用
    QStringList m_tab_tooltip_titles;
    // 再次编辑时使用
    QStringList m_tab_tooltip_texts;
    QList<BlockBase::TooltipLayout> m_tab_tooltip_layouts;

    QList<QPixmap> m_tab_tooltip_imgs;
};