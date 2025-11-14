/// @file      MatrixT.hpp
/// @brief     Class of matrix
/// @details   Implementation of fixed-size matrix
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/CoordT.hpp>

namespace AMCAX
{
/// @brief Class of fixed-size matrix
/// @tparam Scalar Type of matrix elements
/// @tparam ROW Number of row
/// @tparam COL Number of column
template<typename Scalar, int ROW, int COL>
class MatrixT
{
	static_assert(ROW >= 1 && COL >= 1, "Invalid dimensionality");
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, MatrixT<ScalarType, ROW, COL>>;
	template<typename ScalarType, int DIM>
	using ReturnCoord = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, DIM>>;
	template<typename ScalarType, int R, int C>
	using ReturnMatrix = std::enable_if_t<sizeof(ScalarType) >= 0, MatrixT<ScalarType, R, C>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, MatrixT&>;

public:
	/// @brief Default constructor
	/// @details The matrix is initialized as zero matrix
	constexpr MatrixT() noexcept = default;

	/// @brief Construct a diagonal matrix with a value
	/// @param v The diagonal value
	constexpr explicit MatrixT(Scalar v) noexcept
	{
		SetDiagonal(CoordT<Scalar, (ROW < COL ? ROW : COL)>(v));
	}

	/// @brief Construct from column vectors
	/// @tparam ...Ts The scalar types of the other column vector
	/// @param ...ps The other column vectors
	template<typename... Ts, std::enable_if_t<static_cast<int>(sizeof...(Ts)) == COL && are_convertible_v<Scalar, Ts...>, int> = 0>
	constexpr MatrixT(const CoordT<Ts, ROW>&... ps) noexcept
		: matrix{}
	{
		SetCols(ps...);
	}

	/// @brief Set the i-th column
	/// @tparam OtherScalar The scalar type of the new column vector
	/// @param i The index of the column
	/// @param coord The new column vector
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetCol(int i, const CoordT<OtherScalar, ROW>& coord) & noexcept
	{
		for (int j = 0; j < ROW; j++)
		{
			matrix[j][i] = coord[j];
		}
	}

	/// @brief Set all the column vectors
	/// @tparam ...Ts The scalar types of the column vectors
	/// @param ...ps The column vectors
	template<typename... Ts, std::enable_if_t<static_cast<int>(sizeof...(Ts)) == COL && are_convertible_v<Scalar, Ts...>, int> = 0>
	constexpr void SetCols(const CoordT<Ts, ROW>&... ps) & noexcept
	{
		int j = 0;
		(SetCol(j++, ps), ...);
	}

	/// @brief Set the diagonal values of matrix
	/// @details The number of diagonal values should be not more than ROW and COL. The remaining elements of matrix are not changed.
	/// @tparam ...T The types of the diagonal values
	/// @param ...vs The diagonal values
	template<typename... T, std::enable_if_t<(static_cast<int>(sizeof...(T)) <= ROW && static_cast<int>(sizeof...(T)) <= COL) && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void SetDiagonal(T&&... vs) & noexcept
	{
		int i = 0;
		((matrix[i][i] = std::forward<T>(vs), ++i),...);
	}

