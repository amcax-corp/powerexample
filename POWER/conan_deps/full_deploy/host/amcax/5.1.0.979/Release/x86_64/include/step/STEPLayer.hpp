/// @file       STEPLayer.hpp
/// @brief		Represents a STEP layer containing a set of shapes and related metadata.
/// @copyright  Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

#include <common/Macros.hpp>

#include <topology/TopoShape.hpp>

namespace AMCAX::STEP
{
/// @brief Represents a STEP layer containing a set of shapes and related metadata.
class STEPLayer
{
private:
	uint64_t _ID{0};						///< Unique identifier for the layer.
	std::string _Name;						///< Name of the layer.
	std::string _Description;				///< Description of the layer.
	std::unordered_set<TopoShape> _Members; ///< Set of shapes in the layer.
	bool _Invisible{};						///< True if the layer is invisible.

public:
	/// @brief Default constructor.
	AMCAX_API STEPLayer();

	/// @brief Copy constructor.
	/// @param other The STEPLayer to copy from.
	AMCAX_API STEPLayer(const STEPLayer& other);

	/// @brief Move constructor.
	/// @param other The STEPLayer to move from.
	AMCAX_API STEPLayer(STEPLayer&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The STEPLayer to assign from.
	/// @return Reference to this STEPLayer.
	AMCAX_API STEPLayer& operator=(const STEPLayer& other);

	/// @brief Move assignment operator.
	/// @param other The STEPLayer to move from.
	/// @return Reference to this STEPLayer.
	AMCAX_API STEPLayer& operator=(STEPLayer&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~STEPLayer() noexcept;

	/// @brief Construct a layer with a given ID.
	/// @param id Unique identifier for the layer.
	AMCAX_API STEPLayer(uint64_t id);

	/// @brief Construct a layer with a given ID and name.
	/// @param id Unique identifier for the layer.
	/// @param name Name of the layer.
	AMCAX_API STEPLayer(uint64_t id, const std::string& name);

	/// @brief Construct a layer with a given ID, name, and description.
	/// @param id Unique identifier for the layer.
	/// @param name Name of the layer.
	/// @param desc Description of the layer.
	AMCAX_API STEPLayer(uint64_t id, const std::string& name, const std::string& desc);

	/// @brief Construct a layer with a given ID, name, and member shapes.
	/// @param id Unique identifier for the layer.
	/// @param name Name of the layer.
	/// @param layer_items Set of shapes to assign as members.
	AMCAX_API STEPLayer(uint64_t id, const std::string& name,
		const std::unordered_set<TopoShape>& layer_items);

	/// @brief Construct a layer with a given ID, name, description, and members.
	/// @param id Unique identifier for the layer.
	/// @param name Name of the layer.
	/// @param desc Description of the layer.
	/// @param layer_items Set of shapes to assign as members.
	AMCAX_API STEPLayer(uint64_t id, const std::string& name, const std::string& desc,
		const std::unordered_set<TopoShape>& layer_items);

	/// @brief Set the layer ID.
	/// @param id Unique identifier for the layer.
	AMCAX_API void SetID(uint64_t id);

	/// @brief Set the layer name.
	/// @param name New name for the layer.
	AMCAX_API void SetName(const std::string& name);

	/// @brief Set the layer description.
	/// @param desc New description for the layer.
	AMCAX_API void SetDescription(const std::string& desc);

	/// @brief Set the member shapes of the layer.
	/// @param items Set of shapes to assign as members.
	AMCAX_API void SetMembers(const std::unordered_set<TopoShape>& items);

	/// @brief Add a shape to the layer members.
	/// @param shape The shape to add.
	AMCAX_API void AddMember(const TopoShape& shape);

	/// @brief Get the layer ID.
	/// @return Reference to the layer's unique identifier.
	AMCAX_API const uint64_t& GetID() const;

	/// @brief Get the layer name.
	/// @return Const reference to the layer name.
	AMCAX_API const std::string& GetName() const;

	/// @brief Get the layer description.
	/// @return Const reference to the description.
	AMCAX_API const std::string& GetDescription() const;

	/// @brief Get the set of shapes in the layer.
	/// @return Const reference to the member set.
	AMCAX_API const std::unordered_set<TopoShape>& GetMembers() const;

	/// @brief Check if a shape is a member of the layer.
	/// @param member The shape to check.
	/// @retval true If the shape is a member.
	/// @retval false Otherwise.
	AMCAX_API bool Contains(const TopoShape& member) const;

	/// @brief Check whether the layer is invisible.
	/// @retval true If the layer is invisible.
	/// @retval false Otherwise.
	AMCAX_API bool IsInvisible() const;

	/// @brief Set the visibility flag for the layer.
	/// @param invisible True to make the layer invisible, false to make it visible.
	AMCAX_API void SetInvisible(bool invisible);
};

} // namespace AMCAX::STEP
