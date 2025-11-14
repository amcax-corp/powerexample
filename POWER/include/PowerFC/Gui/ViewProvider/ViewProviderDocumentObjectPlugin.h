#pragma once

#include "ViewProviderDocumentObject3D.h"

namespace gui {

class PFC_GUI_API ViewProviderDocumentObjectPlugin : public ViewProviderDocumentObject3D
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    ViewProviderDocumentObjectPlugin();
    ~ViewProviderDocumentObjectPlugin() override;

    void UpdateData(const app::Property*) override;

    void DeleteFromView() override;

    void SetHighlight(bool highlight, AMCAXRender::PickType type, int sub_index, bool refresh = true) override;
    virtual void SetHighlights(bool highlight, AMCAXRender::PickType type, const std::vector<int>& sub_indexs);

    AMCAXRender::EntityId AddRender(AMCAXRender::CAXMeshInfo info) override;

    void FinishRestore() override;
};

}  // namespace gui