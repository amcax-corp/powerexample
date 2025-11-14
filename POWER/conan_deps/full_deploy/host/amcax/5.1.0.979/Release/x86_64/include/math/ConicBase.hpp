/// @file      ConicBase.hpp
/// @brief     Base class of conic section
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/AxisT.hpp>
#include <common/FrameT.hpp>
#include <common/TransformationT.hpp>
#include <common/VectorT.hpp>

namespace AMCAX
{
/// @brief Base class of conic sections, only available in 2D and 3D
/// @tparam Derived Type of derived class
/// @tparam DIM Dimension
template<int DIM, typename Derived>
class ConicBase
{
	static_assert(DIM == 2 || DIM == 3);

public:
	/// @brief Set the location point
	/// @param p The new location point
	constexpr void SetLocation(const PointT<double, DIM>& p) noexcept
	{
		pos.SetLocation(p);
	}

	/// @brief Set the local frame
	/// @param frame The local frame
	constexpr void SetPosition(const FrameT<double, DIM>& frame) noexcept
	{
		pos = frame;
		if constexpr (DIM == 3)
		{
			pos.MakeDirect();
		}
	}

	/// @brief Set the main axis (normal axis) of the local frame in 3D
	/// @param axis The main axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	void SetAxis(const AxisT<double, DIM>& axis) noexcept
	{
		pos.SetAxis(axis);
	}

	/// @brief Get the main axis (normal axis)
	/// @return The main axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr AxisT<double, DIM> Axis() const noexcept
	{
		return pos.Axis();
	}

	/// @brief Get the location point
	/// @return The location point
	[[nodiscard]] constexpr const PointT<double, DIM>& Location() const noexcept
	{
		return pos.Location();
	}

	/// @brief Get the local frame
	/// @return The local frame
	[[nodiscard]] constexpr const FrameT<double, DIM>& Position() const noexcept
	{
		return pos;
	}

	/// @brief Set the x axis
	/// @param axis The new x axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	void SetXAxis(const AxisT<double, DIM>& axis) noexcept
	{
		pos.SetXAxis(axis);
	}

	/// @brief Set the y axis
	/// @param axis The new y axis
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	void SetYAxis(const AxisT<double, DIM>& axis) noexcept
	{
		pos.SetYAxis(axis);
	}

	/// @brief Get the x axis
	/// @return The x axis
	[[nodiscard]] constexpr AxisT<double, DIM> XAxis() const noexcept
	{
		return pos.XAxis();
	}

	/// @brief Get the y axis
	/// @return The y axis
	[[nodiscard]] constexpr AxisT<double, DIM> YAxis() const noexcept
	{
		return pos.YAxis();
	}

	/// @brief Mirror the conic section by a point
	/// @param p The mirror center point
	/// @return The reference to self
	constexpr Derived& Mirror(const PointT<double, DIM>& p) noexcept
	{
		pos.Mirror(p);
		if constexpr (DIM == 3)
		{
			pos.MakeDirect();
		}
		return _derived();
	}

	/// @brief Get the conic section mirrored by a point
	/// @param p The mirror center point
	/// @return The mirrored conic section
	[[nodiscard]] constexpr Derived Mirrored(const PointT<double, DIM>& p) const noexcept
	{
		return Derived(_derived()).Mirror(p);
	}

	/// @brief Mirror the conic section by an axis
	/// @param axis The mirror axis
	/// @return The reference to self
	constexpr Derived& Mirror(const AxisT<double, DIM>& axis) noexcept
	{
		pos.Mirror(axis);
		if constexpr (DIM == 3)
		{
			pos.MakeDirect();
		}
		return _derived();
	}

	/// @brief Get the conic section mirrored by an axis
	/// @param axis The mirror axis
	/// @return The mirrored conic section
	[[nodiscard]] constexpr Derived Mirrored(const AxisT<double, DIM>& axis) const noexcept
	{
		return Derived(_derived()).Mirror(axis);
	}

	/// @brief Mirror the conic section by a frame
	/// @param frame The mirror frame
	/// @return The reference to self
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr Derived& Mirror(const Frame3& frame) noexcept
	{
		pos.Mirror(frame);
		pos.MakeDirect();
		return _derived();
	}

