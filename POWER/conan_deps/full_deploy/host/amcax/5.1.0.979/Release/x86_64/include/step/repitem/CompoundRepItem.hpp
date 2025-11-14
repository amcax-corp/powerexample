/// @file       CompoundRepItem.hpp
/// @brief      Class for representing a compound representation item.
/// @copyright  Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/repitem/AbstractRepItem.hpp>

#include <memory>
#include <vector>

namespace AMCAX::STEP
{
/// @brief Class for representing a compound representation item.
class CompoundRepItem : public AbstractRepItem
{
public:
	/// @brief Default constructor.
	AMCAX_API CompoundRepItem();

	/// @brief Constructor.
	/// @param name The name of the compound representation item.
	/// @param value The value of the value.
	AMCAX_API CompoundRepItem(const std::string& name);

	/// @brief Copy constructor.
	/// @param other The other CompoundRepItem to copy from.
	AMCAX_API CompoundRepItem(const CompoundRepItem& other);

	/// @brief Move constructor.
	/// @param other The other CompoundRepItem to move from.
	AMCAX_API CompoundRepItem(CompoundRepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other CompoundRepItem to copy from.
	AMCAX_API CompoundRepItem& operator=(const CompoundRepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other CompoundRepItem to move from.
	AMCAX_API CompoundRepItem& operator=(CompoundRepItem&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~CompoundRepItem() override;

	/// @brief Set the name of the compound representation item.
	/// @param name The name of the compound representation item.
	/// @return The CompoundRepItem object.
	AMCAX_API CompoundRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the value.
	/// @return An immutable reference to the value.
	AMCAX_API const std::vector<std::shared_ptr<AbstractRepItem>>& GetValue() const;

	/// @brief Get a mutable reference to the value.
	/// @param index The index of the querying object.
	/// @return A mutable reference to the value.
	AMCAX_API std::shared_ptr<AbstractRepItem> GetValue(const size_t index);

	/// @brief Add a representation item to the compound representation item.
	/// @param value The value to be inserted.
	/// @return The CompoundRepItem object.
	AMCAX_API CompoundRepItem& Insert(const std::shared_ptr<AbstractRepItem>& value);

	/// @brief Delete a value from the compound representation item.
	/// @param index The index of the object to be deleted.
	/// @return The CompoundRepItem object.
	AMCAX_API std::shared_ptr<AbstractRepItem> Delete(const size_t index);

	/// @brief If the CompoundRepItem same as the other CompoundRepItem.
	/// @param other The other CompoundRepItem to compare with.
	/// @return True if the CompoundRepItem is the same as the other CompoundRepItem, otherwise false.
	AMCAX_API bool operator==(const CompoundRepItem& other) const;

	/// @brief If the CompoundRepItem different from the other CompoundRepItem.
	/// @param other The other CompoundRepItem to compare with.
	/// @return True if the CompoundRepItem is different from the other CompoundRepItem, otherwise false.
	AMCAX_API bool operator!=(const CompoundRepItem& other) const;

	/// @brief If the CompoundRepItem less than the other CompoundRepItem.
	/// @param other The other CompoundRepItem to compare with.
	///	@return True if the CompoundRepItem is less than the other CompoundRepItem, otherwise false.
	AMCAX_API bool operator<(const CompoundRepItem& other) const;

	/// @brief If the CompoundRepItem greater than the other CompoundRepItem.
	/// @param other The other CompoundRepItem to compare with.
	/// @return True if the CompoundRepItem is greater than the other CompoundRepItem, otherwise false.
	AMCAX_API bool operator>(const CompoundRepItem& other) const;

	/// @brief If the CompoundRepItem less than or equal to the other CompoundRepItem.
	/// @param other The other CompoundRepItem to compare with.
	/// @return True if the CompoundRepItem is less than or equal to the other CompoundRepItem, otherwise false.
	AMCAX_API bool operator<=(const CompoundRepItem& other) const;

	/// @brief If the CompoundRepItem greater than or equal to the other CompoundRepItem.
	/// @param other The other CompoundRepItem to compare with.
	/// @return True if the CompoundRepItem is greater than or equal to the other CompoundRepItem, otherwise false.
	AMCAX_API bool operator>=(const CompoundRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;

	/// @brief Clear the compound.
	/// @return The representation items.
	AMCAX_API std::vector<std::shared_ptr<AbstractRepItem>> Clear() noexcept;

private:
	std::vector<std::shared_ptr<AbstractRepItem>> _Values;
};
} // namespace AMCAX::STEP
