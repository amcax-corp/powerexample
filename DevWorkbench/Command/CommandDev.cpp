#include "CommandDev.h"
#include <App/Color.h>
#include <Gui/Command/Command.h>
#include <QFileDialog>
#include <Gui/MainWindow.h>
#include <Gui/MessageWindow.h>
#include <Gui/Command/Action.h>
#include <Gui/Application.h>
#include <App/Properties/PropertyFloat.h>
#include <App/Application.h>
#include <Gui/Selection/Selection.h>
#include <App/Document.h>
#include <fstream>
#include <iostream>
#include <occtio/OCCTTool.hpp>
#include <step/STEPStyledProduct.hpp>
#include <step/STEPStyledReader.hpp>
#include <step/STEPTool.hpp>
#include <step/STEPWriter.hpp>
#include <step/StepReader.hpp>
#include <step/StepWriter.hpp>
#include <topology/TopoBuilder.hpp>
#include <topology/TopoCompound.hpp>
#include <topology/TopoExplorer.hpp>
#include <topology/TopoShape.hpp>
#include <Base/Tools.h>
#include <App/DocumentObjectTopoShape.h>
#include <Base/DevSetup.h>
#include <Base/Object/CurvesLoftObject.h>
#include <Gui/Document.h>
#include <Gui/ViewProvider/ViewProviderDocumentObjectTopoShape.h>
#include <App/DocumentObjectTopoShape.h>
#include <Gui/BoxDialog.h>
#include <Gui/CurvesLoftDialog.h>
#include <Gui/RenderDistanceDialog.h>
#include <Gui/ViewProvider/ViewProviderDocumentObject.h>
#include <Base/Utils.hpp>

namespace Dev
{

    //===========================================================================
    // Dev_Import
    //===========================================================================

    DEF_STD_CMD_A(DevImport)

    DevImport::DevImport()
        : Command("Dev_Import")
    {
        m_group = QT_TR_NOOP("Dev");
        m_menuText = QT_TR_NOOP("导入");
        m_toolTipText = QT_TR_NOOP("导入");
        m_whatsThis = "导入";
        m_statusTip = QT_TR_NOOP("导入");
        m_pixmap = ":icon/file/import-part.png";
        m_type = 0;
    }

