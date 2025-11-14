/// @file      Array2.hpp
/// @brief     Template class of two dimensional array
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

namespace AMCAX
{
/// @brief Template class of two dimensional array
/// @tparam T Type of element
template<typename T>
class Array2
{
public:
	/// @brief Type of value
	using value_type = T;

	/// @brief Default constructor
	constexpr Array2() noexcept = default;

	/// @brief Construct an nrow x ncol array
	/// @param nrow The number of rows
	/// @param ncol The number of columns
	Array2(int nrow, int ncol)
	{
		assert(nrow > 0 && ncol > 0);
		Resize(nrow, ncol);
	}

	/// @brief Construct an array with an initial value
	/// @tparam T2 The type of initial value
	/// @param nrow The number of rows
	/// @param ncol The number of columns
	/// @param initvalue The initial value
	template<typename T2>
	Array2(int nrow, int ncol, T2&& initvalue)
	{
		assert(nrow > 0 && ncol > 0);
		Assign(nrow, ncol, std::forward<T2>(initvalue));
	}

	/// @brief Destructor
	~Array2() noexcept = default;

	/// @brief Copy constructor
	/// @param other The other array
	Array2(const Array2& other)
	{
		if (!other.Empty())
		{
			Resize(other.nrow, other.ncol);
			for (int i = 0; i < nrow * ncol; i++)
			{
				values[i] = other.values[i];
			}
		}
	}

	/// @brief Move constructor
	/// @param other The other array
	Array2(Array2&& other) noexcept
		: nrow(other.nrow),
		  ncol(other.ncol),
		  values(std::move(other.values))
	{
		other.nrow = other.ncol = 0;
	}

	/// @brief Copy assignment operator
	/// @param other The other array
	/// @return The reference to self
	Array2& operator=(const Array2& other)
	{
		if (this != &other && !other.Empty())
		{
			Resize(other.nrow, other.ncol);
			for (int i = 0; i < nrow * ncol; i++)
			{
				values[i] = other.values[i];
			}
		}
		return *this;
	}

	/// @brief Move assignement operator
	/// @param other The other array
	/// @return The reference to self
	Array2& operator=(Array2&& other) noexcept
	{
		if (this != &other)
		{
			values = std::move(other.values);
			nrow = other.nrow;
			ncol = other.ncol;
			other.nrow = 0;
			other.ncol = 0;
		}
		return *this;
	}

	/// @brief Get the raw data pointer
	/// @return The raw data pointer
	[[nodiscard]] value_type* Data() noexcept
	{
		return values.get();
	}

	/// @brief Get the constant raw data pointer
	/// @return The constant raw data pointer
	[[nodiscard]] const value_type* Data() const noexcept
	{
		return values.get();
	}

	/// @brief Is the array empty
	/// @return True if the array is empty
	[[nodiscard]] bool Empty() const noexcept
	{
		return nrow == 0 || ncol == 0;
	}

	/// @brief Clear the array
	void Clear() noexcept
	{
		nrow = ncol = 0;
		values.reset();
	}

	/// @brief Get the total number of elements
	/// @return The size of array
	[[nodiscard]] int Size() const noexcept
	{
		return nrow * ncol;
	}

	/// @brief Get the number of rows
	/// @return The number of rows
	[[nodiscard]] int NRow() const noexcept
	{
		return nrow;
	}

	/// @brief Get the number of columns
	/// @return The number of columns
	[[nodiscard]] int NCol() const noexcept
	{
		return ncol;
	}

	/// @brief Get the element by indices
	/// @param i The row index
	/// @param j The column index
	/// @return The element at (i, j)
	[[nodiscard]] const value_type& operator()(int i, int j) const noexcept
	{
		assert(i >= 0 && i < nrow && j >= 0 && j < ncol);
		const int id = i * ncol + j;
		return values[id];
	}

	/// @brief Get the element by indices
	/// @param i The row index
	/// @param j The column index
	/// @return The element at (i, j)
	[[nodiscard]] value_type& operator()(int i, int j) noexcept
	{
		assert(i >= 0 && i < nrow && j >= 0 && j < ncol);
		const int id = i * ncol + j;
		return values[id];
	}

	/// @brief Resize the array
	/// @param row New number of rows
	/// @param col New number of columns
	void Resize(int row, int col)
	{
		assert(row > 0 && col > 0);
		const int newSize = row * col;
		if (nrow * ncol != newSize)
		{
			values = std::make_unique<value_type[]>(newSize);
		}
		nrow = row;
		ncol = col;
	}

	/// @brief Assign the array with a value
	/// @tparam T2 The type of value
	/// @param row The new number of rows
	/// @param col The new number of columns
	/// @param value The value
	template<typename T2>
	void Assign(int row, int col, T2&& value)
	{
		assert(row > 0 && col > 0);
		const int newSize = row * col;
		if (nrow * ncol != newSize)
		{
			values = std::make_unique<value_type[]>(newSize);
		}
		values[0] = std::forward<T2>(value);
		for (int i = 1; i < newSize; i++)
		{
			values[i] = values[0];
		}
		nrow = row;
		ncol = col;
	}

	/// @brief Get the row of given index
	/// @param[in] i The index of row
	/// @param[out] data The row data
	void Row(int i, std::vector<value_type>& data) const noexcept
	{
		assert(i >= 0 && i < nrow && static_cast<int>(data.size()) == ncol);
		for (int j = 0; j < ncol; j++)
		{
			data[j] = (*this)(i, j);
		}
	}

	/// @brief Get the column of given index
	/// @param[in] j The index of column
	/// @param[out] data The column data
	void Col(int j, std::vector<value_type>& data) const noexcept
	{
		assert(j >= 0 && j < ncol && static_cast<int>(data.size()) == nrow);
		for (int i = 0; i < nrow; i++)
		{
			data[i] = (*this)(i, j);
		}
	}

	/// @brief Get the row of given index
	/// @param i The index of row
	/// @return The row data
	std::vector<value_type> Row(int i) const
	{
		assert(i >= 0 && i < nrow);
		std::vector<value_type> result(ncol);
		Row(i, result);
		return result;
	}

	/// @brief Get the column of given index
	/// @param j The index of column
	/// @return The column data
	std::vector<value_type> Col(int j) const
	{
		assert(j >= 0 && j < ncol);
		std::vector<value_type> result(nrow);
		Col(j, result);
		return result;
	}

	/// @brief Fill the row of given index with given data
	/// @param i The index of row
	/// @param data The row data
	void FillRow(int i, const std::vector<value_type>& data) noexcept
	{
		assert(i >= 0 && i < nrow && static_cast<int>(data.size()) == ncol);
		for (int j = 0; j < ncol; j++)
		{
			(*this)(i, j) = data[j];
		}
	}

	/// @brief Fill the column of given index with given data
	/// @param j The index of column
	/// @param data The column data
	void FillCol(int j, const std::vector<value_type>& data) noexcept
	{
		assert(j >= 0 && j < ncol && static_cast<int>(data.size()) == nrow);
		for (int i = 0; i < nrow; i++)
		{
			(*this)(i, j) = data[i];
		}
	}

private:
	int nrow = 0;
	int ncol = 0;
	std::unique_ptr<T[]> values;
};
} // namespace AMCAX
