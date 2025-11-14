/// @file      Cylinder.hpp
/// @brief     Class of cylinder
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/SurfaceBase.hpp>

namespace AMCAX
{
/// @brief Class of cylinder
class Cylinder : public SurfaceBase<Cylinder>
{
	using Base = SurfaceBase<Cylinder>;

protected:
	using Base::pos;

public:
	/// @brief Default constructor
	constexpr Cylinder() noexcept = default;

	/// @brief Construct from a local frame and a radius
	/// @param frame The local frame
	/// @param r The radius
	AMCAX_API Cylinder(const Frame3& frame, double r);

	/// @brief Set the radius
	/// @param r The radius
	AMCAX_API void SetRadius(double r);

	/// @brief Reverse the u parameter
	AMCAX_API void UReverse() noexcept;

	/// @brief Reverse the v parameter
	AMCAX_API void VReverse() noexcept;

	/// @brief Get the coefficients of the algebraic representation of the cylinder
	/// @details The algebraic representation of the cylinder is a_1 x^2 + a_2 y^2 + a_3 z^2 + 2 (b_1 xy + b_2 xz + b_3 yz) + 2 (c_1 x + c_2 y + c_3 z) + d = 0
	/// @param[out] a1,a2,a3,b1,b2,b3,c1,c2,c3,d The coefficients
	AMCAX_API void Coefficients(double& a1, double& a2, double& a3, double& b1, double& b2, double& b3, double& c1, double& c2, double& c3, double& d) const noexcept;

	/// @brief Get the radius
	/// @return The radius
	[[nodiscard]] AMCAX_API double Radius() const noexcept;

	/// @brief Scale the cylinder by a point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	AMCAX_API Cylinder& Scale(const Point3& point, double scale) noexcept;

	/// @brief Transform the cylinder
	/// @param tr The transformation
	/// @return The reference to self
	AMCAX_API Cylinder& Transform(const Transformation3& tr) noexcept;

protected:
	/// @brief Check the validity of cylinder
	void CheckValidity() const;

	/// @brief The radius of cylinder
	double radius = std::numeric_limits<double>::max();
};
} // namespace AMCAX
