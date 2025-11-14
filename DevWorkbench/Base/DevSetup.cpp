#include "DevSetup.h"
#include "PartCollection.h"
#include <App/Application.h>
#include <App/Document.h>
#include <Base/Navigator/PartNavigator.h>
#include <Gui/MainWindow.h>
#include <Gui/Selection/Selection.h>
#include <Gui/View/MdiView.h>
#include <Base/Object/CurvesLoftObject.h>
#include <App/DocumentObjectWireframedMarker.h>

PFC_TYPESYSTEM_IMPL(Dev::DevSetup, app::DocumentObject)
namespace Dev
{

    DevSetup::DevSetup()
        : part_collection(nullptr)
    {
        gui::GetMainWindow()->ActiveWindow()->OnMessage("SingleChoice");
        Setup();
        app::GetApplication().SignalFinishRestoreDocument.connect(std::bind(&Dev::DevSetup::OnFinishRestoreDocument, this, std::placeholders::_1));
        app::GetApplication().SignalBeforeDeletingDocument.connect(std::bind(&Dev::DevSetup::OnBeforeDeletingDocument, this, std::placeholders::_1));
    }

    DevSetup::~DevSetup()
    {
        delete part_collection;
    }

    DevSetup *DevSetup::GetCurDevSetup()
    {
        auto doc = app::GetApplication().GetActiveDocument();
        if (!doc)
            return nullptr;
        auto obj = doc->GetObject(Dev_SETUP_NAME);
        if (!obj)
        {
            obj = static_cast<DevSetup *>(doc->AddObject(DevSetup::GetClassType().GetName(), Dev_SETUP_NAME));
        }
        return static_cast<DevSetup *>(obj);
    }

    template <typename T>
    std::vector<T *> DevSetup::GetObjects(app::Document *doc)
    {
        auto type = T::GetClassType();
        auto obj_list = doc->GetObjectsOfType(type);
        std::vector<T *> vector;
        vector.reserve(obj_list.size());
        for (auto &obj : obj_list)
        {
            vector.emplace_back(dynamic_cast<T *>(obj));
        }
        return vector;
    }

    PartCollection *DevSetup::DevPartCollection()
    {
        return part_collection;
    }

    app::DocumentObjectTopoShape *DevSetup::AddPart(std::string_view name, bool isWireframedMark)
    {
        if (isWireframedMark)
        {
            auto obj = new app::DocumentObjectWireframedMarker();
            auto unique_name = part_collection->GetUniqueName(name);
            obj->Label.SetValue(unique_name);
            GetDocument()->AddObject(std::unique_ptr<app::DocumentObjectWireframedMarker>(obj));
            return obj;
        }
        else
        {
            auto obj = new app::DocumentObjectTopoShape();
            auto unique_name = part_collection->GetUniqueName(name);
            obj->Label.SetValue(unique_name);
            GetDocument()->AddObject(std::unique_ptr<app::DocumentObjectTopoShape>(obj));
            return obj;
        }
    }

 BoxObject *DevSetup::AddBoxObject(std::string_view name)
    {
        auto obj = new BoxObject();
        auto unique_name = part_collection->GetUniqueName(name);
        obj->Label.SetValue(unique_name);
        GetDocument()->AddObject(std::unique_ptr<BoxObject>(obj));

        auto objname = obj->GetNameInDocument();//对象在文档中的名字
        auto temp= GetDocument()->GetObject(objname);//直接查找对象
       // std::printf("%d, %d,%s", (int)obj, (int)temp,objname.data());
        return obj;
    }

    RenderDistanceObject *DevSetup::AddRenderDistanceObject(std::string_view name)
    {
        auto obj = new RenderDistanceObject();
        auto unique_name = part_collection->GetUniqueName(name);
        obj->Label.SetValue(unique_name);
        GetDocument()->AddObject(std::unique_ptr<RenderDistanceObject>(obj));
        return obj;
    }

    CurvesLoftObject *DevSetup::AddCurvesLoft(std::string_view name)
    {
        auto obj = new CurvesLoftObject();
        auto unique_name = part_collection->GetUniqueName(name);
        obj->Label.SetValue(unique_name);
        GetDocument()->AddObject(std::unique_ptr<CurvesLoftObject>(obj));
        return obj;
    }

    PartNavigator *DevSetup::GetPartNavigator()
    {
        return dynamic_cast<PartNavigator *>(gui::GetMainWindow()->GetNavigator(0));
    }

    void DevSetup::UpdatePartNavigator()
    {
        GetPartNavigator()->UpdateNavigator();
    }

    void DevSetup::Setup()
    {
        if (!part_collection)
            part_collection = new PartCollection(this);

        auto doc = GetDocument();
        if (!doc)
            doc = app::GetApplication().GetActiveDocument();
        if (!doc)
            return;

        auto parts = GetObjects<app::DocumentObjectTopoShape>(doc);

        auto part_sort_list = part_collection->GetSortList();
        if (!part_sort_list.size())
        {
            part_sort_list["Root"] = {""};
            std::vector<std::string> vec;
            for (auto part : parts)
            {
                vec.push_back(std::string(part->GetNameInDocument()));
            }
            part_sort_list[""] = vec;
            part_collection->SetSortList(part_sort_list);
        }

        part_collection->Setup(doc, parts);
    }

