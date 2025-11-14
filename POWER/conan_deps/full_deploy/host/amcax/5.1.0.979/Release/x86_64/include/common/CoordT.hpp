/// @file      CoordT.hpp
/// @brief     Class of coordinate
/// @details   Implementation of Cartesian coordinates
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numeric>

#include <common/Constants.hpp>
#include <common/Exception.hpp>
#include <common/Macros.hpp>
#include <common/TypeTraits.hpp>

namespace AMCAX
{
/// @brief Base class of coordinate
/// @tparam Scalar The scalar type
/// @tparam DIM The dimension
template<typename Scalar, int DIM>
class CoordBase
{
	static_assert(DIM >= 1, "Invalid dimensionality.");

public:
	/// @brief Get the raw pointer to the data
	/// @return The pointer to the data
	[[nodiscard]] constexpr Scalar* Data() noexcept
	{
		return values.data();
	}

	/// @brief Get the raw pointer to the constant data
	/// @return The pointer to the constant data
	[[nodiscard]] constexpr const Scalar* Data() const noexcept
	{
		return values.data();
	}

	/// @brief Get the component at index i (0 <= i < DIM)
	/// @param i The index
	/// @return The reference to the i-th component
	[[nodiscard]] constexpr Scalar& operator[](int i) noexcept
	{
		assert(i >= 0 && i < DIM);
		return values[static_cast<size_t>(i)];
	}

	/// @brief Get the constant component at index i (0 <= i < DIM)
	/// @param i The index
	/// @return The reference to the constant i-th component
	[[nodiscard]] constexpr const Scalar& operator[](int i) const noexcept
	{
		assert(i >= 0 && i < DIM);
		return values[static_cast<size_t>(i)];
	}

	/// @brief Set the coordinates from each component, the type should be exactly the same
	/// @tparam ...Ts The types of values
	/// @param ...vs The values
	template<typename... Ts, std::enable_if_t<static_cast<int>(sizeof...(Ts)) == DIM && are_convertible_v<Scalar, Ts...>, int> = 0>
	constexpr void SetCoord(Ts&&... vs) & noexcept
	{
		values = {{std::forward<Ts>(vs)...}};
	}

	/// @brief Swap the contents of two coordinates
	/// @param other The other coordinate
	constexpr void swap(CoordBase& other) noexcept
	{
		swap_c(values, other.values);
	}

	/// @brief Get the dimension of the coordinate
	/// @return The dimension of the coordinate
	[[nodiscard]] static constexpr int Size() noexcept
	{
		return DIM;
	}

	/// @brief Get the iterator of the first component
	/// @return The begin iterator
	[[nodiscard]] constexpr auto begin() noexcept
	{
		return values.begin();
	}

	/// @brief Get the const iterator of the first component
	/// @return The const begin iterator
	[[nodiscard]] constexpr auto begin() const noexcept
	{
		return values.begin();
	}

	/// @brief Get the const iterator of the first component
	/// @return The const begin iterator
	[[nodiscard]] constexpr auto cbegin() const noexcept
	{
		return values.cbegin();
	}

	/// @brief Get the iterator after the last component
	/// @return The end iterator
	[[nodiscard]] constexpr auto end() noexcept
	{
		return values.end();
	}

	/// @brief Get the const iterator after the last component
	/// @return The const end iterator
	[[nodiscard]] constexpr auto end() const noexcept
	{
		return values.end();
	}

	/// @brief Get the const iterator after the last component
	/// @return The begin iterator
	[[nodiscard]] constexpr auto cend() const noexcept
	{
		return values.cend();
	}

	/// @brief Get the reverse iterator of the last component
	/// @return The reverse begin iterator
	[[nodiscard]] constexpr auto rbegin() noexcept
	{
		return values.rbegin();
	}

	/// @brief Get the reverse const iterator of the last component
	/// @return The reverse const begin iterator
	[[nodiscard]] constexpr auto rbegin() const noexcept
	{
		return values.rbegin();
	}

	/// @brief Get the reverse const iterator of the last component
	/// @return The reverse const begin iterator
	[[nodiscard]] constexpr auto crbegin() const noexcept
	{
		return values.crbegin();
	}

	/// @brief Get the reverse iterator before the first component
	/// @return The reverse end iterator
	[[nodiscard]] constexpr auto rend() noexcept
	{
		return values.rend();
	}

	/// @brief Get the reverse const iterator before the first component
	/// @return The reverse const end iterator
	[[nodiscard]] constexpr auto rend() const noexcept
	{
		return values.rend();
	}

	/// @brief Get the reverse const iterator before the first component
	/// @return The reverse const end iterator
	[[nodiscard]] constexpr auto crend() const noexcept
	{
		return values.crend();
	}

protected:
	/// @brief Default constructor
	/// @details The coordinates are initialized as zero
	constexpr CoordBase() noexcept
		: values{}
	{
	}

	/// @brief Construct from values
	/// @tparam ...Ts Types of values
	/// @param ...vs The values
	template<typename... Ts, std::enable_if_t<static_cast<int>(sizeof...(Ts)) == DIM && are_convertible_v<Scalar, Ts...>, int> = 0>
	constexpr CoordBase(Ts&&... vs) noexcept
		: values{{std::forward<Ts>(vs)...}}
	{
	}

	/// @brief Underlying array of values
	std::array<Scalar, DIM> values;
};

/// @brief The class of Cartesian coordinates
/// @tparam Scalar Underlying type of coordinates
/// @tparam DIM The dimension of the coordinate
template<typename Scalar, int DIM>
class CoordT : public CoordBase<Scalar, DIM>
{
	static_assert(DIM >= 1, "Invalid dimensionality.");
	using CoordBase<Scalar, DIM>::values;
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, DIM>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, CoordT&>;

public:
	/// @brief Default constructor
	/// @details The coordinates are initialized as zero
	constexpr CoordT() noexcept = default;

	/// @brief Construct from values
	/// @tparam ...Ts Types of values
	/// @param ...vs The values
	template<typename... Ts, std::enable_if_t<static_cast<int>(sizeof...(Ts)) == DIM && are_convertible_v<Scalar, Ts...>, int> = 0>
	constexpr CoordT(Ts&&... vs) noexcept
		: CoordBase<Scalar, DIM>(std::forward<Ts>(vs)...)
	{
	}

