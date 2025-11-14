/// @file      Cone.hpp
/// @brief     Class of cone
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/SurfaceBase.hpp>

namespace AMCAX
{
/// @brief Class of cone
class Cone : public SurfaceBase<Cone>
{
	using Base = SurfaceBase<Cone>;

protected:
	using Base::pos;

public:
	/// @brief Default constructor
	constexpr Cone() noexcept = default;

	/// @brief Construct from a local frame, a reference radius and a semi-angle
	/// @param frame The local frame
	/// @param r The reference radius
	/// @param angle The semi-angle
	AMCAX_API Cone(const Frame3& frame, double r, double angle);

	/// @brief Set the reference radius
	/// @param r The reference radius
	AMCAX_API void SetRadius(double r);

	/// @brief Set the semi-angle
	/// @param angle The semi-angle
	AMCAX_API void SetSemiAngle(double angle);

	/// @brief Get the apex of the cone
	/// @return The apex point
	[[nodiscard]] AMCAX_API Point3 Apex() const noexcept;

	/// @brief Reverse the u parameter
	AMCAX_API void UReverse() noexcept;

	/// @brief Reverse the v parameter
	AMCAX_API void VReverse() noexcept;

	/// @brief Get the coefficients of the algebraic representation of the cone
	/// @details The algebraic representation of the cone is a_1 x^2 + a_2 y^2 + a_3 z^2 + 2 (b_1 xy + b_2 xz + b_3 yz) + 2 (c_1 x + c_2 y + c_3 z) + d = 0
	/// @param[out] a1,a2,a3,b1,b2,b3,c1,c2,c3,d The coefficients
	AMCAX_API void Coefficients(double& a1, double& a2, double& a3, double& b1, double& b2, double& b3, double& c1, double& c2, double& c3, double& d) const noexcept;

	/// @brief Get the reference radius
	/// @return The reference radius
	[[nodiscard]] AMCAX_API double Radius() const noexcept;

	/// @brief Get the semi-angle
	/// @return The semi-angle
	[[nodiscard]] AMCAX_API double SemiAngle() const noexcept;

	/// @brief Scale the cone by a point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	AMCAX_API Cone& Scale(const Point3& point, double scale) noexcept;

	/// @brief Transform the cone
	/// @param tr The transformation
	/// @return The reference to self
	AMCAX_API Cone& Transform(const Transformation3& tr) noexcept;

protected:
	/// @brief Check the validity of cone
	void CheckValidity() const;

	/// @brief The reference radius, i.e. the radius of the cross section of the cone and local XOY plane
	double radius = std::numeric_limits<double>::max();

	/// @brief The semi-angle of cone
	double semiAngle = Constants::quarter_pi;
};
} // namespace AMCAX
