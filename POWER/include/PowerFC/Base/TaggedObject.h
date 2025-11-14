#pragma once
#include <cstdint>
#include <Base/BaseClass.h>

namespace base {
class PFC_BASE_API TaggedObject: public BaseClass
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();
  private:
    std::uint32_t m_tag{0};

  protected:
    TaggedObject();
    TaggedObject(TaggedObject const&);
    TaggedObject& operator=(TaggedObject const&);
    TaggedObject(TaggedObject&&);
    TaggedObject& operator=(TaggedObject&&);

  public:
    virtual ~TaggedObject() override;

    std::uint32_t GetTag() const
    {
        return m_tag;
    }
};
}  // namespace base