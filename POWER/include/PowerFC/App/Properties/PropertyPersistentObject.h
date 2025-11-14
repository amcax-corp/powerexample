#ifndef POWERFC_APP_PROPERTIES_PROPERTY_PERSISTENT_OBJECT_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_PERSISTENT_OBJECT_H_
#pragma once
#include <App/Properties/PropertyString.h>

namespace app {

    /** Property for dynamic creation of a FreeCAD persistent object
 *
 * In Python, this property can be assigned a type string to create a dynamic FreeCAD
 * object, and then read back as the Python binding of the newly created object.
 */
class PFC_APP_API PropertyPersistentObject: public PropertyString {
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();
    using Base = PropertyString;
public:
    // PyObject *getPyObject() override;
    void SetValue(std::string_view type) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override;

    std::shared_ptr<base::Persistence> GetObject() const {
        return m_object;
    }

protected:
    std::shared_ptr<base::Persistence> m_object;
};

}


#endif