	/// @brief Set the diagonal values of matrix by a coordinate
	/// @details The dimension of the coordinate should be not more than ROW and COL. The remaining elements of matrix are not changed.
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @tparam DIM The dimension of the coordinate
	/// @param coord The diagonal coordinate
	template<typename OtherScalar, int DIM, std::enable_if_t<(DIM <= ROW && DIM <= COL) && std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetDiagonal(const CoordT<OtherScalar, DIM>& coord) & noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			matrix[i][i] = coord[i];
		}
	}

	/// @brief Set the matrix to be diagonal
	/// @details The number of the diagonal values should be not more than ROW and COL. The other elements are set to be zero.
	/// @tparam ...T The types of the diagonal values
	/// @param ...vs The diagonal values
	template<typename... T, std::enable_if_t<(static_cast<int>(sizeof...(T)) <= ROW && static_cast<int>(sizeof...(T)) <= COL) && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void AsDiagonal(T&&... vs) & noexcept
	{
		AsDiagonal(CoordT<Scalar, sizeof...(T)>(vs...));
	}

	/// @brief Set the matrix to be diagonal using a coordinate
	/// @details The dimension of the coordinate should be not more than ROW and COL. The other elements are set to be zero.
	/// @tparam OtherScalar The scalar type of the diagonal coordinate
	/// @tparam DIM The dimension of the coordinate
	/// @param coord The diagonal coordinate
	template<typename OtherScalar, int DIM, std::enable_if_t<(DIM <= ROW && DIM <= COL) && std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void AsDiagonal(const CoordT<OtherScalar, DIM>& coord) & noexcept
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				matrix[i][j] = (i == j && i < DIM) ? coord[i] : Scalar{0};
			}
		}
	}

	/// @brief Set the matrix to be dot operator of a coordinate.
	/// @details The dot matrix M is set as vv^T.
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @param coord The coordinate.
	template<typename OtherScalar, int DIM, std::enable_if_t<DIM == ROW && DIM == COL && std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetDot(const CoordT<OtherScalar, DIM>& coord) & noexcept
	{
		for (int i = 0; i < DIM; i++)
		{
			for (int j = i; j < DIM; j++)
			{
				matrix[i][j] = matrix[j][i] = coord[i] * coord[j];
			}
		}
	}

	/// @brief Set the matrix to be identity matrix
	constexpr void SetIdentity() & noexcept
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				matrix[i][j] = i == j ? Scalar{1} : Scalar{0};
			}
		}
	}

	/// @brief Set the i-th row vector
	/// @tparam OtherScalar The scalar type of the row vector
	/// @param i The index of row
	/// @param coord The new row vector
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetRow(int i, const CoordT<OtherScalar, COL>& coord) & noexcept
	{
		for (int j = 0; j < COL; j++)
		{
			matrix[i][j] = coord[j];
		}
	}

	/// @brief Set all the row vectors
	/// @tparam ...Ts The scalar types of the row vectors
	/// @param ...ps The row vectors
	template<typename... Ts, std::enable_if_t<static_cast<int>(sizeof...(Ts)) == ROW && are_convertible_v<Scalar, Ts...>, int> = 0>
	constexpr void SetRows(const CoordT<Ts, COL>&... ps) & noexcept
	{
		int i = 0;
		(SetRow(i++, ps), ...);
	}

	/// @brief Set the matrix as a scaling matrix
	/// @tparam OtherScalar The type of scale value
	/// @param scale The scale value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetScale(const OtherScalar& scale) & noexcept
	{
		AsDiagonal(CoordT<OtherScalar, (ROW < COL ? ROW : COL)>(scale));
	}

	/// @brief Set the element of matrix
	/// @tparam OtherScalar The type of the new element value
	/// @param i The row index
	/// @param j The column index
	/// @param value The new element value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetValue(int i, int j, const OtherScalar& value) & noexcept
	{
		assert(i >= 0 && i < ROW && j >= 0 && j < COL);
		matrix[i][j] = static_cast<Scalar>(value);
	}

	/// @brief Get the i-th column
	/// @param i The column index
	/// @return The coordinate of the i-th column vector
	[[nodiscard]] constexpr CoordT<Scalar, ROW> Column(int i) const noexcept
	{
		assert(i >= 0 && i < COL);
		CoordT<Scalar, ROW> c;
		for (int j = 0; j < ROW; j++)
		{
			c[j] = matrix[j][i];
		}
		return c;
	}

	/// @brief Get the i-th row
	/// @param i The row index
	/// @return The coordinate of the i-th row vector
	[[nodiscard]] constexpr CoordT<Scalar, COL> Row(int i) const noexcept
	{
		assert(i >= 0 && i < ROW);
		CoordT<Scalar, COL> c;
		for (int j = 0; j < COL; j++)
		{
			c[j] = matrix[i][j];
		}
		return c;
	}

	/// @brief Compute the determinant of the matrix, only for square matrix
	/// @return The determinant
	template<int DIM = ROW>
	[[nodiscard]] constexpr auto Determinant() const noexcept -> std::enable_if_t<DIM == ROW && DIM == COL, Scalar>
	{
		if constexpr (DIM == 1)
		{
			return matrix[0][0];
		}
		else
		{
			Scalar det(0);
			MatrixT<Scalar, DIM - 1, DIM - 1> mat;
			for (int j = 0; j < DIM; j++)
			{
				for (int ii = 0; ii + 1 < DIM; ii++)
				{
					for (int jj = 0; jj < j; jj++)
					{
						mat(ii, jj) = matrix[ii + 1][jj];
					}
					for (int jj = j; jj + 1 < DIM; jj++)
					{
						mat(ii, jj) = matrix[ii + 1][jj + 1];
					}
				}
				det += ((j % 2) ? -1 : 1) * matrix[0][j] * mat.Determinant();
			}
			return det;
		}
	}

	/// @brief Get the diagonal values of matrix
	/// @return The coordinate of diagonal values
	[[nodiscard]] constexpr auto Diagonal() const noexcept
	{
		constexpr int DIM = ROW < COL ? ROW : COL;
		CoordT<Scalar, DIM> v;
		for (int i = 0; i < DIM; i++)
		{
			v[i] = matrix[i][i];
		}
		return v;
	}

	/// @brief Get the matrix element by index
	/// @param i The row index
	/// @param j The column index
	/// @return The element of row i and column j
	[[nodiscard]] constexpr const Scalar& operator()(int i, int j) const noexcept
	{
		assert(i >= 0 && i < ROW && j >= 0 && j < COL);
		return matrix[i][j];
	}

	/// @brief Get the matrix element by index for modification
	/// @param i The row index
	/// @param j The column index
	/// @return The element of row i and column j
	[[nodiscard]] constexpr Scalar& operator()(int i, int j) noexcept
	{
		assert(i >= 0 && i < ROW && j >= 0 && j < COL);
		return matrix[i][j];
	}

	/// @brief Is the matrix singular
	/// @return True if the determinant of matrix is zero
	template<int DIM = ROW>
	[[nodiscard]] auto IsSingular() const noexcept -> std::enable_if_t<DIM == ROW && DIM == COL, bool>
	{
		return std::fabs(Determinant()) <= std::numeric_limits<Scalar>::min();
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator+=(const MatrixT<OtherScalar, ROW, COL>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				matrix[i][j] += other(i, j);
			}
		}
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const MatrixT<OtherScalar, ROW, COL>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		MatrixT<decltype(std::declval<Scalar>() + std::declval<OtherScalar>()), ROW, COL> result;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				result(i, j) = matrix[i][j] + other(i, j);
			}
		}
		return result;
	}

	/// @brief Subtraction assignment
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator-=(const MatrixT<OtherScalar, ROW, COL>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				matrix[i][j] -= other(i, j);
			}
		}
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const MatrixT<OtherScalar, ROW, COL>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		MatrixT<decltype(std::declval<Scalar>() - std::declval<OtherScalar>()), ROW, COL> result;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				result(i, j) = matrix[i][j] - other(i, j);
			}
		}
		return result;
	}

	/// @brief Scalar multiplication assignement
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				matrix[i][j] *= scalar;
			}
		}
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplied matrix
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		MatrixT<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), ROW, COL> result;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				result(i, j) = matrix[i][j] * scalar;
			}
		}
		return result;
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @param m The matrix
	/// @return The multiplied matrix
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	friend constexpr auto operator*(const OtherScalar& scalar, const MatrixT& m) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		MatrixT<decltype(std::declval<OtherScalar>() * std::declval<Scalar>()), ROW, COL> result;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				result(i, j) = scalar * m(i, j);
			}
		}
		return result;
	}

	/// @brief Matrix multiplication assignment, only available between squared matrices
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @tparam ROW2 The number of rows of the other matrix
	/// @tparam COL2 The number of columns of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar, int ROW2, int COL2, std::enable_if_t<ROW == ROW2 && COL == COL2 && ROW2 == COL2, int> = 0>
	constexpr auto operator*=(const MatrixT<OtherScalar, ROW2, COL2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		auto mat = operator*(other);
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				matrix[i][j] = static_cast<Scalar>(mat(i, j));
			}
		}
		return *this;
	}

	/// @brief Matrix multiplication operator, only available when the number of columns is equal to the number of rows of the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @tparam ROW2 The number of rows of the other matrix
	/// @tparam COL2 The number of columns of the other matrix
	/// @param other The other matrix
	/// @return The multiplication result
	template<typename OtherScalar, int ROW2, int COL2, std::enable_if_t<COL == ROW2, int> = 0>
	[[nodiscard]] constexpr auto operator*(const MatrixT<OtherScalar, ROW2, COL2>& other) const noexcept -> ReturnMatrix<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), ROW, COL2>
	{
		MatrixT<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), ROW, COL2> mat;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				for (int k = 0; k < COL2; k++)
				{
					mat(i, k) += matrix[i][j] * other(j, k);
				}
			}
		}
		return mat;
	}

	/// @brief A vector is left-multiplied by the matrix
	/// @tparam OtherScalar The scalar type of the vector
	/// @param coord The coordinate of the vector
	/// @return The resulting vector
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, COL>& coord) const noexcept -> ReturnCoord<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), ROW>
	{
		CoordT<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), ROW> v;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				v[i] += matrix[i][j] * coord[j];
			}
		}
		return v;
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				matrix[i][j] /= scalar;
			}
		}
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The divided matrix
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		MatrixT<decltype(std::declval<Scalar>() / std::declval<OtherScalar>()), ROW, COL> result;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				result(i, j) = matrix[i][j] / scalar;
			}
		}
		return result;
	}

	/// @brief Unary minus operator
	/// @return The matrix with opposite sign of elements
	[[nodiscard]] constexpr MatrixT operator-() const noexcept
	{
		MatrixT m;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				m(i, j) = -matrix[i][j];
			}
		}
		return m;
	}

	/// @brief Invert the matrix, only available for squared matrix
	/// @details For 4 or higher dimension, the inversion algorithm is not implemented
	/// @return The reference to self
	template<int DIM = ROW>
	auto Invert() noexcept(DIM == 1) -> std::enable_if_t<DIM == ROW && DIM == COL, MatrixT&>
	{
		return *this = Inverted();
	}

	/// @brief Get the inverted matrix, only available for squared matrix
	/// @details For 4 or higher dimension, the inversion algorithm is not implemented
	/// @return The inverted matrix
	template<int DIM = ROW>
	[[nodiscard]] auto Inverted() const noexcept(DIM == 1) -> std::enable_if_t<DIM == ROW && DIM == COL, MatrixT>
	{
		Scalar det = Determinant();
		if (det != Scalar{0})
		{
			if constexpr (DIM == 1)
			{
				MatrixT mat;
				mat(0, 0) = Scalar{1} / det;
				return mat;
			}
			else
			{
				Throw_Not_Implemented();
			}
		}
		return {};
	}

	/// @brief Matrix left multiplication assignment the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @tparam ROW2 The number of rows of the other matrix
	/// @tparam COL2 The number of columns of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar, int DIM, std::enable_if_t<DIM == ROW && DIM == COL, int> = 0>
	constexpr auto LeftMultiply(const MatrixT<OtherScalar, DIM, DIM>& other) noexcept -> ReturnThis<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		auto mat = other * (*this);
		for (int i = 0; i < DIM; i++)
		{
			for (int j = 0; j < DIM; j++)
			{
				matrix[i][j] = static_cast<Scalar>(mat(i, j));
			}
		}
		return *this;
	}

	/// @brief Get the matrix left multiplied by the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @tparam ROW2 The number of rows of the other matrix
	/// @tparam COL2 The number of columns of the other matrix
	/// @param other The other matrix
	/// @return The multiplied matrix
	template<typename OtherScalar, int ROW2, int COL2, std::enable_if_t<COL2 == ROW, int> = 0>
	[[nodiscard]] constexpr auto LeftMultiplied(const MatrixT<OtherScalar, ROW2, COL2>& other) const noexcept -> ReturnMatrix<decltype(std::declval<OtherScalar>() * std::declval<Scalar>()), ROW2, COL>
	{
		return other * (*this);
	}

	/// @brief Power of the matrix, only available for square matrix
	/// @param pow The exponential
	/// @return The reference to self
	template<int DIM = ROW>
	auto Power(int pow) noexcept(DIM == 1) -> std::enable_if_t<DIM == ROW && DIM == COL, MatrixT&>
	{
		if (pow == 0)
		{
			SetIdentity();
		}
		else if (pow == -1)
		{
			Invert();
		}
		else if (pow != 1)
		{
			if (pow < 0)
			{
				Invert();
				pow = -pow;
			}
			MatrixT tmp(*this);
			--pow;
			while (true)
			{
				if (pow % 2)
				{
					operator*=(tmp);
				}
				if (pow == 1)
				{
					break;
				}
				tmp *= tmp;
				pow /= 2;
			}
		}
		return *this;
	}

	/// @brief Get the power of the matrix, only available for square matrix
	/// @param pow The exponential
	/// @return The powered matrix
	template<int DIM = ROW>
	[[nodiscard]] auto Powered(int pow) const noexcept(DIM == 1) -> std::enable_if_t<DIM == ROW && DIM == COL, MatrixT>
	{
		return MatrixT(*this).Power(pow);
	}

	/// @brief Transpose the matrix, only available for square matrix
	/// @return The reference to self
	template<int DIM = ROW>
	constexpr auto Transpose() noexcept -> std::enable_if_t<DIM == ROW && DIM == COL, MatrixT&>
	{
		for (int i = 0; i < DIM; i++)
		{
			for (int j = i + 1; j < DIM; j++)
			{
				swap_c(matrix[i][j], matrix[j][i]);
			}
		}
		return *this;
	}

	/// @brief Get the transposed matrix
	/// @return The transposed matrix
	[[nodiscard]] constexpr MatrixT<Scalar, COL, ROW> Transposed() const noexcept
	{
		MatrixT<Scalar, COL, ROW> m;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				m(j, i) = matrix[i][j];
			}
		}
		return m;
	}

	/// @brief Write the matrix
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param matrix The matrix
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const MatrixT& matrix)
	{
		for (int i = 0; i < ROW; i++)
		{
			os << matrix(i, 0);
			for (int j = 1; j < COL; j++)
			{
				os << ' ' << matrix(i, j);
			}
			if (i + 1 != ROW)
			{
				os << '\n';
			}
		}
		return os;
	}

