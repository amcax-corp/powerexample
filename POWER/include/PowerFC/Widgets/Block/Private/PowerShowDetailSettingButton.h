#pragma once

#include "PowerButton.h"
#include <QVector3D>
#include <AMCAXRender.h>
#include <common/PointT.hpp>
#include <common/DirectionT.hpp>
class PowerShowDetailSettingButton : public PowerButton
{
    Q_OBJECT

  public:
    enum class DialogType
    {
        Point_Dialog,
        Vector_Dialog,
        Plane_Dialog,
        CSYS_Dialog
    };
    explicit PowerShowDetailSettingButton(DialogType type, QWidget* parent = nullptr);

    void SetHasPreview(bool has_preview);
    bool HasPreview() const;
    void SetDefaultPoint(const QVector3D& point);
    QVector3D GetDefaultPoint() const;
    void SetDefaultVector(const QVector3D& vector);
    QVector3D GetDefaultVector() const;
    void SetDefaultPlane(std::pair<AMCAX::Point3, AMCAX::Direction3> plane);
    std::pair<AMCAX::Point3, AMCAX::Direction3> GetDefaultPlane() const;
    void SetDefaultCsys(const QVector3D& origin, const QVector3D& x_axis, const QVector3D& z_axis);
    QList<QVector3D> GetDefaultCsys() const;
    void SetDefaultEnumIndex(int index);

  Q_SIGNALS:
    void SignalPointConfirmed(const QVector3D& point);
    void SignalVectorConfirmed(const QVector3D& vector, const QVector3D& point);
    void SignalPlaneConfirmed(const std::pair<AMCAX::Point3, AMCAX::Direction3>& plane);
    void SignalCsysConfirmed(const QList<QVector3D>& csys);

  public Q_SLOTS:
    void OnShowDetailSetting();

  private:
    void InitStyle();

  private:
    DialogType m_dialogType;
    bool m_has_preview = true;
    int m_default_enum_index = 0;

    QVector3D m_default_point = QVector3D(0, 0, 0);
    QVector3D m_default_vector = QVector3D(0, 0, 0);
    std::pair<AMCAX::Point3, AMCAX::Direction3> m_default_plane;
    QList<QVector3D> m_default_csys = {QVector3D(0, 0, 0), QVector3D(0, 0, 0), QVector3D(0, 0, 0)};
};