/// @file       MeasureRepItem.hpp
/// @brief      Class for representing a measure representation item.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <step/repitem/AbstractRepItem.hpp>

#include <misc/Measurement.hpp>

namespace AMCAX::STEP
{
/// @brief Class for representing a measure representation item.
class MeasureRepItem : public AbstractRepItem,
					   private Measurement
{
public:
	/// @brief Default constructor.
	AMCAX_API MeasureRepItem();

	/// @brief Constructor.
	/// @param name The name of the measure representation item.
	/// @param value The value of the measure.
	/// @param unit The unit of the measure.
	AMCAX_API MeasureRepItem(const std::string& name, const double& value, const SIUnit& unit);

	/// @brief Copy constructor.
	/// @param other The other MeasureRepItem to copy from.
	AMCAX_API MeasureRepItem(const MeasureRepItem& other);

	/// @brief Move constructor.
	/// @param other The other MeasureRepItem to move from.
	AMCAX_API MeasureRepItem(MeasureRepItem&& other) noexcept;

	/// @brief Copy assignment operator.
	/// @param other The other MeasureRepItem to copy from.
	AMCAX_API MeasureRepItem& operator=(const MeasureRepItem& other);

	/// @brief Move assignment operator.
	/// @param other The other MeasureRepItem to move from.
	AMCAX_API MeasureRepItem& operator=(MeasureRepItem&& other) noexcept;

	/// @brief Destructor.
	AMCAX_API ~MeasureRepItem() override;

	/// @brief Set the name of the measure representation item.
	/// @param name The name of the measure representation item.
	/// @return The CartesianPointRepItem object.
	AMCAX_API MeasureRepItem& SetName(const std::string& name);

	/// @brief Get an immutable reference to the value of the measure.
	/// @return An immutable reference to the value of the measure.
	AMCAX_API const double& GetValue() const;

	/// @brief Set the value of the measure representation item.
	/// @param value The value of the measure.
	/// @return The MeasureRepItem object.
	AMCAX_API MeasureRepItem& SetValue(const double& value);

	/// @brief Get an immutable reference to the unit of the measure.
	/// @return An immutable reference to the unit of the measure.
	AMCAX_API const SIUnit& GetUnit() const;

	/// @brief Get an mutable reference to the unit of the measure.
	/// @return A mutable reference to the unit of the measure.
	AMCAX_API SIUnit& Unit();

	/// @brief Set the unit of the measure representation item.
	/// @param unit The unit of the measure.
	/// @return The MeasureRepItem object.
	AMCAX_API MeasureRepItem& SetUnit(const SIUnit& unit);

	/// @brief If the MeasureRepItem same as the other MeasureRepItem.
	/// @param other The other MeasureRepItem to compare with.
	/// @return True if the MeasureRepItem is the same as the other MeasureRepItem, otherwise false
	AMCAX_API bool operator==(const MeasureRepItem& other) const;

	/// @brief If the MeasureRepItem different from the other MeasureRepItem.
	/// @param other The other MeasureRepItem to compare with.
	/// @return True if the MeasureRepItem is different from the other MeasureRepItem, otherwise false.
	AMCAX_API bool operator!=(const MeasureRepItem& other) const;

	/// @brief If the MeasureRepItem less than the other MeasureRepItem.
	/// @param other The other MeasureRepItem to compare with.
	/// @return True if the MeasureRepItem is less than the other MeasureRepItem, otherwise false.
	AMCAX_API bool operator<(const MeasureRepItem& other) const;

	/// @brief If the MeasureRepItem greater than the other MeasureRepItem.
	/// @param other The other MeasureRepItem to compare with.
	/// @return True if the MeasureRepItem is greater than the other MeasureRepItem, otherwise false.
	AMCAX_API bool operator>(const MeasureRepItem& other) const;

	/// @brief If the MeasureRepItem less than or equal to the other MeasureRepItem.
	/// @param other The other MeasureRepItem to compare with.
	/// @return True if the MeasureRepItem is less than or equal to the other MeasureRepItem, otherwise false.
	AMCAX_API bool operator<=(const MeasureRepItem& other) const;

	/// @brief If the MeasureRepItem greater than or equal to the other MeasureRepItem.
	/// @param other The other MeasureRepItem to compare with.
	/// @return True if the MeasureRepItem is greater than or equal to the other MeasureRepItem, otherwise false.
	AMCAX_API bool operator>=(const MeasureRepItem& other) const;

	/// @brief Deep Copy.
	/// @return The pointer of the duplicated object.
	virtual AMCAX_API std::shared_ptr<AbstractRepItem> Copy() const override;
};
} // namespace AMCAX::STEP