private:
	/// @brief Underlying array of matrix
	Scalar matrix[ROW][COL] = {};
};

/// @brief Specialized class of 2x2 matrix
/// @tparam Scalar Type of matrix elements
template<typename Scalar>
class MatrixT<Scalar, 2, 2>
{
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, MatrixT<ScalarType, 2, 2>>;
	template<typename ScalarType, int DIM>
	using ReturnCoord = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, DIM>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, MatrixT&>;

public:
	/// @brief Default constructor
	/// @details The matrix is initialized as zero matrix
	constexpr MatrixT() noexcept = default;

	/// @brief Construct a diagonal matrix with a value
	/// @param v The diagonal value
	explicit constexpr MatrixT(Scalar v) noexcept
		: matrix{{v, Scalar{0}}, {Scalar{0}, v}}
	{
	}

	/// @brief Construct from values
	/// @tparam T1,T2,T3,T4 The types of the values
	/// @param v1,v2,v3,v4 The values
	template<typename T1, typename T2, typename T3, typename T4, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3, T4>, int> = 0>
	constexpr MatrixT(T1&& v1, T2&& v2, T3&& v3, T4&& v4) noexcept
		: matrix{{std::forward<T1>(v1), std::forward<T2>(v2)}, {std::forward<T3>(v3), std::forward<T4>(v4)}}
	{
	}

	/// @brief Construct from column vectors
	/// @tparam T1,T2 The scalar types of the column vectors
	/// @param p1,p2 The column vectors
	template<typename T1, typename T2, std::enable_if_t<are_convertible_v<Scalar, T1, T2>, int> = 0>
	constexpr MatrixT(const CoordT<T1, 2>& p1, const CoordT<T2, 2>& p2) noexcept
		: matrix{{p1[0], p2[0]}, {p1[1], p2[1]}}
	{
	}

	/// @brief Set the i-th column
	/// @tparam OtherScalar The scalar type of the new column vector
	/// @param i The index of the column
	/// @param coord The new column vector
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetCol(int i, const CoordT<OtherScalar, 2>& coord) & noexcept
	{
		assert(i >= 0 && i < 2);
		matrix[0][i] = coord[0];
		matrix[1][i] = coord[1];
	}

	/// @brief Set all the column vectors
	/// @tparam T1,T2 The scalar types of the column vectors
	/// @param p1,p2 The column vectors
	template<typename T1, typename T2, std::enable_if_t<are_convertible_v<Scalar, T1, T2>, int> = 0>
	constexpr void SetCols(const CoordT<T1, 2>& p1, const CoordT<T2, 2>& p2) & noexcept
	{
		matrix[0][0] = p1[0];
		matrix[0][1] = p2[0];
		matrix[1][0] = p1[1];
		matrix[1][1] = p2[1];
	}

	/// @brief Set the diagonal values of matrix
	/// @details The number of diagonal values should be not more than 2. The remaining elements of matrix are not changed.
	/// @tparam ...T The types of the diagonal values
	/// @param ...vs The diagonal values
	template<typename... T, std::enable_if_t<sizeof...(T) <= 2 && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void SetDiagonal(T&&... vs) & noexcept
	{
		int i = 0;
		((matrix[i][i] = std::forward<T>(vs), ++i), ...);
	}

	/// @brief Set the diagonal values of matrix by a coordinate
	/// @details The dimension of the coordinate should be not more than 2. The remaining elements of matrix are not changed.
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @tparam DIM The dimension of the coordinate
	/// @param coord The diagonal coordinate
	template<typename OtherScalar, int DIM, std::enable_if_t<DIM <= 2 && std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetDiagonal(const CoordT<OtherScalar, DIM>& coord) & noexcept
	{
		matrix[0][0] = coord[0];
		if constexpr (DIM > 1)
		{
			matrix[1][1] = coord[1];
		}
	}

	/// @brief Set the matrix to be diagonal
	/// @details The number of the diagonal values should be not more than 2. The other elements are set to be zero.
	/// @tparam ...T The types of the diagonal values
	/// @param ...vs The diagonal values
	template<typename... T, std::enable_if_t<sizeof...(T) <= 2 && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void AsDiagonal(T&&... vs) & noexcept
	{
		AsDiagonal(CoordT<Scalar, sizeof...(T)>(vs...));
	}