	/// @brief Fill the coordinates by (v, v, ..., v)
	/// @tparam OtherScalar Type of the value
	/// @param v The value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const OtherScalar& v) noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			values[i] = v;
		}
	}

	/// @brief Contruct from other coordinate
	/// @tparam OtherScalar The type of other coordinate
	/// @param other Other coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const CoordT<OtherScalar, DIM>& other) noexcept
	{
		operator=(other);
	}

	/// @brief Set the value of x-coordinate, only available when DIM >= 1
	/// @tparam OtherScalar The type of the input value
	/// @param x New x-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetX(const OtherScalar& x) & noexcept
	{
		values[0] = x;
	}

	/// @brief Set the value of y-coordinate, only available when DIM >= 2
	/// @tparam OtherScalar The type of the input value
	/// @param y New y-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetY(const OtherScalar& y) & noexcept
	{
		values[1] = y;
	}

	/// @brief Set the value of z-coordinate, only available when DIM >= 3
	/// @tparam OtherScalar The type of the input value
	/// @param z New z-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetZ(const OtherScalar& z) & noexcept
	{
		values[2] = z;
	}

	/// @brief Set the value of w-coordinate, only available when DIM >= 4
	/// @tparam OtherScalar The type of the input value
	/// @param w New w-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetW(const OtherScalar& w) & noexcept
	{
		values[3] = w;
	}

	/// @brief Get x-coordinate, only available when DIM >= 1
	/// @return The reference to the x-coordinate
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return values[0];
	}

	/// @brief Get y-coordinate, only available when DIM >= 2
	/// @return The reference to the y-coordinate
	[[nodiscard]] constexpr const Scalar& Y() const noexcept
	{
		return values[1];
	}

	/// @brief Get z-coordinate, only available when DIM >= 3
	/// @return The reference to the z-coordinate
	[[nodiscard]] constexpr const Scalar& Z() const noexcept
	{
		return values[2];
	}

	/// @brief Get w-coordinate, only available when DIM >= 4
	/// @return The reference to the w-coordinate
	[[nodiscard]] constexpr const Scalar& W() const noexcept
	{
		return values[3];
	}

	/// @brief Copy assignment operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param rhs The right-hand side of the assignment operator
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator=(const CoordT<OtherScalar, DIM>& rhs) noexcept -> ReturnThis<OtherScalar>
	{
		for (int i = 0; i < DIM; i++)
		{
			values[i] = static_cast<Scalar>(rhs[i]);
		}
		return *this;
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator+=(const CoordT<OtherScalar, DIM>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		for (int i = 0; i < DIM; ++i)
		{
			values[i] += other[i];
		}
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const CoordT<OtherScalar, DIM>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		CoordT<decltype(std::declval<Scalar>() + std::declval<OtherScalar>()), DIM> result;
		for (int i = 0; i < DIM; i++)
		{
			result[i] = values[i] + other[i];
		}
		return result;
	}

	/// @brief Subtraction assignement
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator-=(const CoordT<OtherScalar, DIM>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		for (int i = 0; i < DIM; ++i)
		{
			values[i] -= other[i];
		}
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const CoordT<OtherScalar, DIM>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		CoordT<decltype(std::declval<Scalar>() - std::declval<OtherScalar>()), DIM> result;
		for (int i = 0; i < DIM; i++)
		{
			result[i] = values[i] - other[i];
		}
		return result;
	}

	/// @brief Scalar multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		for (int i = 0; i < DIM; i++)
		{
			values[i] *= scalar;
		}
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		CoordT<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), DIM> result;
		for (int i = 0; i < DIM; i++)
		{
			result[i] = values[i] * scalar;
		}
		return result;
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @param coord The coordinate
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] friend constexpr auto operator*(const OtherScalar& scalar, const CoordT& coord) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		CoordT<decltype(std::declval<OtherScalar>() * std::declval<Scalar>()), DIM> result;
		for (int i = 0; i < DIM; i++)
		{
			result[i] = scalar * coord[i];
		}
		return result;
	}

	/// @brief Component-wise multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator*=(const CoordT<OtherScalar, DIM>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		for (int i = 0; i < DIM; ++i)
		{
			values[i] *= other[i];
		}
		return *this;
	}

	/// @brief Component-wise multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The component-wise multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, DIM>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		CoordT<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), DIM> result;
		for (int i = 0; i < DIM; i++)
		{
			result[i] = values[i] * other[i];
		}
		return result;
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		for (int i = 0; i < DIM; i++)
		{
			values[i] /= scalar;
		}
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar division result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		CoordT<decltype(std::declval<Scalar>() / std::declval<OtherScalar>()), DIM> result;
		for (int i = 0; i < DIM; i++)
		{
			result[i] = values[i] / scalar;
		}
		return result;
	}

	/// @brief Component-wise division assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator/=(const CoordT<OtherScalar, DIM>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		for (int i = 0; i < DIM; ++i)
		{
			values[i] /= other[i];
		}
		return *this;
	}

	/// @brief Component-wise division operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The component-wise division result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const CoordT<OtherScalar, DIM>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		CoordT<decltype(std::declval<Scalar>() / std::declval<OtherScalar>()), DIM> result;
		for (int i = 0; i < DIM; i++)
		{
			result[i] = values[i] / other[i];
		}
		return result;
	}

	/// @brief Unary minus operator
	/// @return The opposite coordinate
	[[nodiscard]] constexpr CoordT operator-() const noexcept
	{
		CoordT v;
		for (int i = 0; i < DIM; i++)
		{
			v[i] = -values[i];
		}
		return v;
	}

	/// @brief Dot product
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product.
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator|(const CoordT<OtherScalar, DIM>& other) const noexcept -> decltype(*this->Data() * *other.Data())
	{
		auto s = values[0] * other[0];
		for (int i = 1; i < DIM; i++)
		{
			s += values[i] * other[i];
		}
		return s;
	}

	/// @brief Dot product
	/// @tparam OtherScalar the type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const CoordT<OtherScalar, DIM>& other) const noexcept -> decltype(*this | other)
	{
		return operator|(other);
	}

	/// @brief Squared norm
	/// @return The squared norm
	[[nodiscard]] constexpr Scalar SquaredNorm() const noexcept
	{
		Scalar s = values[0] * values[0];
		for (int i = 1; i < DIM; i++)
		{
			s += values[i] * values[i];
		}
		return s;
	}

	/// @brief Norm of coordinate
	/// @return The norm of coordinate
	[[nodiscard]] Scalar Norm() const noexcept
	{
		return static_cast<Scalar>(std::sqrt(SquaredNorm()));
	}

	/// @brief Normalize the coordinate
	/// @return The reference of self
	CoordT& Normalize() noexcept
	{
		Scalar n = SquaredNorm();
		if (n != Scalar{0})
		{
			return operator/=(static_cast<Scalar>(std::sqrt(n)));
		}
		return *this;
	}

	/// @brief Normalized coordinate
	/// @return The normalized coordinate
	[[nodiscard]] CoordT Normalized() const noexcept
	{
		return CoordT(*this).Normalize();
	}

	/// @brief Reverse coordinate
	/// @return The reference of self
	constexpr decltype(auto) Reverse() noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			values[i] = -values[i];
		}
		return *this;
	}

	/// @brief Reversed coordinate
	/// @return The reversed coordinate
	[[nodiscard]] constexpr auto Reversed() const noexcept
	{
		return operator-();
	}

	/// @brief Get the maximal component
	/// @return The value of maximal component
	[[nodiscard]] constexpr Scalar Max() const noexcept
	{
		Scalar result = values[0];
		for (int i = 1; i < DIM; i++)
		{
			if (result < values[i])
			{
				result = values[i];
			}
		}
		return result;
	}

	/// @brief Get the maximal absolute component
	/// @return The value of maximal absolute component
	[[nodiscard]] Scalar MaxAbs() const noexcept
	{
		Scalar result = std::abs(values[0]);
		for (int i = 1; i < DIM; i++)
		{
			Scalar v = std::abs(values[i]);
			if (result < v)
			{
				result = v;
			}
		}
		return result;
	}

	/// @brief Get the minimal component
	/// @return The value of minimal component
	[[nodiscard]] constexpr Scalar Min() const noexcept
	{
		Scalar result= values[0];
		for (int i = 1; i < DIM; i++)
		{
			if (result > values[i])
			{
				result = values[i];
			}
		}
		return result;
	}

	/// @brief Get the minimal absolute component
	/// @return The value of minimal absolute component
	[[nodiscard]] Scalar MinAbs() const noexcept
	{
		Scalar result = std::abs(values[0]);
		for (int i = 1; i < DIM; i++)
		{
			Scalar v = std::abs(values[i]);
			if (result > v)
			{
				result = v;
			}
		}
		return result;
	}

	/// @brief Component-wise minimize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Minimize(const CoordT& other) noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			if (values[i] > other[i])
			{
				values[i] = other[i];
			}
		}
		return *this;
	}

	/// @brief Component-wise maximize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Maximize(const CoordT& other) noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			if (values[i] < other[i])
			{
				values[i] = other[i];
			}
		}
		return *this;
	}

	/// @brief Compute component-wise minimized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise minimized coordinate
	[[nodiscard]] constexpr CoordT Min(const CoordT& other) const noexcept
	{
		return CoordT(*this).Minimize(other);
	}

	/// @brief Compute component-wise maximized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise maximized coordinate
	[[nodiscard]] constexpr CoordT Max(const CoordT& other) const noexcept
	{
		return CoordT(*this).Maximize(other);
	}

	/// @brief Fill the coordinate with a scalar
	/// @param s The scalar
	/// @return The reference of self
	constexpr CoordT& fill(const Scalar& s) noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			values[i] = s;
		}
		return *this;
	}

	/// @brief Does the coordinate equal the other coordinate under a specific tolerance
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @param tol The tolerance
	/// @return True if all the component difference is less than the tolerance
	template<typename OtherScalar>
	[[nodiscard]] bool IsEqual(const CoordT<OtherScalar, DIM>& other, const Scalar& tol) const noexcept
	{
		return operator-(other).MaxAbs() <= tol;
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates coincide exactly
	[[nodiscard]] constexpr bool operator==(const CoordT& other) const noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			if (values[i] != other[i])
			{
				return false;
			}
		}
		return true;
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates do not coincide exactly
	[[nodiscard]] constexpr bool operator!=(const CoordT& other) const noexcept
	{
		return !operator==(other);
	}

	/// @brief Is less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<(const CoordT& other) const noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			if (values[i] < other[i])
			{
				return true;
			}
			else if (values[i] > other[i])
			{
				return false;
			}
		}
		return false;
	}

	/// @brief Is greater the other coordinate than using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>(const CoordT& other) const noexcept
	{
		return other < *this;
	}

	/// @brief Not greater than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<=(const CoordT& other) const noexcept
	{
		return !(other < *this);
	}

	/// @brief Not less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>=(const CoordT& other) const noexcept
	{
		return !operator<(other);
	}

	/// @brief Write the coordinate
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param coord The coordinate
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const CoordT& coord)
	{
		os << coord.values[0];
		for (int i = 1; i < DIM; i++)
		{
			os << " " << coord.values[i];
		}
		return os;
	}

	/// @brief Read the coordinate
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param coord The coordinate
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, CoordT& coord)
	{
		for (int i = 0; i < DIM; i++)
		{
			is >> coord.values[i];
		}
		return is;
	}
};

