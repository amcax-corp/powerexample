/// @file      Geom3Conic.hpp
/// @brief     Base class of 3D conic curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Curve.hpp>

namespace AMCAX
{
/// @brief Base class of 3D conic curve
class AMCAX_CLASS_API Geom3Conic : public Geom3Curve
{
public:
	/// @brief Set the normal axis
	/// @param axis The normal axis
	AMCAX_API void SetAxis(const Axis3& axis) noexcept;

	/// @brief Set the location point
	/// @param point The location point
	AMCAX_API void SetLocation(const Point3& point) noexcept;

	/// @brief Set the local frame
	/// @param frame The local frame
	AMCAX_API void SetPosition(const Frame3& frame) noexcept;

	/// @brief Get the x axis
	/// @return The x axis
	[[nodiscard]] AMCAX_API Axis3 XAxis() const noexcept;

	/// @brief Get the y axis
	/// @return The y axis
	[[nodiscard]] AMCAX_API Axis3 YAxis() const noexcept;

	/// @brief Get the eccentricity
	/// @return The eccentricity
	[[nodiscard]] AMCAX_API virtual double Eccentricity() const = 0;

	/// @brief Get the normal axis
	/// @return The normal axis
	[[nodiscard]] AMCAX_API Axis3 Axis() const noexcept;

	/// @brief Get the location point
	/// @return The location point
	[[nodiscard]] AMCAX_API const Point3& Location() const noexcept;

	/// @brief Get the local frame
	/// @return The local frame
	[[nodiscard]] AMCAX_API const Frame3& Position() const noexcept;

	AMCAX_API void Reverse() noexcept override;

	/// @brief Get the type of continuity
	/// @return Always CN continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the curve has an order n of continuity
	/// @param n The order of continuity
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsCN(int n) const noexcept override;

protected:
	/// @brief Default constructor
	constexpr Geom3Conic() noexcept = default;

	/// @brief Construct from a local frame
	/// @param frame The local frame
	explicit Geom3Conic(const Frame3& frame) noexcept;

	/// @brief Local coordinate system of curve
	Frame3 pos;
};
} // namespace AMCAX
