/// @file       ValueRepItem.hpp
/// @brief      Class for representing a value representation item.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/repitem/AbstractRepItem.hpp>

#include <misc/SIUnit.hpp>

namespace AMCAX::STEP
{
/// @brief Class for representing a value representation item.
class ValueRepItem : public AbstractRepItem
{
public:
	/// @brief Default constructor.
	AMCAX_API ValueRepItem();

	/// @brief Constructor.
	/// @param name The name of the value representation item.
	/// @param value The value of the value.
	AMCAX_API ValueRepItem(const std::string& name, const double& value);

	/// @brief Copy constructor.
	/// @param other The other ValueRepItem to copy from.
	AMCAX_API ValueRepItem(const ValueRepItem& other);

	/// @brief Move constructor
	/// @param other The other ValueRepItem to move from.
	AMCAX_API ValueRepItem(ValueRepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other ValueRepItem to copy from.
	AMCAX_API ValueRepItem& operator=(const ValueRepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other ValueRepItem to move from.
	AMCAX_API ValueRepItem& operator=(ValueRepItem&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~ValueRepItem() override;

	/// @brief Set the name of the value representation item.
	/// @param name The name of the value representation item.
	/// @return The ValueRepItem object.
	AMCAX_API ValueRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the value.
	/// @return An immutable reference to the value.
	AMCAX_API const double& GetValue() const;

	/// @brief Set the value of the value representation item.
	/// @param value The value of the value.
	/// @return The ValueRepItem object.
	AMCAX_API ValueRepItem& SetValue(const double& value);

	/// @brief If the ValueRepItem same as the other ValueRepItem.
	/// @param other The other ValueRepItem to compare with.
	/// @return True if the ValueRepItem is the same as the other ValueRepItem, otherwise false.
	AMCAX_API bool operator==(const ValueRepItem& other) const;

	/// @brief If the ValueRepItem different from the other ValueRepItem.
	/// @param other The other ValueRepItem to compare with.
	/// @return True if the ValueRepItem is different from the other ValueRepItem, otherwise false.
	AMCAX_API bool operator!=(const ValueRepItem& other) const;

	/// @brief If the ValueRepItem less than the other ValueRepItem.
	/// @param other The other ValueRepItem to compare with.
	///	@return True if the ValueRepItem is less than the other ValueRepItem, otherwise false.
	AMCAX_API bool operator<(const ValueRepItem& other) const;

	/// @brief If the ValueRepItem greater than the other ValueRepItem.
	/// @param other The other ValueRepItem to compare with.
	/// @return True if the ValueRepItem is greater than the other ValueRepItem, otherwise false.
	AMCAX_API bool operator>(const ValueRepItem& other) const;

	/// @brief If the ValueRepItem less than or equal to the other ValueRepItem.
	/// @param other The other ValueRepItem to compare with.
	/// @return True if the ValueRepItem is less than or equal to the other ValueRepItem, otherwise false.
	AMCAX_API bool operator<=(const ValueRepItem& other) const;

	/// @brief If the ValueRepItem greater than or equal to the other ValueRepItem.
	/// @param other The other ValueRepItem to compare with.
	/// @return True if the ValueRepItem is greater than or equal to the other ValueRepItem, otherwise false.
	AMCAX_API bool operator>=(const ValueRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;

private:
	double _Value{0.0};
};
} // namespace AMCAX::STEP
