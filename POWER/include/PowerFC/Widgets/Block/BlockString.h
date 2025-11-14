#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <Widgets/Block/BlockBase.h>
#include <QLabel>

class PowerStringLineEdit;

class PW_API BlockString : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(QString Value READ GetValue WRITE SetValue)
    Q_PROPERTY(int MaxTextLength READ GetMaxTextLength WRITE SetMaxTextLength)
    Q_PROPERTY(PresentationStyle PresentationStyle READ GetpresentationStyle WRITE SetPresentationStyle)
    Q_PROPERTY(KeyinFiledWidth KeyinFiledWidth READ GetkeyinFiledWidth WRITE SetkeyinFiledWidth)
    Q_PROPERTY(bool Mandatory READ IsMandatory WRITE SetMandatory)
    Q_PROPERTY(bool ValueReadOnly READ IsValueReadOnly WRITE SetValueReadOnly)
public:
    enum PresentationStyle
    {
        Keyin,
        Wide,
        // ScaleKeyin,
        // Combo
    };
    Q_ENUM(PresentationStyle);

    enum KeyinFiledWidth
    {
        Narrow,
        Standard
    };
    Q_ENUM(KeyinFiledWidth);

public:
    /// @brief 构造函数，初始化BlockString对象
    /// @param parent 父QWidget指针，默认为nullptr
    explicit BlockString(QWidget *parent = nullptr);

    ~BlockString();

    /// @brief 初始化UI
    void InitUi();

    /// @brief 获取当前值
    /// @return 当前值
    QString GetValue();

    /// @brief 获取最大文本长度
    /// @return 最大文本长度
    int GetMaxTextLength();

    /// @brief 获取当前展示样式
    /// @return 当前展示样式
    PresentationStyle GetpresentationStyle();

    /// @brief 获取输入字段宽度
    /// @return 输入字段宽度
    KeyinFiledWidth GetkeyinFiledWidth();

    /// @brief 设置当前值
    /// @param value 新的值
    void SetValue(QString value);

    /// @brief 设置最大文本长度
    /// @param textLength 新的最大文本长度
    void SetMaxTextLength(int textLength);

    /// @brief 设置展示样式
    /// @param presentationStyle 新的展示样式
    void SetPresentationStyle(PresentationStyle presentationStyle);

    /// @brief 设置输入字段宽度
    /// @param keyinFiledWidth 新的输入字段宽度
    void SetkeyinFiledWidth(KeyinFiledWidth keyinFiledWidth);

    bool IsValueReadOnly();

    void SetValueReadOnly(bool valueReadOnly);

    virtual void SetMandatory(bool isMandatory) override;
    virtual bool IsMandatory() const override;
    virtual void SetMandatoryFilled(bool filled) override;
    virtual bool IsMandatoryFilled() const override;

signals:
    /// @brief 值改变信号
    /// @param value 新的值
    void SignalValueChanged(QString value);

private slots:
    /// @brief 展示样式改变槽函数
    /// @param presentationStyle 新的展示样式
    void OnPresentationChanged(PresentationStyle presentationStyle);
    void RequiredCheck();

private:
void UpdateRequiredLabelIcon(bool filled);

private slots:
    void OnResizeStringLineEdit(bool labelVisibility);

private:
    PowerStringLineEdit *m_edit;
    PresentationStyle m_current_style;
    QHBoxLayout *m_hlayout;
    QVBoxLayout *m_vlayout;
    QLabel *m_required_label;
    bool m_requiredInput;
    bool m_is_mandatory = false;
    bool m_mandatory_filled = true;
};
