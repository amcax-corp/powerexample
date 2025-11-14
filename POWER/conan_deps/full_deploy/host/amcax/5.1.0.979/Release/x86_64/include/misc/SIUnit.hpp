/// @file       SIUnit.hpp
/// @brief      Class for representing SI units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <utility>
#include <variant>
#include <vector>

#include <misc/AmountOfSubstanceUnit.hpp>
#include <misc/ElectricCurrentUnit.hpp>
#include <misc/LengthUnit.hpp>
#include <misc/LuminousIntensityUnit.hpp>
#include <misc/MassUnit.hpp>
#include <misc/ThermodynamicTemperatureUnit.hpp>
#include <misc/TimeUnit.hpp>

namespace AMCAX
{
/// @brief Class for representing SI units
class SIUnit
{
public:
	using UnitUnion = std::variant<
		std::monostate,				  // index 0, a placeholder for none of the below
		LengthUnit,					  // index 1
		MassUnit,					  // index 2
		TimeUnit,					  // index 3
		ElectricCurrentUnit,		  // index 4
		ThermodynamicTemperatureUnit, // index 5
		AmountOfSubstanceUnit,		  // index 6
		LuminousIntensityUnit		  // index 7
		>;

	/// @brief The SetUnit and the exponent
	using UnitExpo = std::pair<UnitUnion, double>;

#ifndef DOXYGEN_SKIP
private:
	LengthUnit _LengthUnit;
	double _LengthExponent{0.0};

	MassUnit _MassUnit;
	double _MassExponent{0.0};

	TimeUnit _TimeUnit;
	double _TimeExponent{0.0};

	ElectricCurrentUnit _ElectricCurrentUnit;
	double _ElectricCurrentExponent{0.0};

	ThermodynamicTemperatureUnit _ThermodynamicTemperatureUnit;
	double _ThermodynamicTemperatureExponent{0.0};

	AmountOfSubstanceUnit _AmountOfSubstanceUnit;
	double _AmountOfSubstanceExponent{0.0};

	LuminousIntensityUnit _LuminousIntensityUnit;
	double _LuminousIntensityExponent{0.0};

private:
	SIUnit& InsertImpl(const UnitUnion& unit, const double& exponent = 1.0);
#endif // !DOXYGEN_SKIP

public:
	/// @brief Default constructor for SIUnit
	AMCAX_API SIUnit();

	/// @brief Copy constructor for SIUnit
	/// @param other The other SIUnit object
	AMCAX_API SIUnit(const SIUnit& other);

	/// @brief Move constructor for SIUnit
	/// @param other The other SIUnit object
	AMCAX_API SIUnit(SIUnit&& other) noexcept;

	/// @brief Constructor for SIUnit with a length unit
	/// @param unit The length unit
	/// @param exponent The exponent of the length unit
	AMCAX_API SIUnit(const LengthUnit& unit, const double exponent = 1.0);

	/// @brief Constructor for SIUnit with a mass unit
	/// @param unit The mass unit
	/// @param exponent The exponent of the mass unit
	AMCAX_API SIUnit(const MassUnit& unit, const double exponent = 1.0);

	/// @brief Constructor for SIUnit with a time unit
	/// @param unit The time unit
	/// @param exponent The exponent of the time unit
	AMCAX_API SIUnit(const TimeUnit& unit, const double exponent = 1.0);

	/// @brief Constructor for SIUnit with a electric current unit
	/// @param unit The electric current unit
	/// @param exponent The exponent of the electric current unit
	AMCAX_API SIUnit(const ElectricCurrentUnit& unit, const double exponent = 1.0);

	/// @brief Constructor for SIUnit with a thermodynamic temperature unit
	/// @param unit The thermodynamic temperature unit
	/// @param exponent The exponent of the thermodynamic temperature unit
	AMCAX_API SIUnit(const ThermodynamicTemperatureUnit& unit, const double exponent = 1.0);

	/// @brief Constructor for SIUnit with a amount of substance unit
	/// @param unit The amount of substance unit
	/// @param exponent The exponent of the amount of substance unit
	AMCAX_API SIUnit(const AmountOfSubstanceUnit& unit, const double exponent = 1.0);

