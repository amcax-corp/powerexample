/// @file       TimeUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/AbstractUnit.hpp>

namespace AMCAX
{
/// @brief The TimeUnitType enum
enum class TimeUnitType
{
	Second,
	Minute,
	Hour,
};

/// @brief Class for SI Base Units
class TimeUnit : public AbstractUnit
{
public:
	/// @brief Default constructor
	AMCAX_API TimeUnit();

	/// @brief Construct a new TimeUnit object with a pre-defined non-SI unit
	/// @param type The predefined non-SI unit
	AMCAX_API TimeUnit(const TimeUnitType type);

	/// @brief Construct a new TimeUnit object with a multiplication
	/// @param multiplication How many base units are in the multiplication unit
	/// @note  This constructor should only be used to create a non-SI unit
	AMCAX_API TimeUnit(const double multiplication);

	/// @brief Construct a new TimeUnit object with a prefix
	/// @param prefix The prefix of the unit
	AMCAX_API TimeUnit(const UnitPrefix& prefix);

	/// @brief Copy constructor
	/// @param other The other TimeUnit object
	AMCAX_API TimeUnit(const TimeUnit& unit);

	/// @brief Move constructor
	/// @param other The other TimeUnit object
	AMCAX_API TimeUnit(const TimeUnit&& unit) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other TimeUnit object
	/// @return A reference to this
	AMCAX_API TimeUnit& operator=(const TimeUnit& unit);

	/// @brief Move assignment operator
	/// @param other The other TimeUnit object
	/// @return A reference to this
	AMCAX_API TimeUnit& operator=(const TimeUnit&& unit) noexcept;

	/// @brief Destructor
	AMCAX_API ~TimeUnit() override;

	/// @brief Set the prefix of the unit
	/// @param prefix The prefix of the unit
	/// @return A reference to this
	AMCAX_API TimeUnit& SetPrefix(const UnitPrefix prefix);

	/// @brief Set the multiplication of the unit
	/// @param multiplication How many base units are in the multiplication unit
	/// @return A reference to this
	AMCAX_API TimeUnit& SetMultiplication(const double multiplication);

	/// @brief If the TimeUnit same as the other TimeUnit
	/// @param other The other TimeUnit to compare with
	/// @return True if the TimeUnit is the same as the other TimeUnit, false otherwise
	AMCAX_API bool operator==(const TimeUnit& other) const;

	/// @brief If the TimeUnit different from the other TimeUnit
	/// @param other The other TimeUnit to compare with
	/// @return True if the TimeUnit is different from the other TimeUnit, false otherwise
	AMCAX_API bool operator!=(const TimeUnit& other) const;

	/// @brief If the TimeUnit less than the other TimeUnit
	/// @param other The other TimeUnit to compare with
	/// @return True if the TimeUnit is less than the other TimeUnit, false otherwise
	AMCAX_API bool operator<(const TimeUnit& other) const;

	/// @brief If the TimeUnit greater than the other TimeUnit
	/// @param other The other TimeUnit to compare with
	/// @return True if the TimeUnit is greater than the other TimeUnit, false otherwise
	AMCAX_API bool operator>(const TimeUnit& other) const;

	/// @brief If the TimeUnit less than or equal to the other TimeUnit
	/// @param other The other TimeUnit to compare with
	/// @return True if the TimeUnit is less than or equal to the other TimeUnit, false otherwise
	AMCAX_API bool operator<=(const TimeUnit& other) const;

	/// @brief If the TimeUnit greater than or equal to the other TimeUnit
	/// @param other The other TimeUnit to compare with
	/// @return True if the TimeUnit is greater than or equal to the other TimeUnit, false otherwise
	AMCAX_API bool operator>=(const TimeUnit& other) const;

	/// @brief Use the second unit
	/// @return A reference to this
	AMCAX_API TimeUnit& UseSecond();

	/// @brief Use the minute unit
	/// @return A reference to this
	AMCAX_API TimeUnit& UseMinute();

	/// @brief Use the hour unit
	/// @return A reference to this
	AMCAX_API TimeUnit& UseHour();
};
} // namespace AMCAX
