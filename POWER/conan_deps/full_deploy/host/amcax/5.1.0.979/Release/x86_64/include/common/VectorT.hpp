/// @file      VectorT.hpp
/// @brief     Class of vector
/// @details   Implementation of vector
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/CoordT.hpp>
#include <common/TransformationType.hpp>

namespace AMCAX
{
template<typename Scalar, int ROW, int COL>
class MatrixT;
template<typename Scalar, int DIM>
class PointT;
template<typename Scalar, int DIM>
class DirectionT;
template<typename Scalar, int DIM>
class AxisT;
template<typename Scalar, int DIM>
class FrameT;
template<typename Scalar, int DIM>
class TransformationT;

/// @brief Template class of vector
/// @tparam Scalar The scalar type of vector
/// @tparam DIM The dimension
template<typename Scalar, int DIM>
class VectorT
{
public:
	/// @brief The type of coordinate
	using CoordType = CoordT<Scalar, DIM>;

	/// @brief The default constructor
	/// @details The default vector is (0, 0, ..., 0)
	constexpr VectorT() noexcept = default;

	/// @brief Construct from a direction
	/// @tparam OtherScalar The scalar type of the direction
	/// @param dir The direction
	template<typename OtherScalar>
	constexpr explicit VectorT(const DirectionT<OtherScalar, DIM>& dir) noexcept
		: coord(dir.Coord())
	{
	}

	/// @brief Construct from a coordinate
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @param v The coordinate
	template<typename OtherScalar>
	constexpr explicit VectorT(const CoordT<OtherScalar, DIM>& v) noexcept
		: coord(v)
	{
	}

	/// @brief Construct from component values
	/// @tparam ...T The types of values
	/// @param ...vs The values
	template<typename... T, std::enable_if_t<static_cast<int>(sizeof...(T)) == DIM && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr explicit VectorT(T&&... vs) noexcept
		: coord(std::forward<T>(vs)...)
	{
	}

	/// @brief Construct a vector from a point to another point
	/// @tparam OtherScalar The scalar type of the start point
	/// @tparam OtherScalar2 The scalar type of the end point
	/// @param p1 The start point
	/// @param p2 The end point
	template<typename OtherScalar, typename OtherScalar2>
	constexpr VectorT(const PointT<OtherScalar, DIM>& p1, const PointT<OtherScalar2, DIM>& p2) noexcept
		: coord(p2.Coord() - p1.Coord())
	{
	}

	/// @brief Set the component values
	/// @tparam ...T The types of values
	/// @param ...vs The values
	template<typename... T, std::enable_if_t<static_cast<int>(sizeof...(T)) == DIM && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void SetCoord(T&&... vs) & noexcept
	{
		coord.SetCoord(std::forward<T>(vs)...);
	}

	/// @brief Set from a coordinate
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @param v The coordinate
	template<typename OtherScalar>
	constexpr void SetCoord(const CoordT<OtherScalar, DIM>& v) & noexcept
	{
		coord = v;
	}

	/// @brief Set x-coordinate, only available when DIM >= 1
	/// @tparam OtherScalar The type of scalar
	/// @param x New x-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 1, int> = 0>
	constexpr void SetX(const OtherScalar& x) & noexcept
	{
		coord.SetX(x);
	}

	/// @brief Set y-coordinate, only available when DIM >= 2
	/// @tparam OtherScalar The type of scalar
	/// @param y New y-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 2, int> = 0>
	constexpr void SetY(const OtherScalar& y) & noexcept
	{
		coord.SetY(y);
	}

	/// @brief Set z-coordinate, only available when DIM >= 3
	/// @tparam OtherScalar The type of scalar
	/// @param z New z-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 3, int> = 0>
	constexpr void SetZ(const OtherScalar& z) & noexcept
	{
		coord.SetZ(z);
	}

	/// @brief Set w-coordinate, only available when DIM >= 4
	/// @tparam OtherScalar The type of scalar
	/// @param w New w-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 4, int> = 0>
	constexpr void SetW(const OtherScalar& w) & noexcept
	{
		coord.SetW(w);
	}