	/// @brief Constructor for SIUnit with a luminous intensity unit
	/// @param unit The luminous intensity unit
	/// @param exponent The exponent of the luminous intensity unit
	AMCAX_API SIUnit(const LuminousIntensityUnit& unit, const double exponent = 1.0);

	/// @brief Copy assignment operator for SIUnit with a length unit
	/// @param other The other LengthUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const LengthUnit& other);

	/// @brief Move assignment operator for SIUnit with a length unit
	/// @param other The other LengthUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(LengthUnit&& other) noexcept;

	/// @brief Copy assignment operator for SIUnit with a mass unit
	/// @param other The other MassUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const MassUnit& other);

	/// @brief Move assignment operator for SIUnit with a mass unit
	/// @param other The other MassUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(MassUnit&& other) noexcept;

	/// @brief Copy assignment operator for SIUnit with a time unit
	/// @param other The other TimeUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const TimeUnit& other);

	/// @brief Move assignment operator for SIUnit with a time unit
	/// @param other The other TimeUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(TimeUnit&& other) noexcept;

	/// @brief Copy assignment operator for SIUnit with a electric current unit
	/// @param other The other ElectricCurrentUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const ElectricCurrentUnit& other);

	/// @brief Move assignment operator for SIUnit with a electric current unit
	/// @param other The other ElectricCurrentUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(ElectricCurrentUnit&& other) noexcept;

	/// @brief Copy assignment operator for SIUnit with a thermodynamic temperature unit
	/// @param other The other ThermodynamicTemperatureUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const ThermodynamicTemperatureUnit& other);

	/// @brief Move assignment operator for SIUnit with a thermodynamic temperature unit
	/// @param other The other ThermodynamicTemperatureUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(ThermodynamicTemperatureUnit&& other) noexcept;

	/// @brief Copy assignment operator for SIUnit with a amount of substance unit
	/// @param other The other AmountOfSubstanceUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const AmountOfSubstanceUnit& other);

	/// @brief Move assignment operator for SIUnit with a amount of substance unit
	/// @param other The other AmountOfSubstanceUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(AmountOfSubstanceUnit&& other) noexcept;

	/// @brief Copy assignment operator for SIUnit with a luminous intensity unit
	/// @param other The other LuminousIntensityUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const LuminousIntensityUnit& other);

	/// @brief Move assignment operator for SIUnit with a luminous intensity unit
	/// @param other The other LuminousIntensityUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(LuminousIntensityUnit&& other) noexcept;

	/// @brief Copy assignment operator for SIUnit
	/// @param other The other SIUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(const SIUnit& other);

	/// @brief Move assignment operator for SIUnit
	/// @param other The other SIUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& operator=(SIUnit&& other) noexcept;

	/// @brief Destructor for SIUnit
	AMCAX_API ~SIUnit();

	/// @brief If the SIUnit same as the other SIUnit
	/// @param other The other SIUnit to compare with
	/// @return True if the SIUnit is the same as the other SIUnit, false otherwise
	AMCAX_API bool operator==(const SIUnit& other) const;

	/// @brief If the SIUnit different from the other SIUnit
	/// @param other The other SIUnit to compare with
	/// @return True if the SIUnit is different from the other SIUnit, false otherwise
	AMCAX_API bool operator!=(const SIUnit& other) const;

	/// @brief If the SIUnit less than the other SIUnit
	/// @param other The other SIUnit to compare with
	/// @return True if the SIUnit is less than the other SIUnit, false otherwise
	AMCAX_API bool operator<(const SIUnit& other) const;

	/// @brief If the SIUnit greater than the other SIUnit
	/// @param other The other SIUnit to compare with
	/// @return True if the SIUnit is greater than the other SIUnit, false otherwise
	AMCAX_API bool operator>(const SIUnit& other) const;

	/// @brief If the SIUnit less than or equal to the other SIUnit
	/// @param other The other SIUnit to compare with
	/// @return True if the SIUnit is less than or equal to the other SIUnit, false otherwise
	AMCAX_API bool operator<=(const SIUnit& other) const;

