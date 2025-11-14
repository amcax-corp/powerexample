#ifndef POWERFC_APP_PROPERTIES_PROPERTYINTEGERSET_H_
#define POWERFC_APP_PROPERTIES_PROPERTYINTEGERSET_H_
#pragma once
#include <App/Property.h>

namespace app {

class PFC_APP_API PropertyIntegerSet : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    PropertyIntegerSet() = default;
    ~PropertyIntegerSet() override = default;

    void SetValue(long value);
    void SetValue(){}

    //!@brief 仅添加一个值，不触发信号，不通知其他对象
    void AddValueSilently(long value);

    void SetValues(std::set<long> const& values);

    const std::set<long>& GetValues() const;

    void Visit(std::function<void(long)> visitor) const;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override;

    bool IsSame(const Property& other) const override
    {
        if (&other == this)
        {
            return true;
        }
        return GetClassTypePolymorphic() == other.GetClassTypePolymorphic() &&
               GetValues() == static_cast<decltype(this)>(&other)->GetValues();
    }

    private:
    std::set<long> m_values;
};

}  // namespace app
#endif