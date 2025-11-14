#pragma once
#include <Widgets/Block/BlockBase.h>
#include <QVector3D>
class PowerButton;

class PW_API BlockReverseDirection : public BlockBase
{
    Q_OBJECT
    Q_PROPERTY(QString LabelText READ GetLabelText WRITE SetLabelText DESIGNABLE false)
    Q_PROPERTY(double DirectionX READ GetDirectionX WRITE SetDirectionX)
    Q_PROPERTY(double DirectionY READ GetDirectionY WRITE SetDirectionY)
    Q_PROPERTY(double DirectionZ READ GetDirectionZ WRITE SetDirectionZ)
    Q_PROPERTY(double OriginX READ GetOriginX WRITE SetOriginX)
    Q_PROPERTY(double OriginY READ GetOriginY WRITE SetOriginY)
    Q_PROPERTY(double OriginZ READ GetOriginZ WRITE SetOriginZ)

public:
    /// @brief 构造函数，用于创建一个BlockReverseDirection对象
    /// @param parent 父QWidget对象，默认为nullptr
    explicit BlockReverseDirection(QWidget *parent = nullptr);

    /// @brief 获取X方向上的方向向量
    /// @return X方向上的方向向量
    double GetDirectionX();

    /// @brief 获取Y方向上的方向向量
    /// @return Y方向上的方向向量
    double GetDirectionY();

    /// @brief 获取Z方向上的方向向量
    /// @return Z方向上的方向向量
    double GetDirectionZ();

    /// @brief 获取X方向上的原点
    /// @return X方向上的原点
    double GetOriginX();

    /// @brief 获取Y方向上的原点
    /// @return Y方向上的原点
    double GetOriginY();

    /// @brief 获取Z方向上的原点
    /// @return Z方向上的原点
    double GetOriginZ();

    /// @brief 设置X方向上的方向向量
    /// @param x X方向上的方向向量
    void SetDirectionX(double x);

    /// @brief 设置Y方向上的方向向量
    /// @param y Y方向上的方向向量
    void SetDirectionY(double y);

    /// @brief 设置Z方向上的方向向量
    /// @param z Z方向上的方向向量
    void SetDirectionZ(double z);

    /// @brief 设置X方向上的原点
    /// @param x X方向上的原点
    void SetOriginX(double x);

    /// @brief 设置Y方向上的原点
    /// @param y Y方向上的原点
    void SetOriginY(double y);

    /// @brief 设置Z方向上的原点
    /// @param z Z方向上的原点
    void SetOriginZ(double z);

    /// @brief 获取方向向量
    /// @return 方向向量
    QVector3D GetDirection();

    /// @brief 设置方向向量
    /// @param direction 方向向量
    void SetDirection(QVector3D direction);

    /// @brief 获取原点
    /// @return 原点
    QVector3D GetOrigin();

    /// @brief 设置原点
    /// @param origin 原点
    void SetOrigin(QVector3D origin);

    bool IsReversed() const;
    void SetReversed(bool reversed);

public:
    void SetLabelVisible(bool visible);

signals:
    /// @brief 信号：X方向上的方向向量已改变
    /// @param newX 新的X方向上的方向向量
    void SignalsDirectionXChanged(double newX);

    /// @brief 信号：Y方向上的方向向量已改变
    /// @param newY 新的Y方向上的方向向量
    void SignalsDirectionYChanged(double newY);

    /// @brief 信号：Z方向上的方向向量已改变
    /// @param newZ 新的Z方向上的方向向量
    void SignalsDirectionZChanged(double newZ);

    /// @brief 信号：X方向上的原点已改变
    /// @param newX 新的X方向上的原点
    void SignalsOriginXChanged(double newX);

    /// @brief 信号：Y方向上的原点已改变
    /// @param newY 新的Y方向上的原点
    void SignalsOriginYChanged(double newY);

    /// @brief 信号：Z方向上的原点已改变
    /// @param newZ 新的Z方向上的原点
    void SignalsOriginZChanged(double newZ);

    /// @brief 信号：方向向量已改变
    /// @param newDirection 新的方向向量
    void SignalsDirectionChanged(const QVector3D &newDirection);

    /// @brief 信号：原点已改变
    /// @param newOrigin 新的原点
    void SignalsOriginChanged(const QVector3D &newOrigin);

    /// @brief 信号：方向已反转
    void SignalsDirectionReversed(bool);

private:
    /// @brief 电源按钮指针
    PowerButton *m_button;

    /// @brief 方向向量
    QVector3D m_direction;

    /// @brief 原点
    QVector3D m_origin;

    bool m_reversed = false;
};