	/// @brief Set the matrix to be diagonal using a coordinate
	/// @details The dimension of the coordinate should be not more than 2. The other elements are set to be zero.
	/// @tparam OtherScalar The scalar type of the diagonal coordinate
	/// @tparam DIM The dimension of the coordinate
	/// @param coord The diagonal coordinate
	template<typename OtherScalar, int DIM, std::enable_if_t<DIM <= 2 && std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void AsDiagonal(const CoordT<OtherScalar, DIM>& coord) & noexcept
	{
		matrix[0][0] = coord[0];
		if constexpr (DIM == 2)
		{
			matrix[1][1] = coord[1];
		}
		else
		{
			matrix[1][1] = Scalar{0};
		}
		matrix[0][1] = matrix[1][0] = Scalar{0};
	}

	/// @brief Set the matrix to be dot operator of a coordinate.
	/// @details The dot matrix M is set as vv^T.
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @param coord The coordinate.
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetDot(const CoordT<OtherScalar, 2>& coord) & noexcept
	{
		matrix[0][0] = coord[0] * coord[0];
		matrix[1][1] = coord[1] * coord[1];
		matrix[0][1] = matrix[1][0] = coord[0] * coord[1];
	}

	/// @brief Set the matrix to be identity matrix
	constexpr void SetIdentity() & noexcept
	{
		matrix[0][0] = matrix[1][1] = Scalar{1};
		matrix[0][1] = matrix[1][0] = Scalar{0};
	}

	/// @brief Set the matrix as rotatio with an angle in 2D
	/// @tparam OtherScalar The type of the angle
	/// @param angle The rotation angle
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	void SetRotation(const OtherScalar& angle) & noexcept
	{
		matrix[0][0] = matrix[1][1] = std::cos(angle);
		matrix[0][1] = -(matrix[1][0] = std::sin(angle));
	}

	/// @brief Set the i-th row vector
	/// @tparam OtherScalar The scalar type of the row vector
	/// @param i The index of row
	/// @param coord The new row vector
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetRow(int i, const CoordT<OtherScalar, 2>& coord) & noexcept
	{
		assert(i >= 0 && i < 2);
		matrix[i][0] = coord[0];
		matrix[i][1] = coord[1];
	}

	/// @brief Set all the row vectors
	/// @tparam T1,T2 The scalar types of the row vectors
	/// @param p1,p2 The row vectors
	template<typename T1, typename T2, std::enable_if_t<are_convertible_v<Scalar, T1, T2>, int> = 0>
	constexpr void SetRows(const CoordT<T1, 2>& p1, const CoordT<T2, 2>& p2) & noexcept
	{
		matrix[0][0] = p1[0];
		matrix[0][1] = p1[1];
		matrix[1][0] = p2[0];
		matrix[1][1] = p2[1];
	}

	/// @brief Set the matrix as a scaling matrix
	/// @tparam OtherScalar The type of scale value
	/// @param scale The scale value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetScale(const OtherScalar& scale) & noexcept
	{
		AsDiagonal(scale, scale);
	}

	/// @brief Set the element of matrix
	/// @tparam OtherScalar The type of the new element value
	/// @param i The row index
	/// @param j The column index
	/// @param value The new element value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetValue(int i, int j, const OtherScalar& value) & noexcept
	{
		assert(i >= 0 && i < 2 && j >= 0 && j < 2);
		matrix[i][j] = static_cast<Scalar>(value);
	}

	/// @brief Get the i-th column
	/// @param i The column index
	/// @return The coordinate of the i-th column vector
	[[nodiscard]] constexpr CoordT<Scalar, 2> Column(int i) const noexcept
	{
		assert(i >= 0 && i < 2);
		return CoordT<Scalar, 2>(matrix[0][i], matrix[1][i]);
	}

	/// @brief Get the i-th row
	/// @param i The row index
	/// @return The coordinate of the i-th row vector
	[[nodiscard]] constexpr CoordT<Scalar, 2> Row(int i) const noexcept
	{
		assert(i >= 0 && i < 2);
		return CoordT<Scalar, 2>(matrix[i][0], matrix[i][1]);
	}

	/// @brief Compute the determinant of the matrix, only for square matrix
	/// @return The determinant
	[[nodiscard]] constexpr Scalar Determinant() const noexcept
	{
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	/// @brief Get the diagonal values of matrix
	/// @return The coordinate of diagonal values
	[[nodiscard]] constexpr auto Diagonal() const noexcept
	{
		return CoordT<Scalar, 2>(matrix[0][0], matrix[1][1]);
	}

	/// @brief Get the matrix element by index
	/// @param i The row index
	/// @param j The column index
	/// @return The element of row i and column j
	[[nodiscard]] constexpr const Scalar& operator()(int i, int j) const noexcept
	{
		assert(i >= 0 && i < 2 && j >= 0 && j < 2);
		return matrix[i][j];
	}

	/// @brief Get the matrix element by index for modification
	/// @param i The row index
	/// @param j The column index
	/// @return The element of row i and column j
	[[nodiscard]] constexpr Scalar& operator()(int i, int j) noexcept
	{
		assert(i >= 0 && i < 2 && j >= 0 && j < 2);
		return matrix[i][j];
	}

	/// @brief Is the matrix singular
	/// @return True if the determinant of matrix is zero
	[[nodiscard]] bool IsSingular() const noexcept
	{
		return std::abs(Determinant()) <= std::numeric_limits<Scalar>::min();
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator+=(const MatrixT<OtherScalar, 2, 2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		matrix[0][0] += other(0, 0);
		matrix[0][1] += other(0, 1);
		matrix[1][0] += other(1, 0);
		matrix[1][1] += other(1, 1);
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const MatrixT<OtherScalar, 2, 2>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		return {matrix[0][0] + other(0, 0), matrix[0][1] + other(0, 1), matrix[1][0] + other(1, 0), matrix[1][1] + other(1, 1)};
	}

	/// @brief Subtraction assignment
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator-=(const MatrixT<OtherScalar, 2, 2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		matrix[0][0] -= other(0, 0);
		matrix[0][1] -= other(0, 1);
		matrix[1][0] -= other(1, 0);
		matrix[1][1] -= other(1, 1);
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const MatrixT<OtherScalar, 2, 2>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		return {matrix[0][0] - other(0, 0), matrix[0][1] - other(0, 1), matrix[1][0] - other(1, 0), matrix[1][1] - other(1, 1)};
	}

	/// @brief Scalar multiplication assignement
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		matrix[0][0] *= scalar;
		matrix[0][1] *= scalar;
		matrix[1][0] *= scalar;
		matrix[1][1] *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplied matrix
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {matrix[0][0] * scalar, matrix[0][1] * scalar, matrix[1][0] * scalar, matrix[1][1] * scalar};
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @param m The matrix
	/// @return The multiplied matrix
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	friend constexpr auto operator*(const OtherScalar& scalar, const MatrixT& m) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return {scalar * m(0, 0), scalar * m(0, 1), scalar * m(1, 0), scalar * m(1, 1)};
	}

	/// @brief Matrix multiplication assignment, only available between squared matrices
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @tparam ROW2 The number of rows of the other matrix
	/// @tparam COL2 The number of columns of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator*=(const MatrixT<OtherScalar, 2, 2>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		auto mat = operator*(other);
		matrix[0][0] = static_cast<Scalar>(mat(0, 0));
		matrix[0][1] = static_cast<Scalar>(mat(0, 1));
		matrix[1][0] = static_cast<Scalar>(mat(1, 0));
		matrix[1][1] = static_cast<Scalar>(mat(1, 1));
		return *this;
	}