	/// @brief If the SIUnit greater than or equal to the other SIUnit
	/// @param other The other SIUnit to compare with
	/// @return True if the SIUnit is greater than or equal to the other SIUnit, false otherwise
	AMCAX_API bool operator>=(const SIUnit& other) const;

	/// @brief Insert a base unit into the SI unit
	/// @param unit The base unit to insert
	/// @param exponent The exponent of the base unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& Insert(const UnitUnion& unit, const double& exponent = 1.0);

	/// @brief Inverse the units
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& Inverse();

	/// @brief Clear the units
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& Clear();

	/// @brief Get the units
	/// @return The units
	AMCAX_API std::vector<UnitExpo> Units() const;

	/// @brief Get the LengthUnit object
	/// @return The LengthUnit object
	AMCAX_API const LengthUnit& GetLengthUnit() const;

	/// @brief Set the LengthUnit object
	/// @param lengthUnit The LengthUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetLengthUnit(const AMCAX::LengthUnit& lengthUnit);

	/// @brief Get the exponent of the length unit
	/// @return The exponent of the length unit
	AMCAX_API double GetLengthExponent() const;

	/// @brief Set the exponent of the length unit
	/// @param lengthExponent The exponent of the length unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetLengthExponent(const double& lengthExponent);

	/// @brief Set the LengthUnit object and the exponent of the length unit
	/// @param lengthUnit The LengthUnit object
	/// @param lengthExponent The exponent of the length unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetLengthUnit(const AMCAX::LengthUnit& lengthUnit, const double& lengthExponent);

	/// @brief Get the MassUnit object
	/// @return The MassUnit object
	AMCAX_API const MassUnit& GetMassUnit() const;

	/// @brief Set the MassUnit object
	/// @param massUnit The MassUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetMassUnit(const AMCAX::MassUnit& massUnit);

	/// @brief Get the exponent of the mass unit
	/// @return The exponent of the mass unit
	AMCAX_API double GetMassExponent() const;

	/// @brief Set the exponent of the mass unit
	/// @param massExponent The exponent of the mass unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetMassExponent(const double& massExponent);

	/// @brief Set the MassUnit object and the exponent of the mass unit
	/// @param massUnit The MassUnit object
	/// @param massExponent The exponent of the mass unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetMassUnit(const AMCAX::MassUnit& massUnit, const double& massExponent);

	/// @brief Get the TimeUnit object
	/// @return The TimeUnit object
	AMCAX_API const TimeUnit& GetTimeUnit() const;

	/// @brief Set the TimeUnit object
	/// @param timeUnit The TimeUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetTimeUnit(const AMCAX::TimeUnit& timeUnit);

	/// @brief Get the exponent of the time unit
	/// @return The exponent of the time unit
	AMCAX_API double GetTimeExponent() const;

	/// @brief Set the exponent of the time unit
	/// @param timeExponent The exponent of the time unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetTimeExponent(const double& timeExponent);

	/// @brief Set the TimeUnit object and the exponent of the time unit
	/// @param timeUnit The TimeUnit object
	/// @param timeExponent The exponent of the time unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetTimeUnit(const AMCAX::TimeUnit& timeUnit, const double& timeExponent);

	/// @brief Get the ElectricCurrentUnit object
	/// @return The ElectricCurrentUnit object
	AMCAX_API const ElectricCurrentUnit& GetElectricCurrentUnit() const;

	/// @brief Set the ElectricCurrentUnit object
	/// @param electricCurrentUnit The ElectricCurrentUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetElectricCurrentUnit(const AMCAX::ElectricCurrentUnit& electricCurrentUnit);

	/// @brief Get the exponent of the electric current unit
	/// @return The exponent of the electric current unit
	AMCAX_API double GetElectricCurrentExponent() const;

	/// @brief Set the exponent of the electric current unit
	/// @param electricCurrentExponent The exponent of the electric current unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetElectricCurrentExponent(const double& electricCurrentExponent);

	/// @brief Set the ElectricCurrentUnit object and the exponent of the electric current unit
	/// @param electricCurrentUnit The ElectricCurrentUnit object
	/// @param electricCurrentExponent The exponent of the electric current unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetElectricCurrentUnit(const AMCAX::ElectricCurrentUnit& electricCurrentUnit, const double& electricCurrentExponent);

