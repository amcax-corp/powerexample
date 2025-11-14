#pragma once
#include <App/Property.h>
#include <topology/TopoShape.hpp>

namespace base {
class XMLReader;
class Writer;
}  // namespace base

namespace app {

class PFC_APP_API PropertyTopoShape : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()
  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyTopoShape();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyTopoShape() override;

    void SetValue(const AMCAX::TopoShape& value);
    const AMCAX::TopoShape& GetValue() const;

    size_t GetEstimatedSize() const override;
    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    bool IsNull() const{
      return m_value.IsNull();
    }

  protected:
    AMCAX::TopoShape m_value;
};

}  // namespace app