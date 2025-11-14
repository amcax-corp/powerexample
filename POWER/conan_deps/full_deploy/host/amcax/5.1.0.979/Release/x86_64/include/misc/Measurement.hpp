/// @file       Measurement.hpp
/// @brief      Class for measurement
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>

#include <misc/SIUnit.hpp>

namespace AMCAX
{
/// @brief Class for measurement
class AMCAX_CLASS_API Measurement
{
protected:
	double _Value{0.0};

	SIUnit _Unit;

public:
	/// @brief Default constructor
	AMCAX_API Measurement();

	/// @brief Construct a new Measurement object with a value and a unit
	/// @param value The value of the measurement
	/// @param unit The unit of the measurement
	AMCAX_API Measurement(const double value, const SIUnit& unit);

	/// @brief Copy constructor
	/// @param other The other Measurement object
	AMCAX_API Measurement(const Measurement& other);

	/// @brief Move constructor
	/// @param other The other Measurement object
	AMCAX_API Measurement(Measurement&& other) noexcept;

	/// @brief Copy assignment operator
	/// @param other The other Measurement object
	/// @return A reference to this
	AMCAX_API Measurement& operator=(const Measurement& other);

	/// @brief Move assignment operator
	/// @param other The other Measurement object
	/// @return A reference to this
	AMCAX_API Measurement& operator=(Measurement&& other) noexcept;

	/// @brief Assign a value to the measurement
	/// @param value The value to assign
	/// @return A reference to this
	AMCAX_API Measurement& operator=(const double value);

	/// @brief Assign a SetUnit to the measurement
	/// @param unit The unit to assign
	/// @return A reference to this
	AMCAX_API Measurement& operator=(const SIUnit& unit);

	/// @brief Destructor
	AMCAX_API virtual ~Measurement();

	/// @brief If the measurement is same as the other measurement
	/// @param other The other measurement
	/// @return True if the measurement is same as the other measurement
	AMCAX_API bool operator==(const Measurement& other) const;

	/// @brief If the measurement is not same as the other measurement
	/// @param other The other measurement
	/// @return True if the measurement is not same as the other measurement
	AMCAX_API bool operator!=(const Measurement& other) const;

	/// @brief If the measurement is less than the other measurement
	/// @param other The other measurement
	/// @return True if the measurement is less than the other measurement
	AMCAX_API bool operator<(const Measurement& other) const;

	/// @brief If the measurement is greater than the other measurement
	/// @param other The other measurement
	/// @return True if the measurement is greater than the other measurement
	AMCAX_API bool operator>(const Measurement& other) const;

	/// @brief If the measurement is less than or equal to the other measurement
	/// @param other The other measurement
	/// @return True if the measurement is less than or equal to the other measurement
	AMCAX_API bool operator<=(const Measurement& other) const;

	/// @brief If the measurement is greater than or equal to the other measurement
	/// @param other The other measurement
	/// @return True if the measurement is greater than or equal to the other measurement
	AMCAX_API bool operator>=(const Measurement& other) const;

	/// @brief Get an immutable reference to the value of the measurement
	/// @return An immutable reference to the value of the measurement
	AMCAX_API const double& GetValue() const;

	/// @brief Get a mutable reference to the value of the measurement
	/// @return A mutable reference to the value of the measurement
	AMCAX_API double& SetValue();

	/// @brief Get an immutable reference to the unit of the measurement
	/// @return An immutable reference to the unit of the measurement
	AMCAX_API const SIUnit& GetUnit() const;

	/// @brief Get a mutable reference to the unit of the measurement
	/// @return A mutable reference to the unit of the measurement
	AMCAX_API SIUnit& SetUnit();
};
} // namespace AMCAX
