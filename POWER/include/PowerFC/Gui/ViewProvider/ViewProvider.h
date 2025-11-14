#pragma once

#include <App/PropertyContainer.h>
#include <App/TransactionalObject.h>
#include <Base/XMLReader.h>
#include <Base/XMLWriter.h>
#include <PFCGlobal.h>
#include <QIcon>
#include <QMenu>

namespace app {
class DocumentObject;
class Property;
}  // namespace app

namespace gui {

class MdiView;
class View3DInventorViewer;

class PFC_GUI_API ViewProvider : public app::TransactionalObject
{
    PFC_PROPERTY_DECL_WITH_OVERRIDE()

  public:
    enum class ViewStatus
    {
        UpdateData = 0,
        Detach = 1,
        IsRestoring = 2,
        UpdatingView = 3,
        TouchDocument = 4,
    };

    /// return the status bits
    unsigned long GetStatus() const
    {
        return m_status_bits.to_ulong();
    }
    bool TestStatus(ViewStatus pos) const
    {
        return m_status_bits.test((size_t)pos);
    }
    void SetStatus(ViewStatus pos, bool on)
    {
        m_status_bits.set((size_t)pos, on);
    }

  public:
    /// constructor.
    ViewProvider();

    /// destructor.
    ~ViewProvider() override;

    virtual bool UseNewSelectionModel() const;
    virtual bool IsSelectable() const
    {
        return true;
    }

    virtual bool OnDelete();

    virtual void BeforeDelete();

    virtual void DeleteFromView();

    virtual bool CanDelete(app::DocumentObject* obj);

    virtual QIcon GetIcon() const;

    // virtual QIcon MergeColorfulOverlayIcons(const QIcon& orig) const;

    std::string ToString() const;

    virtual void Show();
    virtual void Hide();

    virtual bool IsShow() const;
    bool IsVisible() const;
    void SetLinkVisible(bool);
    bool IsLinkVisible() const;

    
    virtual QWidget* GetTaskView() const;
    
    bool IsRestoring()
    {
      return TestStatus(ViewStatus::IsRestoring);
    }
    
    bool IsUpdatesEnabled() const;
    void SetUpdatesEnabled(bool enable);

    virtual void Update(const app::Property*);
    virtual void UpdateData(const app::Property*);

    virtual void SetEditViewer(View3DInventorViewer* viewer, int mode);
    virtual void UnsetEditViewer(View3DInventorViewer* viewer);

    virtual void OnPropertyChanged(const app::Property*) override;
    virtual void OnBeforePropertyValueChanging(const app::Property*) override;

  protected:
    std::string overrideMode;
    QIcon m_icon;

  private:
    int m_actual_mod{-1};
    int m_edit_mode{-1};
    int m_view_override_mode{-1};
    std::string m_current_mode;

    std::bitset<32> m_status_bits;  //
};

}  // namespace gui