#pragma once

#include <Base/BaseClass.h>
#include <PFCGlobal.h>
#include <QVariant>

namespace app {
class Document;
}

namespace gui {

class Document;
class ViewProvider;

class PFC_GUI_API BaseView : public base::BaseClass
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    BaseView(gui::Document* document = nullptr);
    ~BaseView() override;

    void SetDocument(gui::Document* document);
    virtual void OnClose();

    gui::Document* GetGuiDocument() const
    {
        return m_doc;
    }

    app::Document* GetAppDocument() const;

    // app::Document* getAppDocument() const;

    virtual void OnUpdate() {}

    virtual void OnRelabel(gui::Document*) {}
    virtual void OnRename(gui::Document*) {}

    virtual bool OnMessage(std::string_view msg, const QVariant& input={}, QVariant* output=nullptr) = 0;
    virtual bool OnHasMessage(const char* message) const = 0;

    virtual bool CanClose()
    {
        return true;
    }

    virtual void DeleteSelf();

  protected:
    gui::Document* m_doc;
    bool m_is_detached;
};

}  // namespace gui