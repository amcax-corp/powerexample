#ifndef POWERSTRINGLINEEDIT_H
#define POWERSTRINGLINEEDIT_H

#include <QLineEdit>
#include <QCompleter>
#include <QPushButton>
#include <QWidgetAction>
#include <Widgets/Block/BlockString.h>

class PowerStringLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit PowerStringLineEdit(QWidget *parent = nullptr);

    ~PowerStringLineEdit();

public:

    BlockString::PresentationStyle GetPresentationStyle() { return m_present_style; }
    BlockString::KeyinFiledWidth GetWidthStyle() { return m_width_style; }
    bool GetRequiredInput() { return m_required_input; }
    int GetMaxTextLength() { return m_max_text_length; }

public slots:
    void SetPresentationStyle(BlockString::PresentationStyle present_style);
    void SetWidthStyle(BlockString::KeyinFiledWidth width);
    void SetRequiredInput(bool required_input);
    void SetMaxTextLength(int length);

private:
    bool m_required_input;
    BlockString::PresentationStyle m_present_style;
    BlockString::KeyinFiledWidth m_width_style;
    int m_max_text_length;
};

#endif // POWERSTRINGLINEEDIT_H