/// @brief The specialized class of 1D Cartesian coordinates
/// @tparam Scalar Underlying type of coordinates
/// @tparam DIM The dimension of the coordinate
template<typename Scalar>
class CoordT<Scalar, 1> : public CoordBase<Scalar, 1>
{
	using CoordBase<Scalar, 1>::values;
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, 1>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, CoordT&>;

public:
	/// @brief Default constructor
	/// @details The coordinates are initialized as zero
	constexpr CoordT() noexcept = default;

	/// @brief Construct from a scalar
	/// @details Fill the coordinates with the scalar (v).
	/// @tparam OtherScalar The type of scalar
	/// @param v The scalar value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr CoordT(const OtherScalar& v) noexcept
		: CoordBase<Scalar, 1>(v)
	{
	}

	/// @brief Contruct from other coordinate
	/// @tparam OtherScalar The type of other coordinate
	/// @param other Other coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const CoordT<OtherScalar, 1>& other) noexcept
		: CoordBase<Scalar, 1>(static_cast<Scalar>(other[0]))
	{
	}

	/// @brief Set the value of x-coordinate, only available when DIM >= 1
	/// @tparam OtherScalar The type of the input value
	/// @param x New x-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetX(const OtherScalar& x) & noexcept
	{
		values[0] = x;
	}

	/// @brief Get x-coordinate, only available when DIM >= 1
	/// @return The reference to the x-coordinate
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return values[0];
	}

	/// @brief Copy assignment operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param rhs The right-hand side of the assignment operator
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator=(const CoordT<OtherScalar, 1>& rhs) noexcept -> ReturnThis<OtherScalar>
	{
		values[0] = static_cast<Scalar>(rhs[0]);
		return *this;
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator+=(const CoordT<OtherScalar, 1>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		values[0] += other[0];
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const CoordT<OtherScalar, 1>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		return {values[0] + other[0]};
	}

	/// @brief Subtraction assignement
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator-=(const CoordT<OtherScalar, 1>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		values[0] -= other[0];
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const CoordT<OtherScalar, 1>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		return {values[0] - other[0]};
	}

	/// @brief Scalar multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * scalar};
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @param coord The coordinate
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] friend constexpr auto operator*(const OtherScalar& scalar, const CoordT& coord) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return {scalar * coord[0]};
	}

	/// @brief Component-wise multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator*=(const CoordT<OtherScalar, 1>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= other[0];
		return *this;
	}

	/// @brief Component-wise multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The component-wise multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, 1>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * other[0]};
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar division result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / scalar};
	}

	/// @brief Component-wise division assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator/=(const CoordT<OtherScalar, 1>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= other[0];
		return *this;
	}

	/// @brief Component-wise division operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The component-wise division result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const CoordT<OtherScalar, 1>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / other[0]};
	}

	/// @brief Unary minus operator
	/// @return The opposite coordinate
	[[nodiscard]] constexpr CoordT operator-() const noexcept
	{
		return {-values[0]};
	}

	/// @brief Dot product
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product.
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator|(const CoordT<OtherScalar, 1>& other) const noexcept -> decltype(*this->Data() * *other.Data())
	{
		return values[0] * other[0];
	}

	/// @brief Dot product
	/// @tparam OtherScalar the type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const CoordT<OtherScalar, 1>& other) const noexcept -> decltype(*this | other)
	{
		return operator|(other);
	}

	/// @brief Squared norm
	/// @return The squared norm
	[[nodiscard]] constexpr Scalar SquaredNorm() const noexcept
	{
		return values[0] * values[0];
	}

	/// @brief Norm of coordinate
	/// @return The norm of coordinate
	[[nodiscard]] constexpr Scalar Norm() const noexcept
	{
		return values[0] < Scalar{0} ? -values[0] : values[0];
	}

	/// @brief Normalize the coordinate
	/// @return The reference of self
	constexpr CoordT& Normalize() noexcept
	{
		if (values[0] < Scalar{0})
		{
			values[0] = Scalar{-1};
		}
		else if (values[0] > Scalar{0})
		{
			values[0] = Scalar{1};
		}
		return *this;
	}

	/// @brief Normalized coordinate
	/// @return The normalized coordinate
	[[nodiscard]] constexpr CoordT Normalized() const noexcept
	{
		return CoordT(values[0] < Scalar{0} ? Scalar{-1} : (values[0] > Scalar{0} ? Scalar{1} : Scalar{0}));
	}

	/// @brief Reverse coordinate
	/// @return The reference of self
	constexpr decltype(auto) Reverse() noexcept
	{
		values[0] = -values[0];
		return *this;
	}

	/// @brief Reversed coordinate
	/// @return The reversed coordinate
	[[nodiscard]] constexpr auto Reversed() const noexcept
	{
		return operator-();
	}

	/// @brief Get the maximal component
	/// @return The value of maximal component
	[[nodiscard]] constexpr Scalar Max() const noexcept
	{
		return values[0];
	}

	/// @brief Get the maximal absolute component
	/// @return The value of maximal absolute component
	[[nodiscard]] Scalar MaxAbs() const noexcept
	{
		return std::abs(values[0]);
	}

	/// @brief Get the minimal component
	/// @return The value of minimal component
	[[nodiscard]] constexpr Scalar Min() const noexcept
	{
		return values[0];
	}

	/// @brief Get the minimal absolute component
	/// @return The value of minimal absolute component
	[[nodiscard]] Scalar MinAbs() const noexcept
	{
		return std::abs(values[0]);
	}

	/// @brief Component-wise minimize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Minimize(const CoordT& other) noexcept
	{
		values[0] = values[0] < other[0] ? values[0] : other[0];
		return *this;
	}

	/// @brief Component-wise maximize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Maximize(const CoordT& other) noexcept
	{
		values[0] = values[0] > other[0] ? values[0] : other[0];
		return *this;
	}

	/// @brief Compute component-wise minimized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise minimized coordinate
	[[nodiscard]] constexpr CoordT Min(const CoordT& other) const noexcept
	{
		return CoordT(*this).Minimize(other);
	}

	/// @brief Compute component-wise maximized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise maximized coordinate
	[[nodiscard]] constexpr CoordT Max(const CoordT& other) const noexcept
	{
		return CoordT(*this).Maximize(other);
	}

	/// @brief Fill the coordinate with a scalar
	/// @param s The scalar
	/// @return The reference of self
	constexpr CoordT& fill(const Scalar& s) noexcept
	{
		values[0] = s;
		return *this;
	}

	/// @brief Does the coordinate equal the other coordinate under a specific tolerance
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @param tol The tolerance
	/// @return True if all the component difference is less than the tolerance
	template<typename OtherScalar>
	[[nodiscard]] bool IsEqual(const CoordT<OtherScalar, 1>& other, const Scalar& tol) const noexcept
	{
		return operator-(other).MaxAbs() <= tol;
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates coincide exactly
	[[nodiscard]] constexpr bool operator==(const CoordT& other) const noexcept
	{
		return values[0] == other.values[0];
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates do not coincide exactly
	[[nodiscard]] constexpr bool operator!=(const CoordT& other) const noexcept
	{
		return !operator==(other);
	}

	/// @brief Is less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<(const CoordT& other) const noexcept
	{
		return values[0] < other.values[0];
	}

	/// @brief Is greater the other coordinate than using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>(const CoordT& other) const noexcept
	{
		return other < *this;
	}

	/// @brief Not greater than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<=(const CoordT& other) const noexcept
	{
		return !(other < *this);
	}

	/// @brief Not less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>=(const CoordT& other) const noexcept
	{
		return !operator<(other);
	}

	/// @brief Write the coordinate
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param coord The coordinate
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const CoordT& coord)
	{
		os << coord.values[0];
		return os;
	}

	/// @brief Read the coordinate
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param coord The coordinate
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, CoordT& coord)
	{
		is >> coord.values[0];
		return is;
	}
};

