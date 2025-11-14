#pragma once

#include "RenderDataHelper.h"
#include "ViewProviderDocumentObject3D.h"
#include <App/Properties/PropertyMap.h>
#include <app/Properties/PropertyMaterial.h>

namespace gui {

class PFC_GUI_API ViewProviderDocumentObjectTopoShape : public ViewProviderDocumentObject3D
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    app::PropertyMaterial Material;  //材质
    app::PropertyMap FaceOpacities;

    ViewProviderDocumentObjectTopoShape();
    ~ViewProviderDocumentObjectTopoShape() override;

    void SetFaceOpacities(std::map<std::string, double> const& opacities);

    virtual void Attach(app::DocumentObject* object) override;
    virtual void Reattach(app::DocumentObject* object) override;

    [[nodiscard]] AMCAXRender::CAXMeshInfo GetMeshInfo(bool isVertex = true,
                                         bool isEdge = true,
                                         bool isFace = true) const;
    void UpdateData(const app::Property*) override;


    void SetHighlight(bool highlight, AMCAXRender::PickType type, int sub_index)
    {
        SetHighlight(highlight, type, sub_index, true);
    }
    void SetHighlight(bool highlight, AMCAXRender::PickType type, int sub_index, bool refresh) override;
    void SetHighlight(std::unordered_map<AMCAXRender::PickType, std::vector<int>>&& map_pick_index);
    void SetSelected(bool highlight, AMCAXRender::PickType type, int sub_index, bool refresh) override;

    void FinishRestore() override;

    /// 会自动清空m_render_id的对象
    void DeleteFromView() override;
};

}  // namespace gui