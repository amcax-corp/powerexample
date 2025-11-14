/// @file      SurfaceBase.hpp
/// @brief     Base class of elementary surfaces
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/AxisT.hpp>
#include <common/FrameT.hpp>
#include <common/TransformationT.hpp>
#include <common/VectorT.hpp>

namespace AMCAX
{
/// @brief Base class of elementary surfaces
/// @tparam Derived Type of derived class
template<typename Derived>
class SurfaceBase
{
public:
	/// @brief Set the location
	/// @param p The new location point
	constexpr void SetLocation(const Point3& p) noexcept
	{
		pos.SetLocation(p);
	}

	/// @brief Set the local frame
	/// @param frame The local frame
	constexpr void SetPosition(const Frame3& frame) noexcept
	{
		pos = frame;
	}

	/// @brief Set the main axis (normal axis) of the local frame in 3D
	/// @param axis The main axis
	void SetAxis(const Axis3& axis) noexcept
	{
		pos.SetAxis(axis);
	}

	/// @brief Get the main axis (normal axis)
	/// @return The main axis
	[[nodiscard]] constexpr Axis3 Axis() const noexcept
	{
		return pos.Axis();
	}

	/// @brief Get the location point
	/// @return The location point
	[[nodiscard]] constexpr const Point3& Location() const noexcept
	{
		return pos.Location();
	}

	/// @brief Get the local frame
	/// @return The local frame
	[[nodiscard]] constexpr const Frame3& Position() const noexcept
	{
		return pos;
	}

	/// @brief Get the x axis
	/// @return The x axis
	[[nodiscard]] constexpr Axis3 XAxis() const noexcept
	{
		return pos.XAxis();
	}

	/// @brief Get the y axis
	/// @return The y axis
	[[nodiscard]] constexpr Axis3 YAxis() const noexcept
	{
		return pos.YAxis();
	}

	/// @brief Determine whether the local frame is right-handed or not
	/// @return True if the local frame is right-handed
	[[nodiscard]] constexpr bool IsDirect() const noexcept
	{
		return pos.IsDirect();
	}

	/// @brief Mirror the surface by a point
	/// @param p The mirror center point
	/// @return The reference to self
	constexpr Derived& Mirror(const Point3& p) noexcept
	{
		pos.Mirror(p);
		return _derived();
	}

	/// @brief Get the surface mirrored by a point
	/// @param p The mirror center point
	/// @return The mirrored surface
	[[nodiscard]] constexpr Derived Mirrored(const Point3& p) const noexcept
	{
		return Derived(_derived()).Mirror(p);
	}

	/// @brief Mirror the surface by an axis
	/// @param axis The mirror axis
	/// @return The reference to self
	constexpr Derived& Mirror(const Axis3& axis) noexcept
	{
		pos.Mirror(axis);
		return _derived();
	}

	/// @brief Get the surface mirrored by an axis
	/// @param axis The mirror axis
	/// @return The mirrored surface
	[[nodiscard]] constexpr Derived Mirrored(const Axis3& axis) const noexcept
	{
		return Derived(_derived()).Mirror(axis);
	}

	/// @brief Mirror the surface by a frame
	/// @param frame The mirror frame
	/// @return The reference to self
	constexpr Derived& Mirror(const Frame3& frame) noexcept
	{
		pos.Mirror(frame);
		return _derived();
	}

	/// @brief Get the surface mirrored by a frame
	/// @param frame The mirror frame
	/// @return The mirrored surface
	[[nodiscard]] constexpr Derived Mirrored(const Frame3& frame) const noexcept
	{
		return Derived(_derived()).Mirror(frame);
	}

	/// @brief Rotate the surface around an axis with an angle in 3D
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	Derived& Rotate(const Axis3& axis, double angle) noexcept
	{
		pos.Rotate(axis, angle);
		return _derived();
	}

	/// @brief Get the surface rotated around an axis with an angle in 3D
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated surface
	[[nodiscard]] Derived Rotated(const Axis3& axis, double angle) const noexcept
	{
		return Derived(_derived()).Rotate(axis, angle);
	}

	/// @brief Scale the surface by a center point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	constexpr Derived& Scale(const Point3& point, double scale) noexcept
	{
		pos.Scale(point, scale);
		return _derived();
	}

	/// @brief Get the surface scaled by a center point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The scaled surface
	[[nodiscard]] constexpr Derived Scaled(const Point3& point, double scale) const noexcept
	{
		return Derived(_derived()).Scale(point, scale);
	}

	/// @brief Transform the surface
	/// @param tr The transformation
	/// @return The reference to self
	Derived& Transform(const Transformation3& tr) noexcept
	{
		pos.Transform(tr);
		return _derived();
	}

	/// @brief Get the transformed surface
	/// @param tr The transformation
	/// @return The transformed surface
	[[nodiscard]] Derived Transformed(const Transformation3& tr) const noexcept
	{
		return Derived(_derived()).Transform(tr);
	}

	/// @brief Translate the surface by a vector
	/// @param vec The translation vector
	/// @return The reference to self
	constexpr Derived& Translate(const Vector3& vec) noexcept
	{
		pos.Translate(vec);
		return _derived();
	}

	/// @brief Get the surface translated by a vector
	/// @param vec The translation vector
	/// @return The translated surface
	[[nodiscard]] constexpr Derived Translated(const Vector3& vec) const noexcept
	{
		return Derived(_derived()).Translate(vec);
	}

	/// @brief Translate the surface by a vector from a source point to a target point
	/// @param p1 The source point
	/// @param p2 The target point
	/// @return The reference to self
	constexpr Derived& Translate(const Point3& p1, const Point3& p2) noexcept
	{
		pos.Translate(p1, p2);
		return _derived();
	}

	/// @brief Get the surface translated by a vector from a source point to a target point
	/// @param p1 The source point
	/// @param p2 The target point
	/// @return The translated surface
	[[nodiscard]] constexpr Derived Translated(const Point3& p1, const Point3& p2) const noexcept
	{
		return Derived(_derived()).Translate(p1, p2);
	}

protected:
	/// @brief Default constructor
	constexpr SurfaceBase() noexcept = default;

	/// @brief Construct from a frame
	/// @param frame The frame
	constexpr explicit SurfaceBase(const Frame3& frame) noexcept
		: pos(frame)
	{
	}

	/// @brief Cast to derived class
	/// @return Reference to self
	[[nodiscard]] constexpr Derived& _derived() noexcept
	{
		return static_cast<Derived&>(*this);
	}

	/// @brief Cast to derived class
	/// @return Constant reference to self
	[[nodiscard]] constexpr const Derived& _derived() const noexcept
	{
		return static_cast<const Derived&>(*this);
	}

	/// @brief The local coordinate system
	Frame3 pos;
};
} // namespace AMCAX