	/// @brief Matrix multiplication operator, only available when the number of columns is equal to the number of rows of the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @tparam ROW2 The number of rows of the other matrix
	/// @tparam COL2 The number of columns of the other matrix
	/// @param other The other matrix
	/// @return The multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const MatrixT<OtherScalar, 2, 2>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {matrix[0][0] * other(0, 0) + matrix[0][1] * other(1, 0), matrix[0][0] * other(0, 1) + matrix[0][1] * other(1, 1), matrix[1][0] * other(0, 0) + matrix[1][1] * other(1, 0), matrix[1][0] * other(0, 1) + matrix[1][1] * other(1, 1)};
	}

	/// @brief A vector is left-multiplied by the matrix
	/// @tparam OtherScalar The scalar type of the vector
	/// @param coord The coordinate of the vector
	/// @return The resulting vector
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, 2>& coord) const noexcept -> ReturnCoord<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), 2>
	{
		return {matrix[0][0] * coord[0] + matrix[0][1] * coord[1], matrix[1][0] * coord[0] + matrix[1][1] * coord[1]};
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		matrix[0][0] /= scalar;
		matrix[0][1] /= scalar;
		matrix[1][0] /= scalar;
		matrix[1][1] /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The divided matrix
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {matrix[0][0] / scalar, matrix[0][1] / scalar, matrix[1][0] / scalar, matrix[1][1] / scalar};
	}

	/// @brief Unary minus operator
	/// @return The matrix with opposite sign of elements
	[[nodiscard]] constexpr MatrixT operator-() const noexcept
	{
		return {-matrix[0][0], -matrix[0][1], -matrix[1][0], -matrix[1][1]};
	}

	/// @brief Invert the matrix
	/// @return The reference to self
	constexpr MatrixT& Invert() noexcept
	{
		auto mat = Inverted();
		matrix[0][0] = mat(0, 0);
		matrix[0][1] = mat(0, 1);
		matrix[1][0] = mat(1, 0);
		matrix[1][1] = mat(1, 1);
		return *this;
	}

	/// @brief Get the inverted matrix
	/// @return The inverted matrix
	[[nodiscard]] constexpr MatrixT Inverted() const noexcept
	{
		Scalar det = Determinant();
		if (det != Scalar{0})
		{
			return MatrixT(matrix[1][1] / det, -matrix[0][1] / det, -matrix[1][0] / det, matrix[0][0] / det);
		}
		return {};
	}

	/// @brief Matrix left multiplication assignment the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto LeftMultiply(const MatrixT<OtherScalar, 2, 2>& other) noexcept -> ReturnThis<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		auto mat = other * (*this);
		matrix[0][0] = static_cast<Scalar>(mat(0, 0));
		matrix[0][1] = static_cast<Scalar>(mat(0, 1));
		matrix[1][0] = static_cast<Scalar>(mat(1, 0));
		matrix[1][1] = static_cast<Scalar>(mat(1, 1));
		return *this;
	}

	/// @brief Get the matrix left multiplied by the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The multiplied matrix
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto LeftMultiplied(const MatrixT<OtherScalar, 2, 2>& other) const noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return other * (*this);
	}

	/// @brief Power of the matrix, only available for square matrix
	/// @param pow The exponential
	/// @return The reference to self
	constexpr MatrixT& Power(int pow) noexcept
	{
		if (pow == 0)
		{
			SetIdentity();
		}
		else if (pow == -1)
		{
			Invert();
		}
		else if (pow != 1)
		{
			if (pow < 0)
			{
				Invert();
				pow = -pow;
			}
			MatrixT tmp(*this);
			--pow;
			while (true)
			{
				if (pow % 2)
				{
					operator*=(tmp);
				}
				if (pow == 1)
				{
					break;
				}
				tmp *= tmp;
				pow /= 2;
			}
		}
		return *this;
	}

	/// @brief Get the power of the matrix, only available for square matrix
	/// @param pow The exponential
	/// @return The powered matrix
	[[nodiscard]] constexpr MatrixT Powered(int pow) const noexcept
	{
		return MatrixT(*this).Power(pow);
	}

	/// @brief Transpose the matrix, only available for square matrix
	/// @return The reference to self
	constexpr MatrixT& Transpose() noexcept
	{
		swap_c(matrix[0][1], matrix[1][0]);
		return *this;
	}

	/// @brief Get the transposed matrix
	/// @return The transposed matrix
	[[nodiscard]] constexpr MatrixT Transposed() const noexcept
	{
		return MatrixT(matrix[0][0], matrix[1][0], matrix[0][1], matrix[1][1]);
	}

	/// @brief Write the matrix
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param matrix The matrix
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const MatrixT& matrix)
	{
		os << matrix.matrix[0][0] << ' ' << matrix.matrix[0][1] << '\n';
		os << matrix.matrix[1][0] << ' ' << matrix.matrix[1][1];
		return os;
	}

private:
	/// @brief Underlying array of matrix
	Scalar matrix[2][2] = {};
};

/// @brief Specialized class of 3x3 matrix
/// @tparam Scalar Type of matrix elements
template<typename Scalar>
class MatrixT<Scalar, 3, 3>
{
	template<typename ScalarType>
	using ReturnType = std::enable_if_t<sizeof(ScalarType) >= 0, MatrixT<ScalarType, 3, 3>>;
	template<typename ScalarType, int DIM>
	using ReturnCoord = std::enable_if_t<sizeof(ScalarType) >= 0, CoordT<ScalarType, DIM>>;
	template<typename ScalarType>
	using ReturnThis = std::enable_if_t<std::is_convertible_v<ScalarType, Scalar>, MatrixT&>;

public:
	/// @brief Default constructor
	/// @details The matrix is initialized as zero matrix
	constexpr MatrixT() noexcept = default;

	/// @brief Construct a diagonal matrix with a value
	/// @param v The diagonal value
	explicit constexpr MatrixT(Scalar v) noexcept
		: matrix{{v, Scalar{0}, Scalar{0}}, {Scalar{0}, v, Scalar{0}}, {Scalar{0}, Scalar{0}, v}}
	{
	}

	/// @brief Construct from values
	/// @tparam T1,T2,T3,T4,T5,T6,T7,T8,T9 The types of the values
	/// @param v1,v2,v3,v4,v5,v6,v7,v8,v9 The values
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3, T4, T5, T6, T7, T8, T9>, int> = 0>
	constexpr MatrixT(T1&& v1, T2&& v2, T3&& v3, T4&& v4, T5&& v5, T6&& v6, T7&& v7, T8&& v8, T9&& v9) noexcept
		: matrix{{std::forward<T1>(v1), std::forward<T2>(v2), std::forward<T3>(v3)}, {std::forward<T4>(v4), std::forward<T5>(v5), std::forward<T6>(v6)}, {std::forward<T7>(v7), std::forward<T8>(v8), std::forward<T9>(v9)}}
	{
	}

	/// @brief Construct from column vectors
	/// @tparam T1,T2,T3 The scalar type of the column vectors
	/// @param p1,p2,p3 The column vectors
	template<typename T1, typename T2, typename T3, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3>, int> = 0>
	constexpr MatrixT(const CoordT<T1, 3>& p1, const CoordT<T2, 3>& p2, const CoordT<T3, 3>& p3) noexcept
		: matrix{{p1[0], p2[0], p3[0]}, {p1[1], p2[1], p3[1]}, {p1[2], p2[2], p3[2]}}
	{
	}

	/// @brief Set the i-th column
	/// @tparam OtherScalar The scalar type of the new column vector
	/// @param i The index of the column
	/// @param coord The new column vector
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetCol(int i, const CoordT<OtherScalar, 3>& coord) & noexcept
	{
		assert(i >= 0 && i < 3);
		matrix[0][i] = coord[0];
		matrix[1][i] = coord[1];
		matrix[2][i] = coord[2];
	}

