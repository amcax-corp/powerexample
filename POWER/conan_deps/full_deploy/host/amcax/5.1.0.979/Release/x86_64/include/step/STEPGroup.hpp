/// @file       STEPGroup.hpp
/// @brief		Represents a group of shapes, with ID, name, optional description, and member set.
/// @copyright  Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_set>

#include <topology/TopoShape.hpp>

namespace AMCAX::STEP
{
/// @brief Represents a group of shapes, with ID, name, optional description, and member set.
class STEPGroup
{
private:
	uint64_t _ID{0};						 ///< Unique identifier. Used by Reader; Writer ignores this field.
	std::string _Name;						 ///< Name of the group.
	std::optional<std::string> _Description; ///< Optional description of the group.
	std::unordered_set<TopoShape> _Members;	 ///< Set of member shapes.

public:
	/// @brief Default constructor.
	AMCAX_API STEPGroup();

	/// @brief Copy constructor.
	/// @param other The STEPGroup to copy.
	AMCAX_API STEPGroup(const STEPGroup& other);

	/// @brief Move constructor.
	/// @param other The STEPGroup to move.
	AMCAX_API STEPGroup(STEPGroup&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The STEPGroup to assign from.
	/// @return Reference to this STEPGroup.
	AMCAX_API STEPGroup& operator=(const STEPGroup& other);

	/// @brief Move assignment operator.
	/// @param other The STEPGroup to move from.
	/// @return Reference to this STEPGroup.
	AMCAX_API STEPGroup& operator=(STEPGroup&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~STEPGroup() noexcept;

	/// @brief Construct a group with a given ID.
	/// @param id Identifier. Used by Reader; Writer ignores this field.
	AMCAX_API STEPGroup(uint64_t id);

	/// @brief Construct a group with a given ID and name.
	/// @param id Identifier. Used by Reader; Writer ignores this field.
	/// @param name Name of the group.
	AMCAX_API STEPGroup(uint64_t id, const std::string& name);

	/// @brief Construct a group with a given ID, name, and description.
	/// @param id Identifier. Used by Reader; Writer ignores this field.
	/// @param name Name of the group.
	/// @param desc Description of the group.
	AMCAX_API STEPGroup(uint64_t id, const std::string& name, const std::string& desc);

	/// @brief Construct a group with a given ID, name, and member shapes.
	/// @param id Identifier. Used by Reader; Writer ignores this field.
	/// @param name Name of the group.
	/// @param group_items Set of shapes to assign as members.
	AMCAX_API STEPGroup(uint64_t id, const std::string& name,
		const std::unordered_set<TopoShape>& group_items);

	/// @brief Construct a group with a given ID, name, description, and members.
	/// @param id Identifier. Used by Reader; Writer ignores this field.
	/// @param name Name of the group.
	/// @param desc Description of the group.
	/// @param group_items Set of shapes to assign as members.
	AMCAX_API STEPGroup(uint64_t id, const std::string& name, const std::string& desc,
		const std::unordered_set<TopoShape>& group_items);

	/// @brief Set the group ID.
	/// @param id Identifier. Used by Reader; Writer ignores this field.
	AMCAX_API void SetID(uint64_t id);

	/// @brief Set the group name.
	/// @param name New name for the group.
	AMCAX_API void SetName(const std::string& name);

	/// @brief Set the group description.
	/// @param desc New description.
	AMCAX_API void SetDescription(const std::string& desc);

	/// @brief Set the member shapes of the group.
	/// @param items Set of shapes to assign as members.
	AMCAX_API void SetMembers(const std::unordered_set<TopoShape>& items);

	/// @brief Add a shape to the group members.
	/// @param shape The shape to add.
	AMCAX_API void AddMember(const TopoShape& shape);

	/// @brief Check if this group has a description.
	/// @retval true If a description is set.
	/// @retval false If no description is present.
	AMCAX_API bool HasDescription() const;

	/// @brief Get the group ID.
	/// @warning The ID is only meaningful when reading; writing ignores this value.
	/// @return Const reference to the group ID.
	AMCAX_API const uint64_t& GetID() const;

	/// @brief Get the group name.
	/// @return Const reference to the name.
	AMCAX_API const std::string& GetName() const;

	/// @brief Get the group description.
	/// @return Copy of the description, or empty string if none is set.
	AMCAX_API std::string GetDescription() const;

	/// @brief Get the member shapes of the group.
	/// @return Const reference to the member set.
	AMCAX_API const std::unordered_set<TopoShape>& GetMembers() const;

	/// @brief Check if a shape is a member of the group.
	/// @param member The shape to check.
	/// @retval true If the shape is a member.
	/// @retval false Otherwise.
	AMCAX_API bool Contains(const TopoShape& member) const;
};

} // namespace AMCAX::STEP
