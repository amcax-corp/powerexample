/// @file		ShapeProperty.hpp
/// @brief		Represents a property attached to a STEP entity (e.g., name, style, visibility).
/// @copyright	Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par		This file is part of AMCAX Kernel.
#pragma once

#include <array>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <common/Macros.hpp>

#include <step/ShapeRGBA.hpp>
#include <step/ShapeStyles.hpp>

namespace AMCAX
{
class TopoShape;

namespace STEP
{
/// @brief Represents a property attached to a STEP entity (e.g., name, style, visibility).
class ShapeProperty
{
public:
	/// @brief Default constructor. Creates an empty property.
	AMCAX_API ShapeProperty();

	/// @brief Construct with an entity ID.
	/// @param id The numeric entity ID.
	explicit AMCAX_API ShapeProperty(const uint64_t id);

	/// @brief Construct with a name.
	/// @param name The name of the entity.
	explicit AMCAX_API ShapeProperty(const std::string& name);

	/// @brief Construct with a shape style.
	/// @param shapestyle The style to set.
	explicit AMCAX_API ShapeProperty(const ShapeStyle& shapestyle);

	/// @brief Copy constructor.
	/// @param other The ShapeProperty to copy.
	AMCAX_API ShapeProperty(const ShapeProperty& other);

	/// @brief Move constructor.
	/// @param other The ShapeProperty to move.
	AMCAX_API ShapeProperty(ShapeProperty&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~ShapeProperty();

	/// @brief Set the entity ID.
	/// @param id The entity ID.
	AMCAX_API void SetEntityID(const uint64_t id);

	/// @brief Set the name.
	/// @param name The name to set.
	AMCAX_API void SetName(const std::string& name);

	/// @brief Set the shape style.
	/// @param shapestyle The style to set.
	AMCAX_API void SetShapeStyle(const ShapeStyle& shapestyle);

	/// @brief Check if an entity ID is set.
	/// @retval true If the ID is nonzero.
	/// @retval false If no ID is set.
	AMCAX_API bool EntityIDHasValue() const;

	/// @brief Check if a name is set.
	/// @retval true If the name has a value.
	/// @retval false Otherwise.
	AMCAX_API bool NameHasValue() const;

	/// @brief Check if a shape style is set.
	/// @retval true If a style value is present.
	/// @retval false Otherwise.
	AMCAX_API bool ShapeStyleHasValue() const;

	/// @brief Get the entity ID.
	/// @return The entity ID value, or 0 if not set.
	AMCAX_API uint64_t EntityID() const;

	/// @brief Get the name.
	/// @return The name value, or an empty string if not set.
	AMCAX_API std::string Name() const;

	/// @brief Get the shape style.
	/// @return The style value, or a default-constructed style if not set.
	AMCAX_API ShapeStyle GetShapeStyle() const;

	/// @brief Clear the entity ID.
	AMCAX_API void EntityIDNullify();

	/// @brief Clear the name.
	AMCAX_API void NameNullify();

	/// @brief Clear the shape style.
	AMCAX_API void ShapeStyleNullify();

	/// @brief Clear all fields.
	AMCAX_API void Nullify();

	/// @brief Check if the property is empty.
	/// @retval true If none of ID, name, or style are set.
	/// @retval false If any field is set.
	AMCAX_API bool IsEmpty() const;

	/// @brief Set the invisibility flag.
	/// @param invisible True if the styled item is invisible.
	AMCAX_API void SetInvisibility(bool invisible);

	/// @brief Get the invisibility flag.
	/// @retval true If the styled item is invisible.
	/// @retval false Otherwise.
	AMCAX_API bool GetInvisibility();

	/// @brief Equality operator.
	/// @param other The ShapeProperty to compare with.
	/// @retval true If all fields are equal.
	/// @retval false Otherwise.
	AMCAX_API bool operator==(const ShapeProperty& other) const;

	/// @brief Assignment operator.
	/// @param other The ShapeProperty to assign from.
	/// @return Reference to this object.
	AMCAX_API ShapeProperty& operator=(const ShapeProperty& other);

	/// @brief Compound addition assignment operator (merge).
	/// @param other The ShapeProperty to merge from.
	/// @return Reference to this object.
	/// @note If a field is valid and non-empty in both objects, the current value is kept.
	AMCAX_API ShapeProperty& operator+=(const ShapeProperty& other);

private:
	std::optional<std::string> _name;
	std::optional<ShapeStyle> _shapestyle;
	uint64_t _id{0ull};
	bool _invisible = false;

	friend AMCAX_API ShapeProperty operator+(const ShapeProperty& a, const ShapeProperty& b);
};

/// @brief Addition operator (merge two ShapeProperty objects).
/// @param a Left-hand operand. Its values take precedence if both objects have the same field.
/// @param b Right-hand operand. Values are copied only if not already set in @p a.
/// @return A new ShapeProperty containing merged values.
AMCAX_API ShapeProperty operator+(const ShapeProperty& a, const ShapeProperty& b);

} // namespace STEP
} // namespace AMCAX
