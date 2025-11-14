#pragma once

#include <App/DocumentObject.h>
#include <Widgets/Block/BlockCAMDimension.h>
#include <Widgets/Block/BlockSpecifyPoint.h>
#include <Widgets/Block/BlockSpecifyVector.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <AMCAXRender.h>
#include <common/PointT.hpp>
#include <common/DirectionT.hpp>
namespace standard {
    class ViewProviderPlane;
}

class PW_API PowerPlaneSettingDialog : public BlockDialog
{
    Q_OBJECT

    friend class standard::ViewProviderPlane;

  public:
    explicit PowerPlaneSettingDialog(std::pair<AMCAX::Point3, AMCAX::Direction3> plane, bool has_preview, QWidget* parent = nullptr);

  public:
    QSize sizeHint() const override;

    const std::pair<AMCAX::Point3, AMCAX::Direction3> GetCurrentPlane() const;
    std::string_view GetDocumentObjectName() const;

  protected:
    explicit PowerPlaneSettingDialog(app::DocumentObject* origin_doc, QWidget* parent = nullptr);

  signals:
    void SignalConfirmed(const std::pair<AMCAX::Point3, AMCAX::Direction3>& plane);

  protected Q_SLOTS:
    bool OnConfirmed() override;
    void OnResetted() override;
    void OnCanceled() override;

  private Q_SLOTS:
    void OnPointChanged(const QVector3D& point);
    void OnVectorPoint(const QVector3D& vector);
    void OnDistanceChanged(double value);
    void OnTypeChanged(int index);
    void OnReverseDirectionChanged(bool reversed);

  private:
    void InitUI();

  private:
    PowerEnumeration* m_enum_select_types = nullptr;
    BlockSpecifyPoint* m_specify_point = nullptr;
    BlockSpecifyVector* m_specify_vector = nullptr;
    BlockCAMDimension* m_cam_distance = nullptr;
    BlockReverseDirection* m_reverse_direction = nullptr;

    double m_original_x = 0.0;
    double m_original_y = 0.0;
    double m_original_z = 0.0;

    double m_original_i = 0.0;
    double m_original_j = 0.0;
    double m_original_k = 0.0;

    app::DocumentObject* m_specify_doc = nullptr;
    app::DocumentObject* m_tmp_doc = nullptr;
};