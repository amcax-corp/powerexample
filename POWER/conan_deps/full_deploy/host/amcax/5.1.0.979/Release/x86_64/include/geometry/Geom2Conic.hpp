/// @file      Geom2Conic.hpp
/// @brief     Base class of 2D conic curve
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <geometry/Geom2Curve.hpp>

namespace AMCAX
{
/// @brief Base class of 2D conic curve
class AMCAX_CLASS_API Geom2Conic : public Geom2Curve
{
public:
	/// @brief Set the local frame
	/// @param frame The local frame
	AMCAX_API void SetPosition(const Frame2& frame) noexcept;

	/// @brief Set the x axis
	/// @param axis The x axis
	AMCAX_API void SetXAxis(const Axis2& axis) noexcept;

	/// @brief Set the y axis
	/// @param axis The y axis
	AMCAX_API void SetYAxis(const Axis2& axis) noexcept;

	/// @brief Set the location point
	/// @param point The location point
	AMCAX_API void SetLocation(const Point2& point) noexcept;

	/// @brief Get the x axis
	/// @return The x axis
	[[nodiscard]] AMCAX_API Axis2 XAxis() const noexcept;

	/// @brief Get the y axis
	/// @return The y axis
	[[nodiscard]] AMCAX_API Axis2 YAxis() const noexcept;

	/// @brief Get the eccentricity
	/// @return The eccentricity
	[[nodiscard]] AMCAX_API virtual double Eccentricity() const = 0;

	/// @brief Get the location point
	/// @return The location point
	[[nodiscard]] AMCAX_API const Point2& Location() const noexcept;

	/// @brief Get the local frame
	/// @return The local frame
	[[nodiscard]] AMCAX_API const Frame2& Position() const noexcept;

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
	constexpr Geom2Conic() noexcept = default;

	/// @brief Construct from a local frame
	/// @param frame The local frame
	explicit Geom2Conic(const Frame2& frame) noexcept;

	/// @brief Construct from an axis
	/// @param axis The axis
	/// @param isRight Is the frame right-handed
	explicit Geom2Conic(const Axis2& axis, bool isRight = true) noexcept;

	/// @brief Local coordinate system
	Frame2 pos;
};
} // namespace AMCAX