    void DevImport::Activated(int iMsg)
    {
        Q_UNUSED(iMsg);
        // LOGGING_INFO("Dev_Import Activated");
        try
        {
            auto doc = app::GetApplication().GetActiveDocument();
            if (!doc)
            {
                LOGGING_ERROR("ActiveDocument is null");
                return;
            }
            QStringList fileList = QFileDialog::getOpenFileNames(gui::GetMainWindow(), QObject::tr("Import file"), ".", "all (*.brep *.step *.stp *Step *Stp);;STEP(*.step *.stp *Step *Stp);;BREP(*.brep)");
            if (!fileList.isEmpty())
            {
                app::OpenCommand(QObject::tr("导入").toStdString());
                for (const QString &filepath : fileList)
                {
                    QFileInfo fileInfo(filepath);

                    if (fileInfo.exists() && fileInfo.isFile())
                    {
                        std::filesystem::path std_path = std::filesystem::path(filepath.toStdWString());
                        std::ifstream ifs(std_path);
                        AMCAX::TopoShape shape;

                        QString suffix = fileInfo.suffix().toLower();
                        if (suffix == "brep")
                        {
                            if (!AMCAX::OCCTIO::OCCTTool::Read(shape, ifs))
                            {
                                continue;
                            }
                            std::string name = QString::fromStdWString(std_path.stem().wstring()).toUtf8().toStdString();
                            auto base_object = Dev::DevSetup::GetCurDevSetup()->AddPart(name);
                            auto object = static_cast<app::DocumentObjectTopoShape *>(base_object);
                            object->Shape.SetValue(shape);
                        }
                        else if (suffix == "step" || suffix == "stp")
                        {
                            AMCAX::STEP::STEPStyledReader reader(ifs);
                            if (!reader.Read())
                                continue;

                            auto ds = reader.GetProducts();
                            AMCAX::STEP::STEPTool::FlattenInplace(ds);

                            for (auto const &shape_data : ds)
                            {
                                if (shape_data->ShapesSize() > 0)
                                {
                                    // 获取类型
                                    auto &represent = shape_data->ShapeRepresentations().front();
                                    bool isWireFrame = (represent == AMCAX::STEP::ShapeRepresentationType::GEOMETRICALLY_BOUNDED_WIREFRAME_SHAPE_REPRESENTATION);
                                    std::string name = base::Tools::DecodeEncodedUnicode(shape_data->ProductName());
                                    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
                                    auto shape = shape_data->Shapes().front();
                                    auto shape_type = shape.Type();
                                    if (shape_type == AMCAX::ShapeType::Compound && !isWireFrame)
                                    {
                                        int i = 0;
                                        for (auto iter = AMCAX::TopoIterator(shape); iter.More(); iter.Next())
                                        {
                                            auto sub_shape = iter.Value();
                                            app::DocumentObjectTopoShape *object = DevSetup::GetCurDevSetup()->AddPart(name + "_" + std::to_string(i++))->SafeDownCast<app::DocumentObjectTopoShape>();
                                            object->Shape.SetValue(sub_shape);
                                            gui::ViewProviderDocumentObjectTopoShape *object_view_provider = nullptr;
                                            auto view_provider = gui::GetGuiApplication()->GetViewProvider(object);
                                            if (view_provider != nullptr)
                                            {
                                                object_view_provider = view_provider->SafeDownCast<gui::ViewProviderDocumentObjectTopoShape>();
                                            }

                                            auto &pcs = shape_data->PropertyAt(0);
                                            {
                                                auto it = std::find_if(pcs.begin(), pcs.end(), [&](const auto &pr)
                                                                       { return pr.first.IsSame(sub_shape); });
                                                if (it != pcs.end())
                                                {
                                                    auto &prop = it->second;
                                                    auto shapestyle = prop.GetShapeStyle();
                                                    if (shapestyle.SurfaceStyleHasValue())
                                                    {
                                                        auto surfacestyle = shapestyle.GetColor();
                                                        if (surfacestyle.IsValidRGB())
                                                        {
                                                            object->SolidColor.SetValue(app::Color(surfacestyle.R(), surfacestyle.G(), surfacestyle.B(), surfacestyle.A()));
                                                        }
                                                    }
                                                }
                                            }
                                            std::vector<std::pair<AMCAX::TopoShape, app::Color>> colors;
                                            std::map<std::string, std::string> face_names;
                                            std::map<std::string, double> face_opacities;

                                            AMCAX::IndexSet<AMCAX::TopoShape> shapeFaces_;
                                            AMCAX::TopoExplorerTool::MapShapes(sub_shape, AMCAX::ShapeType::Face, shapeFaces_);
                                            for (int j = 0; j < shapeFaces_.size(); ++j)
                                            {
                                                const AMCAX::TopoFace &sub_face = static_cast<const AMCAX::TopoFace &>(shapeFaces_[j]);
                                                auto it = std::find_if(pcs.begin(), pcs.end(), [&](const auto &pr)
                                                                       { return pr.first.IsSame(sub_face); });
                                                if (it != pcs.end())
                                                {
                                                    if (it->first.Type() == AMCAX::ShapeType::Face)
                                                    {
                                                        std::string face_id;
                                                        try
                                                        {
                                                            auto shape_full_name = object->GetSubShapeID(it->first);
                                                            face_id = Utils::GetSubNameByFullName(shape_full_name);
                                                        }
                                                        catch (...)
                                                        {
                                                            continue;
                                                        }

                                                        auto &prop = it->second;
                                                        auto shapestyle = prop.GetShapeStyle();
                                                        if (shapestyle.SurfaceStyleHasValue())
                                                        {
                                                            auto surfacestyle = shapestyle.GetColor();
                                                            if (surfacestyle.IsValidRGB())
                                                            {
                                                                colors.emplace_back(it->first, app::Color(surfacestyle.R(), surfacestyle.G(), surfacestyle.B(), surfacestyle.A()));
                                                                if (!face_id.empty())
                                                                    face_opacities[face_id] = surfacestyle.A();
                                                            }
                                                        }
                                                        if (prop.NameHasValue())
                                                        {
                                                            if (!face_id.empty())
                                                                face_names[face_id] = prop.Name();
                                                        }
                                                    }
                                                }
                                            }

                                            object->SetFaceColors(colors);
                                            object->SetFaceNames(face_names);
                                            if (object_view_provider != nullptr)
                                                object_view_provider->SetFaceOpacities(face_opacities);
                                        }
                                    }
                                    else
                                    {
                                        app::DocumentObjectTopoShape *object = DevSetup::GetCurDevSetup()->AddPart(name, isWireFrame)->SafeDownCast<app::DocumentObjectTopoShape>();
                                        gui::ViewProviderDocumentObjectTopoShape *object_view_provider = nullptr;
                                        auto view_provider = gui::GetGuiApplication()->GetViewProvider(object);
                                        if (view_provider != nullptr)
                                        {
                                            object_view_provider = view_provider->SafeDownCast<gui::ViewProviderDocumentObjectTopoShape>();
                                        }
                                        object->Shape.SetValue(shape);

                                        AMCAX::IndexSet<AMCAX::TopoShape> shapeFaces_;
                                        AMCAX::TopoExplorerTool::MapShapes(shape, AMCAX::ShapeType::Face, shapeFaces_);
                                        std::vector<std::pair<AMCAX::TopoShape, app::Color>> colors;
                                        std::map<std::string, std::string> face_names;
                                        std::map<std::string, double> face_opacities;
                                        auto &pcs = shape_data->PropertyAt(0);
                                        {
                                            auto it = std::find_if(pcs.begin(), pcs.end(), [&](const auto &pr)
                                                                   { return pr.first.IsSame(shape); });
                                            if (it != pcs.end())
                                            {
                                                auto &prop = it->second;
                                                auto shapestyle = prop.GetShapeStyle();
                                                if (shapestyle.SurfaceStyleHasValue())
                                                {
                                                    auto surfacestyle = shapestyle.GetColor();
                                                    if (surfacestyle.IsValidRGB())
                                                    {
                                                        object->SolidColor.SetValue(app::Color(surfacestyle.R(), surfacestyle.G(), surfacestyle.B(), surfacestyle.A()));
                                                    }
                                                }
                                            }
                                        }
                                        for (auto &&[pcs_shape, pcs_prop] : pcs)
                                        {
                                            if (pcs_shape.Type() == AMCAX::ShapeType::Face)
                                            {
                                                std::string face_id;
                                                try
                                                {
                                                    auto shape_full_name = object->GetSubShapeID(pcs_shape);
                                                    face_id = Utils::GetSubNameByFullName(shape_full_name);
                                                }
                                                catch (...)
                                                {
                                                    continue;
                                                }

                                                auto shapestyle = pcs_prop.GetShapeStyle();
                                                if (shapestyle.SurfaceStyleHasValue())
                                                {
                                                    auto surfacestyle = shapestyle.GetColor();
                                                    if (surfacestyle.IsValidRGB())
                                                    {
                                                        colors.emplace_back(pcs_shape, app::Color(surfacestyle.R(), surfacestyle.G(), surfacestyle.B(), surfacestyle.A()));
                                                        if (!face_id.empty())
                                                            face_opacities[face_id] = surfacestyle.A();
                                                    }
                                                }
                                                if (pcs_shape.Type() == AMCAX::ShapeType::Face && pcs_prop.NameHasValue())
                                                {
                                                    if (!face_id.empty())
                                                        face_names[face_id] = pcs_prop.Name();
                                                }
                                            }
                                        }
                                        object->SetFaceColors(colors);
                                        object->SetFaceNames(face_names);
                                        if (object_view_provider != nullptr)
                                            object_view_provider->SetFaceOpacities(face_opacities);
                                    }
                                }
                            }
                        }
                    }
                }
                app::CommitCommand();
                gui::GetMainWindow()->ActiveWindow()->OnMessage("ViewAll");
            }
        }
        catch (...)
        {
            LOGGING_ERROR("Import Command Error.");
        }
    }

