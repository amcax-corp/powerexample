/// @file      DirectionT.hpp
/// @brief     Class of direction
/// @details   Implementation of direction
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
class AxisT;
template<typename Scalar, int DIM>
class FrameT;
template<typename Scalar, int DIM>
class PointT;
template<typename Scalar, int DIM>
class TransformationT;
template<typename Scalar, int DIM>
class VectorT;

/// @brief Class of direction, i.e. the unit vector
/// @tparam Scalar Underlying type of direction
/// @tparam DIM Dimension
template<typename Scalar, int DIM>
class DirectionT
{
public:
	/// @brief The type of coordinate
	using CoordType = CoordT<Scalar, DIM>;

	/// @brief Default constructor
	/// @details Default direction is (1, 0, ... , 0)
	constexpr DirectionT() noexcept
	{
		coord[0] = Scalar{1};
	}

	/// @brief Construct from a coordinate, the coordinate will be normalized
	/// @tparam OtherScalar The scalar type of coordinate
	/// @param v The coordinate
	template<typename OtherScalar>
	explicit DirectionT(const CoordT<OtherScalar, DIM>& v)
		: coord(v.Normalized())
	{
		CheckValidity();
	}

	/// @brief Construct from a vector, the vector will be normalized
	/// @tparam OtherScalar The scalar type of vector
	/// @param vec The vector
	template<typename OtherScalar>
	explicit DirectionT(const VectorT<OtherScalar, DIM>& vec)
		: coord(vec.Coord().Normalized())
	{
		CheckValidity();
	}

	/// @brief Construct from component values
	/// @tparam ...T Types of values
	/// @param ...vs Values
	template<typename... T, std::enable_if_t<static_cast<int>(sizeof...(T)) == DIM && are_convertible_v<Scalar, T...>, int> = 0>
	explicit DirectionT(T&&... vs) noexcept(sizeof...(T) == 0)
		: coord(std::forward<T>(vs)...)
	{
		CheckValidity();
		coord.Normalize();
	}

	/// @brief Set the coordinate by components, with normalization
	/// @tparam ...T Types of values
	/// @param ...vs Values
	template<typename... T, std::enable_if_t<static_cast<int>(sizeof...(T)) == DIM && are_convertible_v<Scalar, T...>, int> = 0>
	DirectionT& SetCoord(T&&... vs)
	{
		coord.SetCoord(std::forward<T>(vs)...);
		CheckValidity();
		coord.Normalize();
		return *this;
	}

	/// @brief Set the coordinate, with normalization
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @param v The coordinate
	template<typename OtherScalar>
	void SetCoord(const CoordT<OtherScalar, DIM>& v)
	{
		coord = v;
		CheckValidity();
		coord.Normalize();
	}

	/// @brief Set x component of the direction, with normalization, only available when DIM >= 1
	/// @details Warning: after the normalization, the x component could change.
	/// @tparam OtherScalar The scalar type of the scalar
	/// @param x The new x component
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 1, int> = 0>
	void SetX(const OtherScalar& x)
	{
		coord.SetX(x);
		CheckValidity();
		coord.Normalize();
	}

	/// @brief Set y component of the direction, with normalization, only available when DIM >= 2
	/// @details Warning: after the normalization, the y component could change
	/// @tparam OtherScalar The scalar type of the scalar
	/// @param y The new y component
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 2, int> = 0>
	void SetY(const OtherScalar& y)
	{
		coord.SetY(y);
		CheckValidity();
		coord.Normalize();
	}

	/// @brief Set z component of the direction, with normalization, only available when DIM >= 3
	/// @details Warning: after the normalization, the z component could change
	/// @tparam OtherScalar The scalar type of the scalar
	/// @param z The new z component
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 3, int> = 0>
	void SetZ(const OtherScalar& z)
	{
		coord.SetZ(z);
		CheckValidity();
		coord.Normalize();
	}

	/// @brief Set w component of the direction, with normalization, only available when DIM >= 4
	/// @details Warning: after the normalization, the w component could change
	/// @tparam OtherScalar The scalar type of the scalar
	/// @param w The new w component
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar> && DIM >= 4, int> = 0>
	void SetW(const OtherScalar& w)
	{
		coord.SetW(w);
		CheckValidity();
		coord.Normalize();
	}

