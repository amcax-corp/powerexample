#pragma once

#include <Base/XMLStreamReader.h>
#include <Base/IStorage.h>
#include <string_view>
#include <memory>  
#include <PFCGlobal.h>
#include <istream>
#include <bitset>

namespace base{

class PFC_BASE_API XMLReader : public XMLStreamReader
{

  std::shared_ptr<base::IStorage> m_storage;
  std::string m_entry_name;

public:
    enum ReaderStatus {
        PartialRestore = 0,                     // This bit indicates that a partial restore took place somewhere in this Document
        PartialRestoreInDocumentObject = 1,     // This bit is local to the DocumentObject being read indicating a partial restore therein
        PartialRestoreInProperty = 2,           // Local to the Property
        PartialRestoreInObject = 3              // Local to the object partially restored itself
    };

    /**
     * @brief Construct a new XMLReader object
     * 
     * @param storage 
     * @param entry_file_name reader读取的xml文件在压缩包中的文件路径
     */
    XMLReader(std::shared_ptr<base::IStorage> storage, std::string_view entry_file_name);
    ~XMLReader() override;

    bool TestStatus(ReaderStatus pos) const;
    void SetStatus(ReaderStatus pos, bool on);
    void SetPartialRestore(bool on);
    void ClearPartialRestoreDocumentObject();
    void ClearPartialRestoreProperty();
    void ClearPartialRestoreObject();

    void ReadAttachment(std::string const& attribute_name,std::function<bool(std::istream&, std::uint32_t)> reader); 
    void ReadBinFile(std::string const& filename);

    // 该方法会让渡Storage的拥有权，构造一个新的reader，
    // 以一个新的Entry为主要操作对象，所以注意，让渡之后，旧的Writer是不可以的状态。
    // 在PowerFC中，读取完app::Document的内容后，会读取GuiDocument.xml的内容
    // 从时序上将，app::Document::Restore和gui::Document::Restore是先后调用的，不能有交叉，所以需要让渡Storage的拥有权。
    std::shared_ptr<XMLReader> Transfer(std::string_view entry_name);

    std::string_view GetProgramVersion() const{
      return "1.0.0";
    }

    private:
    std::bitset<32> status_bits;
};

}