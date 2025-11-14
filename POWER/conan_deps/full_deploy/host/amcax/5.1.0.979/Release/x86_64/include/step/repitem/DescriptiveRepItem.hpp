/// @file       DescriptiveRepItem.hpp
/// @brief      Class for Descriptive Representation Items
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/repitem/AbstractRepItem.hpp>

namespace AMCAX::STEP
{
/// @brief Class for Descriptive Representation Items
class DescriptiveRepItem : public AbstractRepItem
{
public:
	/// @brief Default constructor
	AMCAX_API DescriptiveRepItem();

	/// @brief Constructor
	/// @param name The name of the descriptive representation item
	/// @param description The description of the descriptive representation item
	AMCAX_API DescriptiveRepItem(const std::string& name, const std::string& description);

	/// @brief Copy constructor
	/// @param other The other DescriptiveRepItem to copy from
	AMCAX_API DescriptiveRepItem(const DescriptiveRepItem& other);

	/// @brief Move constructor
	/// @param other The other DescriptiveRepItem to move from
	AMCAX_API DescriptiveRepItem(DescriptiveRepItem&& other) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other DescriptiveRepItem to copy from
	/// @return The DescriptiveRepItem object
	AMCAX_API DescriptiveRepItem& operator=(const DescriptiveRepItem& other);

	/// @brief Move assignment operator
	/// @param other The other DescriptiveRepItem to move from
	///	@return The DescriptiveRepItem object
	AMCAX_API DescriptiveRepItem& operator=(DescriptiveRepItem&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~DescriptiveRepItem() override;

	/// @brief Set the name of the descriptive representation item
	/// @param name The name of the descriptive representation item
	/// @return The DescriptiveRepItem object
	AMCAX_API DescriptiveRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the description of the descriptive representation item
	/// @return An immutable reference to the description of the descriptive representation item
	AMCAX_API const std::string& GetDescription() const;

	/// @brief Set the description of the descriptive representation item
	/// @param description The description of the descriptive representation item
	/// @return The DescriptiveRepItem object
	AMCAX_API DescriptiveRepItem& SetDescription(const std::string& description);

	/// @brief If the DescriptiveRepItem same as the other DescriptiveRepItem
	/// @param other The other DescriptiveRepItem to compare with
	/// @return True if the DescriptiveRepItem is the same as the other DescriptiveRepItem, false otherwise
	AMCAX_API bool operator==(const DescriptiveRepItem& other) const;

	/// @brief If the DescriptiveRepItem different from the other DescriptiveRepItem
	/// @param other The other DescriptiveRepItem to compare with
	/// @return True if the DescriptiveRepItem is different from the other DescriptiveRepItem, false otherwise
	AMCAX_API bool operator!=(const DescriptiveRepItem& other) const;

	/// @brief If the DescriptiveRepItem less than the other DescriptiveRepItem
	/// @param other The other DescriptiveRepItem to compare with
	/// @return True if the DescriptiveRepItem is less than the other DescriptiveRepItem, false otherwise
	AMCAX_API bool operator<(const DescriptiveRepItem& other) const;

	/// @brief If the DescriptiveRepItem greater than the other DescriptiveRepItem
	/// @param other The other DescriptiveRepItem to compare with
	/// @return True if the DescriptiveRepItem is greater than the other DescriptiveRepItem, false otherwise
	AMCAX_API bool operator>(const DescriptiveRepItem& other) const;

	/// @brief If the DescriptiveRepItem less than or equal to the other DescriptiveRepItem
	/// @param other The other DescriptiveRepItem to compare with
	/// @return True if the DescriptiveRepItem is less than or equal to the other DescriptiveRepItem, false otherwise
	AMCAX_API bool operator<=(const DescriptiveRepItem& other) const;

	/// @brief If the DescriptiveRepItem greater than or equal to the other DescriptiveRepItem
	/// @param other The other DescriptiveRepItem to compare with
	/// @return True if the DescriptiveRepItem is greater than or equal to the other DescriptiveRepItem, false otherwise
	AMCAX_API bool operator>=(const DescriptiveRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;

private:
	std::string _Description;
};
} // namespace AMCAX::STEP
