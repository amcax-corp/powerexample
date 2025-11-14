#pragma once
#include <PFCGlobal.h>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

namespace base {

class PFC_BASE_API XMLStreamWriter
{
  public:
    XMLStreamWriter(std::ostream& os);
    virtual ~XMLStreamWriter();

  public:
    void WriteStartDocument(std::string_view document_comment = {});

    void WriteEndDocument();

    void WriteAttribute(std::string_view name, std::string_view value);


    void WriteAttributeInteger(std::string_view name, int value);
    void WriteAttributeDouble(std::string_view name, double value);
    void WriteAttributeBool(std::string_view name, bool value);
    void WriteAttributeFloat(std::string_view name, float value);
    void WriteAttributeLong(std::string_view name, long value);
    void WriteAttributeSizeT(std::string_view name, std::size_t const& value);
    void WriteAttributeInteger64(std::string_view name, std::int64_t const& value);
    void WriteAttributeUnsigned(std::string_view name, std::uint32_t value);


    
    void WriteAttributes(std::initializer_list<std::pair<std::string_view, std::string_view>> attributes);

    void WriteAttribute(std::string_view namepsace_uri, std::string_view name, std::string_view value);

    void WriteStartElement(std::string_view namepsace_uri, std::string_view element_name);

    void WriteNamespace(std::string_view namepsace_uri, std::string_view prefix = {});

    void WriteDefaultNamespace(std::string_view namepsace_uri);

    void WriteStartElement(std::string_view element_name);

    void WriteEndElement();
    void WriteEndElement(std::string_view element_name);
    void WriteCDATA(std::string_view text);

    void SetAutoFormatting(bool enable);

  protected:
    
  protected:
    std::ostream& Stream();
    bool NeedFormatting() const;

  private:
    
    struct Private;
    std::unique_ptr<Private> m_p;

    std::ostream& m_output_stream;
};

}  // namespace base