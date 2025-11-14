#ifndef POWERINTEGER_H
#define POWERINTEGER_H

#include <QLineEdit>
#include <QToolButton>
#include <QWidgetAction>
#include <QVBoxLayout>
#include <QTimer>
#include <Widgets/Block/BlockInteger.h>
class PowerInteger : public QLineEdit
{
    Q_OBJECT
public:

    explicit PowerInteger(QWidget *parent = nullptr);

    ~PowerInteger();

    void SetMinimal(int min_value);
    int GetMinimal() { return m_minimal; }

    void SetMinInclusive(bool min_inclusive_value);
    bool GetMinInclusive() { return m_min_inclusive; }

    void SetMaximum(int max_value);
    int GetMaximum() { return m_maximum; }

    void SetMaxInclusive(bool max_inclusive_value);
    bool GetMaxInclusive() { return m_max_inclusive; }

    void SetPresentationStyle(BlockInteger::PresentationStyle style);
    BlockInteger::PresentationStyle GetPresentationStyle() { return m_pre_style; }

    void SetReadOnlyValue(bool only_read);
    bool GetReadOnlyValue() { return m_is_read_only; }

    void SetValue(int value);
    int GetValue() { return m_value; }

    void SetWidthStyle(BlockInteger::KeyinFiledWidth width);
    BlockInteger::KeyinFiledWidth GetWidthStyle() { return m_width_style; }

    void SetIncrement(int increment);
    int GetIncrement() { return m_increment; }

    void SetShowSpinBox();

    void SetMyStyleSheet();

    QString AddEmptyCharacter(QString empty_character);

signals:
    void SignalIntValueChange(int value);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    QSize sizeHint() const override;

private slots:
    void OnEditingFinished();

private:
    int m_minimal;
    int m_maximum;
    int m_value;
    int m_increment;
    bool m_min_inclusive;
    bool m_max_inclusive;
    bool m_is_read_only;
    BlockInteger::PresentationStyle m_pre_style;
    BlockInteger::KeyinFiledWidth m_width_style;
    QString m_last_valid_text;
    QToolButton * m_up_button;
    QToolButton * m_down_button;
    QWidgetAction *m_spin_widget;
    QWidget *m_button_widget;
    QWidget *m_edit_widget;
    QVBoxLayout *m_button_layout;
    QTimer* m_timer;
    bool m_pending_edit_finished = false; 
};

#endif // POWERINTEGER_H