	/// @brief Get the ThermodynamicTemperatureUnit object
	/// @return The ThermodynamicTemperatureUnit object
	AMCAX_API const ThermodynamicTemperatureUnit& GetThermodynamicTemperatureUnit() const;

	/// @brief Set the ThermodynamicTemperatureUnit object
	/// @param thermodynamicTemperatureUnit The ThermodynamicTemperatureUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetThermodynamicTemperatureUnit(const AMCAX::ThermodynamicTemperatureUnit& thermodynamicTemperatureUnit);

	/// @brief Get the exponent of the thermodynamic temperature unit
	/// @return The exponent of the thermodynamic temperature unit
	AMCAX_API double GetThermodynamicTemperatureExponent() const;

	/// @brief Set the exponent of the thermodynamic temperature unit
	/// @param thermodynamicTemperatureExponent The exponent of the thermodynamic temperature unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetThermodynamicTemperatureExponent(const double& thermodynamicTemperatureExponent);

	/// @brief Set the ThermodynamicTemperatureUnit object and the exponent of the thermodynamic temperature unit
	/// @param thermodynamicTemperatureUnit The ThermodynamicTemperatureUnit object
	/// @param thermodynamicTemperatureExponent The exponent of the thermodynamic temperature unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetThermodynamicTemperatureUnit(const AMCAX::ThermodynamicTemperatureUnit& thermodynamicTemperatureUnit, const double& thermodynamicTemperatureExponent);

	/// @brief Get the AmountOfSubstanceUnit object
	/// @return The AmountOfSubstanceUnit object
	AMCAX_API const AmountOfSubstanceUnit& GetAmountOfSubstanceUnit() const;

	/// @brief Set the AmountOfSubstanceUnit object
	/// @param amountOfSubstanceUnit The AmountOfSubstanceUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetAmountOfSubstanceUnit(const AMCAX::AmountOfSubstanceUnit& amountOfSubstanceUnit);

	/// @brief Get the exponent of the amount of substance unit
	/// @return The exponent of the amount of substance unit
	AMCAX_API double GetAmountOfSubstanceExponent() const;

	/// @brief Set the exponent of the amount of substance unit
	/// @param amountOfSubstanceExponent The exponent of the amount of substance unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetAmountOfSubstanceExponent(const double& amountOfSubstanceExponent);

	/// @brief Set the AmountOfSubstanceUnit object and the exponent of the amount of substance unit
	/// @param amountOfSubstanceUnit The AmountOfSubstanceUnit object
	/// @param amountOfSubstanceExponent The exponent of the amount of substance unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetAmountOfSubstanceUnit(const AMCAX::AmountOfSubstanceUnit& amountOfSubstanceUnit, const double& amountOfSubstanceExponent);

	/// @brief Get the LuminousIntensityUnit object
	/// @return The LuminousIntensityUnit object
	AMCAX_API const LuminousIntensityUnit& GetLuminousIntensityUnit() const;

	/// @brief Set the LuminousIntensityUnit object
	/// @param luminousIntensityUnit The LuminousIntensityUnit object
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetLuminousIntensityUnit(const AMCAX::LuminousIntensityUnit& luminousIntensityUnit);

	/// @brief Get the exponent of the luminous intensity unit
	/// @return The exponent of the luminous intensity unit
	AMCAX_API double GetLuminousIntensityExponent() const;

	/// @brief Set the exponent of the luminous intensity unit
	/// @param luminousIntensityExponent The exponent of the luminous intensity unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetLuminousIntensityExponent(const double& luminousIntensityExponent);

	/// @brief Set the LuminousIntensityUnit object and the exponent of the luminous intensity unit
	/// @param luminousIntensityUnit The LuminousIntensityUnit object
	/// @param amountOfSubstanceExponent The exponent of the luminous intensity unit
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& SetLuminousIntensityUnit(const AMCAX::LuminousIntensityUnit& luminousIntensityUnit, const double& luminousIntensityExponent);

	/// @brief If this unit is a base unit
	/// @return True if this unit is a base unit, false otherwise
	AMCAX_API bool IsBaseUnit() const;