	/// @brief Set all the column vectors
	/// @tparam T1,T2,T3 The scalar types of the column vectors
	/// @param p1,p2,p3 The column vectors
	template<typename T1, typename T2, typename T3, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3>, int> = 0>
	constexpr void SetCols(const CoordT<T1, 3>& p1, const CoordT<T2, 3>& p2, const CoordT<T3, 3>& p3) & noexcept
	{
		matrix[0][0] = p1[0];
		matrix[1][0] = p1[1];
		matrix[2][0] = p1[2];
		matrix[0][1] = p2[0];
		matrix[1][1] = p2[1];
		matrix[2][1] = p2[2];
		matrix[0][2] = p3[0];
		matrix[1][2] = p3[1];
		matrix[2][2] = p3[2];
	}

	/// @brief Set the matrix to be cross product operator, only available in 3D
	/// @tparam OtherScalar The scalar type of the vector to be cross-producted
	/// @param coord The vector to be cross-producted
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetCross(const CoordT<OtherScalar, 3>& coord) & noexcept
	{
		matrix[0][0] = matrix[1][1] = matrix[2][2] = 0.0;
		matrix[1][2] = -(matrix[2][1] = coord.X());
		matrix[2][0] = -(matrix[0][2] = coord.Y());
		matrix[0][1] = -(matrix[1][0] = coord.Z());
	}

	/// @brief Set the diagonal values of matrix
	/// @details The number of diagonal values should be not more than 3. The remaining elements of matrix are not changed.
	/// @tparam ...T The types of the diagonal values
	/// @param ...vs The diagonal values
	template<typename... T, std::enable_if_t<sizeof...(T) <= 3 && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void SetDiagonal(T&&... vs) & noexcept
	{
		int i = 0;
		((matrix[i][i] = std::forward<T>(vs), ++i), ...);
	}

	/// @brief Set the diagonal values of matrix by a coordinate
	/// @details The dimension of the coordinate should be not more than 3. The remaining elements of matrix are not changed.
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @tparam DIM The dimension of the coordinate
	/// @param coord The diagonal coordinate
	template<typename OtherScalar, int DIM, std::enable_if_t<DIM <= 3 && std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetDiagonal(const CoordT<OtherScalar, DIM>& coord) & noexcept
	{
		matrix[0][0] = coord[0];
		if constexpr (DIM > 1)
		{
			matrix[1][1] = coord[1];
		}
		if constexpr (DIM > 2)
		{
			matrix[2][2] = coord[2];
		}
	}

	/// @brief Set the matrix to be diagonal
	/// @details The number of the diagonal values should be not more than 3. The other elements are set to be zero.
	/// @tparam ...T The types of the diagonal values
	/// @param ...vs The diagonal values
	template<typename... T, std::enable_if_t<sizeof...(T) <= 3 && are_convertible_v<Scalar, T...>, int> = 0>
	constexpr void AsDiagonal(T&&... vs) & noexcept
	{
		AsDiagonal(CoordT<Scalar, sizeof...(T)>(vs...));
	}

	/// @brief Set the matrix to be diagonal using a coordinate
	/// @details The dimension of the coordinate should be not more than 3. The other elements are set to be zero.
	/// @tparam OtherScalar The scalar type of the diagonal coordinate
	/// @tparam DIM The dimension of the coordinate
	/// @param coord The diagonal coordinate
	template<typename OtherScalar, int DIM, std::enable_if_t<DIM <= 3 && std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void AsDiagonal(const CoordT<OtherScalar, DIM>& coord) & noexcept
	{
		matrix[0][0] = coord[0];
		if constexpr (DIM > 1)
		{
			matrix[1][1] = coord[1];
		}
		else
		{
			matrix[1][1] = Scalar{0};
		}
		if constexpr (DIM > 2)
		{
			matrix[2][2] = coord[2];
		}
		else
		{
			matrix[2][2] = Scalar{0};
		}
		matrix[0][1] = matrix[1][0] = matrix[0][2] = matrix[2][0] = matrix[1][2] = matrix[2][1] = Scalar{0};
	}

	/// @brief Set the matrix to be dot operator of a coordinate.
	/// @details The dot matrix M is set as vv^T.
	/// @tparam OtherScalar The scalar type of the coordinate
	/// @param coord The coordinate.
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetDot(const CoordT<OtherScalar, 3>& coord) & noexcept
	{
		matrix[0][0] = coord[0] * coord[0];
		matrix[1][1] = coord[1] * coord[1];
		matrix[2][2] = coord[2] * coord[2];
		matrix[0][1] = matrix[1][0] = coord[0] * coord[1];
		matrix[0][2] = matrix[2][0] = coord[0] * coord[2];
		matrix[1][2] = matrix[2][1] = coord[1] * coord[2];
	}

	/// @brief Set the matrix to be identity matrix
	constexpr void SetIdentity() & noexcept
	{
		matrix[0][0] = matrix[1][1] = matrix[2][2] = Scalar{1};
		matrix[0][1] = matrix[1][0] = matrix[0][2] = matrix[2][0] = matrix[1][2] = matrix[2][1] = Scalar{0};
	}

	/// @brief Set the matrix as rotation around an axis direction with an angle in 3D
	/// @tparam OtherScalar The scalar type of the axis
	/// @param axis The coordinate of the axis direction
	/// @param angle The rotation angle
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	void SetRotation(const CoordT<OtherScalar, 3>& axis, const Scalar& angle) & noexcept
	{
		Scalar x = static_cast<Scalar>(axis.X());
		Scalar y = static_cast<Scalar>(axis.Y());
		Scalar z = static_cast<Scalar>(axis.Z());
		const Scalar norm = std::sqrt(x * x + y * y + z * z);
		assert(norm > Scalar{0});
		x /= norm;
		y /= norm;
		z /= norm;
		Scalar s = std::sin(angle);
		Scalar c = Scalar{1.0} - std::cos(angle);
		matrix[0][0] = Scalar{1.0} - (z * z + y * y) * c;
		matrix[0][1] = -z * s + x * y * c;
		matrix[0][2] = y * s + x * z * c;
		matrix[1][0] = z * s + x * y * c;
		matrix[1][1] = Scalar{1.0} - (x * x + z * z) * c;
		matrix[1][2] = -x * s + y * z * c;
		matrix[2][0] = -y * s + x * z * c;
		matrix[2][1] = x * s + y * z * c;
		matrix[2][2] = Scalar{1.0} - (x * x + y * y) * c;
	}

	/// @brief Set the i-th row vector
	/// @tparam OtherScalar The scalar type of the row vector
	/// @param i The index of row
	/// @param coord The new row vector
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetRow(int i, const CoordT<OtherScalar, 3>& coord) & noexcept
	{
		assert(i >= 0 && i < 3);
		matrix[i][0] = coord[0];
		matrix[i][1] = coord[1];
		matrix[i][2] = coord[2];
	}

	/// @brief Set all the row vectors
	/// @tparam T1,T2,T3 The scalar types of the row vectors
	/// @param p1,p2,p3 The row vectors
	template<typename T1, typename T2, typename T3, std::enable_if_t<are_convertible_v<Scalar, T1, T2, T3>, int> = 0>
	constexpr void SetRows(const CoordT<T1, 3>& p1, const CoordT<T2, 3>& p2, const CoordT<T3, 3>& p3) & noexcept
	{
		matrix[0][0] = p1[0];
		matrix[0][1] = p1[1];
		matrix[0][2] = p1[2];
		matrix[1][0] = p2[0];
		matrix[1][1] = p2[1];
		matrix[1][2] = p2[2];
		matrix[2][0] = p3[0];
		matrix[2][1] = p3[1];
		matrix[2][2] = p3[2];
	}

	/// @brief Set the matrix as a scaling matrix
	/// @tparam OtherScalar The type of scale value
	/// @param scale The scale value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetScale(const OtherScalar& scale) & noexcept
	{
		AsDiagonal(scale, scale, scale);
	}

