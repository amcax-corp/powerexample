/// @file      QuaternionT.hpp
/// @brief     Class of quaternion
/// @details   Implementation of quaternion
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/MatrixT.hpp>

namespace AMCAX
{
/// @brief Class of quaternion
/// @details A quaternion is defined as a four dimensional coordinate (x, y, z, w).
///          In particular, q = x * i + y * j + z * k + w,
///          where i * i = j * j = k * k = -1,
///                i * j = -j * i = k, j * k = -k * j = i, k * i = -i * k = j
/// @tparam Scalar Underlying scalar type of quaternion
template<typename Scalar>
class QuaternionT
{
	template<typename ScalarType, typename RetType>
	using ReturnCustom = std::enable_if_t<sizeof(ScalarType) >= 0, RetType>;
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, QuaternionT<ScalarType>>;
	template<typename ScalarType>
	using ReturnCoord = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, 3>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, QuaternionT&>;

public:
	/// @brief Default constructor
	/// @details The default quaternion is (0, 0, 0, 1)
	constexpr QuaternionT() noexcept
		: coord(Scalar{0}, Scalar{0}, Scalar{0}, Scalar{1})
	{
	}

	/// @brief Construct from values
	/// @tparam T1,T2,T3,T4 The type of values
	/// @param x,y,z,w The coordinate values
	template<typename T1, typename T2, typename T3, typename T4, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3, T4>, int> = 0>
	constexpr QuaternionT(T1&& x, T2&& y, T3&& z, T4&& w) noexcept
		: coord(std::forward<T1>(x), std::forward<T2>(y), std::forward<T3>(z), std::forward<T4>(w))
	{
	}

	/// @brief Construct from two vector, representing the rotation from the source vector to the target vector
	/// @tparam OtherScalar The scalar of the source vector
	/// @tparam OtherScalar2 The scalar of the target vector
	/// @param vecFrom The source vector
	/// @param vecTo The target vector
	template<typename OtherScalar, typename OtherScalar2>
	QuaternionT(const CoordT<OtherScalar, 3>& vecFrom, const CoordT<OtherScalar2, 3>& vecTo) noexcept
	{
		SetRotation(vecFrom, vecTo);
	}

	/// @brief Construct from three vector, representing the rotation around an axis vector from the source vector to the target vector
	/// @tparam OtherScalar The scalar type of the source vector
	/// @tparam OtherScalar2 The scalar type of the target vector
	/// @tparam OtherScalar3 The scalar type of the rotation axis vector
	/// @param vecFrom The source vector
	/// @param vecTo The target vector
	/// @param vecAxis The rotation axis vector
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3>
	QuaternionT(const CoordT<OtherScalar, 3>& vecFrom, const CoordT<OtherScalar2, 3>& vecTo, const CoordT<OtherScalar3, 3>& vecAxis) noexcept
	{
		SetRotation(vecFrom, vecTo, vecAxis);
	}

	/// @brief Construct from an axis and an angle
	/// @tparam OtherScalar The scalar type of the axis vector
	/// @tparam OtherScalar2 The type of the rotation angle
	/// @param axis The rotation axis vector
	/// @param angle The rotation angle
	template<typename OtherScalar, typename OtherScalar2>
	QuaternionT(const CoordT<OtherScalar, 3>& axis, const OtherScalar2& angle) noexcept
	{
		SetAxisAngle(axis, angle);
	}

	/// @brief Construct from a rotation matrix
	/// @tparam OtherScalar The scalar type of the matrix
	/// @param mat The rotation matrix
	template<typename OtherScalar>
	constexpr explicit QuaternionT(const MatrixT<OtherScalar, 3, 3>& mat) noexcept
	{
		SetMatrix(mat);
	}

	/// @brief Is the quaternion equal to the other quaternion
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param other The other quaternion
	/// @return True if the two quaternions are equal
	template<typename OtherScalar>
	[[nodiscard]] auto IsEqual(const QuaternionT<OtherScalar>& other) const noexcept -> ReturnCustom<decltype(std::declval<Scalar>() - std::declval<OtherScalar>()), bool>
	{
		if (this == &other)
		{
			return true;
		}
		constexpr auto tol = std::numeric_limits<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>::min();
		return std::fabs(coord[0] - other.coord[0]) <= tol && std::fabs(coord[1] - other.coord[1]) <= tol && std::fabs(coord[2] - other.coord[2]) <= tol && std::fabs(coord[3] - other.coord[3]) <= tol;
	}