/// @brief The specialized class of 2D Cartesian coordinates
/// @tparam Scalar Underlying type of coordinates
template<typename Scalar>
class CoordT<Scalar, 2> : public CoordBase<Scalar, 2>
{
	using CoordBase<Scalar, 2>::values;
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, 2>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, CoordT&>;

public:
	/// @brief Default constructor
	/// @details The coordinates are initialized as zero
	constexpr CoordT() noexcept = default;

	/// @brief Construct from values
	/// @tparam T1,T2 Types of the values
	/// @param v1,v2 The values
	template<typename T1, typename T2, std::enable_if_t<are_convertible_v<Scalar, T1, T2>, int> = 0>
	constexpr CoordT(T1&& v1, T2&& v2) noexcept
		: CoordBase<Scalar, 2>(std::forward<T1>(v1), std::forward<T2>(v2))
	{
	}

	/// @brief Construct from a scalar
	/// @details Fill the coordinates with the scalar (v, v).
	/// @tparam OtherScalar The type of scalar
	/// @param v The scalar value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const OtherScalar& v) noexcept
		: CoordBase<Scalar, 2>(v, v)
	{
	}

	/// @brief Contruct from other coordinate
	/// @tparam OtherScalar The type of other coordinate
	/// @param other Other coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const CoordT<OtherScalar, 2>& other) noexcept
		: CoordBase<Scalar, 2>(static_cast<Scalar>(other[0]), static_cast<Scalar>(other[1]))
	{
	}

	/// @brief Set the value of x-coordinate, only available when DIM >= 1
	/// @tparam OtherScalar The type of the input value
	/// @param x New x-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetX(const OtherScalar& x) & noexcept
	{
		values[0] = x;
	}

	/// @brief Set the value of y-coordinate, only available when DIM >= 2
	/// @tparam OtherScalar The type of the input value
	/// @param y New y-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetY(const OtherScalar& y) & noexcept
	{
		values[1] = y;
	}

