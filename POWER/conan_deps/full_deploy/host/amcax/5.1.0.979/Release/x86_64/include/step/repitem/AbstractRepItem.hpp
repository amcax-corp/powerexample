/// @file       AbstractRepItem.hpp
/// @brief      Class for representing a representation item
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <memory>
#include <string>

namespace AMCAX::STEP
{
/// @brief Type of the Representation Item
enum class RepItemType
{
	/// @brief The type of the representation item is unspecified
	UNSPECIFIED,
	/// @brief The representation item is a Cartesian point representation item
	CARTESIAN_POINT_REPITEM,
	/// @brief The representation item is a descriptive representation item
	DESCRIPTIVE_REPITEM,
	/// @brief The representation item is a measure representation item
	MEASURE_REPITEM,
	/// @brief The representation item is a value representation item
	VALUE_REPITEM,
	/// @brief The representation item is a compound representation item
	COMPOUND_REPITEM,
	/// @brief The representation item is a integer representation item
	INTEGER_REPITEM,
	/// @brief The representation item is a real representaion item
	REAL_REPITEM,
	/// @brief The representation item is a binary representaion item
	BINARY_REPITEM,
};

/// @brief Class representing a representation item
class AMCAX_CLASS_API AbstractRepItem
{
public:
	/// @brief Get an immutable reference to the name of the representation item.
	/// @return An immutable reference to name of the representation item.
	AMCAX_API const std::string& GetName() const;

	virtual AMCAX_API RepItemType Type() const;

	/// @brief Default Destructor.
	virtual AMCAX_API ~AbstractRepItem();

	/// @brief Compare Operator
	/// @param other The other AbstractRepItem to be compared
	/// @return true if the name and the type are equal.
	bool operator==(const AbstractRepItem& other) const;

	/// @brief Compare Operator
	/// @param other The other AbstractRepItem to be compared
	/// @return true if the name and / or the type are less.
	bool operator<(const AbstractRepItem& other) const;

	/// @brief Compare Operator
	/// @param other The other AbstractRepItem to be compared
	/// @return true if the name and / or the type are greater.
	bool operator>(const AbstractRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual std::shared_ptr<AbstractRepItem> Copy() const = 0;

#ifndef DOXYGEN_SKIP
protected:
	AbstractRepItem& SetName(const std::string& name);

	RepItemType _Type{RepItemType::UNSPECIFIED};
	std::string _Name;

	// Default constructor
	AbstractRepItem() = delete;
	AbstractRepItem(const RepItemType type);

	// Construct a base repitem with its name
	AbstractRepItem(const RepItemType type, const std::string& name);
	AbstractRepItem(const RepItemType type, std::string&& name);

	// copy constructor and copy assignment operator for the base class
	AbstractRepItem(const AbstractRepItem& other);
	AbstractRepItem(AbstractRepItem&& other) noexcept;
	AbstractRepItem& operator=(const AbstractRepItem& other);
	AbstractRepItem& operator=(AbstractRepItem&& other) noexcept;

#endif // !DOXYGEN_SKIP
};

} // namespace AMCAX::STEP