	/// @brief Get the i-th component of the vector
	/// @param i The index
	/// @return The reference of the i-th component
	[[nodiscard]] constexpr const Scalar& operator[](int i) const noexcept
	{
		return coord[i];
	}

	/// @brief Get the i-th component of the vector
	/// @param i The index
	/// @return The reference of the i-th component
	[[nodiscard]] constexpr Scalar& operator[](int i) noexcept
	{
		return coord[i];
	}

	/// @brief Get x-coordinate, only available when DIM >= 1
	/// @return The reference to the x-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 1, int> = 0>
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return coord.X();
	}

	/// @brief Get y-coordinate, only available when DIM >= 2
	/// @return The reference to the y-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 2, int> = 0>
	[[nodiscard]] constexpr const Scalar& Y() const noexcept
	{
		return coord.Y();
	}

	/// @brief Get z-coordinate, only available when DIM >= 3
	/// @return The reference to the z-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 3, int> = 0>
	[[nodiscard]] constexpr const Scalar& Z() const noexcept
	{
		return coord.Z();
	}

	/// @brief Get w-coordinate, only available when DIM >= 4
	/// @return The reference to the w-coordinate
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 4, int> = 0>
	[[nodiscard]] constexpr const Scalar& W() const noexcept
	{
		return coord.W();
	}

	/// @brief Get the intrinsic coordinate of vector
	/// @return The reference to the coordinate
	[[nodiscard]] constexpr const CoordType& Coord() const noexcept
	{
		return coord;
	}

	/// @brief Get the intrinsic coordinate of vector
	/// @return The reference to the coordinate
	[[nodiscard]] constexpr CoordType& Coord() noexcept
	{
		return coord;
	}

	/// @brief Does the vector equal the other vector under distance and angle tolerance
	/// @tparam OtherScalar The scalar type of the other vector
	/// @tparam OtherScalar2 The type of distance tolerance
	/// @tparam OtherScalar3 The type of angle tolerance
	/// @param other The other vector
	/// @param tolDis The distance tolerance
	/// @param tolAng The angle tolerance
	/// @return True if the distance difference is under distance tolerance and the angle difference is under angle tolerance
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3>
	[[nodiscard]] bool IsEqual(const VectorT<OtherScalar, DIM>& other, const OtherScalar2& tolDis, const OtherScalar3& tolAng) const
	{
		auto norm1 = Norm();
		auto norm2 = other.Norm();
		return std::fabs(norm1 - norm2) <= tolDis && (norm1 <= tolDis || norm2 <= tolDis || std::fabs(Angle(other)) <= tolAng);
	}

	/// @brief Is the vector perpendicular to the other vector under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other vector
	/// @tparam OtherScalar2 The type of tolerance
	/// @param other The other vector
	/// @param tol The angle tolerance
	/// @return True if the angle difference to pi/2 is under the angle tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsNormal(const VectorT<OtherScalar, DIM>& other, const OtherScalar2& tol) const
	{
		return std::fabs(Constants::half_pi - std::fabs(Angle(other))) <= tol;
	}

	/// @brief Is the vector opposite to the other vector under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other vector
	/// @tparam OtherScalar2 The type of tolerance
	/// @param other The other vector
	/// @param tol The angle tolerance
	/// @return True if the angle difference to pi is under the angle tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsOpposite(const VectorT<OtherScalar, DIM>& other, const OtherScalar2& tol) const
	{
		return Constants::pi - std::fabs(Angle(other)) <= tol;
	}

	/// @brief Is the vector parallel to the other vector under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other vector
	/// @tparam OtherScalar2 The type of tolerance
	/// @param other The other vector
	/// @param tol The angle tolerance
	/// @return True is the angle difference to 0 or pi is under the angle tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsParallel(const VectorT<OtherScalar, DIM>& other, const OtherScalar2& tol) const
	{
		const auto angle = std::fabs(Angle(other));
		return angle <= tol || Constants::pi - angle <= tol;
	}