    bool DevImport::IsActive()
    {
        return app::GetApplication().GetActiveDocument();
        // return true;
    }

    DEF_STD_CMD_A(DevExport)

    DevExport::DevExport()
        : Command("Dev_Export")
    {
        m_group = QT_TR_NOOP("File");
        m_menuText = QT_TR_NOOP("导出");
        m_whatsThis = "Export";
        m_statusTip = QT_TR_NOOP("导出");
        m_pixmap = ":icon/file/export.png";
        m_type = 0;
        m_toolTipText = QT_TR_NOOP(GenTipWithTitleAndImage(m_pixmap, m_statusTip, QT_TR_NOOP("将选择的部件导出为模型文件")).toStdString());
    }

    void DevExport::Activated(int i)
    {
        try
        {
            QString fileName = QFileDialog::getSaveFileName(gui::GetMainWindow(), QObject::tr("导出文件"), "", "STEP(*.step *.stp);;BREP(*.brep)");
            auto doc = app::GetApplication().GetActiveDocument();
            if (!doc)
            {
                LOGGING_ERROR("ActiveDocument is null");
                return;
            }
            auto object_list = gui::Selection().GetObjectsOfType<app::DocumentObjectTopoShape>(doc->GetName());
            if (!object_list.size())
            {
                LOGGING_ERROR("There are no Selected DocumentObject of Type ShapeDocumentObject ");
                return;
            }

            AMCAX::TopoShape shape;
            if (object_list.size() > 1)
            {
                AMCAX::TopoBuilder builder;
                AMCAX::TopoCompound compound;
                builder.MakeCompound(compound);
                for (auto object : object_list)
                {
                    AMCAX::TopoShape sub_shape = object->Shape.GetValue();
                    builder.Add(compound, sub_shape);
                }
                shape = compound;
            }
            else if (object_list.size() == 1)
            {
                shape = object_list.front()->Shape.GetValue();
            }

            if (fileName.endsWith(".step") || fileName.endsWith(".stp"))
            {
                std::ofstream ofs(std::filesystem::u8path(fileName.toStdString()));
                AMCAX::STEP::STEPTool::Write(shape, ofs);
            }
            else if (fileName.endsWith(".brep"))
            {
                std::ofstream ofs(std::filesystem::u8path(fileName.toStdString()));
                AMCAX::OCCTIO::OCCTTool::Write(shape, ofs, false);
            }
        }
        catch (...)
        {
            LOGGING_ERROR("Export Command Error.");
        }
    }