	/// @brief Get the conic section mirrored by a frame
	/// @param frame The mirror frame
	/// @return The mirrored conic section
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr Derived Mirrored(const Frame3& frame) const noexcept
	{
		return Derived(_derived()).Mirror(frame);
	}

	/// @brief Rotate the conic section around a point with an angle in 2D
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The reference to self
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	Derived& Rotate(const PointT<double, DIM>& point, double angle) noexcept
	{
		pos.Rotate(point, angle);
		return _derived();
	}

	/// @brief Get the conic section rotated around a point with an angle in 2D
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The rotated conic section
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] Derived Rotated(const PointT<double, DIM>& point, double angle) const noexcept
	{
		return Derived(_derived()).Rotate(point, angle);
	}

	/// @brief Rotate the conic section around an axis with an angle in 3D
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	Derived& Rotate(const Axis3& axis, double angle) noexcept
	{
		pos.Rotate(axis, angle);
		return _derived();
	}

	/// @brief Get the conic section rotated around an axis with an angle in 3D
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated conic section
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] Derived Rotated(const Axis3& axis, double angle) const noexcept
	{
		return Derived(_derived()).Rotate(axis, angle);
	}

	/// @brief Scale the conic section by a center point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	constexpr Derived& Scale(const PointT<double, DIM>& point, double scale) noexcept
	{
		pos.Scale(point, scale);
		if constexpr (DIM == 3)
		{
			pos.MakeDirect();
		}
		return _derived();
	}

	/// @brief Get the conic section scaled by a center point
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The scaled conic section
	[[nodiscard]] constexpr Derived Scaled(const PointT<double, DIM>& point, double scale) const noexcept
	{
		return Derived(_derived()).Scale(point, scale);
	}

	/// @brief Transform the conic section
	/// @param tr The transformation
	/// @return The reference to self
	Derived& Transform(const TransformationT<double, DIM>& tr) noexcept
	{
		pos.Transform(tr);
		if constexpr (DIM == 3)
		{
			pos.MakeDirect();
		}
		return _derived();
	}

	/// @brief Get the transformed conic section
	/// @param tr The transformation
	/// @return The transformed conic section
	[[nodiscard]] Derived Transformed(const TransformationT<double, DIM>& tr) const noexcept
	{
		return Derived(_derived()).Transform(tr);
	}

	/// @brief Translate the conic section by a vector
	/// @param vec The translation vector
	/// @return The reference to self
	constexpr Derived& Translate(const VectorT<double, DIM>& vec) noexcept
	{
		pos.Translate(vec);
		return _derived();
	}

	/// @brief Get the conic section translated by a vector
	/// @param vec The translation vector
	/// @return The translated conic section
	[[nodiscard]] constexpr Derived Translated(const VectorT<double, DIM>& vec) const noexcept
	{
		return Derived(_derived()).Translate(vec);
	}

	/// @brief Translate the conic section by a vector from a source point to a target point
	/// @param p1 The source point
	/// @param p2 The target point
	/// @return The reference to self
	constexpr Derived& Translate(const PointT<double, DIM>& p1, const PointT<double, DIM>& p2) noexcept
	{
		pos.Translate(p1, p2);
		return _derived();
	}

	/// @brief Get the conic section translated by a vector from a source point to a target point
	/// @param p1 The source point
	/// @param p2 The target point
	/// @return The translated conic section
	[[nodiscard]] constexpr Derived Translated(const PointT<double, DIM>& p1, const PointT<double, DIM>& p2) const noexcept
	{
		return Derived(_derived()).Translate(p1, p2);
	}

protected:
	/// @brief Default constructor
	constexpr ConicBase() noexcept = default;

	/// @brief Construct from an axis
	/// @param majorAxis The major axis
	/// @param isRight Is the frame right-handed
	template<int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	constexpr explicit ConicBase(const AxisT<double, DIM>& majorAxis, bool isRight = true) noexcept
		: pos(majorAxis, isRight)
	{
	}

	/// @brief Construct from a frame
	/// @param frame The frame
	constexpr explicit ConicBase(const FrameT<double, DIM>& frame) noexcept
		: pos(frame)
	{
		if constexpr (DIM == 3)
		{
			pos.MakeDirect();
		}
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
	FrameT<double, DIM> pos;
};
} // namespace AMCAX
