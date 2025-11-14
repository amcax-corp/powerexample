/// @file       AbstractUnit.hpp
/// @brief      Class for SI Base Units
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

namespace AMCAX
{
/// @brief The unit prefixes
enum class UnitPrefix
{
	QUECTO = -30,
	RONTO = -27,
	YOCTO = -24,
	ZEPTO = -21,
	ATTO = -18,
	FEMTO = -15,
	PICO = -12,
	NANO = -9,
	MICRO = -6,
	MILLI = -3,
	CENTI = -2,
	DECI = -1,
	NONE = 0,
	DECA = 1,
	HECTO = 2,
	KILO = 3,
	MEGA = 6,
	GIGA = 9,
	TERA = 12,
	PETA = 15,
	EXA = 18,
	ZETTA = 21,
	YOTTA = 24,
	RONNA = 27,
	QUETTA = 30,
};

/// @brief Class for SI Base Units
class AMCAX_CLASS_API AbstractUnit
{
public:
	/// @brief Get an immutable reference to the prefix of the unit
	/// @return An immutable reference to the prefix of the unit
	AMCAX_API const UnitPrefix& GetPrefix() const;

	/// @brief Get the derived prefix of the unit
	/// @return The derived prefix of the unit
	AMCAX_API const double& GetMultiplication() const;

	/// @brief Compute a value in current unit to a value in base unit.
	/// @param value The value in current unit.
	/// @return The value in base unit.
	AMCAX_API virtual double ToBase(const double value = 1.0) const;

	/// @brief If the AbstractUnit object same as the other AbstractUnit object within a tolerance
	/// @param other The other AbstractUnit object
	/// @param tol The tolerance to compare with
	/// @return True if the AbstractUnit object is the same as the other AbstractUnit object, false otherwise
	AMCAX_API bool IsEqual(const AbstractUnit& other, const double tol = 1E-12) const;

	/// @brief If the AbstractUnit object same as the other AbstractUnit object within the epsilon
	/// @param other The other AbstractUnit object
	/// @return True if the AbstractUnit object is the same as the other AbstractUnit object, false otherwise
	AMCAX_API bool IsEqualE(const AbstractUnit& other) const;

#ifndef DOXYGEN_SKIP
protected:
	AbstractUnit& SetPrefix(const UnitPrefix prefix);

	AbstractUnit& SetMultiplication(const double mul);

	bool operator==(const AbstractUnit& other) const;
	bool operator!=(const AbstractUnit& other) const;
	bool operator<(const AbstractUnit& other) const;
	bool operator>(const AbstractUnit& other) const;
	bool operator<=(const AbstractUnit& other) const;
	bool operator>=(const AbstractUnit& other) const;

	UnitPrefix _Prefix = UnitPrefix::NONE;

	double _Multiplication = 1.0;

	AbstractUnit();

	virtual ~AbstractUnit();

	AbstractUnit(const UnitPrefix& prefix);

	AbstractUnit(const double& multiplication);

	AbstractUnit(const AbstractUnit& unit);

	AbstractUnit& operator=(const AbstractUnit& unit);

	AbstractUnit(const AbstractUnit&& unit) noexcept;

	AbstractUnit& operator=(const AbstractUnit&& unit) noexcept;
#endif // !DOXYGEN_SKIP
};
} // namespace AMCAX
