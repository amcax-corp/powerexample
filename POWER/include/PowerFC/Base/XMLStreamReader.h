#pragma once
#include <PFCGlobal.h>
#include <cstdint>
#include <istream>
#include <memory>
#include <vector>
#include <optional>

namespace base {
class PFC_BASE_API XMLStreamReader
{
  public:
    XMLStreamReader(std::istream& input_stream);
    virtual ~XMLStreamReader();

    
    bool HasAttribute(std::string const& attribute_name) const;
    std::int32_t GetAttributeAsInteger(std::string const& attribute_name) const;
    std::uint32_t GetAttributeAsUnsigned(std::string const& attribute_name) const;
    std::size_t GetAttributeAsSizeT(std::string const& attribute_name) const;
    std::int64_t GetAttributeAsInteger64(std::string const& attribute_name) const;
    float GetAttributeAsFloat(std::string const& attribute_name) const;
    double GetAttributeAsDouble(std::string const& attribute_name) const;
    bool GetAttributeAsBool(std::string const& attribute_name) const;
    std::string GetAttribute(std::string const& attribute_name) const;

    void ReadElement(std::string const& element_name);
    void ReadEndElement(std::string const& element_name, std::int32_t level = -1);

    std::string ReadCDATA();

    

    public:
    std::optional<std::string> GetElement() const;
    std::optional<std::string> GetCDATA() const;
    std::optional<std::string> GetCharacters() const;


    public://for debug
    std::vector<std::pair<std::string, std::string>> GetAttributes() const;

    

  private:

    struct Private;
    std::unique_ptr<Private> m_p;
};
}  // namespace base