	/// @brief Set the quaternion as the rotation from a source vector to a target vector
	/// @tparam OtherScalar The scalar type of the source vector
	/// @tparam OtherScalar2 The scalar type of the target vector
	/// @param vecFrom The source vector
	/// @param vecTo The target vector
	template<typename OtherScalar, typename OtherScalar2>
	void SetRotation(const CoordT<OtherScalar, 3>& vecFrom, const CoordT<OtherScalar2, 3>& vecTo) & noexcept
	{
		auto vec = vecFrom.Cross(vecTo);
		Set(vec.X(), vec.Y(), vec.Z(), vecFrom.Dot(vecTo));
		Normalize();
		coord[3] += Scalar{1};
		if (coord[3] <= std::numeric_limits<Scalar>::min())
		{
			if (vecFrom.Z() * vecFrom.Z() > vecFrom.X() * vecFrom.X())
			{
				Set(Scalar{0}, vecFrom.Z(), -vecFrom.Y(), coord[3]);
			}
			else
			{
				Set(vecFrom.Y(), -vecFrom.X(), Scalar{0}, coord[3]);
			}
		}
		Normalize();
	}

	/// @brief Set the quaternion as the rotation around an axis from a source vector to a target vector
	/// @tparam OtherScalar The scalar type of the source vector
	/// @tparam OtherScalar2 The scalar type of the target vector
	/// @tparam OtherScalar3 The scalar type of the rotation axis vector
	/// @param vecFrom The source vector
	/// @param vecTo The target vector
	/// @param vecAxis The rotation axis vector
	template<typename OtherScalar, typename OtherScalar2, typename OtherScalar3>
	void SetRotation(const CoordT<OtherScalar, 3>& vecFrom, const CoordT<OtherScalar2, 3>& vecTo, const CoordT<OtherScalar3, 3>& vecAxis) & noexcept
	{
		auto vec = vecFrom.Cross(vecTo);
		Set(vec.X(), vec.Y(), vec.Z(), vecFrom.Dot(vecTo));
		Normalize();
		coord[3] += Scalar{1};
		if (coord[3] <= std::numeric_limits<Scalar>::min())
		{
			auto vec = vecFrom.Cross(vecAxis);
			Set(vec.X(), vec.Y(), vec.Z(), coord[3]);
		}
		Normalize();
	}

	/// @brief Set the quaternion from an axis and an angle
	/// @tparam OtherScalar The scalar type of the axis
	/// @tparam OtherScalar2 The type of the angle
	/// @param axis The axis
	/// @param angle The angle
	template<typename OtherScalar, typename OtherScalar2>
	void SetAxisAngle(const CoordT<OtherScalar, 3>& axis, const OtherScalar2& angle) & noexcept
	{
		const auto axis2 = axis.Normalized() * std::sin(angle * OtherScalar2{0.5});
		Set(axis2.X(), axis2.Y(), axis2.Z(), std::cos(angle * OtherScalar2{0.5}));
	}

	/// @brief Get the axis and angle from a quaternion
	/// @tparam OtherScalar The scalar type of the axis
	/// @tparam OtherScalar2 The type of the angle
	/// @param[out] axis The axis
	/// @param[out] angle The angle
	template<typename OtherScalar, typename OtherScalar2>
	void GetAxisAngle(CoordT<OtherScalar, 3>& axis, OtherScalar2& angle) const noexcept
	{
		const Scalar vl = std::sqrt(coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2]);
		if (vl > std::numeric_limits<Scalar>::min())
		{
			const Scalar ivl = Scalar{1} / vl;
			axis.SetCoord(coord[0] * ivl, coord[1] * ivl, coord[2] * ivl);
			angle = static_cast<OtherScalar2>(coord[3] < Scalar{0} ? Scalar{2} * std::atan2(-vl, -coord[3]) : Scalar{2} * std::atan2(vl, coord[3]));
		}
		else
		{
			axis.SetCoord(OtherScalar{0}, OtherScalar{0}, OtherScalar{1});
			angle = OtherScalar2{0};
		}
	}

