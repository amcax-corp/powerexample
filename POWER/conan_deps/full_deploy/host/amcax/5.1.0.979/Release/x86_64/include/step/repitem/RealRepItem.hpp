/// @file       RealRepItem.hpp
/// @brief      Class for representing a real representation item.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/repitem/AbstractRepItem.hpp>

namespace AMCAX::STEP
{
/// @brief Class for representing a real representation item.
class RealRepItem : public AbstractRepItem
{
public:
	/// @brief Default constructor.
	AMCAX_API RealRepItem();

	/// @brief Constructor.
	/// @param name The name of the real representation item.
	/// @param value The value of the value.
	AMCAX_API RealRepItem(const std::string& name, const double& value);

	/// @brief Copy constructor.
	/// @param other The other RealRepItem to copy from.
	AMCAX_API RealRepItem(const RealRepItem& other);

	/// @brief Move constructor.
	/// @param other The other RealRepItem to move from.
	AMCAX_API RealRepItem(RealRepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other RealRepItem to copy from.
	AMCAX_API RealRepItem& operator=(const RealRepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other RealRepItem to move from.
	AMCAX_API RealRepItem& operator=(RealRepItem&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~RealRepItem() override;

	/// @brief Set the name of the real representation item.
	/// @param name The name of the real representation item.
	/// @return The RealRepItem object.
	AMCAX_API RealRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the value.
	/// @return An immutable reference to the value.
	AMCAX_API const double& GetValue() const;

	/// @brief Set the value of the real representation item.
	/// @param value The value.
	/// @return The RealRepItem object.
	AMCAX_API RealRepItem& SetValue(const double& value);

	/// @brief If the RealRepItem same as the other RealRepItem.
	/// @param other The other RealRepItem to compare with.
	/// @return True if the RealRepItem is the same as the other RealRepItem, false otherwise.
	AMCAX_API bool operator==(const RealRepItem& other) const;

	/// @brief If the RealRepItem different from the other RealRepItem.
	/// @param other The other RealRepItem to compare with.
	/// @return True if the RealRepItem is different from the other RealRepItem, false otherwise.
	AMCAX_API bool operator!=(const RealRepItem& other) const;

	/// @brief If the RealRepItem less than the other RealRepItem.
	/// @param other The other RealRepItem to compare with.
	///	@return True if the RealRepItem is less than the other RealRepItem, false otherwise.
	AMCAX_API bool operator<(const RealRepItem& other) const;

	/// @brief If the RealRepItem greater than the other RealRepItem.
	/// @param other The other RealRepItem to compare with.
	/// @return True if the RealRepItem is greater than the other RealRepItem, false otherwise.
	AMCAX_API bool operator>(const RealRepItem& other) const;

	/// @brief If the RealRepItem less than or equal to the other RealRepItem.
	/// @param other The other RealRepItem to compare with.
	/// @return True if the RealRepItem is less than or equal to the other RealRepItem, false otherwise.
	AMCAX_API bool operator<=(const RealRepItem& other) const;

	/// @brief If the RealRepItem greater than or equal to the other RealRepItem.
	/// @param other The other RealRepItem to compare with.
	/// @return True if the RealRepItem is greater than or equal to the other RealRepItem, false otherwise.
	AMCAX_API bool operator>=(const RealRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;

private:
	double _Value{0.0};
};
} // namespace AMCAX::STEP
