#pragma once

#include "AMCAXRender.h"
#include "Gui/Selection/BasicSelectionFilterDelegate.h"
#include "Gui/Selection/Selection.h"
#include <App/Color.h>
#include <PFCGlobal.h>
#include <QMainWindow>
#include <App/Color.h>
#include <Base/ParameterGroupObserver.h>
class QImage;

namespace gui {

class ViewProvider;
class Document;

struct View3DInventorViewerPrivate;

/* 
* GUI view into a 3D scene provided by View3DInventor
*/
class PFC_GUI_API View3DInventorViewer : public base::ParameterGroupObserver
{
  public:
    View3DInventorViewer(QMainWindow* parent);
    ~View3DInventorViewer() override;

    void SetDocument(Document* document);
    Document* GetDocument();

    // QWidget* GetRenderWidget();

    void ViewAll();

    void Redraw();

    void PluginPick(bool on);
    void BlockPluginPick(bool block);
    void PluginMouseClick(AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, double* pos);

    std::shared_ptr<AMCAXRender::IRenderComponent> GetComponent() const;
    std::shared_ptr<AMCAXRender::CBasicRender> GetRender() const;

    void SetPosition(double x, double y, double z);
    void GetPosition(double& x, double& y, double& z);

    using XYZ = std::tuple<double, double, double>;
    [[nodiscard]] XYZ GetMousePosition(bool round = false) const;

    void SetFocalPoint(double x, double y, double z);
    void GetFocalPoint(double& x, double& y, double& z);

    void SetPreSelectionColor(app::Color const& color);
    void SetSelectedColor(app::Color const& color);

    void SetSelectionPointSize(int size);

    void SetCameraView(AMCAXRender::CameraView type);

    void SetWcsVisible(bool visible);
    bool IsWcsVisible() const;

    void SetViewRubberBand();
    void SetOrthographicCamera(bool flag);

    void EnableRubberBandSelection();
    void DisableRubberBandSelection();
    bool IsRubberBandSelectable() const;

    std::shared_ptr<AMCAXRender::CameraManage> GetCameraManage() const;

    //!@brief 重载该方法，把属性数据保存到xml文档中
    void Store(base::XMLWriter&, std::uint32_t version) const;

    //!@brief 重载该方法，把属性数据从xml文档中恢复
    void Restore(base::XMLReader&, std::uint32_t version);

    void CaptureImageFromFrameBuffer(int width, int height, int samples, const QColor& background_color, QImage& image);

    static QColor GetPreselectionColor();
    static QColor GetSelectedColor();
    static QColor GetAlternativeSelectionColor();
    static QColor GetAttentionColor();
    QColor GetBackgroundColor() const;

    void SetMultipleChoice(bool multiple_choice);
    bool GetMultipleChoice() const;

    void SetAutoClearSelection(bool auto_clear);
    bool GetAutoClearSelection() const;

    //正常显示
    void SetViewStyleNormal();

    //着色显示
    void SetViewStyleShaded();

    //仅边线显示
    void SetViewStyleEdge();

    //三角化线框
    void SetViewStyleWireframe();

    //无边线显示
    void SetViewStyleNoFrame();

    //透明显示transparent_value取值范围[0,1]，0表示完全透明，1表示完全不透明
    void SetViewStyleTransparent(double transparent_value = 0.5);

    void OnParameterChange(base::ParameterGroup* group, std::string_view parameter_name) override;

    public:
    static std::string GetFullIDFromPickInfo(AMCAXRender::EntityId entity_id, AMCAXRender::PickType type, int index);

    void ResetBackgroundColor();

    void SetSelectionColor();

  protected:
    //获取拾取类型对应的Shape类型名称，和DocumentObjectTopoShape::GetShapeTypeName保持一致
    static std::string_view GetShapeTypeName(AMCAXRender::PickType type);
    
    //从selection的sub_name中提取出PickType和subIndex，传给渲染引擎
    static std::pair<AMCAXRender::PickType, int> ExtractPickTypeAndIndex(std::string_view sub_name_of_selection);

    //从选中对象的渲染对象名中提取document_name和object_name，这个规则和DocumentObject::GetFullName逻辑要保持一致
    static std::pair<std::string_view,std::string_view> ExtractDocNameAndObjectName(std::string_view object_full_name);
    
    void Init();

    void MouseHover(AMCAXRender::EntityId parentId, AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, int* pos);
    void MouseLeave(AMCAXRender::EntityId parentId, AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, int* pos);
    void MouseClick(AMCAXRender::EntityId parentId, AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, int* pos);
    void MouseDoubleClick(AMCAXRender::EntityId parentId, AMCAXRender::EntityId entityId, AMCAXRender::PickType type, int subIndex, int* pos);

    void OnRubberBandSelction(std::unordered_map<AMCAXRender::EntityId, std::unordered_map<AMCAXRender::PickType, std::vector<int>>> sel_map);

    void LostHighlight();
    void LostHighlight(std::string_view object_name);

  private:
    struct Render2ObjectResult
    {
        std::string_view doc_name;
        std::string_view obj_name;
        std::string sub_name;
    };
    static std::optional<Render2ObjectResult> ConvertRender2Object(
        const AMCAXRender::EntityId& parentId,
        const AMCAXRender::EntityId& entityId,
        AMCAXRender::PickType type,
        int subIndex);


  private:
    struct View3DInventorViewerPrivate* m_data;
};

}  // namespace gui
