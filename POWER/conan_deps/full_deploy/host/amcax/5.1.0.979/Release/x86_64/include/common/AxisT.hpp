/// @file      AxisT.hpp
/// @brief     Class of axis
/// @details   Implementation of axis
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>

namespace AMCAX
{
template<typename Scalar, int DIM>
class FrameT;
template<typename Scalar, int DIM>
class TransformationT;
template<typename Scalar, int DIM>
class VectorT;

/// @brief Class of axis
/// @details An axis consists of a location and a direction
/// @tparam Scalar Underlying type of axis
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
class AxisT
{
public:
	/// @brief Default constructor
	/// @details The default location is (0, 0, 0). In 2D, the default direction is (1, 0); in 3D, the default direction is (0, 0, 1).
	constexpr AxisT() noexcept
	{
		if constexpr (DIM == 3)
		{
			direction.coord.SetCoord(Scalar{0}, Scalar{0}, Scalar{1});
		}
	}

	/// @brief Construct from a location and a direction
	/// @tparam OtherScalar The scalar type of the location
	/// @tparam OtherScalar2 The scalar type of the direction
	/// @param point The location
	/// @param dir The direction
	template<typename OtherScalar, typename OtherScalar2>
	constexpr AxisT(const PointT<OtherScalar, DIM>& point, const DirectionT<OtherScalar2, DIM>& dir) noexcept
		: location(point),
		  direction(dir)
	{
	}

	/// @brief Set a new location
	/// @tparam OtherScalar The scalar type of the new location
	/// @param point The new location
	template<typename OtherScalar>
	constexpr void SetLocation(const PointT<OtherScalar, DIM>& point) noexcept
	{
		location = point;
	}

	/// @brief Set a new direction
	/// @tparam OtherScalar The scalar type of the new direction
	/// @param dir The new direction
	template<typename OtherScalar>
	constexpr void SetDirection(const DirectionT<OtherScalar, DIM>& dir) noexcept
	{
		direction = dir;
	}

	/// @brief Get the location
	/// @return The location
	[[nodiscard]] constexpr const PointT<Scalar, DIM>& Location() const noexcept
	{
		return location;
	}

	/// @brief Get the direction
	/// @return The direction
	[[nodiscard]] constexpr const DirectionT<Scalar, DIM>& Direction() const noexcept
	{
		return direction;
	}

	/// @brief Is the axis coaxial with the other axis, 2D version
	/// @details Two axes are coaxial if their directions are equal and their locations are colinear with the directions
	/// @tparam OtherScalar The scalar type of the other axis
	/// @tparam OtherScalar2 The type of angle tolerance
	/// @tparam OtherScalar3 The type of distance tolerance
	/// @param other The other axis
	/// @param angtol The angle tolerance
	/// @param distol The distance tolerance
	/// @return True is the direction difference is under the angle tolerance and the distance from one location to the other axis is under the distance tolerance
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] bool IsCoaxial(const AxisT<OtherScalar, DIM>& other, const OtherScalar2& angtol, const OtherScalar3& distol) const noexcept
	{
		return direction.IsEqual(other.direction, angtol) && std::fabs((location.Coord() - other.location.Coord()).Cross(other.direction.Coord())) < distol && std::fabs((other.location.Coord() - location.Coord()).Cross(direction.Coord())) < distol;
	}