	/// @brief Get x-coordinate, only available when DIM >= 1
	/// @return The reference to the x-coordinate
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return values[0];
	}

	/// @brief Get y-coordinate, only available when DIM >= 2
	/// @return The reference to the y-coordinate
	[[nodiscard]] constexpr const Scalar& Y() const noexcept
	{
		return values[1];
	}

	/// @brief Copy assignment operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param rhs The right-hand side of the assignment operator
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator=(const CoordT<OtherScalar, 2>& rhs) noexcept -> ReturnThis<OtherScalar>
	{
		values[0] = static_cast<Scalar>(rhs[0]);
		values[1] = static_cast<Scalar>(rhs[1]);
		return *this;
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator+=(const CoordT<OtherScalar, 2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		values[0] += other[0];
		values[1] += other[1];
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const CoordT<OtherScalar, 2>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		return {values[0] + other[0], values[1] + other[1]};
	}

	/// @brief Subtraction assignement
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator-=(const CoordT<OtherScalar, 2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		values[0] -= other[0];
		values[1] -= other[1];
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const CoordT<OtherScalar, 2>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		return {values[0] - other[0], values[1] - other[1]};
	}

	/// @brief Scalar multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= scalar;
		values[1] *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * scalar, values[1] * scalar};
	}

	/// @brief Left scalar multiplication operator
	/// @param scalar The scalar
	/// @param coord The coordinate
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] friend constexpr auto operator*(const OtherScalar& scalar, const CoordT& coord) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return {scalar * coord[0], scalar * coord[1]};
	}

	/// @brief Component-wise multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator*=(const CoordT<OtherScalar, 2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= other[0];
		values[1] *= other[1];
		return *this;
	}

	/// @brief Component-wise multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The component-wise multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, 2>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * other[0], values[1] * other[1]};
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= scalar;
		values[1] /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar division result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / scalar, values[1] / scalar};
	}

	/// @brief Component-wise division assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator/=(const CoordT<OtherScalar, 2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= other[0];
		values[1] /= other[1];
		return *this;
	}

	/// @brief Component-wise division operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The component-wise division result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const CoordT<OtherScalar, 2>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / other[0], values[1] / other[1]};
	}

	/// @brief Unary minus operator
	/// @return The opposite coordinate
	[[nodiscard]] constexpr CoordT operator-(void) const noexcept
	{
		return {-values[0], -values[1]};
	}

	/// @brief 2D cross product
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of cross product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator%(const CoordT<OtherScalar, 2>& other) const noexcept -> decltype((*this)[0] * other[0] - (*this)[0] * other[0])
	{
		return values[0] * other[1] - values[1] * other[0];
	}

	/// @brief 2D cross product
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of cross product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Cross(const CoordT<OtherScalar, 2>& other) const noexcept -> decltype((*this)[0] * other[0] - (*this)[0] * other[0])
	{
		return operator%(other);
	}

	/// @brief Dot product
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product.
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator|(const CoordT<OtherScalar, 2>& other) const noexcept -> decltype(*this->Data() * *other.Data())
	{
		return values[0] * other[0] + values[1] * other[1];
	}

	/// @brief Dot product
	/// @tparam OtherScalar the type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const CoordT<OtherScalar, 2>& other) const noexcept -> decltype(*this->Data() * *other.Data())
	{
		return operator|(other);
	}

	/// @brief Squared norm
	/// @return The squared norm
	[[nodiscard]] constexpr Scalar SquaredNorm() const noexcept
	{
		return values[0] * values[0] + values[1] * values[1];
	}

	/// @brief Norm of coordinate
	/// @return The norm of coordinate
	[[nodiscard]] Scalar Norm() const noexcept
	{
		return static_cast<Scalar>(std::sqrt(SquaredNorm()));
	}

	/// @brief Normalize the coordinate
	/// @return The reference of self
	CoordT& Normalize() noexcept
	{
		Scalar n = SquaredNorm();
		if (n != Scalar{0})
		{
			return operator/=(static_cast<Scalar>(std::sqrt(n)));
		}
		return *this;
	}

	/// @brief Normalized coordinate
	/// @return The normalized coordinate
	[[nodiscard]] CoordT Normalized() const noexcept
	{
		Scalar n = SquaredNorm();
		if (n != Scalar{0})
		{
			return operator/(static_cast<Scalar>(std::sqrt(n)));
		}
		return CoordT(*this);
	}

	/// @brief Reverse coordinate
	/// @return The reference of self
	constexpr decltype(auto) Reverse() noexcept
	{
		values[0] = -values[0];
		values[1] = -values[1];
		return *this;
	}

	/// @brief Reversed coordinate
	/// @return The reversed coordinate
	[[nodiscard]] constexpr auto Reversed() const noexcept
	{
		return operator-();
	}

	/// @brief Get the maximal component
	/// @return The value of maximal component
	[[nodiscard]] constexpr Scalar Max() const noexcept
	{
		return std::max(values[0], values[1]);
	}

	/// @brief Get the maximal absolute component
	/// @return The value of maximal absolute component
	[[nodiscard]] Scalar MaxAbs() const noexcept
	{
		return std::max(std::abs(values[0]), std::abs(values[1]));
	}

	/// @brief Get the minimal component
	/// @return The value of minimal component
	[[nodiscard]] constexpr Scalar Min() const noexcept
	{
		return std::min(values[0], values[1]);
	}

	/// @brief Get the minimal absolute component
	/// @return The value of minimal absolute component
	[[nodiscard]] Scalar MinAbs() const noexcept
	{
		return std::min(std::abs(values[0]), std::abs(values[1]));
	}

	/// @brief Component-wise minimize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Minimize(const CoordT& other) noexcept
	{
		values[0] = values[0] < other[0] ? values[0] : other[0];
		values[1] = values[1] < other[1] ? values[1] : other[1];
		return *this;
	}

	/// @brief Component-wise maximize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Maximize(const CoordT& other) noexcept
	{
		values[0] = values[0] > other[0] ? values[0] : other[0];
		values[1] = values[1] > other[1] ? values[1] : other[1];
		return *this;
	}

	/// @brief Compute component-wise minimized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise minimized coordinate
	[[nodiscard]] constexpr CoordT Min(const CoordT& other) const noexcept
	{
		return CoordT(*this).Minimize(other);
	}

	/// @brief Compute component-wise maximized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise maximized coordinate
	[[nodiscard]] constexpr CoordT Max(const CoordT& other) const noexcept
	{
		return CoordT(*this).Maximize(other);
	}

	/// @brief Fill the coordinate with a scalar
	/// @param s The scalar
	/// @return The reference of self
	constexpr CoordT& fill(const Scalar& s) noexcept
	{
		values[0] = values[1] = s;
		return *this;
	}

	/// @brief Does the coordinate equal the other coordinate under a specific tolerance
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @param tol The tolerance
	/// @return True if all the component difference is less than the tolerance
	template<typename OtherScalar>
	[[nodiscard]] bool IsEqual(const CoordT<OtherScalar, 2>& other, const Scalar& tol) const noexcept
	{
		return operator-(other).MaxAbs() <= tol;
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates coincide exactly
	[[nodiscard]] constexpr bool operator==(const CoordT& other) const noexcept
	{
		return values[0] == other.values[0] && values[1] == other.values[1];
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates do not coincide exactly
	[[nodiscard]] constexpr bool operator!=(const CoordT& other) const noexcept
	{
		return !operator==(other);
	}

	/// @brief Is less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<(const CoordT& other) const noexcept
	{
		return values[0] < other[0] || (values[0] == other[0] && values[1] < other[1]);
	}

	/// @brief Is greater the other coordinate than using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>(const CoordT& other) const noexcept
	{
		return other < *this;
	}

	/// @brief Not greater than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<=(const CoordT& other) const noexcept
	{
		return !(other < *this);
	}

	/// @brief Not less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>=(const CoordT& other) const noexcept
	{
		return !operator<(other);
	}

	/// @brief Write the coordinate
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param coord The coordinate
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const CoordT& coord)
	{
		os << coord.values[0] << " " << coord.values[1];
		return os;
	}

	/// @brief Read the coordinate
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param coord The coordinate
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, CoordT& coord)
	{
		is >> coord.values[0] >> coord.values[1];
		return is;
	}
};

/// @brief The specialized class of 3D Cartesian coordinates
/// @tparam Scalar Underlying type of coordinates
template<typename Scalar>
class CoordT<Scalar, 3> : public CoordBase<Scalar, 3>
{
	using CoordBase<Scalar, 3>::values;
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, 3>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, CoordT&>;

public:
	/// @brief Default constructor
	/// @details The coordinates are initialized as zero
	constexpr CoordT() noexcept = default;

	/// @brief Construct from values
	/// @tparam T1,T2,T3 Type of the values
	/// @param v1,v2,v3 The values
	template<typename T1, typename T2, typename T3, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3>, int> = 0>
	constexpr CoordT(T1&& v1, T2&& v2, T3&& v3) noexcept
		: CoordBase<Scalar, 3>(std::forward<T1>(v1), std::forward<T2>(v2), std::forward<T3>(v3))
	{
	}

	/// @brief Construct from a scalar
	/// @details Fill the coordinates with the scalar (v, v, v).
	/// @tparam OtherScalar The type of scalar
	/// @param v The scalar value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const OtherScalar& v) noexcept
		: CoordBase<Scalar, 3>(v, v, v)
	{
	}

	/// @brief Contruct from other coordinate
	/// @tparam OtherScalar The type of other coordinate
	/// @param other Other coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const CoordT<OtherScalar, 3>& other) noexcept
		: CoordBase<Scalar, 3>(static_cast<Scalar>(other[0]), static_cast<Scalar>(other[1]), static_cast<Scalar>(other[2]))
	{
	}

	/// @brief Set the value of x-coordinate, only available when DIM >= 1
	/// @tparam OtherScalar The type of the input value
	/// @param x New x-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetX(const OtherScalar& x) & noexcept
	{
		values[0] = x;
	}

	/// @brief Set the value of y-coordinate, only available when DIM >= 2
	/// @tparam OtherScalar The type of the input value
	/// @param y New y-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetY(const OtherScalar& y) & noexcept
	{
		values[1] = y;
	}

	/// @brief Set the value of z-coordinate, only available when DIM >= 3
	/// @tparam OtherScalar The type of the input value
	/// @param z New z-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetZ(const OtherScalar& z) & noexcept
	{
		values[2] = z;
	}