	/// @brief If this unit is a derived unit
	/// @return True if this unit is a derived unit, false otherwise
	AMCAX_API bool IsDerivedUnit() const;

	/// @brief Setup the derived unit as meter
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIMeter(const bool denominator = false);

	/// @brief Dertermain if the unit is a length unit
	/// @return True if the unit is a length unit, false otherwise
	AMCAX_API bool IsLengthUnit() const;

	/// @brief Setup the derived unit as kilogram
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIKilogram(const bool denominator = false);

	/// @brief Dertermain if the unit is a mass unit
	/// @return True if the unit is a mass unit, false otherwise
	AMCAX_API bool IsMassUnit() const;

	/// @brief Setup the derived unit as second
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSISecond(const bool denominator = false);

	/// @brief Dertermain if the unit is a time unit
	/// @return True if the unit is a time unit, false otherwise
	AMCAX_API bool IsTimeUnit() const;

	/// @brief Setup the derived unit as ampere
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIAmpere(const bool denominator = false);

	/// @brief Dertermain if the unit is a electric current unit
	/// @return True if the unit is a electric current unit, false otherwise
	AMCAX_API bool IsElectricCurrentUnit() const;

	/// @brief Setup the derived unit as kelvin
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIKelvin(const bool denominator = false);

	/// @brief Dertermain if the unit is a thermodynamic temperature unit
	/// @return True if the unit is a thermodynamic temperature unit, false otherwise
	AMCAX_API bool IsThermodynamicTemperatureUnit() const;

	/// @brief Setup the derived unit as mole
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIMole(const bool denominator = false);

	/// @brief Dertermain if the unit is a amount of substance unit
	/// @return True if the unit is a amount of substance unit, false otherwise
	AMCAX_API bool IsAmountOfSubstanceUnit() const;

	/// @brief Setup the derived unit as candela
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSICandela(const bool denominator = false);

	/// @brief Dertermain if the unit is a luminous intensity unit
	/// @return True if the unit is a luminous intensity unit, false otherwise
	AMCAX_API bool IsLuminousIntensityUnit() const;

	/// @brief Setup the derived unit as hertz
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIHertz(const bool denominator = false);

	/// @brief Dertermain if the unit is a frequency unit
	/// @return True if the unit is a frequency unit, false otherwise
	AMCAX_API bool IsFrequencyUnit() const;

	/// @brief Setup the derived unit as radian
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIRadian(const bool denominator = false);

	/// @brief Dertermain if the unit is a angle unit
	/// @return True if the unit is a angle unit, false otherwise
	AMCAX_API bool IsAngleUnit() const;

	/// @brief Setup the derived unit as steradian
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSISteradian(const bool denominator = false);

	/// @brief Dertermain if the unit is a solid angle unit
	/// @return True if the unit is a solid angle unit, false otherwise
	AMCAX_API bool IsSolidAngleUnit() const;

	/// @brief Setup the derived unit as newton
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSINewton(const bool denominator = false);

	/// @brief Dertermain if the unit is a force unit
	/// @return True if the unit is a force unit, false otherwise
	AMCAX_API bool IsForceUnit() const;

	/// @brief Setup the derived unit as pascal
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIPascal(const bool denominator = false);

	/// @brief Dertermain if the unit is a pressure unit
	/// @return True if the unit is a pressure unit, false otherwise
	AMCAX_API bool IsPressureUnit() const;

	/// @brief Setup the derived unit as joule
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIJoule(const bool denominator = false);

	/// @brief Determain if the unit is a energy unit
	/// @return True if the unit is a energy unit, false otherwise
	AMCAX_API bool IsEnergyUnit() const;

	/// @brief Setup the derived unit as watt
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIWatt(const bool denominator = false);

	/// @brief Determain if the unit is a power unit
	/// @return True if the unit is a power unit, false otherwise
	AMCAX_API bool IsPowerUnit() const;

	/// @brief Setup the derived unit as coulomb
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSICoulomb(const bool denominator = false);

	/// @brief Determain if the unit is a electric charge unit
	/// @return True if the unit is a electric charge unit, false otherwise
	AMCAX_API bool IsElectricChargeUnit() const;

