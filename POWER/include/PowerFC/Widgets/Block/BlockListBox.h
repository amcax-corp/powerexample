#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QCheckBox>
#include <Widgets/PowerWidgetsConfig.h>
#define BLOCK_LIST_ITEM_HEIGHT 16
class PW_API BlockListBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int Height READ GetHeight WRITE SetHeight)
    Q_PROPERTY(QStringList Listltems READ GetListltems WRITE SetListltems)
    Q_PROPERTY(int MaximumStringLength READ GetMaximumStringLength WRITE SetMaximumStringLength)
    Q_PROPERTY(bool AddButtonVisibility READ IsAddButtonVisibility WRITE SetAddButtonVisibility)
    Q_PROPERTY(bool DeleteButtonVisibility READ IsDeleteButtonVisibility WRITE SetDeleteButtonVisibility)
    Q_PROPERTY(bool MoveUpDownButtonsVisibility READ IsMoveUpDownButtonsVisibility WRITE SetMoveUpDownButtonsVisibility)
    Q_PROPERTY(bool SingleSelect READ GetSingleSelect WRITE SetSingleSelect)
    Q_PROPERTY(bool ResizeHeightWithDialog READ GetResizeHeightWithDialog WRITE SetResizeHeightWithDialog)

public:
    /// @brief 构造函数，初始化BlockListBox对象
    /// @param parent 父QWidget指针，默认为nullptr
    explicit BlockListBox(QWidget *parent = nullptr);
    ~BlockListBox();

    /// @brief 获取当前高度
    /// @return 当前高度
    int GetHeight() const;

    /// @brief 获取当前列表所有项
    /// @return 当前列表所有项
    QStringList GetListltems() const;

    /// @brief 获取最大字符串长度
    /// @return 最大字符串长度
    int GetMaximumStringLength() const;

    /// @brief 是否显示添加按钮
    /// @return 是否显示添加按钮
    bool IsAddButtonVisibility() const;

    /// @brief 是否显示删除按钮
    /// @return 是否显示删除按钮
    bool IsDeleteButtonVisibility() const;

    /// @brief 是否显示上下移动按钮
    /// @return 是否显示上下移动按钮
    bool IsMoveUpDownButtonsVisibility() const;

    /// @brief 是否单选
    /// @return 是否单选
    bool GetSingleSelect() const;

    /// @brief 设置当前高度
    /// @param height 新高度
    void SetHeight(int height);

    /// @brief 设置当前列表项
    /// @param listltems 新列表项
    void SetListltems(QStringList listltems);

    /// @brief 设置最大字符串长度
    /// @param maximumStringLength 新最大字符串长度
    void SetMaximumStringLength(int maximumStringLength);

    /// @brief 设置是否显示添加按钮
    /// @param showAddButton 是否显示添加按钮
    void SetAddButtonVisibility(bool showAddButton);

    /// @brief 设置是否显示删除按钮
    /// @param showDeleteButton 是否显示删除按钮
    void SetDeleteButtonVisibility(bool showDeleteButton);

    /// @brief 设置是否显示上下移动按钮
    /// @param showMoveUpDownButtons 是否显示上下移动按钮
    void SetMoveUpDownButtonsVisibility(bool showMoveUpDownButtons);

    /// @brief 设置是否单选
    /// @param singleSelect 是否单选
    void SetSingleSelect(bool singleSelect);

    /// @brief 获取高度是否随Dialog调整
    /// @return int类型的多行字符串显示的行数
    bool GetResizeHeightWithDialog();

    /// @brief 获取当前索引
    /// @return 当前索引
    int GetCurrentIndex() const;

    /// @brief 获取当前数据
    /// @return 当前数据
    QString GetCurrentData() const;

    /// @brief 获取选中索引列表
    /// @return 选中索引列表
    QList<int> GetSelectedIndexes() const;

    /// @brief 获取选中数据列表
    /// @return 选中数据列表
    QStringList GetSelectedData() const;

    /// @brief 设置指定行的数据
    /// @param row 行索引
    /// @param data 新数据
    void SetItemData(int row, const QString &data);

    /// @brief 设置当前索引
    /// @param index 新索引
    void SetCurrentIndex(int index);

    /// @brief 设置是否可编辑
    /// @param enable 是否可编辑
    void SetEditable(bool enable);

    /// @brief 设置高度是否随Dialog调整
    /// @param height int类型的多行字符串显示的行数
    void SetResizeHeightWithDialog(bool resizeHeightWithDialog);

protected:
    /// @brief 重写按键事件处理函数
    /// @param event 按键事件
    void keyPressEvent(QKeyEvent *event) override;

signals:
    /// @brief 信号：项索引被点击
    /// @param index 被点击的索引
    void SignalItemIndexClicked(int index);

    /// @brief 信号：项文本被改变
    /// @param index 被改变的索引
    /// @param newText 新文本
    void SignalItemTextChanged(int index, const QString &newText);

    /// @brief 信号：值被改变
    /// @param value 新值
    void SignalValueChanged(QStringList value);

    void SignalDeleteItem(int index);

  private slots:
    void MoveItemsUp();
    void MoveItemsDown();
    void AddItem();
    void DeleteItems();

private:
    void SetupUI();
    void SetupConnections();
    void AddDemoItems();
    void MoveItems(int direction);
    void UpdateButtonsStatue();
    void ResizeHeight();

private:
    void onShowButtonsChanged();

    QListWidget *m_listWidget;
    QWidget *m_control_widget;
    QPushButton *m_up_button;
    QPushButton *m_down_button;
    QPushButton *m_add_button;
    QPushButton *m_delete_button;
    int m_height;
    int m_max_string_length;
    bool m_resize_height_with_dialog = false;
};
