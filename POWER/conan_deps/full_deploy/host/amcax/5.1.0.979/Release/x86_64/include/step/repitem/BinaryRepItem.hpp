/// @file       BinaryRepItem.hpp
/// @brief      Class for representing a Binary Representation Items.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/repitem/AbstractRepItem.hpp>

namespace AMCAX::STEP
{
/// @brief Class for representing a Binary Representation Items.
class BinaryRepItem : public AbstractRepItem
{
public:
	/// @brief Default constructor.
	AMCAX_API BinaryRepItem();

	/// @brief Constructor.
	/// @param name The name of the binary representation item.
	/// @param value The value of the binary representation item.
	AMCAX_API BinaryRepItem(const std::string& name, const std::string& value);

	/// @brief Copy constructor.
	/// @param other The other BinaryRepItem to copy from.
	AMCAX_API BinaryRepItem(const BinaryRepItem& other);

	/// @brief Move constructor.
	/// @param other The other BinaryRepItem to move from.
	AMCAX_API BinaryRepItem(BinaryRepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other BinaryRepItem to copy from.
	/// @return The BinaryRepItem object.
	AMCAX_API BinaryRepItem& operator=(const BinaryRepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other BinaryRepItem to move from.
	///	@return The BinaryRepItem object.
	AMCAX_API BinaryRepItem& operator=(BinaryRepItem&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~BinaryRepItem() override;

	/// @brief Set the name of the binary representation item.
	/// @param name The name of the binary representation item.
	/// @return The BinaryRepItem object.
	AMCAX_API BinaryRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the value of the binary representation item.
	/// @return An immutable reference to the value of the binary representation item.
	AMCAX_API const std::string& GetValue() const;

	/// @brief Set the value of the binary representation item.
	/// @param value The value of the binary representation item.
	/// @return The BinaryRepItem object.
	AMCAX_API BinaryRepItem& SetValue(const std::string& value);

	/// @brief If the BinaryRepItem same as the other BinaryRepItem.
	/// @param other The other BinaryRepItem to compare with.
	/// @return True if the BinaryRepItem is the same as the other BinaryRepItem, otherwise false.
	AMCAX_API bool operator==(const BinaryRepItem& other) const;

	/// @brief If the BinaryRepItem different from the other BinaryRepItem.
	/// @param other The other BinaryRepItem to compare with.
	/// @return True if the BinaryRepItem is different from the other BinaryRepItem, otherwise false.
	AMCAX_API bool operator!=(const BinaryRepItem& other) const;

	/// @brief If the BinaryRepItem less than the other BinaryRepItem.
	/// @param other The other BinaryRepItem to compare with.
	/// @return True if the BinaryRepItem is less than the other BinaryRepItem, otherwise false.
	AMCAX_API bool operator<(const BinaryRepItem& other) const;

	/// @brief If the BinaryRepItem greater than the other BinaryRepItem.
	/// @param other The other BinaryRepItem to compare with.
	/// @return True if the BinaryRepItem is greater than the other BinaryRepItem, otherwise false.
	AMCAX_API bool operator>(const BinaryRepItem& other) const;

	/// @brief If the BinaryRepItem less than or equal to the other BinaryRepItem.
	/// @param other The other BinaryRepItem to compare with.
	/// @return True if the BinaryRepItem is less than or equal to the other BinaryRepItem, otherwise false.
	AMCAX_API bool operator<=(const BinaryRepItem& other) const;

	/// @brief If the BinaryRepItem greater than or equal to the other BinaryRepItem.
	/// @param other The other BinaryRepItem to compare with.
	/// @return True if the BinaryRepItem is greater than or equal to the other BinaryRepItem, otherwise false.
	AMCAX_API bool operator>=(const BinaryRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;

private:
	std::string _Value;
};
} // namespace AMCAX::STEP