    bool DevExport::IsActive()
    {
        if (!gui::GetGuiApplication()->ActiveDocument())
            return false;
        if (!gui::Selection().HasSelection())
            return false;
        if (!gui::Selection().GetObjectsOfType<app::DocumentObjectTopoShape>().size())
            return false;

        return true;
    }

    //===========================================================================
    // 创建创建立方体 CreateBox
    //===========================================================================

    DEF_STD_CMD_A(CreateBox)

    CreateBox::CreateBox()
        : Command("Dev_CreateBox")
    {
        m_group = QT_TR_NOOP("Dev");
        m_menuText = QT_TR_NOOP("创建立方体");
        m_toolTipText = QT_TR_NOOP("创建立方体");
        m_whatsThis = "创建立方体";
        m_statusTip = QT_TR_NOOP("创建立方体");
        m_pixmap = ":icon/toolbar/bounding-cube.png";
        m_type = 0;
    }

    void CreateBox::Activated(int iMsg)
    {
        Q_UNUSED(iMsg);
        auto dialog = new BoxDialog(nullptr, gui::GetMainWindow());
        dialog->show();
    }

    bool CreateBox::IsActive()
    {
        return true;
    }

    //===========================================================================
    // 曲线放样 CreateCurvesLoft
    //===========================================================================

