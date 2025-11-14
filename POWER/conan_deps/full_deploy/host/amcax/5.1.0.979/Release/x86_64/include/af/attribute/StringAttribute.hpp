/// @file      StringAttribute.hpp
/// @brief     The class of StringAttribute
/// @details   The class of StringAttribute is used to store a string value. The value can be a string.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/Attribute.hpp>
#include <common/Macros.hpp>
#include <memory>
#include <string>
#include <string_view>

namespace AMCAX {
/// @brief The class of StringAttribute
/// @details The class of StringAttribute is used to store a string value. The value can be a string.
class StringAttribute : public Attribute {
public:
    using value_type = std::string;
    static constexpr AttributeMeta default_meta = MetaSet::HasDefaultValue | MetaSet::Persistable;

public:
    /// @brief Construct a StringAttribute with id, metainfo and value
    /// @param id The input id
    /// @param metainfo The input metainfo
    /// @param value The input value
    AMCAX_API StringAttribute(const std::string& id, AttributeMeta metainfo, const std::string& value) noexcept;

    /// @brief Construct a StringAttribute with id and value
    /// @param id The input id
    /// @param value The input value
    AMCAX_API StringAttribute(const std::string& id, const std::string& value) noexcept;

    /// @brief Construct a default StringAttribute
    /// @details Costruct with no argument list, the id is ""
    AMCAX_API StringAttribute() noexcept;

public:
    /// @brief Set the value of the StringAttribute
    /// @param value The value to set
    AMCAX_API void SetValue(const std::string& value);

    /// @brief Get the value of the StringAttribute
    /// @return The value of the StringAttribute
    AMCAX_API std::string& GetValue() noexcept;

    /// @brief Get the value of the StringAttribute
    /// @return The value of the StringAttribute
    AMCAX_API const std::string& GetValue() const noexcept;

    /// @brief Implement the clone function to create a new instance of StringAttribute
    /// @return A new instance of StringAttribute
    AMCAX_API std::shared_ptr<Attribute> Clone() override;

    /// @brief Serialize the attribute to string
    /// @return The serialized string
    AMCAX_API std::string Serialize() const override;

private:
    std::string _data;
};
}  // namespace AMCAX
