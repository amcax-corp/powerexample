#pragma once

#include <QVector3D>
#include <QList>
#include <unordered_map>

#include <App/DocumentObject.h>
#include <Widgets/Block/BlockSpecifyPoint.h>
#include <Widgets/Block/BlockSpecifyVector.h>
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Widgets/PowerWidgetsConfig.h>
#include <AMCAXRender.h>
#include <common/PointT.hpp>

class BlockGroup;
class PowerEnumeration;

namespace standard {
    class ViewProviderCoordinate;
}

class PW_API PowerCsysSettingDialog : public BlockDialog
{
    Q_OBJECT

    friend class standard::ViewProviderCoordinate;

public:

    explicit PowerCsysSettingDialog(QVector3D origin, QVector3D x_axis, QVector3D z_axis, bool has_preview, QWidget* parent = nullptr);
    explicit PowerCsysSettingDialog(app::DocumentObject* origin_doc, QWidget* parent = nullptr);
    ~PowerCsysSettingDialog();

    const QList<QVector3D> GetCurrentCsys() const;
    std::string_view GetDocumentObjectName() const;
    QSize sizeHint() const override;
    void SetEnumIndex(int index);

    // 枚举类型定义
    enum class AxisType 
    {
        XAxis,
        YAxis,
        ZAxis
    };

    // 拾取方式
    enum class AxisPairType 
    {
        XY_Origin,
        XZ_Origin,
        YZ_Origin
    };

signals:
    void SignalConfirmed(const QList<QVector3D>& csys);

protected Q_SLOTS:
    bool OnConfirmed() override;
    void OnResetted() override;
    void OnCanceled() override;
    void showEvent(QShowEvent *event) override;
    
private:
    // UI初始化
    void InitUI();
    void InitConnection();
   

    // 坐标轴操作
    void SetSelectionPointSize(int size);
    bool CheckParallel(AxisType type);
    // 渲染更新
    void RestoreVectorArrow();
    void UpdateAxisVisibleStatus();
    void RenderVectorArrow(const AMCAX::Point3& origin, const QVector3D& vector, AxisType type);
    void RemoveRenderVectorArrow(AxisType type);
    void UpdateCysProvider();
private:
    // 文档对象
    app::DocumentObject* m_specify_doc = nullptr;
    app::DocumentObject* m_axis_tmp_doc = nullptr;

    // 原始坐标系数据
    QVector3D m_original_origin;
    QVector3D m_original_x_axis;
    QVector3D m_original_z_axis;

    // UI组件
    BlockSpecifyPoint* m_specify_origin;
    BlockSpecifyVector* m_specify_x_axis;
    BlockSpecifyVector* m_specify_y_axis;
    BlockSpecifyVector* m_specify_z_axis;

    BlockGroup *group_origin;
    BlockGroup *group_x;
    BlockGroup *group_y;
    BlockGroup *group_z;

    PowerEnumeration* m_enum_select_types;

    // 状态标志
    bool m_selections_satisfied[4] = {false};
    bool m_in_automic_update_axis = false;

    // 渲染相关
    std::string m_original_entity_id;
    std::unordered_map<AxisType, std::optional<AMCAXRender::EntityId>> m_axis_dircetion_entity_ids;
    AxisPairType m_current_axis_pair_type = AxisPairType::XY_Origin;
};    