	/// @brief Set the quaternion by a rotation matrix
	/// @tparam OtherScalar The scalar type of the matrix
	/// @param mat The matrix
	template<typename OtherScalar>
	constexpr void SetMatrix(const MatrixT<OtherScalar, 3, 3>& mat) & noexcept
	{
		OtherScalar tr = mat(0, 0) + mat(1, 1) + mat(2, 2);
		if (tr > OtherScalar{0})
		{
			Set(mat(2, 1) - mat(1, 2), mat(0, 2) - mat(2, 0), mat(1, 0) - mat(0, 1), tr + OtherScalar{1});
			operator*=(Scalar{0.5} / std::sqrt(coord[3]));
		}
		else if ((mat(0, 0) > mat(1, 1)) && (mat(0, 0) > mat(2, 2)))
		{
			Set(OtherScalar{1} + mat(0, 0) - mat(1, 1) - mat(2, 2), mat(0, 1) + mat(1, 0), mat(0, 2) + mat(2, 0), mat(2, 1) - mat(1, 2));
			operator*=(Scalar{0.5} / std::sqrt(coord[0]));
		}
		else if (mat(1, 1) > mat(2, 2))
		{
			Set(mat(0, 1) + mat(1, 0), OtherScalar{1} + mat(1, 1) - mat(0, 0) - mat(2, 2), mat(1, 2) + mat(2, 1), mat(0, 2) - mat(2, 0));
			operator*=(Scalar{0.5} / std::sqrt(coord[1]));
		}
		else
		{
			Set(mat(0, 2) + mat(2, 0), mat(1, 2) + mat(2, 1), OtherScalar{1} + mat(2, 2) - mat(0, 0) - mat(1, 1), mat(1, 0) - mat(0, 1));
			operator*=(Scalar{0.5} / std::sqrt(coord[2]));
		}
	}

	/// @brief Get the rotation matrix from the quaternion
	/// @return The rotation matrix
	[[nodiscard]] constexpr MatrixT<Scalar, 3, 3> GetMatrix() const noexcept
	{
		Scalar s = Scalar{2} / SquaredNorm();
		Scalar x2 = coord[0] * s;
		Scalar y2 = coord[1] * s;
		Scalar z2 = coord[2] * s;
		Scalar xx = coord[0] * x2;
		Scalar xy = coord[0] * y2;
		Scalar xz = coord[0] * z2;
		Scalar yy = coord[1] * y2;
		Scalar yz = coord[1] * z2;
		Scalar zz = coord[2] * z2;
		Scalar wx = coord[3] * x2;
		Scalar wy = coord[3] * y2;
		Scalar wz = coord[3] * z2;
		return {Scalar{1} - (yy + zz), xy - wz, xz + wy,
			xy + wz, Scalar{1} - (xx + zz), yz - wx,
			xz - wy, yz + wx, Scalar{1} - (xx + yy)};
	}

	/// @brief Set the coordinates of quaternion
	/// @tparam T1,T2,T3,T4 The types of values
	/// @param x,y,z,w The coordinate values
	template<typename T1, typename T2, typename T3, typename T4, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3, T4>, int> = 0>
	constexpr void Set(T1&& x, T2&& y, T3&& z, T4&& w) & noexcept
	{
		coord.SetCoord(std::forward<T1>(x), std::forward<T2>(y), std::forward<T3>(z), std::forward<T4>(w));
	}

	/// @brief Set the quaternion by another quaternion
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param q The other quaternion
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void Set(const QuaternionT<OtherScalar>& q) & noexcept
	{
		coord.SetCoord(q.X(), q.Y(), q.Z(), q.W());
	}

	/// @brief Get the x component
	/// @return The x component
	[[nodiscard]] constexpr auto X() const noexcept
	{
		return coord.X();
	}

	/// @brief Get the y component
	/// @return The y component
	[[nodiscard]] constexpr auto Y() const noexcept
	{
		return coord.Y();
	}

