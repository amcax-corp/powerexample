#include "ViewProviderCurvesLoft.h"
#include <App/Application.h>
#include <App/Document.h>
#include <App/Properties/PropertyVector.h>
#include <Gui/Document.h>
#include <App/DocumentObjectTopoShape.h>
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>
#include <Gui/CurvesLoftDialog.h>
#include <Gui/MainWindow.h>
#include <Base/Object/BoxObject.h>
#include <modeling/MakeBox.hpp>

PFC_TYPESYSTEM_IMPL(Dev::ViewProviderCurvesLoft, gui::ViewProviderDocumentObjectTopoShape)

namespace Dev
{

    ViewProviderCurvesLoft::ViewProviderCurvesLoft()
        : ViewProviderDocumentObjectTopoShape()
    {
    }

    ViewProviderCurvesLoft::~ViewProviderCurvesLoft()
    {
    }

    QWidget *ViewProviderCurvesLoft::GetTaskView() const
    {
        auto object = GetObject<CurvesLoftObject>();
        auto dialog = new CurvesLoftDialog(object, gui::GetMainWindow());
        return dialog;
    }

} // namespace Dev
