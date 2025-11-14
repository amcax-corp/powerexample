/// @file      ColorAttribute.hpp
/// @brief     The class of ColorAttribute
/// @details   The class of ColorAttribute is used to store a color value in RGBA format. The color value is represented as a tuple of four double values, each ranging from 0.0 to 1.0.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/Attribute.hpp>
#include <common/Macros.hpp>
#include <common/Precision.hpp>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>

namespace AMCAX {

/// @brief The class of ColorAttribute
/// @details The class of ColorAttribute is used to store a color value in RGBA format. The color value is represented as a tuple of four double values, each ranging from 0.0 to 1.0.
class ColorAttribute : public Attribute {
public:
    using value_type = std::tuple<double, double, double, double>;
    constexpr static AttributeMeta default_meta = MetaSet::Persistable | MetaSet::HasDefaultValue;

    /// @brief Construct a ColorAttribute with id, metainfo and r, g, b, a
    /// @param id The input id
    /// @param metainfo The input metainfo
    /// @param r,g,b,a The input rgba
    AMCAX_API ColorAttribute(const std::string& id, AttributeMeta metainfo, double r, double g, double b, double a);
    
    /// @brief Construct a ColorAttribute with id and value
    /// @param id The input id
    /// @param value The input value
    AMCAX_API ColorAttribute(const std::string& id, const value_type& value);

    /// @brief Construct a default ColorAttribute
    /// @details Costruct with no argument list, the id is ""
    AMCAX_API ColorAttribute();

    /// @brief Get the value of the ColorAttribute
    /// @return The value of the ColorAttribute
    AMCAX_API std::tuple<double, double, double, double> GetValue() const noexcept;

    /// @brief Set the color value of the ColorAttribute
    /// @param rgba The color value to set
    AMCAX_API void SetValue(std::tuple<double, double, double, double> rgba);

    /// @brief Implement the clone function to create a new instance of ColorAttribute
    /// @return A new instance of ColorAttribute
    AMCAX_API std::shared_ptr<Attribute> Clone() override;

    /// @brief Check if the color value is euqal to the input color value
    /// @param colorValue The input color value
    /// @param precision The compaire precision
    /// @return True if they are equal, otherwise return false
    AMCAX_API bool IsValueEqual(const value_type colorValue, double precision = Precision::Confusion()) const;

    /// @brief Serialize the attribute to a string
    /// @return The serialized string
    AMCAX_API std::string Serialize() const override;

private:
    bool isValidColor(double r, double g, double b, double a);

private:
    // Range: [0., 1.]
    double _r, _g, _b, _a;
};
}
