/// @file       AmountOfSubstanceUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/AbstractUnit.hpp>

namespace AMCAX
{
/// @brief Class for SI Base Units
class AmountOfSubstanceUnit : public AbstractUnit
{
public:
	/// @brief Default constructor
	AMCAX_API AmountOfSubstanceUnit();

	/// @brief Construct a new AmountOfSubstanceUnit object with a multiplication
	/// @param multiplication How many base units are in the multiplication unit
	/// @note  This constructor should only be used to create a non-SI unit
	AMCAX_API AmountOfSubstanceUnit(const double multiplication);

	/// @brief Construct a new AmountOfSubstanceUnit object with a prefix
	/// @param prefix The prefix of the unit
	AMCAX_API AmountOfSubstanceUnit(const UnitPrefix prefix);

	/// @brief Copy constructor
	/// @param other The other AmountOfSubstanceUnit object
	AMCAX_API AmountOfSubstanceUnit(const AmountOfSubstanceUnit& other);

	/// @brief Move constructor
	/// @param other The other AmountOfSubstanceUnit object
	AMCAX_API AmountOfSubstanceUnit(const AmountOfSubstanceUnit&& other) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other AmountOfSubstanceUnit object
	/// @return A reference to this
	AMCAX_API AmountOfSubstanceUnit& operator=(const AmountOfSubstanceUnit& other);

	/// @brief Move assignment operator
	/// @param other The other AmountOfSubstanceUnit object
	/// @return A reference to this
	AMCAX_API AmountOfSubstanceUnit& operator=(const AmountOfSubstanceUnit&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~AmountOfSubstanceUnit() override;

	/// @brief Set the prefix of the unit
	/// @param prefix The prefix of the unit
	/// @return A reference to this
	AMCAX_API AmountOfSubstanceUnit& SetPrefix(const UnitPrefix prefix);

	/// @brief Set the multiplication of the unit
	/// @param multiplication How many base units are in the multiplication unit
	/// @return A reference to this
	AMCAX_API AmountOfSubstanceUnit& SetMultiplication(const double multiplication);

	/// @brief If the AmountOfSubstanceUnit same as the other AmountOfSubstanceUnit
	/// @param other The other AmountOfSubstanceUnit to compare with
	/// @return True if the AmountOfSubstanceUnit is the same as the other AmountOfSubstanceUnit, false otherwise
	AMCAX_API bool operator==(const AmountOfSubstanceUnit& other) const;

	/// @brief If the AmountOfSubstanceUnit different from the other AmountOfSubstanceUnit
	/// @param other The other AmountOfSubstanceUnit to compare with
	/// @return True if the AmountOfSubstanceUnit is different from the other AmountOfSubstanceUnit, false otherwise
	AMCAX_API bool operator!=(const AmountOfSubstanceUnit& other) const;

	/// @brief If the AmountOfSubstanceUnit less than the other AmountOfSubstanceUnit
	/// @param other The other AmountOfSubstanceUnit to compare with
	/// @return True if the AmountOfSubstanceUnit is less than the other AmountOfSubstanceUnit, false otherwise
	AMCAX_API bool operator<(const AmountOfSubstanceUnit& other) const;

	/// @brief If the AmountOfSubstanceUnit greater than the other AmountOfSubstanceUnit
	/// @param other The other AmountOfSubstanceUnit to compare with
	/// @return True if the AmountOfSubstanceUnit is greater than the other AmountOfSubstanceUnit, false otherwise
	AMCAX_API bool operator>(const AmountOfSubstanceUnit& other) const;

	/// @brief If the AmountOfSubstanceUnit less than or equal to the other AmountOfSubstanceUnit
	/// @param other The other AmountOfSubstanceUnit to compare with
	/// @return True if the AmountOfSubstanceUnit is less than or equal to the other AmountOfSubstanceUnit, false otherwise
	AMCAX_API bool operator<=(const AmountOfSubstanceUnit& other) const;

	/// @brief If the AmountOfSubstanceUnit greater than or equal to the other AmountOfSubstanceUnit
	/// @param other The other AmountOfSubstanceUnit to compare with
	/// @return True if the AmountOfSubstanceUnit is greater than or equal to the other AmountOfSubstanceUnit, false otherwise
	AMCAX_API bool operator>=(const AmountOfSubstanceUnit& other) const;
};
} // namespace AMCAX
