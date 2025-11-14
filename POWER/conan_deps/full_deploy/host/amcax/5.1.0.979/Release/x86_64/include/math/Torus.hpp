/// @file      Torus.hpp
/// @brief     Class of torus
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/SurfaceBase.hpp>

namespace AMCAX
{
/// @brief Class of torus
class Torus : public SurfaceBase<Torus>
{
	using Base = SurfaceBase<Torus>;

protected:
	using Base::pos;

public:
	/// @brief Default constructor
	constexpr Torus() noexcept = default;

	/// @brief Construct from a local frame, a major and a minor radius
	/// @param frame The local frame
	/// @param major The major radius
	/// @param minor The minor radius
	AMCAX_API Torus(const Frame3& frame, double major, double minor);

	/// @brief Set the major radius
	/// @param r The major radius
	AMCAX_API void SetMajorRadius(double r);

	/// @brief Set the minor radius
	/// @param r The minor radius
	AMCAX_API void SetMinorRadius(double r);

	/// @brief Reverse the u parameter
	AMCAX_API void UReverse() noexcept;

	/// @brief Reverse the v parameter
	AMCAX_API void VReverse() noexcept;

	/// @brief Get the area of the torus
	/// @return The area of the torus
	[[nodiscard]] AMCAX_API double Area() const noexcept;

	/// @brief Get the coefficients of the algebraic representation of the torus
	/// @details The algebraic representation of the torus is
	/// @code
	///     coeff[0]  * x^4    + coeff[1]  * y^4    + coeff[2]  * z^4    +
	///     coeff[3]  * x^3y   + coeff[4]  * x^3z   + coeff[5]  * xy^3   +
	///     coeff[6]  * y^3z   + coeff[7]  * xz^3   + coeff[8]  * yz^3   +
	///     coeff[9]  * x^2y^2 + coeff[10] * x^2z^2 + coeff[11] * y^2z^2 +
	///     coeff[12] * x^2yz  + coeff[13] * xy^2z  + coeff[14] * xyz^2  +
	///     coeff[15] * x^3    + coeff[16] * y^3    + coeff[17] * z^3    +
	///     coeff[18] * x^2y   + coeff[19] * x^2z   + coeff[20] * xy^2   +
	///     coeff[21] * y^2z   + coeff[22] * xz^2   + coeff[23] * yz^2   +
	///     coeff[24] * xyz    +
	///     coeff[25] * x^2    + coeff[26] * y^2    + coeff[27] * z^2    +
	///     coeff[28] * xy     + coeff[29] * xz     + coeff[30] * yz     +
	///     coeff[31] * x      + coeff[32] * y      + coeff[33] * z      +
	///     coeff[34] = 0.0
	/// @endcode
	/// @param[out] coeff The coefficients
	AMCAX_API void Coefficients(std::array<double, 35>& coeff) const noexcept;

	/// @brief Get the major radius
	/// @return The major radius
	[[nodiscard]] AMCAX_API double MajorRadius() const noexcept;

	/// @brief Get the minor radius
	/// @return The minor radius
	[[nodiscard]] AMCAX_API double MinorRadius() const noexcept;

	/// @brief Get the volume of the torus
	/// @return The volume of the torus
	[[nodiscard]] AMCAX_API double Volume() const noexcept;

	/// @brief Scale the torus by a point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	AMCAX_API Torus& Scale(const Point3& point, double scale) noexcept;

	/// @brief Transform the torus
	/// @param tr The transformation
	/// @return The reference to self
	AMCAX_API Torus& Transform(const Transformation3& tr) noexcept;

protected:
	/// @brief Check the validity of torus
	void CheckValidity() const;

	/// @brief The major radius of torus
	double majorRadius = std::numeric_limits<double>::max();

	/// @brief The minor radius of torus
	double minorRadius = std::numeric_limits<double>::min();
};
} // namespace AMCAX