	/// @brief Get the i-th component
	/// @param i The index
	/// @return The const reference to the i-th component
	[[nodiscard]] constexpr const Scalar& operator[](int i) const noexcept
	{
		return coord[i];
	}

	/// @brief Get the x component, only available when DIM >= 1
	/// @return The x component
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 1, int> = 0>
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return coord.X();
	}

	/// @brief Get the y component, only available when DIM >= 2
	/// @return The y component
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 2, int> = 0>
	[[nodiscard]] constexpr const Scalar& Y() const noexcept
	{
		return coord.Y();
	}

	/// @brief Get the z component, only available when DIM >= 3
	/// @return The z component
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 3, int> = 0>
	[[nodiscard]] constexpr const Scalar& Z() const noexcept
	{
		return coord.Z();
	}

	/// @brief Get the w component, only available when DIM >= 4
	/// @return The w component
	template<int DIM2 = DIM, std::enable_if_t<DIM2 >= 4, int> = 0>
	[[nodiscard]] constexpr const Scalar& W() const noexcept
	{
		return coord.W();
	}

	/// @brief Get the intrinsic coordinate of the direction
	/// @return The coordinate
	[[nodiscard]] constexpr const CoordType& Coord() const noexcept
	{
		return coord;
	}

	/// @brief Does the direction equal the other direction under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other direction
	/// @tparam OtherScalar2 The type of angle tolerance
	/// @param other The other direction
	/// @param tol The angle tolerance
	/// @return True if the angle difference is under the angle tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsEqual(const DirectionT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		return std::fabs(Angle(other)) <= tol;
	}

	/// @brief Is the direction perpendicular to the other direction under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other direction
	/// @tparam OtherScalar2 The type of angle tolerance
	/// @param other The other direction
	/// @param tol The angle tolerance
	/// @return True if the angle difference to pi/2 is under the angle tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsNormal(const DirectionT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		return std::fabs(Constants::half_pi - std::fabs(Angle(other))) <= tol;
	}

	/// @brief Is the direction opposite to the other direction under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other direction
	/// @tparam OtherScalar2 The type of angle tolerance
	/// @param other The other direction
	/// @param tol The angle tolerance
	/// @return True if the angle difference to pi is under the angle tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsOpposite(const DirectionT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		return Constants::pi - std::fabs(Angle(other)) <= tol;
	}

	/// @brief Is the direction parallel to the other direction under an angle tolerance
	/// @tparam OtherScalar The scalar type of the other direction
	/// @tparam OtherScalar2 The type of angle tolerance
	/// @param other The other direction
	/// @param tol The angle tolerance
	/// @return True if the angle difference to 0 or pi is under the angle tolerance
	template<typename OtherScalar, typename OtherScalar2>
	[[nodiscard]] bool IsParallel(const DirectionT<OtherScalar, DIM>& other, const OtherScalar2& tol) const noexcept
	{
		const auto angle = std::fabs(Angle(other));
		return angle <= tol || Constants::pi - angle <= tol;
	}

	/// @brief Compute the angle difference to the other direction in 2D
	/// @tparam OtherScalar The scalar type of the other direction
	/// @param other The other direction
	/// @return The angle difference to the other direction, range in [-pi, pi]
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] auto Angle(const DirectionT<OtherScalar, DIM>& other) const noexcept
	{
		const double cosine = coord.Dot(other.coord);
		const double sine = coord.Cross(other.coord);
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

	/// @brief Compute the angle difference to the other direction in 3D
	/// @tparam OtherScalar The scalar type of the other direction
	/// @param other The other direction
	/// @return The angle difference to the other direction, range in [0, pi]
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] auto Angle(const DirectionT<OtherScalar, DIM>& other) const noexcept
	{
		auto cosine = coord.Dot(other.Coord());
		if (cosine > -Constants::half_sqrt2 && cosine < Constants::half_sqrt2)
		{
			return std::acos(cosine);
		}
		else
		{
			auto sine = coord.Cross(other.Coord()).Norm();
			return cosine < 0.0 ? (Constants::pi - std::asin(sine)) : std::asin(sine);
		}
	}

	/// @brief Compute the angle difference to the other direction in terms of a reference direction as the z-axis, only available in 3D
	/// @details If the direction, the other direction and the reference direction forms a right-handed frame system, the angle is positive; otherwise, the angle is negative.
	/// @tparam OtherScalar The scalar type of the other direction
	/// @tparam OtherScalar2 The scalar type of the reference direction
	/// @param other The other direction
	/// @param ref The reference direction
	/// @return The angle difference to the other direction with a reference direction, range in [-pi, pi].
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] auto AngleWithRef(const DirectionT<OtherScalar, DIM>& other, const DirectionT<OtherScalar2, DIM>& ref) const noexcept
	{
		const auto cross = coord.Cross(other.Coord());
		const auto cosine = coord.Dot(other.Coord());
		const auto sine = cross.Norm();
		const auto angle = (cosine > -Constants::half_sqrt2 && cosine < Constants::half_sqrt2) ? std::acos(cosine) : (cosine < 0.0 ? (Constants::pi - std::asin(sine)) : std::asin(sine));
		return cross.Dot(ref.coord) >= 0.0 ? angle : -angle;
	}

	/// @brief 2D Cross product
	/// @tparam OtherScalar The scalar type of the other direction
	/// @param other The other direction
	/// @return The result of cross product, a scalar
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] constexpr auto Cross(const DirectionT<OtherScalar, DIM>& other) const noexcept
	{
		return coord.Cross(other.Coord());
	}

	/// @brief 3D Cross product
	/// @tparam OtherScalar The scalar type of the other direction
	/// @param other The other direction
	/// @return The result of cross product, a 3D direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] auto Cross(const DirectionT<OtherScalar, DIM>& other) const
	{
		return DirectionT(coord.Cross(other.Coord()));
	}

	/// @brief Dot product
	/// @tparam OtherScalar The scalar type of the other direction
	/// @param other The other direction
	/// @return The result of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const DirectionT<OtherScalar, DIM>& other) const noexcept
	{
		return coord.Dot(other.Coord());
	}

	/// @brief Dot product with a vector
	/// @tparam OtherScalar The scalar type of the vector
	/// @param other The vector
	/// @return The result of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const VectorT<OtherScalar, DIM>& other) const noexcept
	{
		return coord.Dot(other.Coord());
	}

	/// @brief Reverse the direction
	/// @return The reference to self
	constexpr DirectionT& Reverse() noexcept
	{
		coord.Reverse();
		return *this;
	}

	/// @brief Get the reversed direction
	/// @return The reversed direction
	[[nodiscard]] constexpr DirectionT Reversed() const noexcept
	{
		return DirectionT(*this).Reverse();
	}

	/// @brief Unary minus operator
	/// @return The reversed vector
	[[nodiscard]] constexpr DirectionT operator-() const noexcept
	{
		return Reversed();
	}

	/// @brief Mirror the direction by a direction
	/// @tparam OtherScalar The scalar type of the other direction
	/// @param dir The mirror direction
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr DirectionT& Mirror(const DirectionT<OtherScalar, DIM>& dir) noexcept
	{
		MatrixT<OtherScalar, DIM, DIM> mat1, mat2;
		mat1.SetDot(dir.Coord());
		mat2.SetIdentity();
		coord = (mat1 * 2.0 - mat2) * coord;
		return *this;
	}

	/// @brief Get the direction mirrored by a direction
	/// @tparam OtherScalar The scalar type of the other direction
	/// @param dir The mirror direction
	/// @return The mirrored direction
	template<typename OtherScalar>
	[[nodiscard]] constexpr DirectionT Mirrored(const DirectionT<OtherScalar, DIM>& dir) const noexcept
	{
		return DirectionT(*this).Mirror(dir);
	}

	/// @brief Mirror the direction by an axis
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The mirror axis
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr DirectionT& Mirror(const AxisT<OtherScalar, DIM>& axis) noexcept
	{
		return Mirror(axis.Direction());
	}

	/// @brief Get the direction mirrored by an axis
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The mirror axis
	/// @return The mirrored direction
	template<typename OtherScalar>
	[[nodiscard]] constexpr DirectionT Mirrored(const AxisT<OtherScalar, DIM>& axis) const noexcept
	{
		return DirectionT(*this).Mirror(axis);
	}

	/// @brief Mirror the direction by a frame
	/// @tparam OtherScalar The scalar type of the frame
	/// @param frame The mirror frame
	/// @return The reference to self
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	constexpr DirectionT& Mirror(const FrameT<OtherScalar, DIM>& frame) noexcept
	{
		return Mirror(frame.Direction()).Reverse();
	}

	/// @brief Get the direction mirrored by a frame
	/// @tparam OtherScalar The scalar type of the frame
	/// @param frame The mirror frame
	/// @return The mirrored direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] constexpr DirectionT Mirrored(const FrameT<OtherScalar, DIM>& frame) const noexcept
	{
		return DirectionT(*this).Mirror(frame);
	}

	/// @brief Rotate the direction by an angle in 2D
	/// @tparam OtherScalar The type of the rotation angle
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	DirectionT& Rotate(const OtherScalar& angle) noexcept
	{
		TransformationT<Scalar, DIM> tr;
		tr.SetRotation(PointT<Scalar, DIM>(0.0, 0.0), angle);
		coord = tr.HVectorialPart() * coord;
		return *this;
	}

	/// @brief Get the direction rotated by an angle in 2D
	/// @tparam OtherScalar The type of the rotation angle
	/// @param angle The rotation angle
	/// @return The rotated direction
	template<typename OtherScalar, int DIM2 = DIM, std::enable_if_t<DIM2 == 2, int> = 0>
	[[nodiscard]] DirectionT Rotated(const OtherScalar& angle) const noexcept
	{
		return DirectionT(*this).Rotate(angle);
	}

	/// @brief Rotate the direction by an axis and an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The reference to self
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	DirectionT& Rotate(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) noexcept
	{
		TransformationT<Scalar, DIM> tr;
		tr.SetRotation(axis, angle);
		coord = tr.HVectorialPart() * coord;
		return *this;
	}

	/// @brief Get the direction rotated by an axis and an angle in 3D
	/// @tparam OtherScalar The scalar type of the rotation axis
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotation axis
	/// @param angle The rotation angle
	/// @return The rotated direction
	template<typename OtherScalar, typename OtherScalar2, int DIM2 = DIM, std::enable_if_t<DIM2 == 3, int> = 0>
	[[nodiscard]] DirectionT Rotated(const AxisT<OtherScalar, DIM>& axis, const OtherScalar2& angle) const noexcept
	{
		return DirectionT(*this).Rotate(axis, angle);
	}

	/// @brief Transform the direction
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The reference to self
	template<typename OtherScalar>
	DirectionT& Transform(const TransformationT<OtherScalar, DIM>& tr) noexcept
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
			if (tr.ScaleFactor() < 0.0)
			{
				coord.Reverse();
			}
		}
		else
		{
			coord = tr.HVectorialPart() * coord;
			coord.Normalize();
			if (tr.ScaleFactor() < 0.0)
			{
				coord.Reverse();
			}
		}
		return *this;
	}

	/// @brief Get the transformed direction
	/// @tparam OtherScalar The scalar type of the transformation
	/// @param tr The transformation
	/// @return The transformed direction
	template<typename OtherScalar>
	[[nodiscard]] DirectionT Transformed(const TransformationT<OtherScalar, DIM>& tr) const noexcept
	{
		return DirectionT(*this).Transform(tr);
	}

	/// @brief Write the direction
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param dir The direction
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const DirectionT& dir)
	{
		os << dir.coord;
		return os;
	}

	/// @brief Read The direction
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param dir The direction
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, DirectionT& dir)
	{
		is >> dir.coord;
		dir.coord.Normalize();
		return is;
	}

#ifndef DOXYGEN_SKIP
protected:
	/// @brief Check the validity of direction
	void CheckValidity() const
	{
		if (coord.SquaredNorm() <= std::numeric_limits<Scalar>::min())
		{
			throw ConstructionError("coordinate has zero norm");
		}
	}

	friend class AxisT<Scalar, DIM>;
	friend class FrameT<Scalar, DIM>;

	/// @brief Underlying coordinate of direction
	CoordType coord;
#endif
};

/// @brief 2D direction
using Direction2 = DirectionT<double, 2>;

/// @brief 3D direction
using Direction3 = DirectionT<double, 3>;

} // namespace AMCAX
