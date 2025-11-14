#ifndef POWERDOUBLELINEEDIT_H
#define POWERDOUBLELINEEDIT_H

#include <QLineEdit>
#include <QCompleter>
#include <QPushButton>
#include <QWidgetAction>
#include <QToolButton>
#include <Widgets/Block/BlockDouble.h>

class PowerDoubleLineEdit : public QLineEdit
{
    Q_OBJECT
public:


    explicit PowerDoubleLineEdit(QWidget *parent = nullptr);

    ~PowerDoubleLineEdit();

    void SetMinimal(double min_value);
    double GetMinimal(){return m_minimal;}

    void SetMinInclusive(bool min_inclusive_value);
    bool GetMinInclusive(){return m_min_inclusive;}

    void SetMaximum(double max_value);
    double GetMaximum(){return m_maximum;}

    void SetMaxInclusive(bool max_inclusive_value);
    bool GetMaxInclusive(){return m_max_inclusive;}

    void SetTolerance(double tolerance_value);
    double GetTolerance(){return m_tolerance;}

    void SetPresentationStyle(BlockDouble::PresentationStyle style);
    BlockDouble::PresentationStyle GetPresentationStyle(){return m_pre_style;}

    void SetReadOnlyValue(bool only_read);
    bool GetReadOnlyValue(){return m_is_read_only;}

    void SetShowUnitLabel(bool show_unit);
    bool GetShowUnitLabel(){return m_show_unit_label;}

    void SetValue(double value);
    double GetValue(){return m_value;}

    void SetWidthStyle(BlockDouble::KeyinFiledWidth width);
    BlockDouble::KeyinFiledWidth GetWidthStyle(){return m_width_style;}

    void SetIncrement(double increment);
    double GetIncrement() const { return m_increment; }

    void SetShowSpinBox();

    QString FormatDouble(const QString& inputText, int decimalPlaces);
    void SetMyStyleSheet();

    void IsDisplayDouble(bool is_display);
    
signals:
    void SignalDoubleValueChange(double value);


protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void OnEditingFinished();

private:
    double m_minimal;
    double m_maximum;
    double m_tolerance;
    double m_value;
    double m_increment;
    bool m_min_inclusive;
    bool m_max_inclusive;
    bool m_show_unit_label;
    bool m_is_read_only;
    BlockDouble::PresentationStyle m_pre_style;
    BlockDouble::KeyinFiledWidth m_width_style;
    QPushButton* m_unit_btn = nullptr;
    QString m_last_valid_text;
    QToolButton *m_up_button;   
    QToolButton *m_down_button; 
    QWidgetAction *m_spin_widget; 
    QWidgetAction* m_unit_widget;
    QTimer* m_timer;
    bool m_pending_edit_finished = false; 
};

#endif // DOUBLELINEEDIT_H
