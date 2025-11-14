#pragma once

#include "AMCAXRender.h"
#include "RenderDataHelper.h"
#include "ViewProviderDocumentObject.h"
#include <App/Properties/PropertyBool.h>
#include <App/Properties/PropertyMatrix.h>
#include <base/Uuid.h>

namespace gui {

class PFC_GUI_API ViewProviderDocumentObject3D : public ViewProviderDocumentObject, public RenderDataHelper
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    // 透明度 0-100
    app::PropertyFloat Opacity;
    app::PropertyMatrix Matrix;

    ViewProviderDocumentObject3D();
    ~ViewProviderDocumentObject3D() override;

    virtual void UpdateView() override;

    void SetRenderView(std::shared_ptr<AMCAXRender::IRenderComponent> component, std::shared_ptr<AMCAXRender::CBasicRender> render);

    virtual AMCAXRender::EntityId AddRender(AMCAXRender::CAXMeshInfo info);

    bool IsSelectable() const override { return true; }

    void SetHighlight(bool highlight, AMCAXRender::PickType type, int sub_index)
    {
        SetHighlight(highlight, type, sub_index, true);
    }
    virtual void SetHovered(bool hovered, AMCAXRender::PickType type, int sub_index, bool refresh) {}
    virtual void SetHighlight(bool highlight, AMCAXRender::PickType type, int sub_index, bool refresh) {}
    virtual void LostHighlight() {}
    virtual void SetSelected(bool highlight, AMCAXRender::PickType type, int sub_index, bool refresh) {}
    virtual void SetAttention(bool highlight, AMCAXRender::PickType type, int sub_index, bool refresh) {}

  protected:
    std::string GetUuid() const;

  protected:
    std::shared_ptr<AMCAXRender::IRenderComponent> m_component;
    std::shared_ptr<AMCAXRender::CBasicRender> m_render;

    // 渲染id
    std::string m_render_id;
};

}  // namespace gui