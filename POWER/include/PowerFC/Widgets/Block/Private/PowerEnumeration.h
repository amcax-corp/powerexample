#ifndef POWERENUMERATION_H
#define POWERENUMERATION_H

#include <QComboBox>
#include <QStringList>
#include "PowerToolTip.h"

class PowerEnumeration : public QComboBox
{
    Q_OBJECT

public:
    PowerEnumeration(QWidget* parent = nullptr);
    ~PowerEnumeration();

    void SetSensitivity(const QStringList& sens_list);
    QStringList GetSensitivity();

    void SetVisibility(const QStringList& visi_list);
    QStringList GetVisibility();

    void SetValue(const QStringList& value_list);
    QStringList GetValue();

    void SetImage(const QStringList& pixmap_list);
    QStringList GetImage();

    void SetTipTextList(const QStringList& tiptext_list);
    QStringList GetTipTextList();

    void SetTipTitleList(const QStringList& tiptitle_list);
    QStringList GetTipTitleList();

    void SetTipImageList(const QStringList& tipimage_list);
    QStringList GetTipImageList();

    void SetEditMode(bool edit_mode);
    bool GetEditMode();

    void SetToolTips();         // 初始化提示框相关设置
    bool ViewportEventFilter(QObject* obj, QEvent* event); // 视图事件过滤器

    void SetCurrentIndex(int index);
    int GetCurrentIndex();

    int GetCharacterMaxWidth();

    void SetWidth(int fixed_width);

    int CalculateMinimumPopupWidth() const;
    void AdjustPopupWidth();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void focusOutEvent(QFocusEvent *e) override;
    void showPopup() override;

    // void paintEvent(QPaintEvent *event) override;
    
private slots:
    void OnCurrentIndexChanged();


private:
    QStringList m_sens_list;
    QStringList m_visi_list;
    QStringList m_value_list;
    QStringList m_image_list;
    bool m_dropdown_clicked = false; 
    
    QStringList m_item_tips;       // 存储每项提示文本
    QStringList m_item_titles;     // 存储每项标题
    QStringList m_item_images;     // 存储每项图片路径
    PowerToolTip* m_current_tooltip = nullptr; // 当前显示的提示框
    int m_current_index = 0;
    bool m_edit_mode = false;
};
#endif //POWERENUMERATION_H