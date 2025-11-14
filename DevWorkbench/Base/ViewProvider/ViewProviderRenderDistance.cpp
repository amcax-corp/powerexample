#include "ViewProviderRenderDistance.h"
#include <App/Application.h>
#include <App/Document.h>
#include <App/Properties/PropertyVector.h>
#include <Gui/Document.h>
#include <App/DocumentObjectTopoShape.h>
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>
#include <Gui/RenderDistanceDialog.h>
#include <Gui/MainWindow.h>
#include <Base/Object/RenderDistanceObject.h>
#include <modeling/MakeBox.hpp>

#ifdef GetObject
#undef GetObject
#endif
PFC_TYPESYSTEM_IMPL(Dev::ViewProviderRenderDistance, gui::ViewProviderDocumentObjectTopoShape)

namespace Dev
{

    ViewProviderRenderDistance::ViewProviderRenderDistance()
        : ViewProviderDocumentObjectTopoShape()
    {
    }

    ViewProviderRenderDistance::~ViewProviderRenderDistance()
    {
    }

    QWidget *ViewProviderRenderDistance::GetTaskView() const
    {
        auto object = GetObject<RenderDistanceObject>();
        auto dialog = new RenderDistanceDialog(object, gui::GetMainWindow());
        return dialog;
    }

    void ViewProviderRenderDistance::UpdateData(const app::Property *prop)
    {
        auto object = GetObject<RenderDistanceObject>();
        ViewProviderDocumentObjectTopoShape::UpdateData(prop);

        if (prop == &Visibility || prop == object->GetPropertyFloat("point1x")|| prop == object->GetPropertyFloat("point1y")|| prop == object->GetPropertyFloat("point1z")|| prop == object->GetPropertyFloat("point2x")|| prop == object->GetPropertyFloat("point2y")|| prop == object->GetPropertyFloat("point2z"))
        {
            if (Visibility.GetValue() && m_render != nullptr)
            {

                double point1x, point1y, point1z, point2x, point2y, point2z;
                point1x = object->GetPropertyFloatValue("point1x");
                point1y = object->GetPropertyFloatValue("point1y");
                point1z = object->GetPropertyFloatValue("point1z");
                point2x = object->GetPropertyFloatValue("point2x");
                point2y = object->GetPropertyFloatValue("point2y");
                point2z = object->GetPropertyFloatValue("point2z");

                double dist = sqrt(pow(point2x - point1x, 2) +
                                   pow(point2y - point1y, 2) +
                                   pow(point2z - point1z, 2));
                std::vector<double> point1Vec = {point1x, point1y, point1z};
                std::vector<double> point2Vec = {point2x, point2y, point2z};

                auto color = QColor(43, 0, 255);

                if (m_measure_id.has_value())
                {
                    m_render->pluginManage->RemovePlugin(m_measure_id.value());
                }

                m_measure_id = m_render->pluginManage->AddPluginFromType(AMCAXRender::PluginType::kArrowAnnocation);
                auto att = m_render->pluginManage->GetProperty<AMCAXRender::ArrowAnnocationProp>(m_measure_id.value());

                att->SetPointParameter({point1Vec[0], point1Vec[1], point1Vec[2]}, {point2Vec[0], point2Vec[1], point2Vec[2]});

                att->SetTopRender(true);
                att->SetPointSize(10);
                att->SetLabel((QString::number(dist, 'f', 4) + "mm").toStdWString());
                att->SetFontSize(16);
                att->SetLightOn(false);
                att->SetColor({color.redF(), color.greenF(), color.blueF()});

                m_render->pluginManage->SetProperty(m_measure_id.value(), att);
            }
            else
            {
                if (m_measure_id.has_value())
                {
                    m_render->pluginManage->RemovePlugin(m_measure_id.value());
                }
            }
            GetDocument()->GetActiveView()->OnUpdate();
        }
    }

    void ViewProviderRenderDistance::FinishRestore()
    {
        ViewProviderDocumentObjectTopoShape::FinishRestore();
        UpdateData(&Visibility);
    }
    void ViewProviderRenderDistance::DeleteFromView()
    {
        if (!m_measure_id.has_value())
        {
            return;
        }
        m_render->pluginManage->RemovePlugin(m_measure_id.value());
        m_measure_id->clear();
        GetDocument()->GetActiveView()->OnUpdate();
    }

} // namespace Dev