	/// @brief Set the element of matrix
	/// @tparam OtherScalar The type of the new element value
	/// @param i The row index
	/// @param j The column index
	/// @param value The new element value
	template<typename OtherScalar, std::enable_if_t<std::is_convertible_v<OtherScalar, Scalar>, int> = 0>
	constexpr void SetValue(int i, int j, const OtherScalar& value) & noexcept
	{
		assert(i >= 0 && i < 3 && j >= 0 && j < 3);
		matrix[i][j] = static_cast<Scalar>(value);
	}

	/// @brief Get the i-th column
	/// @param i The column index
	/// @return The coordinate of the i-th column vector
	[[nodiscard]] constexpr CoordT<Scalar, 3> Column(int i) const noexcept
	{
		assert(i >= 0 && i < 3);
		return CoordT<Scalar, 3>(matrix[0][i], matrix[1][i], matrix[2][i]);
	}

	/// @brief Get the i-th row
	/// @param i The row index
	/// @return The coordinate of the i-th row vector
	[[nodiscard]] constexpr CoordT<Scalar, 3> Row(int i) const noexcept
	{
		assert(i >= 0 && i < 3);
		return CoordT<Scalar, 3>(matrix[i][0], matrix[i][1], matrix[i][2]);
	}

	/// @brief Compute the determinant of the matrix, only for square matrix
	/// @return The determinant
	[[nodiscard]] constexpr Scalar Determinant() const noexcept
	{
		return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
	}

	/// @brief Get the diagonal values of matrix
	/// @return The coordinate of diagonal values
	[[nodiscard]] constexpr auto Diagonal() const noexcept
	{
		return CoordT<Scalar, 3>(matrix[0][0], matrix[1][1], matrix[2][2]);
	}

	/// @brief Get the matrix element by index
	/// @param i The row index
	/// @param j The column index
	/// @return The element of row i and column j
	[[nodiscard]] constexpr const Scalar& operator()(int i, int j) const noexcept
	{
		assert(i >= 0 && i < 3 && j >= 0 && j < 3);
		return matrix[i][j];
	}

	/// @brief Get the matrix element by index for modification
	/// @param i The row index
	/// @param j The column index
	/// @return The element of row i and column j
	[[nodiscard]] constexpr Scalar& operator()(int i, int j) noexcept
	{
		assert(i >= 0 && i < 3 && j >= 0 && j < 3);
		return matrix[i][j];
	}

	/// @brief Is the matrix singular
	/// @return True if the determinant of matrix is zero
	[[nodiscard]] bool IsSingular() const noexcept
	{
		return std::fabs(Determinant()) <= std::numeric_limits<Scalar>::min();
	}

	/// @brief Addition assignment
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator+=(const MatrixT<OtherScalar, 3, 3>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		matrix[0][0] += other(0, 0);
		matrix[0][1] += other(0, 1);
		matrix[0][2] += other(0, 2);
		matrix[1][0] += other(1, 0);
		matrix[1][1] += other(1, 1);
		matrix[1][2] += other(1, 2);
		matrix[2][0] += other(2, 0);
		matrix[2][1] += other(2, 1);
		matrix[2][2] += other(2, 2);
		return *this;
	}

	/// @brief Addition operator
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The addition result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator+(const MatrixT<OtherScalar, 3, 3>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() + std::declval<OtherScalar>())>
	{
		return {matrix[0][0] + other(0, 0), matrix[0][1] + other(0, 1), matrix[0][2] + other(0, 2),
			matrix[1][0] + other(1, 0), matrix[1][1] + other(1, 1), matrix[1][2] + other(1, 2),
			matrix[2][0] + other(2, 0), matrix[2][1] + other(2, 1), matrix[2][2] + other(2, 2)};
	}

	/// @brief Subtraction assignment
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator-=(const MatrixT<OtherScalar, 3, 3>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		matrix[0][0] -= other(0, 0);
		matrix[0][1] -= other(0, 1);
		matrix[0][2] -= other(0, 2);
		matrix[1][0] -= other(1, 0);
		matrix[1][1] -= other(1, 1);
		matrix[1][2] -= other(1, 2);
		matrix[2][0] -= other(2, 0);
		matrix[2][1] -= other(2, 1);
		matrix[2][2] -= other(2, 2);
		return *this;
	}

	/// @brief Subtraction operator
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The subtraction result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator-(const MatrixT<OtherScalar, 3, 3>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() - std::declval<OtherScalar>())>
	{
		return {matrix[0][0] - other(0, 0), matrix[0][1] - other(0, 1), matrix[0][2] - other(0, 2),
			matrix[1][0] - other(1, 0), matrix[1][1] - other(1, 1), matrix[1][2] - other(1, 2),
			matrix[2][0] - other(2, 0), matrix[2][1] - other(2, 1), matrix[2][2] - other(2, 2)};
	}

