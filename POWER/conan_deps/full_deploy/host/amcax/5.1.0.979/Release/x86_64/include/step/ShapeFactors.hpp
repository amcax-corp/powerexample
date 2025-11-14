/// @file       ShapeFactors.hpp
/// @brief		Encapsulates the unit length factor and Shape_Aspect attribute items for STEP entities.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <step/repitem/RepItem.hpp>

namespace AMCAX::STEP
{
/// @brief Encapsulates the unit length factor and Shape_Aspect attribute items for STEP entities.
class ShapeFactors
{
public:
	/// @brief Container type for Shape_Aspect attributes.
	/// @details
	/// Key = a set of entity IDs associated with a Shape_Aspect.
	/// Value = a map from attribute name (string) to a list of RepItem values.
	using ValueType_SA = std::map<std::set<uint64_t>, std::map<std::string, std::vector<RepItem>>>;

	/// @brief Default constructor. Initializes length factor to 1.0 and leaves attributes empty.
	AMCAX_API ShapeFactors();

	/// @brief Copy constructor.
	/// @param other The ShapeFactors to copy.
	AMCAX_API ShapeFactors(const ShapeFactors& other);

	/// @brief Copy assignment operator.
	/// @param other The ShapeFactors to copy.
	/// @return Reference to this object.
	AMCAX_API ShapeFactors& operator=(const ShapeFactors& other);

	/// @brief Move constructor.
	/// @param other The ShapeFactors to move.
	AMCAX_API ShapeFactors(ShapeFactors&& other) noexcept;

	/// @brief Move assignment operator.
	/// @param other The ShapeFactors to move.
	/// @return Reference to this object.
	AMCAX_API ShapeFactors& operator=(ShapeFactors&& other) noexcept;

	/// @brief Construct with a specific length factor.
	/// @param lengthFactor The unit conversion factor for length (relative to millimetres).
	AMCAX_API ShapeFactors(const double lengthFactor);

	/// @brief Destructor.
	AMCAX_API ~ShapeFactors();

	/// @brief Implicit conversion to the underlying length factor.
	/// @return The length factor value.
	AMCAX_API operator double() const;

	/// @brief Get the current length factor (read-only).
	/// @return Const reference to the length factor.
	AMCAX_API const double& LengthFactor() const;

	/// @brief Get the current length factor (modifiable).
	/// @return Reference to the length factor.
	AMCAX_API double& LengthFactor();

	/// @brief Get all Shape_Aspect attribute items (read-only).
	/// @return Const reference to the Shape_Aspect attributes.
	AMCAX_API const ValueType_SA& AttributeItems_SA() const;

	/// @brief Get all Shape_Aspect attribute items (modifiable).
	/// @return Reference to the Shape_Aspect attributes.
	AMCAX_API ValueType_SA& AttributeItems_SA();

private:
	double _LengthFactor = 1.0; ///< Length factor (default = 1.0, meaning millimetres).
	ValueType_SA _attrs_sa;		///< Shape_Aspect attribute items.
};
} // namespace AMCAX::STEP