	/// @brief Get the z component
	/// @return The z component
	[[nodiscard]] constexpr auto Z() const noexcept
	{
		return coord.Z();
	}

	/// @brief Get the w component
	/// @return The w component
	[[nodiscard]] constexpr auto W() const noexcept
	{
		return coord.W();
	}

	/// @brief Get the underlying coordinate
	/// @return The underlying coordinate
	constexpr const CoordT<Scalar, 4>& Coord() const noexcept
	{
		return coord;
	}

	/// @brief Set the quaternion as identity
	constexpr void SetIdentity() & noexcept
	{
		coord.SetCoord(Scalar{0}, Scalar{0}, Scalar{0}, Scalar{1});
	}

	/// @brief Reverse the quaternion (conjugate)
	/// @return The reference to self
	constexpr QuaternionT& Reverse() noexcept
	{
		coord[0] = -coord[0];
		coord[1] = -coord[1];
		coord[2] = -coord[2];
		return *this;
	}

	/// @brief Get the reversed (conjugate) quaternion
	/// @return The reversed quaternion
	[[nodiscard]] constexpr QuaternionT Reversed() const noexcept
	{
		return {-coord[0], -coord[1], -coord[2], coord[3]};
	}

	/// @brief Invert the quaternion
	/// @return The reference to self
	constexpr QuaternionT& Invert() noexcept
	{
		auto norm = SquaredNorm();
		coord.SetCoord(-coord[0] / norm, -coord[1] / norm, -coord[2] / norm, coord[3] / norm);
		return *this;
	}

	/// @brief Get the inverted quaternion
	/// @return The inverted quaternion
	[[nodiscard]] constexpr QuaternionT Inverted() const noexcept
	{
		auto norm = SquaredNorm();
		return {-coord[0] / norm, -coord[1] / norm, -coord[2] / norm, coord[3] / norm};
	}

	/// @brief Compute the norm of the quaternion
	/// @return The norm of the quaternion
	[[nodiscard]] auto Norm() const noexcept
	{
		return std::sqrt(SquaredNorm());
	}

	/// @brief Compute the squared norm of the quaternion
	/// @return The squared norm of the quaternion
	[[nodiscard]] constexpr auto SquaredNorm() const noexcept
	{
		return coord.SquaredNorm();
	}

	/// @brief Stabilize the length of quaternion, thus avoiding the length approaching zero or infinity
	void StablilizeLength() & noexcept
	{
		Scalar c = std::fabs(coord[0]) + std::fabs(coord[1]) + std::fabs(coord[2]) + std::fabs(coord[3]);
		if (c > Scalar{0})
		{
			coord /= c;
		}
		else
		{
			SetIdentity();
		}
	}

	/// @brief Normalize the quaternion
	/// @return The reference to self
	QuaternionT& Normalize() noexcept
	{
		auto norm = Norm();
		if (norm < std::numeric_limits<decltype(norm)>::min())
		{
			StablilizeLength();
			norm = Norm();
		}
		coord /= norm;
		return *this;
	}

	/// @brief Get the normalized quaternion
	/// @return The normalized quaternion
	[[nodiscard]] QuaternionT Normalized() const noexcept
	{
		return QuaternionT(*this).Normalize();
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param other The other quaternion
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator+=(const QuaternionT<OtherScalar>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		coord += other.coord;
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param other The other quaternion
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const QuaternionT<OtherScalar>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		return {coord[0] + other.X(), coord[1] + other.Y(), coord[2] + other.Z(), coord[3] + other.W()};
	}

	/// @brief Subtraction assignment
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param other The other quaternion
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator-=(const QuaternionT<OtherScalar>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		coord -= other.coord;
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The scalar type fo the other quaternion
	/// @param other The other quaternion
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const QuaternionT<OtherScalar>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		return {coord[0] - other.X(), coord[1] - other.Y(), coord[2] - other.Z(), coord[3] - other.W()};
	}

	/// @brief Scalar multiplication assignment
	/// @tparam OtherScalar The type of the scalar value
	/// @param scalar The scalar value
	/// @return The reference to self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		coord *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of the scalar value
	/// @param scalar The scalar value
	/// @return The scalar multiplied quaternion
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {coord[0] * scalar, coord[1] * scalar, coord[2] * scalar, coord[3] * scalar};
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @param q The quaternion
	/// @return The scalar multiplied quaternion
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	friend constexpr auto operator*(double scalar, const QuaternionT& q) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return {scalar * q.X(), scalar * q.Y(), scalar * q.Z(), scalar * q.W()};
	}

