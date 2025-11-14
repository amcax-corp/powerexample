#ifndef POWERFC_APP_PROPERTIES_PROPERTY_FILE_PATH_H_
#define POWERFC_APP_PROPERTIES_PROPERTY_FILE_PATH_H_
#pragma once
#include <App/Property.h>
#include <filesystem>

namespace base {
class XMLReader;
class Writer;
}  // namespace base

namespace app {

/** @brief 存储一个文件名的属性
*/
class PFC_APP_API PropertyFilePath : public Property
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyFilePath();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    ~PropertyFilePath() override;

    void SetValue(std::filesystem::path const& value);

    std::filesystem::path const& GetValue() const;

    std::string_view GetEditorTypeName() const override
    {
        return "Gui::PropertyEditor::PropertyFilePathItem";
    }

    // PyObject* getPyObject() override;
    // void setPyObject(PyObject* py) override;

    void Store(base::XMLWriter& writer, std::uint32_t) const override;
    void Restore(base::XMLReader& reader, std::uint32_t) override;

    std::unique_ptr<Property> Clone() const override;
    void Paste(const Property& from) override;

    size_t GetEstimatedSize() const override
    {
        return sizeof(double);
    }

    // void SetPathValue(const app::ObjectIdentifier& path, const std::any& value) override;
    // const std::any GetPathValue(const app::ObjectIdentifier& path) const override;

    bool IsSame(const Property& other) const override;

  private:
    std::filesystem::path m_value;
};
}  // namespace app

#endif /* POWERFC_APP_PROPERTIES_PROPERTYFile_H_ */