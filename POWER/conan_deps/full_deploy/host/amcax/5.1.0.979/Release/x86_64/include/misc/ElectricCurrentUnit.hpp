/// @file       ElectricCurrentUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/AbstractUnit.hpp>

namespace AMCAX
{
/// @brief Class for SI Base Units
class ElectricCurrentUnit : public AbstractUnit
{
public:
	/// @brief Default constructor
	AMCAX_API ElectricCurrentUnit();

	/// @brief Construct a new ElectricCurrentUnit object with a multiplication
	/// @param multiplication How many base units are in the multiplication unit
	/// @note  This constructor should only be used to create a non-SI unit
	AMCAX_API ElectricCurrentUnit(const double multiplication);

	/// @brief Construct a new ElectricCurrentUnit object with a prefix
	/// @param prefix The prefix of the unit
	AMCAX_API ElectricCurrentUnit(const UnitPrefix prefix);

	/// @brief Copy constructor
	/// @param other The other ElectricCurrentUnit object
	AMCAX_API ElectricCurrentUnit(const ElectricCurrentUnit& other);

	/// @brief Move constructor
	/// @param other The other ElectricCurrentUnit object
	AMCAX_API ElectricCurrentUnit(const ElectricCurrentUnit&& other) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other ElectricCurrentUnit object
	/// @return A reference to this
	AMCAX_API ElectricCurrentUnit& operator=(const ElectricCurrentUnit& other);

	/// @brief Move assignment operator
	/// @param other The other ElectricCurrentUnit object
	/// @return A reference to this
	AMCAX_API ElectricCurrentUnit& operator=(const ElectricCurrentUnit&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~ElectricCurrentUnit() override;

	/// @brief Set the prefix of the unit
	/// @param prefix The prefix of the unit
	/// @return A reference to this
	AMCAX_API ElectricCurrentUnit& SetPrefix(const UnitPrefix prefix);

	/// @brief Set the multiplication of the unit
	/// @param multiplication How many base units are in the multiplication unit
	/// @return A reference to this
	AMCAX_API ElectricCurrentUnit& SetMultiplication(const double multiplication);

	/// @brief If the ElectricCurrentUnit same as the other ElectricCurrentUnit
	/// @param other The other ElectricCurrentUnit to compare with
	/// @return True if the ElectricCurrentUnit is the same as the other ElectricCurrentUnit, false otherwise
	AMCAX_API bool operator==(const ElectricCurrentUnit& other) const;

	/// @brief If the ElectricCurrentUnit different from the other ElectricCurrentUnit
	/// @param other The other ElectricCurrentUnit to compare with
	/// @return True if the ElectricCurrentUnit is different from the other ElectricCurrentUnit, false otherwise
	AMCAX_API bool operator!=(const ElectricCurrentUnit& other) const;

	/// @brief If the ElectricCurrentUnit less than the other ElectricCurrentUnit
	/// @param other The other ElectricCurrentUnit to compare with
	/// @return True if the ElectricCurrentUnit is less than the other ElectricCurrentUnit, false otherwise
	AMCAX_API bool operator<(const ElectricCurrentUnit& other) const;

	/// @brief If the ElectricCurrentUnit greater than the other ElectricCurrentUnit
	/// @param other The other ElectricCurrentUnit to compare with
	/// @return True if the ElectricCurrentUnit is greater than the other ElectricCurrentUnit, false otherwise
	AMCAX_API bool operator>(const ElectricCurrentUnit& other) const;

	/// @brief If the ElectricCurrentUnit less than or equal to the other ElectricCurrentUnit
	/// @param other The other ElectricCurrentUnit to compare with
	/// @return True if the ElectricCurrentUnit is less than or equal to the other ElectricCurrentUnit, false otherwise
	AMCAX_API bool operator<=(const ElectricCurrentUnit& other) const;

	/// @brief If the ElectricCurrentUnit greater than or equal to the other ElectricCurrentUnit
	/// @param other The other ElectricCurrentUnit to compare with
	/// @return True if the ElectricCurrentUnit is greater than or equal to the other ElectricCurrentUnit, false otherwise
	AMCAX_API bool operator>=(const ElectricCurrentUnit& other) const;
};
} // namespace AMCAX
