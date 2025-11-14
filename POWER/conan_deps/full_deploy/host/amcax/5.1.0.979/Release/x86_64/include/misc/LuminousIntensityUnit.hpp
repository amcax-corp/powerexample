/// @file       LuminousIntensityUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/AbstractUnit.hpp>

namespace AMCAX
{
/// @brief Class for SI Base Units
class LuminousIntensityUnit : public AbstractUnit
{
public:
	/// @brief Default constructor
	AMCAX_API LuminousIntensityUnit();

	/// @brief Construct a new LuminousIntensityUnit object with a multiplication
	/// @param multiplication How many base units are in the multiplication unit
	///	@note  This constructor should only be used to create a non-SI unit
	AMCAX_API LuminousIntensityUnit(const double multiplication);

	/// @brief Construct a new LuminousIntensityUnit object with a prefix
	/// @param prefix The prefix of the unit
	AMCAX_API LuminousIntensityUnit(const UnitPrefix prefix);

	/// @brief Copy constructor
	/// @param other The other LuminousIntensityUnit object
	AMCAX_API LuminousIntensityUnit(const LuminousIntensityUnit& other);

	/// @brief Move constructor
	/// @param other The other LuminousIntensityUnit object
	AMCAX_API LuminousIntensityUnit(const LuminousIntensityUnit&& other) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other LuminousIntensityUnit object
	/// @return A reference to this
	AMCAX_API LuminousIntensityUnit& operator=(const LuminousIntensityUnit& other);

	/// @brief Move assignment operator
	/// @param other The other LuminousIntensityUnit object
	/// @return A reference to this
	AMCAX_API LuminousIntensityUnit& operator=(const LuminousIntensityUnit&& other) noexcept;

	/// @brief Destructor
	AMCAX_API ~LuminousIntensityUnit() override;

	/// @brief Set the prefix of the unit
	/// @param prefix The prefix of the unit
	/// @return A reference to this
	AMCAX_API LuminousIntensityUnit& SetPrefix(const UnitPrefix prefix);

	/// @brief Set the multiplication of the unit
	/// @param multiplication How many base units are in the multiplication unit
	/// @return A reference to this
	AMCAX_API LuminousIntensityUnit& SetMultiplication(const double multiplication);

	/// @brief If the LuminousIntensityUnit same as the other LuminousIntensityUnit
	/// @param other The other LuminousIntensityUnit to compare with
	/// @return True if the LuminousIntensityUnit is the same as the other LuminousIntensityUnit, false otherwise
	AMCAX_API bool operator==(const LuminousIntensityUnit& other) const;

	/// @brief If the LuminousIntensityUnit different from the other LuminousIntensityUnit
	/// @param other The other LuminousIntensityUnit to compare with
	/// @return True if the LuminousIntensityUnit is different from the other LuminousIntensityUnit, false otherwise
	AMCAX_API bool operator!=(const LuminousIntensityUnit& other) const;

	/// @brief If the LuminousIntensityUnit less than the other LuminousIntensityUnit
	/// @param other The other LuminousIntensityUnit to compare with
	/// @return True if the LuminousIntensityUnit is less than the other LuminousIntensityUnit, false otherwise
	AMCAX_API bool operator<(const LuminousIntensityUnit& other) const;

	/// @brief If the LuminousIntensityUnit greater than the other LuminousIntensityUnit
	/// @param other The other LuminousIntensityUnit to compare with
	/// @return True if the LuminousIntensityUnit is greater than the other LuminousIntensityUnit, false otherwise
	AMCAX_API bool operator>(const LuminousIntensityUnit& other) const;

	/// @brief If the LuminousIntensityUnit less than or equal to the other LuminousIntensityUnit
	/// @param other The other LuminousIntensityUnit to compare with
	/// @return True if the LuminousIntensityUnit is less than or equal to the other LuminousIntensityUnit, false otherwise
	AMCAX_API bool operator<=(const LuminousIntensityUnit& other) const;

	/// @brief If the LuminousIntensityUnit greater than or equal to the other LuminousIntensityUnit
	/// @param other The other LuminousIntensityUnit to compare with
	/// @return True if the LuminousIntensityUnit is greater than or equal to the other LuminousIntensityUnit, false otherwise
	AMCAX_API bool operator>=(const LuminousIntensityUnit& other) const;
};
} // namespace AMCAX