	/// @brief Setup the derived unit as volt
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIVolt(const bool denominator = false);

	/// @brief Determain if the unit is a electric potential unit
	/// @return True if the unit is a electric potential unit, false otherwise
	AMCAX_API bool IsElectricPotentialUnit() const;

	/// @brief Setup the derived unit as farad
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIFarad(const bool denominator = false);

	/// @brief Determain if the unit is a electric capacitance unit
	/// @return True if the unit is a electric capacitance unit, false otherwise
	AMCAX_API bool IsCapacitanceUnit() const;

	/// @brief Setup the derived unit as ohm
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIOhm(const bool denominator = false);

	/// @brief Determain if the unit is a electric resistance unit
	/// @return True if the unit is a electric resistance unit, false otherwise
	AMCAX_API bool IsResistanceUnit() const;

	/// @brief Setup the derived unit as siemens
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSISiemens(const bool denominator = false);

	/// @brief Determain if the unit is a electric conductance unit
	/// @return True if the unit is a electric conductance unit, false otherwise
	AMCAX_API bool IsElectricConductanceUnit() const;

	/// @brief Setup the derived unit as weber
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIWeber(const bool denominator = false);

	/// @brief Determain if the unit is a magnetic flux unit
	/// @return True if the unit is a magnetic flux unit, false otherwise
	AMCAX_API bool IsMagneticFluxUnit() const;

	/// @brief Setup the derived unit as tesla
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSITesla(const bool denominator = false);

	/// @brief Determain if the unit is a magnetic flux density unit
	/// @return True if the unit is a magnetic flux density unit, false otherwise
	AMCAX_API bool IsMagneticFluxDensityUnit() const;

	/// @brief Setup the derived unit as henry
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIHenry(const bool denominator = false);

	/// @brief Determain if the unit is an electrical inductance unit
	/// @return True if the unit is an electrical inductance unit, false otherwise
	AMCAX_API bool IsInductanceUnit() const;

	/// @brief Setup the derived unit as degree celsius
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIDegreeCelsius(const bool denominator = false);

	/// @brief Determain if the unit is a temperature unit
	/// @return True if the unit is a temperature unit, false otherwise
	AMCAX_API bool IsTemperatureUnit() const;

	/// @brief Setup the derived unit as lumen
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSILumen(const bool denominator = false);

	/// @brief Determain if the unit is a luminous flux unit
	/// @return True if the unit is a luminous flux unit, false otherwise
	AMCAX_API bool IsLuminousFluxUnit() const;

	/// @brief Setup the derived unit as lux
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSILux(const bool denominator = false);

	/// @brief Determain if the unit is a illuminance unit
	/// @return True if the unit is a illuminance unit, false otherwise
	AMCAX_API bool IsIlluminanceUnit() const;

	/// @brief Setup the derived unit as becquerel
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIBecquerel(const bool denominator = false);

	/// @brief Determain if the unit is a radioactivity decay unit
	/// @return True if the unit is a radioactivity decay unit, false otherwise
	AMCAX_API bool IsRadioactivityDecayUnit() const;

	/// @brief Setup the derived unit as gray
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIGray(const bool denominator = false);

	/// @brief Determain if the unit is a absorbed dose unit
	/// @return True if the unit is a absorbed dose unit, false otherwise
	AMCAX_API bool IsAbsorbedDoseUnit() const;

	/// @brief Setup the derived unit as sievert
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSISievert(const bool denominator = false);

	/// @brief Determain if the unit is a equivalent dose unit
	/// @return True if the unit is a equivalent dose unit, false otherwise
	AMCAX_API bool IsEquivalentDoseUnit() const;

	/// @brief Setup the derived unit as katal
	/// @param denominator If the unit is added as a denominator
	/// @return A reference to current SIUnit
	AMCAX_API SIUnit& AddSIKatal(const bool denominator = false);

	/// @brief Determain if the unit is a catalytic activity unit
	/// @return True if the unit is a catalytic activity unit, false otherwise
	AMCAX_API bool IsCatalyticActivityUnit() const;
};

} // namespace AMCAX