	/// @brief Scalar multiplication assignement
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator*=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		matrix[0][0] *= scalar;
		matrix[0][1] *= scalar;
		matrix[0][2] *= scalar;
		matrix[1][0] *= scalar;
		matrix[1][1] *= scalar;
		matrix[1][2] *= scalar;
		matrix[2][0] *= scalar;
		matrix[2][1] *= scalar;
		matrix[2][2] *= scalar;
		return *this;
	}

	/// @brief Scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @return The scalar multiplied matrix
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	[[nodiscard]] constexpr auto operator*(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {matrix[0][0] * scalar, matrix[0][1] * scalar, matrix[0][2] * scalar,
			matrix[1][0] * scalar, matrix[1][1] * scalar, matrix[1][2] * scalar,
			matrix[2][0] * scalar, matrix[2][1] * scalar, matrix[2][2] * scalar};
	}

	/// @brief Left scalar multiplication operator
	/// @tparam OtherScalar The type of scalar
	/// @param scalar The scalar
	/// @param m The matrix
	/// @return The multiplied matrix
	template<typename OtherScalar, std::enable_if_t<std::is_arithmetic_v<OtherScalar>, int> = 0>
	friend constexpr auto operator*(const OtherScalar& scalar, const MatrixT& m) noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return {scalar * m(0, 0), scalar * m(0, 1), scalar * m(0, 2),
			scalar * m(1, 0), scalar * m(1, 1), scalar * m(1, 2),
			scalar * m(2, 0), scalar * m(2, 1), scalar * m(2, 2)};
	}

	/// @brief Matrix multiplication assignment, only available between squared matrices
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator*=(const MatrixT<OtherScalar, 3, 3>& other) noexcept -> ReturnThis<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		auto mat = operator*(other);
		matrix[0][0] = static_cast<Scalar>(mat(0, 0));
		matrix[0][1] = static_cast<Scalar>(mat(0, 1));
		matrix[0][2] = static_cast<Scalar>(mat(0, 2));
		matrix[1][0] = static_cast<Scalar>(mat(1, 0));
		matrix[1][1] = static_cast<Scalar>(mat(1, 1));
		matrix[1][2] = static_cast<Scalar>(mat(1, 2));
		matrix[2][0] = static_cast<Scalar>(mat(2, 0));
		matrix[2][1] = static_cast<Scalar>(mat(2, 1));
		matrix[2][2] = static_cast<Scalar>(mat(2, 2));
		return *this;
	}

	/// @brief Matrix multiplication operator
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The multiplication result
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const MatrixT<OtherScalar, 3, 3>& other) const noexcept -> ReturnType<decltype(std::declval<Scalar>() * std::declval<OtherScalar>())>
	{
		return {matrix[0][0] * other(0, 0) + matrix[0][1] * other(1, 0) + matrix[0][2] * other(2, 0), matrix[0][0] * other(0, 1) + matrix[0][1] * other(1, 1) + matrix[0][2] * other(2, 1), matrix[0][0] * other(0, 2) + matrix[0][1] * other(1, 2) + matrix[0][2] * other(2, 2),
			matrix[1][0] * other(0, 0) + matrix[1][1] * other(1, 0) + matrix[1][2] * other(2, 0), matrix[1][0] * other(0, 1) + matrix[1][1] * other(1, 1) + matrix[1][2] * other(2, 1), matrix[1][0] * other(0, 2) + matrix[1][1] * other(1, 2) + matrix[1][2] * other(2, 2),
			matrix[2][0] * other(0, 0) + matrix[2][1] * other(1, 0) + matrix[2][2] * other(2, 0), matrix[2][0] * other(0, 1) + matrix[2][1] * other(1, 1) + matrix[2][2] * other(2, 1), matrix[2][0] * other(0, 2) + matrix[2][1] * other(1, 2) + matrix[2][2] * other(2, 2)};
	}

	/// @brief A vector is left-multiplied by the matrix
	/// @tparam OtherScalar The scalar type of the vector
	/// @param coord The coordinate of the vector
	/// @return The resulting vector
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator*(const CoordT<OtherScalar, 3>& coord) const noexcept -> ReturnCoord<decltype(std::declval<Scalar>() * std::declval<OtherScalar>()), 3>
	{
		return {matrix[0][0] * coord[0] + matrix[0][1] * coord[1] + matrix[0][2] * coord[2], matrix[1][0] * coord[0] + matrix[1][1] * coord[1] + matrix[1][2] * coord[2], matrix[2][0] * coord[0] + matrix[2][1] * coord[1] + matrix[2][2] * coord[2]};
	}

	/// @brief Scalar division assignment
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto operator/=(const OtherScalar& scalar) noexcept -> ReturnThis<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		matrix[0][0] /= scalar;
		matrix[0][1] /= scalar;
		matrix[0][2] /= scalar;
		matrix[1][0] /= scalar;
		matrix[1][1] /= scalar;
		matrix[1][2] /= scalar;
		matrix[2][0] /= scalar;
		matrix[2][1] /= scalar;
		matrix[2][2] /= scalar;
		return *this;
	}

	/// @brief Scalar division operator
	/// @tparam OtherScalar The type of the scalar
	/// @param scalar The scalar
	/// @return The divided matrix
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto operator/(const OtherScalar& scalar) const noexcept -> ReturnType<decltype(std::declval<Scalar>() / std::declval<OtherScalar>())>
	{
		return {matrix[0][0] / scalar, matrix[0][1] / scalar, matrix[0][2] / scalar, matrix[1][0] / scalar, matrix[1][1] / scalar, matrix[1][2] / scalar, matrix[2][0] / scalar, matrix[2][1] / scalar, matrix[2][2] / scalar};
	}

	/// @brief Unary minus operator
	/// @return The matrix with opposite sign of elements
	[[nodiscard]] constexpr MatrixT operator-() const noexcept
	{
		return {-matrix[0][0], -matrix[0][1], -matrix[0][2], -matrix[1][0], -matrix[1][1], -matrix[1][2], -matrix[2][0], -matrix[2][1], -matrix[2][2]};
	}

	/// @brief Invert the matrix
	/// @return The reference to self
	constexpr MatrixT& Invert() noexcept
	{
		return *this = Inverted();
	}

	/// @brief Get the inverted matrix
	/// @return The inverted matrix
	[[nodiscard]] constexpr MatrixT Inverted() const noexcept
	{
		Scalar det = Determinant();
		if (det != Scalar{0})
		{
			det = Scalar{1} / det;
			return {(matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) * det, -(matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]) * det, (matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]) * det,
				-(matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]) * det, (matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2]) * det, -(matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2]) * det,
				(matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) * det, -(matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1]) * det, (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) * det};
		}
		return {};
	}

	/// @brief Matrix left multiplication assignment the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The reference to self
	template<typename OtherScalar>
	constexpr auto LeftMultiply(const MatrixT<OtherScalar, 3, 3>& other) noexcept -> ReturnThis<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		auto mat = other * (*this);
		matrix[0][0] = static_cast<Scalar>(mat(0, 0));
		matrix[0][1] = static_cast<Scalar>(mat(0, 1));
		matrix[0][2] = static_cast<Scalar>(mat(0, 2));
		matrix[1][0] = static_cast<Scalar>(mat(1, 0));
		matrix[1][1] = static_cast<Scalar>(mat(1, 1));
		matrix[1][2] = static_cast<Scalar>(mat(1, 2));
		matrix[2][0] = static_cast<Scalar>(mat(2, 0));
		matrix[2][1] = static_cast<Scalar>(mat(2, 1));
		matrix[2][2] = static_cast<Scalar>(mat(2, 2));
		return *this;
	}

	/// @brief Get the matrix left multiplied by the other matrix
	/// @tparam OtherScalar The scalar type of the other matrix
	/// @param other The other matrix
	/// @return The multiplied matrix
	template<typename OtherScalar>
	[[nodiscard]] constexpr auto LeftMultiplied(const MatrixT<OtherScalar, 3, 3>& other) const noexcept -> ReturnType<decltype(std::declval<OtherScalar>() * std::declval<Scalar>())>
	{
		return other * (*this);
	}

	/// @brief Power of the matrix, only available for square matrix
	/// @param pow The exponential
	/// @return The reference to self
	constexpr MatrixT& Power(int pow) noexcept
	{
		if (pow == 0)
		{
			SetIdentity();
		}
		else if (pow == -1)
		{
			Invert();
		}
		else if (pow != 1)
		{
			if (pow < 0)
			{
				Invert();
				pow = -pow;
			}
			MatrixT tmp(*this);
			--pow;
			while (true)
			{
				if (pow % 2)
				{
					operator*=(tmp);
				}
				if (pow == 1)
				{
					break;
				}
				tmp *= tmp;
				pow /= 2;
			}
		}
		return *this;
	}

	/// @brief Get the power of the matrix, only available for square matrix
	/// @param pow The exponential
	/// @return The powered matrix
	[[nodiscard]] constexpr MatrixT Powered(int pow) const noexcept
	{
		return MatrixT(*this).Power(pow);
	}

	/// @brief Transpose the matrix, only available for square matrix
	/// @return The reference to self
	constexpr MatrixT& Transpose() noexcept
	{
		swap_c(matrix[0][1], matrix[1][0]);
		swap_c(matrix[0][2], matrix[2][0]);
		swap_c(matrix[1][2], matrix[2][1]);
		return *this;
	}

	/// @brief Get the transposed matrix
	/// @return The transposed matrix
	[[nodiscard]] constexpr MatrixT Transposed() const noexcept
	{
		return {matrix[0][0], matrix[1][0], matrix[2][0], matrix[0][1], matrix[1][1], matrix[2][1], matrix[0][2], matrix[1][2], matrix[2][2]};
	}

	/// @brief Write the matrix
	/// @tparam Stream The type of output stream
	/// @param os The output stream
	/// @param matrix The matrix
	/// @return The output stream
	template<typename Stream>
	friend Stream& operator<<(Stream& os, const MatrixT& matrix)
	{
		os << matrix.matrix[0][0] << ' ' << matrix.matrix[0][1] << ' ' << matrix.matrix[0][2] << '\n';
		os << matrix.matrix[1][0] << ' ' << matrix.matrix[1][1] << ' ' << matrix.matrix[1][2] << '\n';
		os << matrix.matrix[2][0] << ' ' << matrix.matrix[2][1] << ' ' << matrix.matrix[2][2];
		return os;
	}

private:
	/// @brief Underlying array of matrix
	Scalar matrix[3][3] = {};
};

/// @brief 2 x 2 real matrix
using Matrix2 = MatrixT<double, 2, 2>;

/// @brief 3 x 3 real matrix
using Matrix3 = MatrixT<double, 3, 3>;

} // namespace AMCAX
