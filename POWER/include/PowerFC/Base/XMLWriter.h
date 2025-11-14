#pragma once
#include <set>
#include <Base/OStorage.h>
#include <Base/XMLStreamWriter.h>
namespace base {
class PFC_BASE_API XMLWriter : public XMLStreamWriter
{
    std::shared_ptr<OStorage> m_storage;
    // std::shared_ptr<std::ostream> m_os;

    std::string m_entry_name;

  public:
    XMLWriter(std::shared_ptr<OStorage> storage, std::string_view entry_name);
    ~XMLWriter() override;

    /**
     * @brief <xxx name="filename"/>
     * 
     * @param name xml attribute name, e.g. "file"
     * @param filename xml attribute value
     * @param writer 
     */
    void WriteAttachment(std::string_view name,
                         std::string_view filename,
                         const base::Persistence* persistence,
                         std::function<bool(std::ostream&,std::uint32_t)> writer);

    std::string const& GetName();
    
    void SetMode(std::string const& mode);
    bool HasMode(std::string const& mode) const;
    void ClearMode(std::string const& mode);
    void ClearModes();

    void AddError(std::string && error);
    bool HasError() const;
    void ClearErrors();

    std::vector<std::string> const& GetErrors() const;
    
    // 该方法会让渡Storage的拥有权，构造一个新的writer，
    // 以一个新的Entry为主要操作对象，所以注意，让渡之后，旧的Writer是不可以的状态。
    // 在PowerFC中，保存完app::Document的内容后，会向GuiDocument.xml写入gui::Document的内容
    // 从时序上将，app::Document::Store和gui::Document::Store是先后调用的，不能有交叉，所以需要让渡Storage的拥有权。
    std::shared_ptr<XMLWriter> Transfer(std::string_view entry_name);


  private:
    XMLWriter(std::ostream&) = delete;

    std::set<std::string> m_modes;
    std::vector<std::string> m_errors;


};
}  // namespace base