	/// @brief Get x-coordinate, only available when DIM >= 1
	/// @return The reference to the x-coordinate
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return values[0];
	}

	/// @brief Get y-coordinate, only available when DIM >= 2
	/// @return The reference to the y-coordinate
	[[nodiscard]] constexpr const Scalar& Y() const noexcept
	{
		return values[1];
	}

	/// @brief Get z-coordinate, only available when DIM >= 3
	/// @return The reference to the z-coordinate
	[[nodiscard]] constexpr const Scalar& Z() const noexcept
	{
		return values[2];
	}

	/// @brief Copy assignment operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param rhs The right-hand side of the assignment operator
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator=(const CoordT<OtherScalar, 3>& rhs) noexcept -> ReturnThis<OtherScalar>
	{
		values[0] = static_cast<Scalar>(rhs[0]);
		values[1] = static_cast<Scalar>(rhs[1]);
		values[2] = static_cast<Scalar>(rhs[2]);
		return *this;
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator+=(const CoordT<OtherScalar, 3>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		values[0] += other[0];
		values[1] += other[1];
		values[2] += other[2];
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const CoordT<OtherScalar, 3>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		return {values[0] + other[0], values[1] + other[1], values[2] + other[2]};
	}

	/// @brief Subtraction assignement
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator-=(const CoordT<OtherScalar, 3>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		values[0] -= other[0];
		values[1] -= other[1];
		values[2] -= other[2];
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const CoordT<OtherScalar, 3>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		return {values[0] - other[0], values[1] - other[1], values[2] - other[2]};
	}

	/// @brief Scalar multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= scalar;
		values[1] *= scalar;
		values[2] *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * scalar, values[1] * scalar, values[2] * scalar};
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @param coord The coordinate
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] friend constexpr auto operator*(const OtherScalar& scalar, const CoordT& coord) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return {scalar * coord[0], scalar * coord[1], scalar * coord[2]};
	}

	/// @brief Component-wise multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator*=(const CoordT<OtherScalar, 3>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= other[0];
		values[1] *= other[1];
		values[2] *= other[2];
		return *this;
	}

	/// @brief Component-wise multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The component-wise multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, 3>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * other[0], values[1] * other[1], values[2] * other[2]};
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= scalar;
		values[1] /= scalar;
		values[2] /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar division result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / scalar, values[1] / scalar, values[2] / scalar};
	}

	/// @brief Component-wise division assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator/=(const CoordT<OtherScalar, 3>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= other[0];
		values[1] /= other[1];
		values[2] /= other[2];
		return *this;
	}

	/// @brief Component-wise division operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The component-wise division result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const CoordT<OtherScalar, 3>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / other[0], values[1] / other[1], values[2] / other[2]};
	}

	/// @brief Unary minus operator
	/// @return The opposite coordinate
	[[nodiscard]] constexpr CoordT operator-() const noexcept
	{
		return {-values[0], -values[1], -values[2]};
	}

	/// @brief Cross product, only available when DIM = 3
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting coordinate of cross product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator%(const CoordT<OtherScalar, 3>& other) const noexcept -> CoordT<decltype((*this)[0] * other[0] - (*this)[0] * other[0]), 3>
	{
		return {
			values[1] * other[2] - values[2] * other[1],
			values[2] * other[0] - values[0] * other[2],
			values[0] * other[1] - values[1] * other[0]};
	}

	/// @brief Cross product, available when DIM = 2 or 3
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value or coordinate of cross product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Cross(const CoordT<OtherScalar, 3>& other) const noexcept -> CoordT<decltype((*this)[0] * other[0] - (*this)[0] * other[0]), 3>
	{
		return operator%(other);
	}

	/// @brief Dot product
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product.
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator|(const CoordT<OtherScalar, 3>& other) const noexcept -> decltype(*this->Data() * *other.Data())
	{
		return values[0] * other[0] + values[1] * other[1] + values[2] * other[2];
	}

	/// @brief Dot product
	/// @tparam OtherScalar the type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const CoordT<OtherScalar, 3>& other) const noexcept -> decltype(*this | other)
	{
		return operator|(other);
	}

	/// @brief Squared norm
	/// @return The squared norm
	[[nodiscard]] constexpr Scalar SquaredNorm() const noexcept
	{
		return values[0] * values[0] + values[1] * values[1] + values[2] * values[2];
	}

	/// @brief Norm of coordinate
	/// @return The norm of coordinate
	[[nodiscard]] Scalar Norm() const noexcept
	{
		return static_cast<Scalar>(std::sqrt(SquaredNorm()));
	}

	/// @brief Normalize the coordinate
	/// @return The reference of self
	CoordT& Normalize() noexcept
	{
		Scalar n = SquaredNorm();
		if (n != Scalar{0})
		{
			return operator/=(static_cast<Scalar>(std::sqrt(n)));
		}
		return *this;
	}

	/// @brief Normalized coordinate
	/// @return The normalized coordinate
	[[nodiscard]] CoordT Normalized() const noexcept
	{
		Scalar n = SquaredNorm();
		if (n != Scalar{0})
		{
			return operator/(static_cast<Scalar>(std::sqrt(n)));
		}
		return CoordT(*this);
	}

	/// @brief Reverse coordinate
	/// @return The reference of self
	constexpr decltype(auto) Reverse() noexcept
	{
		values[0] = -values[0];
		values[1] = -values[1];
		values[2] = -values[2];
		return *this;
	}

	/// @brief Reversed coordinate
	/// @return The reversed coordinate
	[[nodiscard]] constexpr auto Reversed() const noexcept
	{
		return operator-();
	}

	/// @brief Get the maximal component
	/// @return The value of maximal component
	[[nodiscard]] constexpr Scalar Max() const noexcept
	{
		return std::max(std::max(values[0], values[1]), values[2]);
	}

	/// @brief Get the maximal absolute component
	/// @return The value of maximal absolute component
	[[nodiscard]] Scalar MaxAbs() const noexcept
	{
		return std::max(std::max(std::abs(values[0]), std::abs(values[1])), std::abs(values[2]));
	}

	/// @brief Get the minimal component
	/// @return The value of minimal component
	[[nodiscard]] constexpr Scalar Min() const noexcept
	{
		return std::min(std::min(values[0], values[1]), values[2]);
	}

	/// @brief Get the minimal absolute component
	/// @return The value of minimal absolute component
	[[nodiscard]] Scalar MinAbs() const noexcept
	{
		return std::min(std::min(std::abs(values[0]), std::abs(values[1])), std::abs(values[2]));
	}

	/// @brief Component-wise minimize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Minimize(const CoordT& other) noexcept
	{
		values[0] = values[0] < other[0] ? values[0] : other[0];
		values[1] = values[1] < other[1] ? values[1] : other[1];
		values[2] = values[2] < other[2] ? values[2] : other[2];
		return *this;
	}

	/// @brief Component-wise maximize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Maximize(const CoordT& other) noexcept
	{
		values[0] = values[0] > other[0] ? values[0] : other[0];
		values[1] = values[1] > other[1] ? values[1] : other[1];
		values[2] = values[2] > other[2] ? values[2] : other[2];
		return *this;
	}

	/// @brief Compute component-wise minimized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise minimized coordinate
	[[nodiscard]] constexpr CoordT Min(const CoordT& other) const noexcept
	{
		return CoordT(*this).Minimize(other);
	}

	/// @brief Compute component-wise maximized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise maximized coordinate
	[[nodiscard]] constexpr CoordT Max(const CoordT& other) const noexcept
	{
		return CoordT(*this).Maximize(other);
	}

	/// @brief Fill the coordinate with a scalar
	/// @param s The scalar
	/// @return The reference of self
	constexpr CoordT& fill(const Scalar& s) noexcept
	{
		values[0] = values[1] = values[2] = s;
		return *this;
	}

	/// @brief Does the coordinate equal the other coordinate under a specific tolerance
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @param tol The tolerance
	/// @return True if all the component difference is less than the tolerance
	template<typename OtherScalar>
	[[nodiscard]] bool IsEqual(const CoordT<OtherScalar, 3>& other, const Scalar& tol) const noexcept
	{
		return operator-(other).MaxAbs() <= tol;
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates coincide exactly
	[[nodiscard]] constexpr bool operator==(const CoordT& other) const noexcept
	{
		return values[0] == other.values[0] && values[1] == other.values[1] && values[2] == other.values[2];
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates do not coincide exactly
	[[nodiscard]] constexpr bool operator!=(const CoordT& other) const noexcept
	{
		return !operator==(other);
	}

	/// @brief Is less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<(const CoordT& other) const noexcept
	{
		return values[0] < other[0] || (values[0] == other[0] && (values[1] < other[1] || (values[1] == other[1] && values[2] < other[2])));
	}

	/// @brief Is greater the other coordinate than using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>(const CoordT& other) const noexcept
	{
		return other < *this;
	}

	/// @brief Not greater than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<=(const CoordT& other) const noexcept
	{
		return !(other < *this);
	}

	/// @brief Not less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>=(const CoordT& other) const noexcept
	{
		return !operator<(other);
	}

	/// @brief Write the coordinate
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param coord The coordinate
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const CoordT& coord)
	{
		os << coord.values[0] << " " << coord.values[1] << " " << coord.values[2];
		return os;
	}

	/// @brief Read the coordinate
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param coord The coordinate
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, CoordT& coord)
	{
		is >> coord.values[0] >> coord.values[1] >> coord.values[2];
		return is;
	}
};

