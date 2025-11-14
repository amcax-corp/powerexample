#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPoint>
#include <QTimer>
#include <QLineEdit>
#include <QComboBox>
#include <QScrollArea>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include "ColorTable.hpp"
class PowerEnumeration;

class PW_API BlockColorPickerDialog : public BlockDialog{

    Q_OBJECT

public:
    enum class SortMode {
        ByColorOrder,  // 按颜色表原始顺序
        ByColorId      // 按颜色ID升序
    };

    BlockColorPickerDialog(QWidget *parent = nullptr);

    ~BlockColorPickerDialog();

    void Initial();

    void SetPalettePart();

    void SetInheritPart();

    void UpdateColorButtons(SortMode mode); // 更新颜色按钮

    bool OnConfirmed() override;
    bool OnApplied() override;
    void OnResetted() override;
    void OnCanceled() override;

signals:
    void SignalColorSelected(const QColor& color, int colorId);

private slots:
    void OnTogglePaletteWidget();
    void OnToggleInheritWidget();
    void OnFindEditTextChanged(const QString& text);

private:
    QVBoxLayout *m_main_vlayout;

    QVBoxLayout *m_color_layout;
    QPushButton *m_palette_button;

    bool m_is_palette_expanded;

    QWidget *m_palette_widget;
    QVBoxLayout *m_palette_vlayout;
    QHBoxLayout *m_find_layout;
    QLabel *m_find_label;
    QLineEdit *m_find_edit;
    QLabel *m_subset_label;
    PowerEnumeration *m_find_combox;
    QWidget *m_select_color_widget;
    QGridLayout *m_select_color_layout;

    QVBoxLayout *m_inherit_layout;
    QPushButton *m_inherit_button;
    QWidget *m_inherit_widget;
    QHBoxLayout *m_inherit_button_layout;
    QLabel *m_object_label;
    QPushButton *m_object_button;

    bool m_is_inherit_expanded;

    QPoint m_drag_position;
    bool m_is_top_area = false;    // 标识是否在可拖拽区域内
    // 用于拉伸窗口
    bool m_is_resizing;
    QPoint m_drag_position_resize;

    QScrollArea *m_color_scroll_area;  // 新增滚动区域

