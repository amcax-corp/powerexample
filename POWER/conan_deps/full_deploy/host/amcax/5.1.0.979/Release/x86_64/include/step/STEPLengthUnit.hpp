/// @file       STEPLengthUnit.hpp
/// @brief		Length unit used by AMCAX::STEP::STEPReader and AMCAX::STEP::STEPWriter.
/// @copyright  Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par        This file is part of AMCAX Kernel.
#pragma once

namespace AMCAX::STEP
{
/// @brief Length unit used by AMCAX::STEP::STEPReader and AMCAX::STEP::STEPWriter.
class STEPLengthUnit
{
public:
	/// @brief Predefined length units and scale factors relative to millimetres.
	struct Presets
	{
		// Standard SI length units, expressed as scale factors relative to millimetres.
		constexpr static double EXAMETRE = 1E+21;
		constexpr static double PETAMETRE = 1E+18;
		constexpr static double TERAMETRE = 1E+15;
		constexpr static double GIGAMETRE = 1E+12;
		constexpr static double MEGAMETRE = 1E+9;
		constexpr static double KILOMETRE = 1E+6;
		constexpr static double METRE = 1E+3;
		constexpr static double DECIMETRE = 1E+2;
		constexpr static double CENTIMETRE = 1E+1;
		constexpr static double MILLIMETRE = 1E0;
		constexpr static double MICROMETRE = 1E-3;
		constexpr static double NANOMETRE = 1E-6;
		constexpr static double PICOMETRE = 1E-9;
		constexpr static double FEMTOMETRE = 1E-12;
		constexpr static double ATTOMETRE = 1E-15;

		// Conversions to common imperial units.
		constexpr static double INCH = MILLIMETRE * 25.4;
		constexpr static double FOOT = INCH * 12.0;

		// Special value: no scaling (identity, not a valid physical unit).
		constexpr static double NOSCALE = 0.0;
	};

public:
	/// @brief Construct a STEPLengthUnit with a given scale factor.
	/// @details The factor represents the conversion from the target unit to millimetres.
	/// Use @ref Presets for predefined constants.
	/// @param length_factor Scale factor from the target length unit to millimetres.
	STEPLengthUnit(const double& length_factor = Presets::MILLIMETRE)
		: length_factor(length_factor)
	{
	}

	/// @brief Default destructor.
	~STEPLengthUnit() = default;

	/// @brief Implicit conversion to the underlying scale factor.
	/// @return Scale factor from the target unit to millimetres.
	operator double() const
	{
		return length_factor;
	}

private:
	double length_factor;
};

} // namespace AMCAX::STEP
