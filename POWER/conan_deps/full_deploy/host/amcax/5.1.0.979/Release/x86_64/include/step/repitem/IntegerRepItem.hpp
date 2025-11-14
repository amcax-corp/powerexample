/// @file       IntegerRepItem.hpp
/// @brief      Class for representing an integer representation item.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/repitem/AbstractRepItem.hpp>

#include <misc/SIUnit.hpp>

namespace AMCAX::STEP
{
/// @brief Class for representing an integer representation item.
class IntegerRepItem : public AbstractRepItem
{
public:
	/// @brief Default constructor.
	AMCAX_API IntegerRepItem();

	/// @brief Constructor.
	/// @param name The name of the integer representation item.
	/// @param value The value of the value.
	AMCAX_API IntegerRepItem(const std::string& name, const int64_t& value);

	/// @brief Copy constructor.
	/// @param other The other IntegerRepItem to copy from.
	AMCAX_API IntegerRepItem(const IntegerRepItem& other);

	/// @brief Move constructor.
	/// @param other The other IntegerRepItem to move from.
	AMCAX_API IntegerRepItem(IntegerRepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other IntegerRepItem to copy from.
	AMCAX_API IntegerRepItem& operator=(const IntegerRepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other IntegerRepItem to move from.
	AMCAX_API IntegerRepItem& operator=(IntegerRepItem&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~IntegerRepItem() override;

	/// @brief Set the name of the integer representation item.
	/// @param name The name of the integer representation item.
	/// @return The IntegerRepItem object.
	AMCAX_API IntegerRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the value.
	/// @return An immutable reference to the value.
	AMCAX_API const int64_t& GetValue() const;

	/// @brief Set the value of the integer representation item.
	/// @param value The value.
	/// @return The IntegerRepItem object,
	AMCAX_API IntegerRepItem& SetValue(const int64_t& value);

	/// @brief If the IntegerRepItem same as the other IntegerRepItem.
	/// @param other The other IntegerRepItem to compare with.
	/// @return True if the IntegerRepItem is the same as the other IntegerRepItem, otherwise false.
	AMCAX_API bool operator==(const IntegerRepItem& other) const;

	/// @brief If the IntegerRepItem different from the other IntegerRepItem.
	/// @param other The other IntegerRepItem to compare with.
	/// @return True if the IntegerRepItem is different from the other IntegerRepItem, otherwise false.
	AMCAX_API bool operator!=(const IntegerRepItem& other) const;

	/// @brief If the IntegerRepItem less than the other IntegerRepItem.
	/// @param other The other IntegerRepItem to compare with
	///	@return True if the IntegerRepItem is less than the other IntegerRepItem, otherwise false.
	AMCAX_API bool operator<(const IntegerRepItem& other) const;

	/// @brief If the IntegerRepItem greater than the other IntegerRepItem.
	/// @param other The other IntegerRepItem to compare with.
	/// @return True if the IntegerRepItem is greater than the other IntegerRepItem, otherwise false.
	AMCAX_API bool operator>(const IntegerRepItem& other) const;

	/// @brief If the IntegerRepItem less than or equal to the other IntegerRepItem.
	/// @param other The other IntegerRepItem to compare with.
	/// @return True if the IntegerRepItem is less than or equal to the other IntegerRepItem, otherwise false
	AMCAX_API bool operator<=(const IntegerRepItem& other) const;

	/// @brief If the IntegerRepItem greater than or equal to the other IntegerRepItem.
	/// @param other The other IntegerRepItem to compare with.
	/// @return True if the IntegerRepItem is greater than or equal to the other IntegerRepItem, otherwise false.
	AMCAX_API bool operator>=(const IntegerRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;

private:
	int64_t _Value{0};
};
} // namespace AMCAX::STEP