/// @brief The specialized class of 4D Cartesian coordinates
/// @tparam Scalar Underlying type of coordinates
/// @tparam DIM The dimension of the coordinate
template<typename Scalar>
class CoordT<Scalar, 4> : public CoordBase<Scalar, 4>
{
	using CoordBase<Scalar, 4>::values;
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, 4>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, CoordT&>;

public:
	/// @brief Default constructor
	/// @details The coordinates are initialized as zero
	constexpr CoordT() noexcept = default;

	/// @brief Construct from values
	/// @tparam T1,T2,T3,T4 Types of values
	/// @param v1,v2,v3,v4 The values
	template<typename T1, typename T2, typename T3, typename T4, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3, T4>, int> = 0>
	constexpr CoordT(T1&& v1, T2&& v2, T3&& v3, T4&& v4) noexcept
		: CoordBase<Scalar, 4>(std::forward<T1>(v1), std::forward<T2>(v2), std::forward<T3>(v3), std::forward<T4>(v4))
	{
	}

	/// @brief Construct from a scalar
	/// @details Fill the coordinates with the scalar (v, v, v, v).
	/// @tparam OtherScalar The type of scalar
	/// @param v The scalar value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const OtherScalar& v) noexcept
		: CoordBase<Scalar, 4>(v, v, v, v)
	{
	}

	/// @brief Contruct from other coordinate
	/// @tparam OtherScalar The type of other coordinate
	/// @param other Other coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr explicit CoordT(const CoordT<OtherScalar, 4>& other) noexcept
		: CoordBase<Scalar, 4>(static_cast<Scalar>(other[0]), static_cast<Scalar>(other[1]), static_cast<Scalar>(other[2]), static_cast<Scalar>(other[3]))
	{
	}

	/// @brief Set the value of x-coordinate, only available when DIM >= 1
	/// @tparam OtherScalar The type of the input value
	/// @param x New x-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetX(const OtherScalar& x) & noexcept
	{
		values[0] = x;
	}

	/// @brief Set the value of y-coordinate, only available when DIM >= 2
	/// @tparam OtherScalar The type of the input value
	/// @param y New y-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetY(const OtherScalar& y) & noexcept
	{
		values[1] = y;
	}

	/// @brief Set the value of z-coordinate, only available when DIM >= 3
	/// @tparam OtherScalar The type of the input value
	/// @param z New z-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetZ(const OtherScalar& z) & noexcept
	{
		values[2] = z;
	}

	/// @brief Set the value of w-coordinate, only available when DIM >= 4
	/// @tparam OtherScalar The type of the input value
	/// @param w New w-coordinate
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetW(const OtherScalar& w) & noexcept
	{
		values[3] = w;
	}

	/// @brief Get x-coordinate, only available when DIM >= 1
	/// @return The reference to the x-coordinate
	[[nodiscard]] constexpr const Scalar& X() const noexcept
	{
		return values[0];
	}

	/// @brief Get y-coordinate, only available when DIM >= 2
	/// @return The reference to the y-coordinate
	[[nodiscard]] constexpr const Scalar& Y() const noexcept
	{
		return values[1];
	}

	/// @brief Get z-coordinate, only available when DIM >= 3
	/// @return The reference to the z-coordinate
	[[nodiscard]] constexpr const Scalar& Z() const noexcept
	{
		return values[2];
	}

	/// @brief Get w-coordinate, only available when DIM >= 4
	/// @return The reference to the w-coordinate
	[[nodiscard]] constexpr const Scalar& W() const noexcept
	{
		return values[3];
	}

