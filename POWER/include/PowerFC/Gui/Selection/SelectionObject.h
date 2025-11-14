

#ifndef GUI_SelectionObject_H
#define GUI_SelectionObject_H

#pragma once
#include <Base/BaseClass.h>
#include <string>
#include <set>
#include <Base/Vector3D.h>

namespace app {
class DocumentObject;
}

namespace gui {

class SelectionChanges;

/**
 * The Selection object class
 */
class PFC_GUI_API SelectionObject : public base::BaseClass
{
    PFC_TYPESYSTEM_DECL()

  public:
    SelectionObject();
    SelectionObject(const SelectionChanges& msg);
    explicit SelectionObject(const app::DocumentObject*);
    virtual ~SelectionObject();

    /// get the SubElement name of this SelectionObject
    inline const std::vector<std::string>& GetSubNames() const
    {
        return m_sub_names;
    }
    /// are there any SubNames selected
    bool HasSubNames() const
    {
        return m_sub_names.size() != 0;
    }
    /// get the name of the Document of this SelctionObject
    inline const std::string& GetDocName() const
    {
        return m_document_name;
    }
    /// get the name of the Document Object of this SelectionObject
    inline const std::string& GetFeatName() const
    {
        return m_feat_name;
    }

    inline std::string_view GetDocumentObjectName() const{
        return m_feat_name;
    }
    /// get the selection points
    inline const std::vector<base::Vector3d> GetPickedPoints() const
    {
        return m_sel_poses;
    }

    /// returns the selected DocumentObject or NULL if the object is already deleted
    const app::DocumentObject* GetDocumentObject() const;
    /// returns the selected DocumentObject or NULL if the object is already deleted
    app::DocumentObject* GetDocumentObject();

    /// check the selected object is a special type or derived of
    bool IsObjectTypeOf(const base::Type& typeId) const;

    friend class SelectionSingleton;

  protected:
    std::vector<std::string> m_sub_names;
    std::string m_document_name;
    std::string m_feat_name;
    std::vector<base::Vector3d> m_sel_poses;

  private:
    /// to make sure no duplicates of subnames
    std::set<std::string> m_sub_name_set;
};

}  // namespace gui

#endif  // GUI_SelectionObject_H