    DEF_STD_CMD_A(CreateCurvesLoft)

    CreateCurvesLoft::CreateCurvesLoft()
        : Command("Dev_CreateCurvesLoft")
    {
        m_group = QT_TR_NOOP("Dev");
        m_menuText = QT_TR_NOOP("曲线放样");
        m_toolTipText = QT_TR_NOOP("曲线放样");
        m_whatsThis = "曲线放样";
        m_statusTip = QT_TR_NOOP("曲线放样");
        m_pixmap = ":icon/toolbar/loft.png";
        m_type = 0;
    }

    void CreateCurvesLoft::Activated(int iMsg)
    {
        Q_UNUSED(iMsg);
        auto dialog = new CurvesLoftDialog(nullptr, gui::GetMainWindow());
        dialog->show();
    }

    bool CreateCurvesLoft::IsActive()
    {
        return true;
    }

    //===========================================================================
    // 距离渲染
    //===========================================================================

    DEF_STD_CMD_A(CreateRenderDistance)

    CreateRenderDistance::CreateRenderDistance()
        : Command("Dev_CreateRenderDistance")
    {
        m_group = QT_TR_NOOP("Dev");
        m_menuText = QT_TR_NOOP("距离渲染");
        m_toolTipText = QT_TR_NOOP("距离渲染");
        m_whatsThis = "距离渲染";
        m_statusTip = QT_TR_NOOP("距离渲染");
        m_pixmap = ":icon/toolbar/loft.png";
        m_type = 0;
    }

    void CreateRenderDistance::Activated(int iMsg)
    {
        Q_UNUSED(iMsg);
        auto dialog = new RenderDistanceDialog(nullptr, gui::GetMainWindow());
        dialog->show();
    }

    bool CreateRenderDistance::IsActive()
    {
        return true;
    }

    //===========================================================================
    // Dev_EditDisplay
    //===========================================================================

    DEF_STD_CMD(EditDisplay)

    EditDisplay::EditDisplay()
        : Command("Dev_EditDisplay")
    {
        m_group = QT_TR_NOOP("Dev");
        m_menuText = QT_TR_NOOP("编辑对象");
        m_toolTipText = QT_TR_NOOP("编辑对象");
        m_whatsThis = "编辑对象";
        m_statusTip = QT_TR_NOOP("编辑对象");
        m_pixmap = ":icon/file/open.png";
        m_type = 0;
    }

    void EditDisplay::Activated(int iMsg)
    {
        Q_UNUSED(iMsg);
        auto doc = app::GetApplication().GetActiveDocument();
        auto selection = gui::Selection().GetObjectsOfType<DevObject>(doc->GetName());
        if (!selection.size())
            return;

        if (auto object = selection[0])
        {
            auto view = gui::GetGuiApplication()->ActiveDocument()->GetViewProvider(object);
            if (view)
            {
                if (auto dialog = view->GetTaskView())
                {
                    dialog->show();
                }
            }
        }
    }

    void CreateDevWorkbenchCommands()
    {
        gui::CommandManager &commandMgr = gui::CommandManager::GetInstance();

        commandMgr.AddCommand(new DevImport());
        commandMgr.AddCommand(new DevExport());
        commandMgr.AddCommand(new EditDisplay());
        commandMgr.AddCommand(new CreateBox());
        commandMgr.AddCommand(new CreateCurvesLoft());
        commandMgr.AddCommand(new CreateRenderDistance());
    }
} // namespace Dev