    DisplayColorTable m_color_table;  // 新增颜色表
    QList<QColor> m_color_list;  // 缓存颜色值
    QList<int> m_color_id_list;  // 缓存颜色 ID
    int m_current_color_id = -1; // 当前选中颜色 ID
    QColor m_current_color = "#FFFFFF";  // 当前选中颜色
    QMap<int, QString> m_color_label_map;  // 颜色标签映射
    QStringList m_color_label_list{
        "White",
        "Pale Lemon",
        "Medium Lemon",
        "Strong Lemon",
        "Medium Yellow",
        "Yellow",
        "Pale Sky",
        "Pale Green",
        "Pale Lime",
        "Medium Lime",
        "Lime",
        "Deep Lemon",
        "Pale Cyan",
        "Pale Emerald",
        "Powder Gray",
        "Pale Spring",
        "Pale Yellow",
        "Strong Pistachio",
        "Medium Cyan",
        "Medium Emerald",
        "Pale Aqua",
        "Pale Mint",
        "Pale Khaki",
        "Deep Pistachio",
        "Strong Cyan",
        "Medium Aqua",
        "Pale Turquoise",
        "Medium Spring",
        "Strong Green",
        "Strong Lime",
        "Cyan",
        "Medium Sky",
        "Strong Aqua",
        "Medium Mint",
        "Medium Green",
        "Green",
        "Pale Pink",
        "Pale Salmon",
        "Pale Orange",
        "Medium Peach",
        "Medium Orange",
        "Deep Yellow",
        "Pale Lavender",
        "Light Gray",
        "Pale Brown",
        "Strong Yellow",
        "Medium Olive",
        "Pale Olive",
        "Pale Ice",
        "Ash Gray",
        "Pale Pistachio",
        "Pale Gold",
        "Medium Gold",
        "Pale Leaf",
        "Medium Cornflower",
        "Deep Aqua",
        "Pale Pine",
        "Medium Pistachio",
        "Deep Lime",
        "Deep Green",
        "Pale Cornflower",
        "Deep Cyan",
        "Strong Spring",
        "Deep Spring",
        "Medium Pine",
        "Strong Pine",
        "Strong Sky",
        "Strong Mint",
        "Strong Emerald",
        "Pale Sea",
        "Pale Forest",
        "Deep Mint",
        "Pale Magenta",
        "Pale Peach",
        "Strong Salmon",
        "Pale Carrot",
        "Strong Orange",
        "Orange",
        "Medium Ice",
        "Pale Stone",
        "Pale Maroon",
        "Medium Coral",
        "Medium Brown",
        "Strong Gold",
        "Pale Midnight",
        "Strong Lavender",
        "Silver Gray",
        "Medium Stone",
        "Strong Olive",
        "Medium Khaki",
        "Pale Blue",
        "Deep Ice",
        "Medium Sea",
        "Pale Moss",
        "Strong Khaki",
        "Medium Leaf",
        "Strong Cornflower",
        "Medium Azure",
        "Pale Teal",
        "Medium Moss",
        "Medium Forest",
        "Strong Sea",
        "Cornflower",
        "Pale Azure",
        "Medium Teal",
        "Deep Emerald",
        "Deep Pine",
        "Emerald",
        "Medium Pink",
        "Medium Salmon",
        "Pale Red",
        "Medium Red",
        "Deep Peach",
        "Deep Orange",
        "Pale Purple",
        "Pale Fuchsia",
        "Pale Plum",
        "Strong Peach",
        "Medium Carrot",
        "Strong Coral",
        "Pale Steel",
        "Medium Lavender",
        "Smoke Gray",
        "Medium Maroon",
        "Brown",
        "Deep Olive",
        "Medium Purple",
        "Pale Violet",
        "Medium Steel",
        "Granite Gray",
        "Deep Khaki",
        "Deep Leaf",
        "Medium Turquoise",
        "Medium Royal",
        "Strong Steel",
        "Strong Moss",
        "Deep Sea",
        "Strong Leaf",
        "Medium Blue",
        "Strong Turquoise",
        "Strong Azure",
        "Strong Teal",
        "Deep Forest",
        "Strong Forest",
        "Medium Magenta",
        "Strong Magenta",
        "Deep Red",
        "Deep Salmon",
        "Pale Crimson",
        "Deep Pink",
        "Pale Tan",
        "Deep Magenta",
        "Strong Tan",
        "Deep Tan",
        "Medium Crimson",
        "Deep Gold",
        "Pale Coral",
        "Pale Indigo",
        "Medium Gray",
        "Strong Plum",
        "Strong Maroon",
        "Deep Brown",
        "Medium Tan",
        "Purple",
        "Medium Indigo",
        "Medium Violet",
        "Deep Carrot",
        "Deep Stone",
        "Strong Blue",
        "Strong Ice",
        "Medium Midnight",
        "Deep Indigo",
        "Dark Gray",
        "Deep Umber",
        "Deep Cornflower",
        "Pale Royal",
        "Deep Turquoise",
        "Deep Azure",
        "Deep Teal",
        "Deep Moss",
        "Magenta",
        "Strong Red",
        "Medium Fuchsia",
        "Strong Fuchsia",
        "Strong Pink",
        "Red",
        "Pale Umber",
        "Medium Plum",
        "Strong Brown",
        "Strong Carrot",
        "Strong Stone",
        "Deep Coral",
        "Deep Lavender",
        "Strong Indigo",
        "Medium Umber",
        "Strong Umber",
        "Deep Crimson",
        "Strong Crimson",
        "Strong Purple",
        "Deep Purple",
        "Iron Gray",
        "Deep Fuchsia",
        "Deep Plum",
        "Deep Maroon",
        "Deep Sky",
        "Strong Royal",
        "Strong Midnight",
        "Strong Violet",
        "Deep Violet",
        "Charcoal Gray",
        "Blue",
        "Deep Blue",
        "Deep Steel",
        "Deep Royal",
        "Deep Midnight",
        "Black"
    };


};