    void DevSetup::Store(base::XMLWriter &writer, std::uint32_t version) const
    {
        writer.WriteAttributeBool("PartCollection", true);
        DevObject::Store(writer, version);

        {
            writer.WriteStartElement("NavSortList");
            writer.WriteAttributeInteger("Count", static_cast<std::uint32_t>(nav_sort_list.size()));
            for (auto &&[key, value] : nav_sort_list)
            {
                writer.WriteStartElement("Item");
                writer.WriteAttributeInteger("Key", key);
                writer.WriteStartElement("Value");
                writer.WriteAttributeUnsigned("Name_Count", static_cast<std::uint32_t>(value.size()));
                for (auto &&[name, vec] : value)
                {
                    writer.WriteStartElement("Item");
                    writer.WriteAttribute("Vec_Count", std::to_string(vec.size()));
                    writer.WriteAttribute("Key", name);
                    writer.WriteStartElement("Value");
                    for (auto it : vec)
                    {
                        writer.WriteStartElement("Item");
                        writer.WriteAttribute("Value", it);
                        writer.WriteEndElement("Item");
                    }
                    writer.WriteEndElement("Value");
                    writer.WriteEndElement("Item");
                }
                writer.WriteEndElement("Value");
                writer.WriteEndElement("Item");
            }
            writer.WriteEndElement("NavSortList");
        }

        {
            writer.WriteStartElement("PartSortList");
            auto part_sort_list = part_collection->GetSortList();
            writer.WriteAttributeUnsigned("Name_Count", static_cast<std::uint32_t>(part_sort_list.size()));
            for (auto &&[name, vec] : part_sort_list)
            {
                writer.WriteStartElement("Item");
                writer.WriteAttributeUnsigned("Vec_Count", static_cast<std::uint32_t>(vec.size()));
                writer.WriteAttribute("Key", name);
                writer.WriteStartElement("Value");
                for (auto it : vec)
                {
                    writer.WriteStartElement("Item");
                    writer.WriteAttribute("Value", it);
                    writer.WriteEndElement("Item");
                }
                writer.WriteEndElement("Value");
                writer.WriteEndElement("Item");
            }
            writer.WriteEndElement("PartSortList");
        }
    }

    void DevSetup::Restore(base::XMLReader &reader, std::uint32_t version)
    {
        bool isPartCollection = reader.HasAttribute("PartCollection");
        DevObject::Restore(reader, version);
        {
            reader.ReadElement("NavSortList");
            nav_sort_list.clear();
            std::uint32_t count = reader.GetAttributeAsUnsigned("Count");
            for (std::uint32_t i = 0; i < count; i++)
            {
                reader.ReadElement("Item");
                int key = reader.GetAttributeAsInteger("Key");
                reader.ReadElement("Value");
                std::map<std::string, std::vector<std::string>> values;
                std::uint32_t name_count = reader.GetAttributeAsUnsigned("Name_Count");
                for (std::uint32_t i = 0; i < name_count; ++i)
                {
                    reader.ReadElement("Item");
                    std::vector<std::string> vec;
                    std::uint32_t vec_count = reader.GetAttributeAsUnsigned("Vec_Count");
                    std::string name = reader.GetAttribute("Key");
                    reader.ReadElement("Value");
                    vec.resize(vec_count);
                    for (std::uint32_t j = 0; j < vec_count; j++)
                    {
                        reader.ReadElement("Item");
                        vec[j] = reader.GetAttribute("Value");
                        reader.ReadEndElement("Item");
                    }
                    reader.ReadEndElement("Value");
                    reader.ReadEndElement("Item");
                    values.emplace(name, vec);
                }
                reader.ReadEndElement("Value");
                reader.ReadEndElement("Item");
                nav_sort_list.emplace(key, values);
            }

            reader.ReadEndElement("NavSortList");
        }

        std::map<std::string, std::vector<std::string>> part_sort_list;
        if (isPartCollection)
        {
            reader.ReadElement("PartSortList");
            std::uint32_t name_count = reader.GetAttributeAsUnsigned("Name_Count");
            for (std::uint32_t i = 0; i < name_count; ++i)
            {
                reader.ReadElement("Item");
                std::vector<std::string> vec;
                std::uint32_t vec_count = reader.GetAttributeAsUnsigned("Vec_Count");
                std::string name = reader.GetAttribute("Key");
                reader.ReadElement("Value");
                vec.resize(vec_count);
                for (std::uint32_t j = 0; j < vec_count; j++)
                {
                    reader.ReadElement("Item");
                    vec[j] = reader.GetAttribute("Value");
                    reader.ReadEndElement("Item");
                }
                reader.ReadEndElement("Value");
                reader.ReadEndElement("Item");
                part_sort_list.emplace(name, vec);
            }
            reader.ReadEndElement("PartSortList");
        }
        part_collection->SetSortList(part_sort_list);
    }

    void DevSetup::SetNavSortList(int index, std::map<std::string, std::vector<std::string>> &map)
    {
        nav_sort_list[index] = map;
    }

    std::map<std::string, std::vector<std::string>> &DevSetup::GetNavSortList(int index)
    {
        return nav_sort_list[index];
    }

    void DevSetup::AddToSelection(DevObject *obj)
    {
        if (!obj)
            return;
        gui::Selection().ClearSelection();
        gui::Selection().AddSelection(obj->GetDocument()->GetName(), obj->GetNameInDocument());
    }

    void DevSetup::OnFinishRestoreDocument(const app::Document &doc)
    {
        if (&doc == GetDocument())
            Setup();
    }

    void DevSetup::OnBeforeDeletingDocument(const app::Document &doc)
    {
        // if (&doc == GetDocument())
        //     toolpath_mgr->CleanTool();
    }

} // namespace Dev