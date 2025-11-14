#include "PartCollection.h"
#include "DevSetup.h"
#include <App/Application.h>
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <Base/Tools.h>

namespace Dev {

PartCollection::PartCollection(DevSetup* owner)
  : m_owner(owner)
{
}

PartCollection::~PartCollection()
{
    Clear();
}

void PartCollection::Clear()
{
    m_parts.clear();
    if (connectNewObject.connected())
        connectNewObject.disconnect();
    if (connectDeletedObject.connected())
        connectDeletedObject.disconnect();
    if (connectBeforeObjectPropertyChanged.connected())
        connectBeforeObjectPropertyChanged.disconnect();
    if (connectObjectPropertyChanged.connected())
        connectObjectPropertyChanged.disconnect();
}

DevSetup* PartCollection::GetSetup()
{
    return m_owner;
}

std::vector<app::DocumentObjectTopoShape*> PartCollection::PartList()
{
    return m_parts;
}

bool PartCollection::IsLabelUnique(std::string_view label)
{
    for (auto part : m_parts)
        if (part->Label.GetValue() == label)
            return false;
    return true;
}

std::string PartCollection::GetUniqueName(std::string_view name)
{
    if (name.empty())
        return std::string();

    if (IsLabelUnique(name))
    {
        return std::string(name);
    }
    else
    {
        std::string cleanName = base::Tools::GetIdentifierWithChinese(name);
        std::vector<std::string_view> names;
        names.reserve(m_parts.size());
        for (auto group : m_parts)
        {
            names.push_back(group->Label.GetValue());
        }
        return base::Tools::GetUniqueName(cleanName + "_", names, 1);
    }
}

void PartCollection::Setup(app::Document* doc, std::vector<app::DocumentObjectTopoShape*> parts)
{
    Clear();
    m_parts = parts;

    connectNewObject = doc->SignalNewObject.connect(std::bind(&Dev::PartCollection::SlotNewObject, this, std::placeholders::_1));
    connectDeletedObject = doc->SignalDeletingObject.connect(std::bind(&Dev::PartCollection::SlotObjectDeleted, this, std::placeholders::_1));
    connectBeforeObjectPropertyChanged = doc->SignalBeforeObjectPropertyChanging.connect(std::bind(&Dev::PartCollection::SlotObjectBeforePropertyChanged, this, std::placeholders::_1, std::placeholders::_2));
    connectObjectPropertyChanged = doc->SignalObjectPropertyChanged.connect(std::bind(&Dev::PartCollection::SlotObjectPropertyChanged, this, std::placeholders::_1, std::placeholders::_2));
}

app::DocumentObjectTopoShape* PartCollection::FindObject(std::string_view name)
{
    for (auto part : m_parts)
    {
        if (part->GetNameInDocument() == name)
        {
            return part;
        }
    }
    return nullptr;
}

void PartCollection::SetSortList(const std::map<std::string, std::vector<std::string>>& map)
{
    sort_list = map;
}

std::map<std::string, std::vector<std::string>>& PartCollection::GetSortList()
{
    return sort_list;
}

void PartCollection::RemovePart(std::string_view name)
{
    auto doc = app::GetApplication().GetActiveDocument();
    if (doc)
    {
        doc->RemoveObject(name);
    }
}

void PartCollection::RemovePart(app::DocumentObjectTopoShape* part)
{
    if (!part)
        return;
    RemovePart(part->GetNameInDocument());
}

void PartCollection::SlotNewObject(const app::DocumentObject& obj)
{
    auto type = obj.GetClassTypePolymorphic();
    if (!type.IsSubTypeOf(app::DocumentObjectTopoShape::GetClassType()))
        return;

    app::DocumentObject* part_obj = const_cast<app::DocumentObject*>(&obj);
    auto part = dynamic_cast<app::DocumentObjectTopoShape*>(part_obj);
    m_parts.emplace_back(part);

    SignalNewObject(obj);
}

void PartCollection::SlotObjectDeleted(const app::DocumentObject& obj)
{
    auto type = obj.GetClassTypePolymorphic();
    if (!type.IsSubTypeOf(app::DocumentObjectTopoShape::GetClassType()))
        return;

    app::DocumentObject* part_obj = const_cast<app::DocumentObject*>(&obj);
    auto part = dynamic_cast<app::DocumentObjectTopoShape*>(part_obj);
    m_parts.erase(std::remove(m_parts.begin(), m_parts.end(), part), m_parts.end());

    SignalDeletedObject(obj);
}

void PartCollection::SlotObjectBeforePropertyChanged(const app::DocumentObject& obj, const app::Property& prop)
{
    auto type = obj.GetClassTypePolymorphic();
    if (!type.IsSubTypeOf(app::DocumentObjectTopoShape::GetClassType()))
        return;
}

void PartCollection::SlotObjectPropertyChanged(const app::DocumentObject& obj, const app::Property& prop)
{
    auto type = obj.GetClassTypePolymorphic();
    if (!type.IsSubTypeOf(app::DocumentObjectTopoShape::GetClassType()))
        return;

    auto doc = app::GetApplication().GetActiveDocument();
    if (doc->TestStatus(app::Document::Status::RESTORING))
        return;

    SignalObjectPropertyChanged(obj, prop);
}

}  // namespace cam