	/// @brief Is the axis coaxial with the other axis, 3D version
	/// @details Two axes are coaxial if their directions are equal and their locations are colinear with the directions
	/// @tparam OtherScalar The scalar type of the other axis
	/// @tparam OtherScalar2 The type of angle tolerance
	/// @tparam OtherScalar3 The type of distance tolerance
	/// @param other The other axis
	/// @param angtol The angle tolerance
	/// @param distol The distance tolerance
	/// @return True is the direction difference is under the angle tolerance and the distance from one location to the other axis is under the distance tolerance
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] bool IsCoaxial(const AxisT<OtherScalar, DIM>& other, const OtherScalar2& angtol, const OtherScalar3& distol) const noexcept
	{
		return direction.IsEqual(other.direction, angtol) && (location.Coord() - other.location.Coord()).Cross(other.direction.Coord()).Norm() < distol && (other.location.Coord() - location.Coord()).Cross(direction.Coord()).Norm() < distol;
	}

	/// @brief Is the axis perpendicular to the other axis under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other axis
	/// @tparam OtherScalar2 The type of the angle tolerance
	/// @param other The other axis
	/// @param tol The angle tolerance
	/// @return True if the direction is perpendicular to the direction of the other axis
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsNormal(const AxisT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		return direction.IsNormal(other.direction, tol);
	}

	/// @brief Is the axis opposite to the other axis under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other axis
	/// @tparam OtherScalar2 The type of the angle tolerance
	/// @param other The other axis
	/// @param tol The angle tolerance
	/// @return True if the direction is opposite to the direction of the other axis
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsOpposite(const AxisT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		return direction.IsOpposite(other.direction, tol);
	}

	/// @brief Is the axis parallel to the other axis under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other axis
	/// @tparam OtherScalar2 The type of angle tolerance
	/// @param other The other axis
	/// @param tol The angle tolerance
	/// @return True if the direction is parallel to the direction of the other axis
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsParallel(const AxisT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		return direction.IsParallel(other.direction, tol);
	}

	/// @brief Compute the angle difference to the other axis
	/// @tparam OtherScalar The scalar type of the other axis
	/// @param other The other axis
	/// @return The angle difference to the other direction
	template<typename OtherScalar>
	[[nodiscard]] double Angle(const AxisT<OtherScalar, DIM>& other) const noexcept
	{
		return direction.Angle(other.direction);
	}

	/// @brief Reverse the axis, that is reverse the direction
	/// @return The reference to self
	constexpr AxisT& Reverse() noexcept
	{
		direction.Reverse();
		return *this;
	}

	/// @brief Get the reversed axis
	/// @return The reversed axis
	[[nodiscard]] constexpr AxisT Reversed() const noexcept
	{
		return AxisT(*this).Reverse();
	}

	/// @brief Mirror the axis by a point
	/// @tparam OtherScalar The scalar type of the mirror point
	/// @param point The mirror point
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr AxisT& Mirror(const PointT<OtherScalar, DIM>& point) noexcept
	{
		location.Mirror(point);
		direction.Reverse();
		return *this;
	}

	/// @brief Get the axis mirrored by a point
	/// @tparam OtherScalar The scalar type of the mirror point
	/// @param point The mirror point
	/// @return The mirrored axis
	template<typename OtherScalar>
	[[nodiscard]] constexpr AxisT Mirrored(const PointT<OtherScalar, DIM>& point) const noexcept
	{
		return AxisT(*this).Mirror(point);
	}

	/// @brief Mirror the axis by an axis
	/// @tparam OtherScalar The scalar type of the mirror axis
	/// @param axis The mirror axis
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr AxisT& Mirror(const AxisT<OtherScalar, DIM>& axis) noexcept
	{
		location.Mirror(axis);
		direction.Mirror(axis.Direction());
		return *this;
	}

	/// @brief Get the axis mirrored by an axis
	/// @tparam OtherScalar The scalar type of the mirror axis
	/// @param axis The mirror axis
	/// @return The mirrored axis
	template<typename OtherScalar>
	[[nodiscard]] constexpr AxisT Mirrored(const AxisT<OtherScalar, DIM>& axis) const noexcept
	{
		return AxisT(*this).Mirror(axis);
	}

	/// @brief Mirror the axis by a frame
	/// @tparam OtherScalar The scalar type of the mirror frame
	/// @param frame The mirror frame
	/// @return The reference to self
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr AxisT& Mirror(const FrameT<OtherScalar, DIM>& frame) noexcept
	{
		location.Mirror(frame);
		direction.Mirror(frame);
		return *this;
	}

	/// @brief Get the axis mirrored by a frame
	/// @tparam OtherScalar The scalar type of the mirror frame
	/// @param frame The mirror frame
	/// @return The mirrored axis
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr AxisT Mirrored(const FrameT<OtherScalar, DIM>& frame) const noexcept
	{
		return AxisT(*this).Mirror(frame);
	}

	/// @brief Rotate the axis around a point by an angle in 2D
	/// @tparam OtherScalar The scalar type of the rotation center point
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	AxisT& Rotate(const PointT<OtherScalar, DIM>& point, const OtherScalar2& angle) noexcept
	{
		location.Rotate(point, angle);
		direction.Rotate(angle);
		return *this;
	}

	/// @brief Get the axis rotated around a point by an angle in 2D
	/// @tparam OtherScalar The scalar type of the rotation center point
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param point The rotation center point
	/// @param angle The rotation angle
	/// @return The rotated axis
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] AxisT Rotated(const PointT<OtherScalar, DIM>& point, const OtherScalar2& angle) const noexcept
	{
		return AxisT(*this).Rotate(point, angle);
	}

	/// @brief Rotate the axis around an axis by an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	AxisT& Rotate(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) noexcept
	{
		location.Rotate(axis, angle);
		direction.Rotate(axis, angle);
		return *this;
	}

	/// @brief Get the axis rotated around an axis by an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated axis
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] AxisT Rotated(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) const noexcept
	{
		return AxisT(*this).Rotate(axis, angle);
	}

	/// @brief Scale the axis
	/// @tparam OtherScalar The scalar type of the scaling center point
	/// @tparam OtherScalar2 The type of the scale
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2>
	constexpr AxisT& Scale(const PointT<OtherScalar, DIM>& point, const OtherScalar2& scale) noexcept
	{
		location.Scale(point, scale);
		if (scale < OtherScalar2{0})
		{
			direction.Reverse();
		}
		return *this;
	}

	/// @brief Get the scaled axis
	/// @tparam OtherScalar The scalar type of the scaling center point
	/// @tparam OtherScalar2 The type of the scale
	/// @param point The scaling center point
	/// @param scale The scale value
	/// @return The scaled axis
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] constexpr AxisT Scaled(const PointT<OtherScalar, DIM> point, const OtherScalar2& scale) const noexcept
	{
		return AxisT(*this).Scale(point, scale);
	}

	/// @brief Transform the axis
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The reference to self
	template<typename OtherScalar>
	AxisT& Transform(const TransformationT<OtherScalar, DIM>& tr) noexcept
	{
		location.Transform(tr);
		direction.Transform(tr);
		return *this;
	}

	/// @brief Get the transformed axis
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The transformed axis
	template<typename OtherScalar>
	[[nodiscard]] AxisT Transformed(const TransformationT<OtherScalar, DIM>& tr) const noexcept
	{
		return AxisT(*this).Transform(tr);
	}

	/// @brief Translate the axis
	/// @tparam OtherScalar The scalar type of the translation vector
	/// @param vec The translation vector
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr AxisT& Translate(const VectorT<OtherScalar, DIM>& vec) noexcept
	{
		location.Translate(vec);
		return *this;
	}

	/// @brief Get the translated axis
	/// @tparam OtherScalar The scalar type of the translation vector
	/// @param vec The translation vector
	/// @return The translated axis
	template<typename OtherScalar>
	[[nodiscard]] constexpr AxisT Translated(const VectorT<OtherScalar, DIM>& vec) const noexcept
	{
		return AxisT(*this).Translate(vec);
	}

	/// @brief Translate the axis by a vector from a point to another point
	/// @tparam OtherScalar The scalar type of the first point
	/// @tparam OtherScalar2 The scalar type of the second point
	/// @param p1 The first point
	/// @param p2 The second point
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2>
	constexpr AxisT& Translate(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) noexcept
	{
		location.Translate(p1, p2);
		return *this;
	}

	/// @brief Get the axis translated by a vector from a point to another point
	/// @tparam OtherScalar The scalar type of the first point
	/// @tparam OtherScalar2 The scalar type of the second point
	/// @param p1 The first point
	/// @param p2 The second point
	/// @return The translated axis
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] constexpr AxisT Translated(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) const noexcept
	{
		return AxisT(*this).Translate(p1, p2);
	}

	/// @brief Write the axis
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param axis The axis
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const AxisT& axis)
	{
		os << axis.location << ' ' << axis.direction;
		return os;
	}

	/// @brief Read the axis
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param axis The axis
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, AxisT& axis)
	{
		is >> axis.location >> axis.direction;
		return is;
	}

private:
	/// @brief A point on the axis
	PointT<Scalar, DIM> location;

	/// @brief The direction of the axis
	DirectionT<Scalar, DIM> direction;
};

/// @brief 2D axis
using Axis2 = AxisT<double, 2>;

/// @brief 3D axis
using Axis3 = AxisT<double, 3>;

} // namespace AMCAX
