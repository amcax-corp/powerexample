#include <occtio/OCCTTool.hpp>
#include "BoxDialog.h"
#include "ui_BoxDialog.h"
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
#include <App/Application.h>
namespace Dev{
BoxDialog::BoxDialog(Dev::BoxObject *obj, QWidget *parent)
    : BlockDialog(parent), m_object(obj), ui(new Ui::BoxDialog)
{
    std::string open_commend_name;
    ui->setupUi(this);
    if (m_object == nullptr)
    {
        app::OpenCommand(tr("创建 ").toStdString() + "box");
        m_object = Dev::DevSetup::GetCurDevSetup()->AddBoxObject("box");
    }
    else
    {
        app::OpenCommand(tr("编辑 ").toStdString() + std::string(m_object->Label.GetValue()));
    }
    SetSelectionPointSize(16);
    ui->blockspecifypoint->SetLabelText("指定原点");
    ConnectPropertyData(ui->blockspecifypoint, "Position");
    ConnectPropertyData(ui->Length, "Length");
    ConnectPropertyData(ui->Width, "Width");
    ConnectPropertyData(ui->Height, "Height");
    UpdataBoxTopoShape();
    ui->blockspecifypoint->SetFocused(true);
}

BoxDialog::~BoxDialog()
{
    delete ui;
    SetSelectionPointSize(4);
}

bool BoxDialog::OnConfirmed()
{
    app::CommitCommand();
    return true;
}

bool BoxDialog::OnApplied()
{
    return true;
}

void BoxDialog::OnResetted() {}

void BoxDialog::OnCanceled()
{
    app::AbortCommand();
}

void BoxDialog::ConnectPropertyData(BlockBase *block, std::string property)
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
    else if (auto v_val = qobject_cast<BlockSpecifyPoint *>(block))
    {
        auto p_point = m_object->GetPropertyVector(property)->GetValue();
        v_val->SetPoint(QVector3D(p_point.x, p_point.y, p_point.z));
        connect(v_val, &BlockSpecifyPoint::SignalGetPoint, this, [this, block, property](const QVector3D &point)
                {
            m_object->GetPropertyVector(property)->SetValue(base::Vector3d(point.x(), point.y(), point.z()));
            OnValueChanged(block, QString::fromStdString(property)); });
        return;
    }
}

void BoxDialog::OnValueChanged(BlockBase *block, QString property)
{
    if (qobject_cast<BlockDouble *>(block))
    {
        UpdataBoxTopoShape();
    }
    if (qobject_cast<BlockSpecifyPoint *>(block))
    {
        UpdataBoxTopoShape();
    }
}
void BoxDialog::UpdataBoxTopoShape()
{
    auto l = m_object->GetPropertyFloatValue("Length");
    auto w = m_object->GetPropertyFloatValue("Width");
    auto h = m_object->GetPropertyFloatValue("Height");
    auto p_p = m_object->GetPropertyVector("Position")->GetValue();
    AMCAX::Point3 position(p_p.x, p_p.y, p_p.z);
    auto shape = AMCAX::MakeBox(position, l, w, h).Shape();

    auto loc = shape.Location();
    m_object->Shape.SetValue(shape);
}

void BoxDialog::SetSelectionPointSize(int size)
{
    auto active_window = gui::GetMainWindow()->ActiveWindow();
    auto view = dynamic_cast<gui::View3DInventor *>(active_window)->GetViewer();
    view->SetSelectionPointSize(size);
}
}