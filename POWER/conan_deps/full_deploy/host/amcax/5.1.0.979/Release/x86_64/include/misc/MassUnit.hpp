/// @file       MassUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/AbstractUnit.hpp>

namespace AMCAX
{
/// @brief Class for SI Base Units
class MassUnit : public AbstractUnit
{
public:
	/// @brief Default constructor
	AMCAX_API MassUnit();

	/// @brief Construct a new MassUnit object with a multiplication
	/// @param multiplication How many base units are in the multiplication unit
	/// @note  This constructor should only be used to create a non-SI unit
	AMCAX_API MassUnit(const double multiplication);

	/// @brief Construct a new MassUnit object with a prefix
	/// @param prefix The prefix of the unit
	AMCAX_API MassUnit(const UnitPrefix prefix);

	/// @brief Copy constructor
	/// @param other The other MassUnit object
	AMCAX_API MassUnit(const MassUnit& other);

	/// @brief Move constructor
	/// @param other The other MassUnit object
	AMCAX_API MassUnit(const MassUnit&& other) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other MassUnit object
	/// @return A reference to this
	AMCAX_API MassUnit& operator=(const MassUnit& other);

	/// @brief Move assignment operator
	/// @param other The other MassUnit object
	/// @return A reference to this
	AMCAX_API MassUnit& operator=(const MassUnit&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~MassUnit() override;

	/// @brief Set the prefix of the unit
	/// @param prefix The prefix of the unit
	/// @return A reference to this
	AMCAX_API MassUnit& SetPrefix(const UnitPrefix prefix);

	/// @brief Set the multiplication of the unit
	/// @param multiplication How many base units are in the multiplication unit
	/// @return A reference to this
	AMCAX_API MassUnit& SetMultiplication(const double multiplication);

	/// @brief If the MassUnit same as the other MassUnit
	/// @param other The other MassUnit to compare with
	/// @return True if the MassUnit is the same as the other MassUnit, false otherwise
	AMCAX_API bool operator==(const MassUnit& other) const;

	/// @brief If the MassUnit different from the other MassUnit
	/// @param other The other MassUnit to compare with
	/// @return True if the MassUnit is different from the other MassUnit, false otherwise
	AMCAX_API bool operator!=(const MassUnit& other) const;

	/// @brief If the MassUnit less than the other MassUnit
	/// @param other The other MassUnit to compare with
	/// @return True if the MassUnit is less than the other MassUnit, false otherwise
	AMCAX_API bool operator<(const MassUnit& other) const;

	/// @brief If the MassUnit greater than the other MassUnit
	/// @param other The other MassUnit to compare with
	/// @return True if the MassUnit is greater than the other MassUnit, false otherwise
	AMCAX_API bool operator>(const MassUnit& other) const;

	/// @brief If the MassUnit less than or equal to the other MassUnit
	/// @param other The other MassUnit to compare with
	/// @return True if the MassUnit is less than or equal to the other MassUnit, false otherwise
	AMCAX_API bool operator<=(const MassUnit& other) const;

	/// @brief If the MassUnit greater than or equal to the other MassUnit
	/// @param other The other MassUnit to compare with
	/// @return True if the MassUnit is greater than or equal to the other MassUnit, false otherwise
	AMCAX_API bool operator>=(const MassUnit& other) const;

	/// @brief Compute a value in current unit to a value in Kilogram
	/// @param value A value in current unit
	/// @return The same weight in Kilogram
	AMCAX_API virtual double ToBase(const double value = 1.0) const override;
};
} // namespace AMCAX
