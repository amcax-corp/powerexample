/// @file      Geom3ElementarySurface.hpp
/// @brief     Base class of 3D elementary surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/Geom3Surface.hpp>

namespace AMCAX
{
/// @brief Base class of 3D elementary surface
/// @details The types of elementary surfaces include plane, cylindrical surface, conical surface, spherical surface, and toroidal surface.
///          The elementary surfaces share a common geometric property, a local frame.
///          The z-axis is called a main axis, which represents a rotational axis of symmetry.
class AMCAX_CLASS_API Geom3ElementarySurface : public Geom3Surface
{
public:
	/// @brief Set the main axis (z-axis of the local frame)
	/// @param axis The main axis
	AMCAX_API void SetAxis(const Axis3& axis) noexcept;

	/// @brief Set the location point
	/// @param point The location point
	AMCAX_API void SetLocation(const Point3& point) noexcept;

	/// @brief Set the local frame
	/// @param frame The local frame
	AMCAX_API void SetPosition(const Frame3& frame) noexcept;

	/// @brief Get the main axis (z-axis of the local frame)
	/// @return The main axis
	[[nodiscard]] AMCAX_API Axis3 Axis() const noexcept;

	/// @brief Get the location point
	/// @return The location point
	[[nodiscard]] AMCAX_API const Point3& Location() const noexcept;

	/// @brief Get the local frame
	/// @return The local frame
	[[nodiscard]] AMCAX_API const Frame3& Position() const noexcept;

	AMCAX_API void UReverse() noexcept override;
	AMCAX_API void VReverse() noexcept override;

	/// @brief Get the continuity of the elementary surface
	/// @return CN continuity
	[[nodiscard]] AMCAX_API ContinuityType Continuity() const noexcept override;

	/// @brief Is the elementary surface has an order n of continuity along the u direction
	/// @param n The order of continuity
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsCNu(int n) const noexcept override;

	/// @brief Is the elementary surface has an order n of continuity along the v direction
	/// @param n The order of continuity
	/// @return Always true
	[[nodiscard]] AMCAX_API bool IsCNv(int n) const noexcept override;

protected:
	/// @brief Default constructor
	constexpr Geom3ElementarySurface() noexcept = default;

	/// @brief Construct from a local frame
	/// @param frame The local frame
	explicit Geom3ElementarySurface(const Frame3& frame) noexcept;

	/// @brief Local coordinate system
	Frame3 pos;
};
} // namespace AMCAX
