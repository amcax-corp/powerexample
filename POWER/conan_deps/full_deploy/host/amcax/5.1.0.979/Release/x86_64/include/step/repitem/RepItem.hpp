/// @file       RepItem.hpp
/// @brief      Class for representing a representation item.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <memory>
#include <string>
#include <variant>

#include <step/repitem/BinaryRepItem.hpp>
#include <step/repitem/CartesianPointRepItem.hpp>
#include <step/repitem/CompoundRepItem.hpp>
#include <step/repitem/DescriptiveRepItem.hpp>
#include <step/repitem/IntegerRepItem.hpp>
#include <step/repitem/MeasureRepItem.hpp>
#include <step/repitem/RealRepItem.hpp>
#include <step/repitem/ValueRepItem.hpp>

namespace AMCAX::STEP
{
/// @brief Class representing a representation item
class RepItem
{
public:
	using RepItemUnion = std::variant<
		std::monostate,
		CartesianPointRepItem,
		DescriptiveRepItem,
		MeasureRepItem,
		ValueRepItem,
		CompoundRepItem,
		IntegerRepItem,
		RealRepItem,
		BinaryRepItem>;

public:
	/// @brief Default constructor.
	AMCAX_API RepItem();

	/// @brief Copy constructor.
	/// @param other The other RepItem object.
	AMCAX_API RepItem(const RepItem& other);

	/// @brief Move constructor.
	/// @param other The other RepItem object.
	AMCAX_API RepItem(RepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other RepItem object.
	/// @return The reference to the current RepItem object.
	AMCAX_API RepItem& operator=(const RepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other RepItem object.
	/// @return The reference to the current RepItem object.
	AMCAX_API RepItem& operator=(RepItem&& other) noexcept;

	/// @brief Construct with a RepItemUnion object.
	/// @param item The RepItemUnion object.
	AMCAX_API RepItem(const RepItemUnion& item);

	/// @brief Construct with a CartesianPointRepItem object.
	/// @param item The CartesianPointRepItem object.
	AMCAX_API RepItem(const CartesianPointRepItem& item);

	/// @brief Construct with a DescriptiveRepItem object.
	/// @param item The DescriptiveRepItem object.
	AMCAX_API RepItem(const DescriptiveRepItem& item);

	/// @brief Construct with a MeasureRepItem object.
	/// @param item The MeasureRepItem object.
	AMCAX_API RepItem(const MeasureRepItem& item);

	/// @brief Construct with a ValueRepItem object.
	/// @param item The ValueRepItem object.
	AMCAX_API RepItem(const ValueRepItem& item);

	/// @brief Construct with a CompoundRepItem object.
	/// @param item The CompoundRepItem object.
	AMCAX_API RepItem(const CompoundRepItem& item);

	/// @brief Construct with a IntegerRepItem object.
	/// @param item The IntegerRepItem object.
	AMCAX_API RepItem(const IntegerRepItem& item);

	/// @brief Construct with a RealRepItem object.
	/// @param item The RealRepItem object.
	AMCAX_API RepItem(const RealRepItem& item);

	/// @brief Construct with a BinaryRepItem object.
	/// @param item The BinaryRepItem object.
	AMCAX_API RepItem(const BinaryRepItem& item);

	/// @brief Assign a RepItem object.
	/// @param item The RepItemUnion object.
	/// @return The reference to the current RepItem object.
	AMCAX_API RepItem& operator=(const RepItemUnion& item);

	/// @brief Destructor.
	AMCAX_API virtual ~RepItem();

	/// @brief Get the type of the representation item.
	/// @return The type of the representation item.
	AMCAX_API RepItemType Type() const;

	// @brief Get the name of the representation item.
	AMCAX_API std::string GetName() const;

	// @brief Set the name of the representation item.
	// @param name The name of the representation item.
	// @return The RepItem object.
	AMCAX_API RepItem& SetName(const std::string& name);

	/// @brief Get the representation item.
	/// @return The representation item.
	AMCAX_API const RepItemUnion& GetItem() const;

	/// @brief Get the representation item.
	/// @param item The representation item.
	/// @return The representation item.
	AMCAX_API RepItem& SetItem(const RepItemUnion& item);

	/// @brief If the repitem same as the other repitem.
	/// @param other The other repitem.
	/// @return True if the repitem is the same as the other repitem, otherwise false.
	AMCAX_API bool operator==(const RepItem& other) const;

	/// @brief If the repitem is not the same as the other repitem.
	/// @param other The other repitem.
	/// @return True if the repitem is not the same as the other repitem, otherwise false.
	AMCAX_API bool operator!=(const RepItem& other) const;

	/// @brief If the repitem is less than the other repitem.
	/// @param other The other repitem.
	/// @return True if the repitem is less than the other repitem, otherwise false.
	AMCAX_API bool operator<(const RepItem& other) const;

	/// @brief If the repitem is greater than the other repitem.
	/// @param other The other repitem.
	/// @return True if the repitem is greater than the other repitem, otherwise false.
	AMCAX_API bool operator>(const RepItem& other) const;

	/// @brief If the repitem is less than or equal to the other repitem.
	/// @param other The other repitem.
	/// @return True if the repitem is less than or equal to the other repitem, otherwise false.
	AMCAX_API bool operator<=(const RepItem& other) const;

	/// @brief If the repitem is greater than or equal to the other repitem.
	/// @param other The other repitem.
	/// @return True if the repitem is greater than or equal to the other repitem, otherwise false.
	AMCAX_API bool operator>=(const RepItem& other) const;

	AMCAX_API operator const RepItemUnion&() const;

	AMCAX_API operator RepItemUnion&();

private:
	RepItemUnion _Item;
};
} // namespace AMCAX::STEP
