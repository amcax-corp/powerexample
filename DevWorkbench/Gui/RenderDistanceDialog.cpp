#include <occtio/OCCTTool.hpp>
#include "RenderDistanceDialog.h"
#include "ui_RenderDistanceDialog.h"
#include <App/Properties/PropertyInteger.h>
#include <App/Properties/PropertyVector.h>
#include <Base/DevSetup.h>
#include <App/Properties/PropertyFloat.h>
#include <modeling/MakeBox.hpp>
#include <App/Properties/PropertyVector.h>
#include <Gui/MainWindow.h>
#include <Gui/View/View3DInventor.h>
#include <Gui/View/View3DInventorViewer.h>
#include <Logging/Logging.h>
#include <Base/Object/RenderDistanceObject.h>
#include <App/Application.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/View/View3DInventor.h>
#include <Gui/View/View.h>
#include <Gui/ViewProvider/ViewProvider.h>
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>
#ifdef GetObject
#undef GetObject
#endif
namespace Dev
{
RenderDistanceDialog::RenderDistanceDialog(Dev::RenderDistanceObject *obj, QWidget *parent)
    : BlockDialog(parent), m_object(obj), ui(new Ui::RenderDistanceDialog)
{

    ui->setupUi(this);
    if (m_object == nullptr)
    {
        app::OpenCommand(tr("创建 ").toStdString() + "render_distance");
        m_object = Dev::DevSetup::GetCurDevSetup()->AddRenderDistanceObject("render_distance");
    }
    else
    {
        app::OpenCommand(tr("编辑 ").toStdString() + std::string(m_object->Label.GetValue()));
    }
    if (auto view = gui::GetGuiApplication()->ActiveDocument()->GetView())
    {
        m_view = view->SafeDownCast<gui::View3DInventor>();
    }
    ConnectPropertyData(ui->point1x, "point1x");
    ConnectPropertyData(ui->point1y, "point1y");
    ConnectPropertyData(ui->point1z, "point1z");
    ConnectPropertyData(ui->point2x, "point2x");
    ConnectPropertyData(ui->point2y, "point2y");
    ConnectPropertyData(ui->point2z, "point2z");
    if (auto view_provider = gui::GetGuiApplication()->GetViewProvider(m_object))
    {
        ui->Preview->SetValue(view_provider->SafeDownCast<gui::ViewProviderDocumentObjectTopoShape>()->Visibility.GetValue());
    }
    connect(ui->Preview, &BlockToggle::SignalCheckStateChanged, this, [this](bool value)
            {
                if (auto view_provider = gui::GetGuiApplication()->GetViewProvider(m_object))
                {
                    view_provider->SafeDownCast<gui::ViewProviderDocumentObjectTopoShape>()->Visibility.SetValue(value);
                    Dev::DevSetup::GetCurDevSetup()->UpdatePartNavigator();
                }
            });
}

RenderDistanceDialog::~RenderDistanceDialog()
{
    delete ui;
    SetSelectionPointSize(4);
    if (auto view = gui::GetGuiApplication()->GetViewProvider(m_object))
    {
        view->SafeDownCast<gui::ViewProviderDocumentObjectTopoShape>()->Visibility.SetValue(true);
    }
}

bool RenderDistanceDialog::OnConfirmed()
{
    app::CommitCommand();
    return true;
}

bool RenderDistanceDialog::OnApplied()
{
    return true;
}

void RenderDistanceDialog::OnResetted() {}

void RenderDistanceDialog::OnCanceled()
{
    app::AbortCommand();
}

void RenderDistanceDialog::SetSelectionPointSize(int size)
{
    m_view->GetViewer()->SetSelectionPointSize(size);
}
void RenderDistanceDialog::ConnectPropertyData(BlockBase *block, std::string property)
{

    if (auto d_val = qobject_cast<BlockDouble *>(block))
    {
        d_val->SetValue(m_object->GetPropertyFloat(property)->GetValue());
        connect(d_val, &BlockDouble::SignalDoubleValueChange, this, [this, block, property](double value)
                {
            m_object->GetPropertyFloat(property)->SetValue(value);
            OnValueChanged(block, QString::fromStdString(property)); });
        return;
    }
}
void RenderDistanceDialog::OnValueChanged(BlockBase *block, QString property)
{
}
}