	/// @brief Compute the angle difference to the other vector in 2D
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The angle difference to the other vector, range in [-pi, pi]
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] auto Angle(const VectorT<OtherScalar, DIM>& other) const
	{
		auto n1 = coord.Norm();
		auto n2 = other.Norm();
		Throw_Null_Value_if(n1 <= std::numeric_limits<Scalar>::min() || n2 <= std::numeric_limits<OtherScalar>::min(), "");
		auto cosine = coord.Dot(other.coord) / (n1 * n2);
		auto sine = coord.Cross(other.coord) / (n1 * n2);
		if (cosine > -Constants::half_sqrt2 && cosine < Constants::half_sqrt2)
		{
			return sine > 0.0 ? std::acos(cosine) : -std::acos(cosine);
		}
		else if (cosine > 0.0)
		{
			return std::asin(sine);
		}
		else
		{
			return sine > 0.0 ? (Constants::pi - std::asin(sine)) : (-Constants::pi - std::asin(sine));
		}
	}

	/// @brief Compute the angle difference to the other vector in 3D
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The angle difference to the other vector, range in [0, pi]
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] auto Angle(const VectorT<OtherScalar, DIM>& other) const
	{
		auto n1 = coord.Norm();
		auto n2 = other.Norm();
		Throw_Null_Value_if(n1 <= std::numeric_limits<Scalar>::min() || n2 <= std::numeric_limits<OtherScalar>::min(), "");
		auto cosine = coord.Dot(other.Coord()) / (n1 * n2);
		if (cosine > -Constants::half_sqrt2 && cosine < Constants::half_sqrt2)
		{
			return std::acos(cosine);
		}
		else
		{
			auto sine = coord.Cross(other.Coord()).Norm() / (n1 * n2);
			return cosine < 0.0 ? (Constants::pi - std::asin(sine)) : std::asin(sine);
		}
	}

	/// @brief Compute the angle difference to the other vector in terms of a reference vector as the Z-axis, only available in 3D
	/// @details If the vector, the other vector and the reference vector forms a right-handed frame system, the angle is positive; otherwise, the angle is negative.
	/// @tparam OtherScalar The scalar type of the other vector
	/// @tparam OtherScalar2 The scalar type of the reference vector
	/// @param other The other vector
	/// @param ref The reference vector
	/// @return The angle difference to the other vector with a reference vector, range in [-pi, pi].
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] Scalar AngleWithRef(const VectorT<OtherScalar, DIM>& other, const VectorT<OtherScalar2, DIM>& ref) const
	{
		auto n1 = coord.Norm();
		auto n2 = other.Norm();
		Throw_Null_Value_if(n1 <= std::numeric_limits<Scalar>::min() || n2 <= std::numeric_limits<OtherScalar>::min(), "");
		const auto cross = coord.Cross(other.Coord()) / (n1 * n2);
		auto cosine = coord.Dot(other.Coord()) / (n1 * n2);
		auto sine = cross.Norm();
		const auto angle = (cosine > -Constants::half_sqrt2 && cosine < Constants::half_sqrt2) ? std::acos(cosine) : (cosine < 0.0 ? (Constants::pi - std::asin(sine)) : std::asin(sine));
		return cross.Dot(ref.coord) >= 0.0 ? angle : -angle;
	}

	/// @brief Get the norm of vector
	/// @return The norm of vector
	[[nodiscard]] auto Norm() const noexcept
	{
		return coord.Norm();
	}

	/// @brief Get the squared norm of vector
	/// @return The squared norm of vector
	[[nodiscard]] constexpr double SquaredNorm() const noexcept
	{
		return coord.SquaredNorm();
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr VectorT& operator+=(const VectorT<OtherScalar, DIM>& other) noexcept
	{
		coord += other.Coord();
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr VectorT operator+(const VectorT<OtherScalar, DIM>& other) const noexcept
	{
		return VectorT(*this) += other;
	}

	/// @brief Subtraction assignment
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr VectorT& operator-=(const VectorT<OtherScalar, DIM>& other) noexcept
	{
		coord -= other.Coord();
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr VectorT operator-(const VectorT<OtherScalar, DIM>& other) const noexcept
	{
		return VectorT(*this) -= other;
	}

	/// @brief Scalar multiplication assignment
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr VectorT& operator*=(const OtherScalar& scalar) noexcept
	{
		coord *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr VectorT operator*(const OtherScalar& scalar) const noexcept
	{
		return VectorT(*this) *= scalar;
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @param v The vector
	/// @return The multiplication result
	template<typename OtherScalar>
	friend constexpr VectorT operator*(const OtherScalar& scalar, const VectorT& v) noexcept
	{
		return v * scalar;
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr VectorT& operator/=(const OtherScalar& scalar) noexcept
	{
		coord /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The division result
	template<typename OtherScalar>
	[[nodiscard]] constexpr VectorT operator/(const OtherScalar& scalar) const noexcept
	{
		return VectorT(*this) /= scalar;
	}

	/// @brief 2D Cross product operator
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The result of cross product, a scalar
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] constexpr auto Cross(const VectorT<OtherScalar, DIM>& other) const noexcept
	{
		return coord.Cross(other.Coord());
	}

	/// @brief 3D Cross product operator
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The result of cross product, a 3D vector
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr auto Cross(const VectorT<OtherScalar, DIM>& other) const noexcept
	{
		return VectorT{coord.Cross(other.Coord())};
	}

	/// @brief Dot product operator
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param other The other vector
	/// @return The result of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const VectorT<OtherScalar, DIM>& other) const noexcept
	{
		return coord.Dot(other.Coord());
	}

	/// @brief Dot product with a direction
	/// @tparam OtherScalar The scalar type of the direction
	/// @param other The direction
	/// @return The result of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const DirectionT<OtherScalar, DIM>& other) const noexcept
	{
		return coord.Dot(other.Coord());
	}

	/// @brief Normalize the vector
	/// @return The reference to self
	VectorT& Normalize() noexcept
	{
		coord.Normalize();
		return *this;
	}

	/// @brief Get the normalized vector
	/// @return The normalized vector
	[[nodiscard]] VectorT Normalized() const noexcept
	{
		return VectorT(*this).Normalize();
	}

	/// @brief Reverse the vector
	/// @return The reference to self
	constexpr VectorT& Reverse() noexcept
	{
		coord.Reverse();
		return *this;
	}

	/// @brief Get the reversed vector
	/// @return The reversed vector
	[[nodiscard]] constexpr VectorT Reversed() const noexcept
	{
		return VectorT(*this).Reverse();
	}

	/// @brief Unary minus operator
	/// @return The reversed vector
	[[nodiscard]] constexpr VectorT operator-() const noexcept
	{
		return Reversed();
	}

	/// @brief Mirror the vector by a vector
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param p The mirror vector
	/// @return The reference to self
	template<typename OtherScalar>
	VectorT& Mirror(const VectorT<OtherScalar, DIM>& p) noexcept
	{
		OtherScalar d = p.Norm();
		if (d > std::numeric_limits<OtherScalar>::min())
		{
			MatrixT<OtherScalar, DIM, DIM> mat1, mat2;
			mat1.SetDot(p.Coord().Normalized());
			mat2.SetIdentity();
			coord = (mat1 * 2.0 - mat2) * coord;
		}
		return *this;
	}

	/// @brief Get the vector mirrored by a vector
	/// @tparam OtherScalar The scalar type of the other vector
	/// @param p The mirror vector
	/// @return The mirrored vector
	template<typename OtherScalar>
	[[nodiscard]] VectorT Mirrored(const VectorT<OtherScalar, DIM>& p) const noexcept
	{
		return VectorT(*this).Mirror(p);
	}

	/// @brief Mirror the vector by an axis
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The mirror axis
	/// @return The reference to self
	template<typename OtherScalar>
	VectorT& Mirror(const AxisT<OtherScalar, DIM>& axis) noexcept
	{
		return Mirror(VectorT<OtherScalar, DIM>(axis.Direction()));
	}

	/// @brief Get the vector mirrored by an axis
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The mirror axis
	/// @return The mirrored vector
	template<typename OtherScalar>
	[[nodiscard]] VectorT Mirrored(const AxisT<OtherScalar, DIM>& axis) const noexcept
	{
		return VectorT(*this).Mirror(axis);
	}

	/// @brief Mirror the vector by a frame
	/// @tparam OtherScalar The scalar type of the frame
	/// @param frame The mirror frame
	/// @return The reference to self
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	VectorT& Mirror(const FrameT<OtherScalar, DIM>& frame) noexcept
	{
		return Mirror(frame.Axis()).Reverse();
	}

	/// @brief Get the vector mirrored by a frame
	/// @tparam OtherScalar The scalar type of the frame
	/// @param frame The mirror frame
	/// @return The mirrored vector
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] VectorT Mirrored(const FrameT<OtherScalar, DIM>& frame) const noexcept
	{
		return VectorT(*this).Mirror(frame);
	}

	/// @brief Rotate the vector by an angle in 2D
	/// @tparam OtherScalar The type of the rotation angle
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	VectorT& Rotate(const OtherScalar& angle) noexcept
	{
		TransformationT<Scalar, DIM> tr;
		tr.SetRotation(PointT<Scalar, DIM>(0.0, 0.0), angle);
		coord = tr.HVectorialPart() * coord;
		return *this;
	}

	/// @brief Get the vector rotated by an angle in 2D
	/// @tparam OtherScalar The type of the rotation angle
	/// @param angle The rotation angle
	/// @return The rotated vector
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] VectorT Rotated(const OtherScalar& angle) const noexcept
	{
		return VectorT(*this).Rotate(angle);
	}

	/// @brief Rotate the vector by an axis and an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	VectorT& Rotate(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) noexcept
	{
		TransformationT<Scalar, DIM> tr;
		tr.SetRotation(axis, angle);
		coord = tr.HVectorialPart() * coord;
		return *this;
	}

	/// @brief Get the vector rotated by an axis and an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated vector
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] VectorT Rotated(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) const noexcept
	{
		return VectorT(*this).Rotate(axis, angle);
	}

	/// @brief Scale the vector
	/// @tparam OtherScalar The type of scale
	/// @param scale The scale
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr VectorT& Scale(const OtherScalar& scale) noexcept
	{
		coord *= scale;
		return *this;
	}

	/// @brief Get the scaled vector
	/// @tparam OtherScalar The type of scale
	/// @param scale The scale
	/// @return The scaled vector
	template<typename OtherScalar>
	[[nodiscard]] constexpr VectorT Scaled(const OtherScalar& scale) const noexcept
	{
		return VectorT(*this).Scale(scale);
	}

	/// @brief Transform the vector
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr VectorT& Transform(const TransformationT<OtherScalar, DIM>& tr) noexcept
	{
		if (tr.Type() == TransformationType::Identity || tr.Type() == TransformationType::Translation)
		{
		}
		else if (tr.Type() == TransformationType::PointMirror)
		{
			coord.Reverse();
		}
		else if (tr.Type() == TransformationType::Scale)
		{
			coord *= tr.ScaleFactor();
		}
		else
		{
			coord = tr.ScaleFactor() * (tr.HVectorialPart() * coord);
		}
		return *this;
	}

	/// @brief Get the transformed vector
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The transformed vector
	template<typename OtherScalar>
	[[nodiscard]] constexpr VectorT Transformed(const TransformationT<OtherScalar, DIM>& tr) const noexcept
	{
		return VectorT(*this).Transform(tr);
	}

	/// @brief Write the vector
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param vec The vector
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const VectorT& vec)
	{
		os << vec.coord;
		return os;
	}

	/// @brief Read the vector
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param vec The vector
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, VectorT& vec)
	{
		is >> vec.coord;
		return is;
	}

private:
	/// @brief Underlying coordinate of vector
	CoordType coord;
};

/// @brief 2D vector
using Vector2 = VectorT<double, 2>;

/// @brief 3D vector
using Vector3 = VectorT<double, 3>;

} // namespace AMCAX