	/// @brief Multiplication assignment
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param other The other quaternion
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator*=(const QuaternionT<OtherScalar>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		auto result = operator*(other);
		coord[0] = static_cast<Scalar>(result.X());
		coord[1] = static_cast<Scalar>(result.Y());
		coord[2] = static_cast<Scalar>(result.Z());
		coord[3] = static_cast<Scalar>(result.W());
		return *this;
	}

	/// @brief Multiplication operator
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param other The other quaternion
	/// @return The quaternion multiplied by the other quaternion
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const QuaternionT<OtherScalar>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {coord[3] * other.X() + coord[0] * other.W() + coord[1] * other.Z() - coord[2] * other.Y(),
			coord[3] * other.Y() + coord[1] * other.W() + coord[2] * other.X() - coord[0] * other.Z(),
			coord[3] * other.Z() + coord[2] * other.W() + coord[0] * other.Y() - coord[1] * other.X(),
			coord[3] * other.W() - coord[0] * other.X() - coord[1] * other.Y() - coord[2] * other.Z()};
	}

	/// @brief Multiplication of vector, i.e. rotate the vector by the quaternion
	/// @tparam OtherScalar The scalar type of the vector
	/// @param vec The vector
	/// @return The rotated vector
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, 3>& vec) const noexcept -> ReturnCoord<decltype(std::declval<Scalar>() * (std::declval<OtherScalar>() * std::declval<Scalar>()))>
	{
		using TypeA = decltype(std::declval<OtherScalar>() * std::declval<Scalar>());
		using TypeB = decltype(std::declval<Scalar>() * std::declval<TypeA>());
		const QuaternionT<TypeA> q(
			vec.X() * coord[3] + vec.Z() * coord[1] - vec.Y() * coord[2],
			vec.Y() * coord[3] + vec.X() * coord[2] - vec.Z() * coord[0],
			vec.Z() * coord[3] + vec.Y() * coord[0] - vec.X() * coord[1],
			vec.X() * coord[0] + vec.Y() * coord[1] + vec.Z() * coord[2]);
		return CoordT<TypeB, 3>{
				   coord[3] * q.X() + coord[0] * q.W() + coord[1] * q.Z() - coord[2] * q.Y(),
				   coord[3] * q.Y() + coord[1] * q.W() + coord[2] * q.X() - coord[0] * q.Z(),
				   coord[3] * q.Z() + coord[2] * q.W() + coord[0] * q.Y() - coord[1] * q.X()} /
			SquaredNorm();
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of the scalar value
	/// @param scalar The scalar value
	/// @return The reference to self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		coord /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of the scalar value
	/// @param scalar The scalar value
	/// @return The quaternion divided by the scalar
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {coord[0] / scalar, coord[1] / scalar, coord[2] / scalar, coord[3] / scalar};
	}

	/// @brief Unary minus operator
	/// @return The minus quaternion
	[[nodiscard]] constexpr QuaternionT operator-() const noexcept
	{
		return {-coord[0], -coord[1], -coord[2], -coord[3]};
	}

	/// @brief Dot product
	/// @tparam OtherScalar The scalar type of the other quaternion
	/// @param other The other quaternion
	/// @return The result of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const QuaternionT<OtherScalar>& other) const noexcept
	{
		return coord.Dot(other.Coord());
	}

	/// @brief Get the rotation angle from the quaternion
	/// @return The rotation angle
	[[nodiscard]] auto GetRotationAngle() const noexcept
	{
		if (coord[3] < 0.0)
		{
			return Scalar{2} * std::atan2(-std::sqrt(coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2]), -coord[3]);
		}
		else
		{
			return Scalar{2} * std::atan2(std::sqrt(coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2]), coord[3]);
		}
	}

private:
	/// @brief Underlying coordinate of quaternion
	CoordT<Scalar, 4> coord;
};
} // namespace AMCAX
