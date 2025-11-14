#ifndef POWERFC_GUI_THUMBNAIL_H
#define POWERFC_GUI_THUMBNAIL_H
#pragma once
#include <Base/Persistence.h>
#include <filesystem>
#include <QUrl>
namespace gui {
class View3DInventorViewer;

class Thumbnail : public base::Persistence
{
  public:
    Thumbnail(int size = 128);
    ~Thumbnail() override;

    void SetViewer(View3DInventorViewer&);
    void SetSize(int);
    void SetFileName(std::filesystem::path const& );

    /** @name I/O of the document */
    //@{
    virtual std::size_t GetEstimatedSize() const override;

    //!@brief 重载该方法，把属性数据保存到xml文档中
    virtual void Store(base::XMLWriter&, std::uint32_t version) const override;

    //!@brief 重载该方法，把属性数据从xml文档中恢复
    virtual void Restore(base::XMLReader&, std::uint32_t version) override;
    //@}

  private:
    QUrl uri;
    View3DInventorViewer* viewer{nullptr};
    int size{128};
};

}  // namespace gui

#endif