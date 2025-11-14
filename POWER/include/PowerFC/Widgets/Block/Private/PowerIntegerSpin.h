#ifndef POWERINTEGERSPIN_H
#define POWERINTEGERSPIN_H

#include <QSpinBox>
#include <QEvent>
#include <QLineEdit>
#include <QString>

class PowerIntegerSpin : public QSpinBox
{
    Q_OBJECT
public:
    enum PresentationStyle {
        Keyin,    // 纯输入模式（隐藏按钮）
        Spin,     // 带按钮模式
        Scale,    // 保留（需配合其他控件实现）
        ScaleKeyin,
        Combo
    };
    Q_ENUM(PresentationStyle);

    enum KeyinFiledWidth {
        Narrow,
        Standard
    };
    Q_ENUM(KeyinFiledWidth);

    explicit PowerIntegerSpin(QWidget *parent = nullptr);
    ~PowerIntegerSpin() override;

    void SetMinimal(int min_value);
    int GetMinimal() const { return m_minimal; }

    void SetMinInclusive(bool min_inclusive);
    bool GetMinInclusive() const { return m_minInclusive; }

    void SetMaximum(int max_value);
    int GetMaximum() const { return m_maximum; }

    void SetMaxInclusive(bool max_inclusive);
    bool GetMaxInclusive() const { return m_maxInclusive; }

    void SetPresentationStyle(PresentationStyle style);
    PresentationStyle GetPresentationStyle() const { return m_preStyle; }

    void SetReadOnlyValue(bool readOnly);
    bool GetReadOnlyValue() const { return isReadOnly(); }

    void SetValue(int value);
    int GetValue() const { return value(); }

    void SetWidthStyle(KeyinFiledWidth width);
    KeyinFiledWidth GetWidthStyle() const { return m_widthStyle; }

    void SetIncrement(int increment);
    int GetIncrement() const { return singleStep(); }

signals:
    void SignalIntValueChange(int value);

protected:
    QValidator::State validate(QString &input, int &pos) const override;
    QString textFromValue(int value) const override;
    QSize sizeHint() const override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    int m_minimal;
    int m_maximum;
    bool m_minInclusive;
    bool m_maxInclusive;
    PresentationStyle m_preStyle;
    KeyinFiledWidth m_widthStyle;
    QString m_lastValidText;
};

#endif // POWERINTEGERSPIN_H