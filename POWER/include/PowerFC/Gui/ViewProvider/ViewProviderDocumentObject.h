#pragma once

#include "App/Properties/PropertyBool.h"
#include "App/Properties/PropertyEnumeration.h"
#include "App/Properties/PropertyFloat.h"
#include "App/Property.h"
#include "ViewProvider.h"

namespace app {
class DocumentObject;
class Property;
}  // namespace app

namespace gui {
class MdiView;
class Document;

class PFC_GUI_API ViewProviderDocumentObject : public ViewProvider
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    ViewProviderDocumentObject();
    ~ViewProviderDocumentObject() override;

    // 使用app::DocumentObject::Visibility代替
    app::PropertyBool Visibility;
    app::PropertyBool ShowInTree;
    app::PropertyBool ExpandInTree;

    // app::PropertyEnumeration OnTopWhenSelected;
    // app::PropertyEnumeration SelectionStyle;

    virtual std::size_t GetEstimatedSize() const override;

    virtual void Attach(app::DocumentObject* pcObject);
    virtual void Reattach(app::DocumentObject*);
    // void Update(const app::Property*) override;
    /// Get the object of this ViewProvider object
    app::DocumentObject* GetDocumentObject() const
    {
        return m_app_doc_object;
    }
    /// Get the object of this ViewProvider object as specified type
    template<class T>
    T* GetObject() const
    {
        return dynamic_cast<T*>(m_app_doc_object);
    }

    gui::Document* GetDocument() const;
    bool IsAttachedToDocument() const override;
    std::string_view DetachFromDocument() override;

    /// Run a redraw
    virtual void UpdateView();
    /// Set the active mode, i.e. the first item of the 'Display' property.
    void SetActiveMode();

    virtual void FinishRestore();

    virtual void Update(const app::Property*);

    void SetVisible(bool);
    virtual void Show() override;
    virtual void Hide() override;

    /** @name Restoring view provider from document load */
    //@{
    virtual void StartRestoring();
    virtual void FinishRestoring();
    //@}

    virtual void OnBeforePropertyValueChanging(const app::Property* property) override;

    /** @name Tree rank */
    //@{
    int GetTreeRank() const
    {
        return m_tree_rank;
    }
    void SetTreeRank(int value)
    {
        m_tree_rank = value;
    }
    //@}

    /** Allow this class to be used as an override for the original view provider of the given object
     *
     * @sa App::DocumentObject::getViewProviderNameOverride()
     */
    virtual bool AllowOverride(const app::DocumentObject&) const
    {
        return false;
    }

    virtual void OnPropertyChanged(const app::Property*) override;

  protected:
    app::DocumentObject* m_app_doc_object;
    gui::Document* m_doc;

    int m_tree_rank{-1};

    friend class gui::Document;
};

}  // namespace gui