	/// @brief Copy assignment operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param rhs The right-hand side of the assignment operator
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator=(const CoordT<OtherScalar, 4>& rhs) noexcept -> ReturnThis<OtherScalar>
	{
		values[0] = static_cast<Scalar>(rhs[0]);
		values[1] = static_cast<Scalar>(rhs[1]);
		values[2] = static_cast<Scalar>(rhs[2]);
		values[3] = static_cast<Scalar>(rhs[3]);
		return *this;
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator+=(const CoordT<OtherScalar, 4>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		values[0] += other[0];
		values[1] += other[1];
		values[2] += other[2];
		values[3] += other[3];
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const CoordT<OtherScalar, 4>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		return {values[0] + other[0], values[1] + other[1], values[2] + other[2], values[3] + other[3]};
	}

	/// @brief Subtraction assignement
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator-=(const CoordT<OtherScalar, 4>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		values[0] -= other[0];
		values[1] -= other[1];
		values[2] -= other[2];
		values[3] -= other[3];
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The type of the other coordinate
	/// @param other The other coordinate
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const CoordT<OtherScalar, 4>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		return {values[0] - other[0], values[1] - other[1], values[2] - other[2], values[3] - other[3]};
	}

	/// @brief Scalar multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= scalar;
		values[1] *= scalar;
		values[2] *= scalar;
		values[3] *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * scalar, values[1] * scalar, values[2] * scalar, values[3] * scalar};
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @param coord The coordinate
	/// @return The scalar multiplication result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] friend constexpr auto operator*(const OtherScalar& scalar, const CoordT& coord) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return {scalar * coord[0], scalar * coord[1], scalar * coord[2], scalar * coord[3]};
	}

	/// @brief Component-wise multiplication assignment
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator*=(const CoordT<OtherScalar, 4>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		values[0] *= other[0];
		values[1] *= other[1];
		values[2] *= other[2];
		values[3] *= other[3];
		return *this;
	}

	/// @brief Component-wise multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param other The scalar
	/// @return The component-wise multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, 4>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {values[0] * other[0], values[1] * other[1], values[2] * other[2], values[3] * other[3]};
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference of self
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= scalar;
		values[1] /= scalar;
		values[2] /= scalar;
		values[3] /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar division result
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / scalar, values[1] / scalar, values[2] / scalar, values[3] / scalar};
	}

	/// @brief Component-wise division assignment
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	template<typename OtherScalar>
	constexpr auto operator/=(const CoordT<OtherScalar, 4>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		values[0] /= other[0];
		values[1] /= other[1];
		values[2] /= other[2];
		values[3] /= other[3];
		return *this;
	}

	/// @brief Component-wise division operator
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The component-wise division result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const CoordT<OtherScalar, 4>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {values[0] / other[0], values[1] / other[1], values[2] / other[2], values[3] / other[3]};
	}

	/// @brief Unary minus operator
	/// @return The opposite coordinate
	[[nodiscard]] constexpr CoordT operator-(void) const noexcept
	{
		return {-values[0], -values[1], -values[2], -values[3]};
	}

	/// @brief Dot product
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product.
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator|(const CoordT<OtherScalar, 4>& other) const noexcept -> decltype(*this->Data() * *other.Data())
	{
		return values[0] * other[0] + values[1] * other[1] + values[2] * other[2] + values[3] * other[3];
	}

	/// @brief Dot product
	/// @tparam OtherScalar the type of other coordinate
	/// @param other The other coordinate
	/// @return The resulting value of dot product
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto Dot(const CoordT<OtherScalar, 4>& other) const noexcept -> decltype(*this | other)
	{
		return operator|(other);
	}

	/// @brief Squared norm
	/// @return The squared norm
	[[nodiscard]] constexpr Scalar SquaredNorm() const noexcept
	{
		return values[0] * values[0] + values[1] * values[1] + values[2] * values[2] + values[3] * values[3];
	}

	/// @brief Norm of coordinate
	/// @return The norm of coordinate
	[[nodiscard]] Scalar Norm() const noexcept
	{
		return static_cast<Scalar>(std::sqrt(SquaredNorm()));
	}

	/// @brief Normalize the coordinate
	/// @return The reference of self
	CoordT& Normalize() noexcept
	{
		Scalar n = SquaredNorm();
		if (n != Scalar{0})
		{
			return operator/=(static_cast<Scalar>(std::sqrt(n)));
		}
		return *this;
	}

	/// @brief Normalized coordinate
	/// @return The normalized coordinate
	[[nodiscard]] CoordT Normalized() const noexcept
	{
		Scalar n = SquaredNorm();
		if (n != Scalar{0})
		{
			return operator/(static_cast<Scalar>(std::sqrt(n)));
		}
		return CoordT(*this);
	}

	/// @brief Reverse coordinate
	/// @return The reference of self
	constexpr decltype(auto) Reverse() noexcept
	{
		values[0] = -values[0];
		values[1] = -values[1];
		values[2] = -values[2];
		values[3] = -values[3];
		return *this;
	}

	/// @brief Reversed coordinate
	/// @return The reversed coordinate
	[[nodiscard]] constexpr auto Reversed() const noexcept
	{
		return operator-();
	}

	/// @brief Get the maximal component
	/// @return The value of maximal component
	[[nodiscard]] constexpr Scalar Max() const noexcept
	{
		return std::max(std::max(values[0], values[1]), std::max(values[2], values[3]));
	}

	/// @brief Get the maximal absolute component
	/// @return The value of maximal absolute component
	[[nodiscard]] Scalar MaxAbs() const noexcept
	{
		return std::max(std::max(std::abs(values[0]), std::abs(values[1])), std::max(std::abs(values[2]), std::abs(values[3])));
	}

	/// @brief Get the minimal component
	/// @return The value of minimal component
	[[nodiscard]] constexpr Scalar Min() const noexcept
	{
		return std::min(std::min(values[0], values[1]), std::min(values[2], values[3]));
	}

	/// @brief Get the minimal absolute component
	/// @return The value of minimal absolute component
	[[nodiscard]] Scalar MinAbs() const noexcept
	{
		return std::min(std::min(std::abs(values[0]), std::abs(values[1])), std::min(std::abs(values[2]), std::abs(values[3])));
	}

	/// @brief Component-wise minimize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Minimize(const CoordT& other) noexcept
	{
		values[0] = values[0] < other[0] ? values[0] : other[0];
		values[1] = values[1] < other[1] ? values[1] : other[1];
		values[2] = values[2] < other[2] ? values[2] : other[2];
		values[3] = values[3] < other[3] ? values[3] : other[3];
		return *this;
	}

	/// @brief Component-wise maximize the coordinate
	/// @param other The other coordinate
	/// @return The reference of self
	constexpr CoordT& Maximize(const CoordT& other) noexcept
	{
		values[0] = values[0] > other[0] ? values[0] : other[0];
		values[1] = values[1] > other[1] ? values[1] : other[1];
		values[2] = values[2] > other[2] ? values[2] : other[2];
		values[3] = values[3] > other[3] ? values[3] : other[3];
		return *this;
	}

	/// @brief Compute component-wise minimized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise minimized coordinate
	[[nodiscard]] constexpr CoordT Min(const CoordT& other) const noexcept
	{
		return CoordT(*this).Minimize(other);
	}

	/// @brief Compute component-wise maximized coordinate
	/// @param other The other coordinate
	/// @return The result of component-wise maximized coordinate
	[[nodiscard]] constexpr CoordT Max(const CoordT& other) const noexcept
	{
		return CoordT(*this).Maximize(other);
	}

	/// @brief Fill the coordinate with a scalar
	/// @param s The scalar
	/// @return The reference of self
	constexpr CoordT& fill(const Scalar& s) noexcept
	{
		values[0] = values[1] = values[2] = values[3] = s;
		return *this;
	}

	/// @brief Does the coordinate equal the other coordinate under a specific tolerance
	/// @tparam OtherScalar The type of other coordinate
	/// @param other The other coordinate
	/// @param tol The tolerance
	/// @return True if all the component difference is less than the tolerance
	template<typename OtherScalar>
	[[nodiscard]] bool IsEqual(const CoordT<OtherScalar, 4>& other, const Scalar& tol) const noexcept
	{
		return operator-(other).MaxAbs() <= tol;
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates coincide exactly
	[[nodiscard]] constexpr bool operator==(const CoordT& other) const noexcept
	{
		return values[0] == other.values[0] && values[1] == other.values[1] && values[2] == other.values[2] && values[3] == other.values[3];
	}

	/// @brief Does the coordinate equal the other coordinate exactly
	/// @param other The other coordinate
	/// @return True if the two coordinates do not coincide exactly
	[[nodiscard]] constexpr bool operator!=(const CoordT& other) const noexcept
	{
		return !operator==(other);
	}

	/// @brief Is less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<(const CoordT& other) const noexcept
	{
		return values[0] < other[0] || (values[0] == other[0] && (values[1] < other[1] || (values[1] == other[1] && (values[2] < other[2] || (values[2] == other[2] && values[3] < other[3])))));
	}

	/// @brief Is greater the other coordinate than using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>(const CoordT& other) const noexcept
	{
		return other < *this;
	}

	/// @brief Not greater than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not greater than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator<=(const CoordT& other) const noexcept
	{
		return !(other < *this);
	}

	/// @brief Not less than the other coordinate using lexicographical order
	/// @param other The other coordinate
	/// @return True if the coordinate is not less than the other coordinate in the lexicographical order
	[[nodiscard]] constexpr bool operator>=(const CoordT& other) const noexcept
	{
		return !operator<(other);
	}

	/// @brief Write the coordinate
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param coord The coordinate
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const CoordT& coord)
	{
		os << coord.values[0] << " " << coord.values[1] << " " << coord.values[2] << " " << coord.values[3];
		return os;
	}

	/// @brief Read the coordinate
	/// @tparam Stream The type of input stream
	/// @param is The input stream
	/// @param coord The coordinate
	/// @return The input stream
	template<typename Stream>
	friend Stream& operator>>(Stream& is, CoordT& coord)
	{
		is >> coord.values[0] >> coord.values[1] >> coord.values[2] >> coord.values[3];
		return is;
	}
};

/// @brief 2D coordinate in float precision
using Coord2f = CoordT<float, 2>;

/// @brief 3D coordinate in float precision
using Coord3f = CoordT<float, 3>;

/// @brief 4D coordinate in float precision
using Coord4f = CoordT<float, 4>;

/// @brief 2D coordinate in double precision
using Coord2d = CoordT<double, 2>;

/// @brief 3D coordinate in double precision
using Coord3d = CoordT<double, 3>;

/// @brief 4D coordinate in double precision
using Coord4d = CoordT<double, 4>;

/// @brief 2D coordinate
using Coord2 = Coord2d;

/// @brief 3D coordinate
using Coord3 = Coord3d;

/// @brief 4D coordinate
using Coord4 = Coord4d;

} // namespace AMCAX
