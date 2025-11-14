#include "ViewProviderBox.h"
#include <App/Application.h>
#include <App/Document.h>
#include <App/Properties/PropertyVector.h>
#include <Gui/Document.h>
#include <App/DocumentObjectTopoShape.h>
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>
#include <Gui/BoxDialog.h>
#include <Gui/MainWindow.h>
#include <Base/Object/BoxObject.h>
#include <modeling/MakeBox.hpp>

PFC_TYPESYSTEM_IMPL(Dev::ViewProviderBox, gui::ViewProviderDocumentObjectTopoShape)

namespace Dev
{

    ViewProviderBox::ViewProviderBox()
        : ViewProviderDocumentObjectTopoShape()
    {
    }

    ViewProviderBox::~ViewProviderBox()
    {
    }

    QWidget *ViewProviderBox::GetTaskView() const
    {
        auto object = GetObject<BoxObject>();
        auto dialog = new BoxDialog(object, gui::GetMainWindow());
        return dialog;
    }

} // namespace Dev
