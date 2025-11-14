#pragma once
#include <QWidget>
#include <Widgets/PowerWidgetsConfig.h>
#include <QObject>
class BlockBasePrivate;
class PowerToolTip;
class PowerLabel;

class PW_API BlockBase : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText)
    Q_PROPERTY(bool LabelTextVisibility READ IsLabelTextVisibility WRITE SetLabelTextVisibility)
    Q_PROPERTY(QPixmap LabelBitmap READ GetLabelBitmap WRITE SetLabelBitmap)
    Q_PROPERTY(bool LabelBitmapVisibility READ IsLabelBitmapVisibility WRITE SetLabelBitmapVisibility)
    Q_PROPERTY(bool LabelVisibility READ IsLabelVisibility WRITE SetLabelVisibility)
    Q_PROPERTY(QString TooltipTitle READ GetTooltipTitle WRITE SetTooltipTitle)
    Q_PROPERTY(QString TooltipText READ GetTooltipText WRITE SetTooltipText)
    Q_PROPERTY(QPixmap TooltipImage READ GetTooltipImage WRITE SetTooltipImage)
    Q_PROPERTY(TooltipLayout TooltipLayout READ GetTooltipLayout WRITE SetTooltipLayout)

    Q_PROPERTY(bool Mandatory READ IsMandatory WRITE SetMandatory NOTIFY SignalMandatoryChanged REQUIRED)
public:

    enum TooltipLayout
    {
        Vertical,
        Horizontal
    };
    Q_ENUM(TooltipLayout);

public:
    /// @brief 构造函数,创建一个BlockBase基类对象
    /// @param parent 父对象指针
    explicit BlockBase(QWidget* parent = nullptr);
    ~BlockBase() override = default;

    /// @brief 获取当前Label内容
    /// @return 返回一个QString类型
    QString GetLabelText() const;
    /// @brief 设置当前Label内容
    /// @param text QString类型
    void SetLabelText(const QString& text);

    /// @brief 当前Label内容是否显示
    /// @return 返回一个bool类型，true为显示，false为不显示
    bool IsLabelTextVisibility() const;
    /// @brief 设置当前Label内容是否显示
    /// @param visibility bool类型
    void SetLabelTextVisibility(bool visibility);

    /// @brief 获取当前Label位图
    /// @return 返回一个QPixmap类型
    QPixmap GetLabelBitmap() const;
    /// @brief 设置当前Label位图
    /// @param bitmap QPixmap类型
    void SetLabelBitmap(QPixmap bitmap);

    /// @brief 当前Label位图是否显示
    /// @return 返回一个bool类型，true为显示，false为不显示
    bool IsLabelBitmapVisibility() const;
    /// @brief 设置当前Label位图是否显示
    /// @param visibility bool类型
    void SetLabelBitmapVisibility(bool visibility);

    /// @brief 当前Label是否显示
    /// @return 返回一个bool类型，true为显示，false为不显示
    bool IsLabelVisibility() const { return m_lable_visibility; }
    /// @brief 设置当前Label是否显示
    /// @param visibility bool类型
    void SetLabelVisibility(bool visibility);

    /// @brief 获取当前提示框标题
    /// @return 返回一个QString类型
    QString GetTooltipTitle() const;
    /// @brief 设置当前提示框标题
    /// @param title QString类型
    void SetTooltipTitle(const QString& title);

    /// @brief 获取当前提示框内容
    /// @return 返回一个QString类型
    QString GetTooltipText() const;
    /// @brief 设置当前提示框内容
    /// @param text QString类型
    void SetTooltipText(const QString& text);

    /// @brief 获取当前提示框图像
    /// @return 返回一个QPixmap类型
    QPixmap GetTooltipImage() const;
    /// @brief 设置当前提示框图片
    /// @param image QPixmap类型
    void SetTooltipImage(QPixmap image);

    /// @brief 获取当前提示框布局方向
    /// @return 返回一个BlockBase::TooltipLayout类型
    TooltipLayout GetTooltipLayout() const;
    /// @brief 设置当前提示框布局方向
    /// @param layout BlockBase::TooltipLayout类型
    void SetTooltipLayout(TooltipLayout layout);

    virtual void SetMandatory(bool) {}
    virtual bool IsMandatory() const { return false; }
    virtual void SetMandatoryFilled(bool) {}
    virtual bool IsMandatoryFilled() const { return false; }

    virtual bool IsValid() const;

Q_SIGNALS:
    void SignalLabelTextChanged(const QString&);
    void SignalTooltipLayoutChanged(TooltipLayout);
    void SignalLabelVisibilityChanged(bool);
    void SignalLabelTextVisibilityChanged(bool);

    void SignalMandatoryChanged(bool);
    void SignalMandatoryFilled(bool);
protected:
    /// @brief 获取当前块，不断向上查找父对象，直到找到BlockDialog对象，否则返回nullptr
    /// @return 返回一个BlockDialog指针，可能为nullptr
    QWidget* FindParentDialog() const;
    QWidget* FindParentGroup() const;

    PowerLabel* GetLabelWidget() const;
private:
    PowerLabel* m_label;
    bool m_lable_visibility = true;
};
