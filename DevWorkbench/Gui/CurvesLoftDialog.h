#pragma once

// 如果包含头文件异常，请检查是否在Make(CMake/QMake)中添加了依赖库
#include <Widgets/ContainerBlock/BlockDialog.h>
#include <Base/Object/CurvesLoftObject.h>
#include <Gui/Selection/Selection.h>
#include <topology/TopoFace.hpp>
#include <topology/TopoEdge.hpp>
#include <App/Properties/PropertyTopoShape.h>
#include <App/Properties/PropertyString.h>
#include <App/Properties/PropertyBool.h>
#include <Interface/Entity.h>
#include <App/DocumentObjectTopoShape.h>
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>
class GeometrySelectTableWidget;

namespace Ui
{
  class CurvesLoftDialog;
}
class BlockSelectObject;
namespace Dev
{
  class CurvesLoftDialog : public BlockDialog
  {
    Q_OBJECT
  public:
    CurvesLoftDialog(CurvesLoftObject *object, QWidget *parent = nullptr);
    ~CurvesLoftDialog();
  public slots:
    // 点击确定时触发
    bool OnConfirmed() override;
    void OnCanceled() override;
  private slots:
    // 鼠标拾取到曲线后的槽函数
    void OnCurvesSelectionChanged(const QList<gui::SelectionChanges> &changes);
    void OnButtonClicked();

    // 预览放样的曲面
    void OnPreviewLoft(bool is_preview);

  private:    
    // 曲线放样接口，输入两个曲线，输出放样曲面
    AMCAX::TopoFace StartLoft(std::vector<AMCAX::TopoEdge> &edges);

    // 渲染拾取曲线的起始方向
    AMCAXRender::EntityId RenderEdgeDirection(AMCAX::TopoEdge &edge);

    bool SplitFullName(std::string id_name, std::string &document_name, std::string &object_name, std::string &sub_name);

    // 刷新渲染窗口
    void RefreshRenderWindow();

    std::shared_ptr<AMCAXRender::CBasicRender> GetCurrentRender();

    // 初始化选择控件UI
    void InitSelectUI();
    
    // 初始化边的渲染
    void InitEdgeRender(app::PropertyTopoShape* topoShape, AMCAXRender::EntityId& renderId);
    
    // 初始化选择器控件
    void InitSelector(BlockSelectObject* selector, app::PropertyString* edgeName);

    // 更新指定曲线的选择和渲染（curveIndex: 1 或 2）
    void UpdateCurveSelection(int curveIndex, const std::string& full_name, const AMCAX::TopoShape& edge);

    // 反转指定曲线的方向（curveIndex: 1 或 2）
    void ReverseEdgeOrientation(int curveIndex);
  private:
    Ui::CurvesLoftDialog *ui;

    CurvesLoftObject *m_object;
    AMCAXRender::EntityId m_curve1_render_id;
    AMCAXRender::EntityId m_curve2_render_id;

    /*当前被选中放样的对象，如果用户不选择逆向则和m_edge_name1指向的TopoShape对象是一样的，否则会拷贝一份然后做逆向处理*/
    app::PropertyTopoShape *m_topo_shape1;
    app::PropertyTopoShape *m_topo_shape2;

    /*当前被选中edge的名字*/
    app::PropertyString *m_edge_name1;
    app::PropertyString *m_edge_name2;
  };
}