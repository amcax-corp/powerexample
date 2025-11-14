#pragma once

#include <QWidget>
#include <Widgets/Block/BlockBase.h>
#include <Widgets/PowerWidgetsConfig.h>

class PowerEnumeration;

class PW_API BlockEnumeration : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(QStringList Sensitivity READ GetSensitivity WRITE SetSensitivity)
    Q_PROPERTY(QStringList Visibility READ  IsVisibility WRITE SetVisibility)
    Q_PROPERTY(QStringList Value READ GetValue WRITE SetValue)
    Q_PROPERTY(QStringList Image READ GetImage WRITE SetImage)
    Q_PROPERTY(QStringList TipText READ GetTipText WRITE SetTipText)
    Q_PROPERTY(QStringList TipTitle READ GetTipTitle WRITE SetTipTitle)
    Q_PROPERTY(QStringList TipImage READ GetTipImage WRITE SetTipImage)
    Q_PROPERTY(int CurrentIndex READ GetCurrentIndex WRITE SetCurrentIndex)

public:
    /// @brief 构造函数，初始化BlockEnumeration对象
    /// @param parent 父QWidget对象，默认为nullptr
    explicit BlockEnumeration(QWidget *parent = nullptr);
    ~BlockEnumeration();

    /// @brief 获取当前枚举框中项的可用性列表，1表示禁用，其余表示可用
    /// @return QStringList 字符串列表
    QStringList GetSensitivity();

    /// @brief 获取当前枚举框中项的可见性列表，1表示隐藏，其余表示可见
    /// @return QStringList 可见性列表
    QStringList IsVisibility();

    /// @brief 获取当前枚举框中项的值列表
    /// @return QStringList 值列表
    QStringList GetValue();

    /// @brief 获取当前枚举框项的图像列表
    /// @return QStringList 图像列表
    QStringList GetImage();

    /// @brief 获取当前枚举框项的提示文本列表
    /// @return QStringList 提示文本列表
    QStringList GetTipText();

    /// @brief 获取当前枚举框项的提示标题列表
    /// @return QStringList 提示标题列表
    QStringList GetTipTitle();

    /// @brief 获取当前枚举框项的提示图像列表
    /// @return QStringList 提示图像列表
    QStringList GetTipImage();

    /// @brief 获取当前枚举框中项的索引
    /// @return int 索引值
    int GetCurrentIndex();

    /// @brief 设置当前枚举框中项的可用性列表，1表示禁用，其余表示可用
    /// @param sens_list QStringList类型 可用性列表
    void SetSensitivity(QStringList sens_list);

    /// @brief 设置当前枚举框中项的可见性列表，1表示隐藏，其余表示可见
    /// @param visi_list QStringList类型 可见性列表
    void SetVisibility(QStringList visi_list);

    /// @brief 设置当前枚举框中项的值列表
    /// @param value_list QStringList类型 值列表
    void SetValue(QStringList value_list);

    /// @brief 设置当前枚举框项的图像列表
    /// @param pixmap_list QStringList类型 图像列表
    void SetImage(QStringList pixmap_list);

    /// @brief 设置获取当前枚举框项的提示文本列表
    /// @param tiptext_list QStringList类型 提示文本列表
    void SetTipText(QStringList tiptext_list);

    /// @brief 设置当前枚举框项的提示标题列表
    /// @param tiptitle_list QStringList类型 提示标题列表
    void SetTipTitle(QStringList tiptitle_list);

    /// @brief 设置当前枚举框项的提示图像列表
    /// @param tipimage_list QStringList类型 提示图像列表
    void SetTipImage(QStringList tipimage_list);

    /// @brief 设置当前枚举框中项的索引
    /// @param index 索引值
    void SetCurrentIndex(int index);

    void SetEditable(bool editable);
    bool IsEdit();

    QString GetCurrentText();
    void SetCurrentText(const QString& text);

Q_SIGNALS:
    /// @brief 信号，当索引改变时发出
    /// @param index 索引值
    void SignalIndexChanged(int index);

    void SignalTextChanged(const QString& text);

public Q_SLOTS:
    /// @brief 槽函数，当索引改变时调用
    /// @param index 索引值
    void OnIndexChanged(int index);

private slots:
    void OnResizeEnumeration(bool labelVisibility);

private:
    PowerEnumeration* m_combobox;

};
