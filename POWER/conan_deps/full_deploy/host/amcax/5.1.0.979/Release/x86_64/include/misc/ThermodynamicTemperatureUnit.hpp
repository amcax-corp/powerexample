/// @file       ThermodynamicTemperatureUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/AbstractUnit.hpp>

namespace AMCAX
{
/// @brief Class for SI Base Units
class ThermodynamicTemperatureUnit : public AbstractUnit
{
public:
	/// @brief Default constructor
	AMCAX_API ThermodynamicTemperatureUnit();

	/// @brief Construct a new ThermodynamicTemperatureUnit object with a multiplication
	/// @param multiplication How many base units are in the multiplication unit
	/// @note  This constructor should only be used to create a non-SI unit
	AMCAX_API ThermodynamicTemperatureUnit(const double multiplication);

	/// @brief Construct a new ThermodynamicTemperatureUnit object with a prefix
	/// @param prefix The prefix of the unit
	AMCAX_API ThermodynamicTemperatureUnit(const UnitPrefix prefix);

	/// @brief Copy constructor
	/// @param other The other ThermodynamicTemperatureUnit object
	AMCAX_API ThermodynamicTemperatureUnit(const ThermodynamicTemperatureUnit& other);

	/// @brief Move constructor
	/// @param other The other ThermodynamicTemperatureUnit object
	AMCAX_API ThermodynamicTemperatureUnit(const ThermodynamicTemperatureUnit&& other) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other ThermodynamicTemperatureUnit object
	/// @return A reference to this
	AMCAX_API ThermodynamicTemperatureUnit& operator=(const ThermodynamicTemperatureUnit& other);

	/// @brief Move assignment operator
	/// @param other The other ThermodynamicTemperatureUnit object
	/// @return A reference to this
	AMCAX_API ThermodynamicTemperatureUnit& operator=(const ThermodynamicTemperatureUnit&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~ThermodynamicTemperatureUnit() override;

	/// @brief Set the prefix of the unit
	/// @param prefix The prefix of the unit
	/// @return A reference to this
	AMCAX_API ThermodynamicTemperatureUnit& SetPrefix(const UnitPrefix prefix);

	/// @brief Set the multiplication of the unit
	/// @param multiplication How many base units are in the multiplication unit
	/// @return A reference to this
	AMCAX_API ThermodynamicTemperatureUnit& SetMultiplication(const double multiplication);

	/// @brief If the ThermodynamicTemperatureUnit same as the other ThermodynamicTemperatureUnit
	/// @param other The other ThermodynamicTemperatureUnit to compare with
	/// @return True if the ThermodynamicTemperatureUnit is the same as the other ThermodynamicTemperatureUnit, false otherwise
	AMCAX_API bool operator==(const ThermodynamicTemperatureUnit& other) const;

	/// @brief If the ThermodynamicTemperatureUnit different from the other ThermodynamicTemperatureUnit
	/// @param other The other ThermodynamicTemperatureUnit to compare with
	/// @return True if the ThermodynamicTemperatureUnit is different from the other ThermodynamicTemperatureUnit, false otherwise
	AMCAX_API bool operator!=(const ThermodynamicTemperatureUnit& other) const;

	/// @brief If the ThermodynamicTemperatureUnit less than the other ThermodynamicTemperatureUnit
	/// @param other The other ThermodynamicTemperatureUnit to compare with
	/// @return True if the ThermodynamicTemperatureUnit is less than the other ThermodynamicTemperatureUnit, false otherwise
	AMCAX_API bool operator<(const ThermodynamicTemperatureUnit& other) const;

	/// @brief If the ThermodynamicTemperatureUnit greater than the other ThermodynamicTemperatureUnit
	/// @param other The other ThermodynamicTemperatureUnit to compare with
	/// @return True if the ThermodynamicTemperatureUnit is greater than the other ThermodynamicTemperatureUnit, false otherwise
	AMCAX_API bool operator>(const ThermodynamicTemperatureUnit& other) const;

	/// @brief If the ThermodynamicTemperatureUnit less than or equal to the other ThermodynamicTemperatureUnit
	/// @param other The other ThermodynamicTemperatureUnit to compare with
	/// @return True if the ThermodynamicTemperatureUnit is less than or equal to the other ThermodynamicTemperatureUnit, false otherwise
	AMCAX_API bool operator<=(const ThermodynamicTemperatureUnit& other) const;

	/// @brief If the ThermodynamicTemperatureUnit greater than or equal to the other ThermodynamicTemperatureUnit
	/// @param other The other ThermodynamicTemperatureUnit to compare with
	/// @return True if the ThermodynamicTemperatureUnit is greater than or equal to the other ThermodynamicTemperatureUnit, false otherwise
	AMCAX_API bool operator>=(const ThermodynamicTemperatureUnit& other) const;
};
} // namespace AMCAX
