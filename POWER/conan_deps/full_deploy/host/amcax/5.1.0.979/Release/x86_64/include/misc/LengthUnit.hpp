/// @file       LengthUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/AbstractUnit.hpp>

namespace AMCAX
{
/// @brief The non-SI units
enum class LengthUnitType
{
	MetricMeter,
	Foot,
	Inch,
	Yard,
	Mile,
};

/// @brief Class for SI Base Units
class LengthUnit : public AbstractUnit
{
public:
	/// @brief Default constructor
	AMCAX_API LengthUnit();

	/// @brief Construct a new LengthUnit object with a pre-defined non-SI unit
	/// @param type The predefined non-SI unit
	AMCAX_API LengthUnit(const LengthUnitType type);

	/// @brief Construct a new LengthUnit object with a multiplication
	/// @param multiplication How many base units are in the multiplication unit
	/// @note  This constructor should only be used to create a non-SI unit
	AMCAX_API LengthUnit(const double multiplication);

	/// @brief Construct a new LengthUnit object with a prefix
	/// @param prefix The prefix of the unit
	AMCAX_API LengthUnit(const UnitPrefix& prefix);

	/// @brief Copy constructor
	/// @param other The other LengthUnit object
	AMCAX_API LengthUnit(const LengthUnit& unit);

	/// @brief Move constructor
	/// @param other The other LengthUnit object
	AMCAX_API LengthUnit(const LengthUnit&& unit) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other LengthUnit object
	/// @return A reference to this
	AMCAX_API LengthUnit& operator=(const LengthUnit& unit);

	/// @brief Move assignment operator
	/// @param other The other LengthUnit object
	/// @return A reference to this
	AMCAX_API LengthUnit& operator=(const LengthUnit&& unit) noexcept;

	/// @brief Destructor
	AMCAX_API ~LengthUnit() override;

	/// @brief Set the prefix of the unit
	/// @param prefix The prefix of the unit
	/// @return A reference to this
	AMCAX_API LengthUnit& SetPrefix(const UnitPrefix prefix);

	/// @brief Set the multiplication of the unit
	/// @param multiplication How many base units are in the multiplication unit
	/// @return A reference to this
	AMCAX_API LengthUnit& SetMultiplication(const double multiplication);

	/// @brief If the LengthUnit same as the other LengthUnit
	/// @param other The other LengthUnit to compare with
	/// @return True if the LengthUnit is the same as the other LengthUnit, false otherwise
	AMCAX_API bool operator==(const LengthUnit& other) const;

	/// @brief If the LengthUnit different from the other LengthUnit
	/// @param other The other LengthUnit to compare with
	/// @return True if the LengthUnit is different from the other LengthUnit, false otherwise
	AMCAX_API bool operator!=(const LengthUnit& other) const;

	/// @brief If the LengthUnit less than the other LengthUnit
	/// @param other The other LengthUnit to compare with
	/// @return True if the LengthUnit is less than the other LengthUnit, false otherwise
	AMCAX_API bool operator<(const LengthUnit& other) const;

	/// @brief If the LengthUnit greater than the other LengthUnit
	/// @param other The other LengthUnit to compare with
	/// @return True if the LengthUnit is greater than the other LengthUnit, false otherwise
	AMCAX_API bool operator>(const LengthUnit& other) const;

	/// @brief If the LengthUnit less than or equal to the other LengthUnit
	/// @param other The other LengthUnit to compare with
	/// @return True if the LengthUnit is less than or equal to the other LengthUnit, false otherwise
	AMCAX_API bool operator<=(const LengthUnit& other) const;

	/// @brief If the LengthUnit greater than or equal to the other LengthUnit
	/// @param other The other LengthUnit to compare with
	/// @return True if the LengthUnit is greater than or equal to the other LengthUnit, false otherwise
	AMCAX_API bool operator>=(const LengthUnit& other) const;

	/// @brief Set the unit to be a metric micro meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseMicroMeter();

	/// @brief Set the unit to be a metric milli meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseMilliMeter();

	/// @brief Set the unit to be a metric centi meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseCentiMeter();

	/// @brief Set the unit to be a metric deci meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseDeciMeter();

	/// @brief Set the unit to be a metric meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseMeter();

	/// @brief Set the unit to be a metric deca meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseDecaMeter();

	/// @brief Set the unit to be a metric hecto meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseHectoMeter();

	/// @brief Set the unit to be a metric kilo meter
	/// @return A reference to this
	AMCAX_API LengthUnit& UseKiloMeter();

	/// @brief Set the unit to be a foot
	/// @return A reference to this
	AMCAX_API LengthUnit& UseFoot();

	/// @brief Set the unit to be an inch
	/// @return A reference to this
	AMCAX_API LengthUnit& UseInch();

	/// @brief Set the unit to be a yard
	/// @return A reference to this
	AMCAX_API LengthUnit& UseYard();

	/// @brief Set the unit to be a mile
	/// @return A reference to this
	AMCAX_API LengthUnit& UseMile();
};
} // namespace AMCAX
