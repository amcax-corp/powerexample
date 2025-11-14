#ifndef POWERLABEL_H
#define POWERLABEL_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
class PowerToolTip;
class PowerLabel : public QWidget
{
    Q_OBJECT
public:

    PowerLabel(QWidget *parent = nullptr);
    ~PowerLabel();

    void SetDisPlayLabel(bool is_display_label);
    bool GetDisPlayLabel(){return m_is_display_label;}
    
    void SetDisplayBitMap(bool is_display_bitmap);
    bool GetDisplayBitMap(){return m_is_display_bitmap;}
    
    void SetLabelBitMap(QPixmap pixmap);
    QPixmap GetLabelBitMap(){return m_label_bitmap;}
    
    void SetLabelText(const QString& label);
    QString GetLabelText(){return m_label_text;}
    
    void SetToolTipTitle(const QString& title);
    QString GetToolTipTitle(){return m_tooltip_title;}
    
    void SetToolTip(PowerToolTip* tooltip);
    PowerToolTip* GetToolTip(){return m_tooltip;}
    
    void SetBitMapAndLabel();

    void SetMyStyleSheet();

private:
    QLabel* m_bitmap_label;
    QLabel* m_text_label;
    QPixmap m_label_bitmap;
    bool m_is_display_bitmap;
    bool m_is_display_label;
    QString m_label_text;
    QString m_tooltip_title;
    PowerToolTip* m_tooltip;
};


#endif // POWERLABEL_H
