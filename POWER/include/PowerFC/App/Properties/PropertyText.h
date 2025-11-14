#pragma once
#include <App/Property.h>

namespace base {
class XMLReader;
class Writer;
}  // namespace base

namespace app {

class PFC_APP_API PropertyText : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()
  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyText();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyText() override;

    void SetValue(const std::string& value);
    const std::string& GetValue() const;

    size_t GetEstimatedSize() const override;
    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

  protected:
    std::string m_value;
};

}  // namespace app