/// @file      Triangle.hpp
/// @brief     Class of triangle
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <tuple>

#include <common/Macros.hpp>

namespace AMCAX
{
/// @brief Class of triangle, used in TriangularMesh
class Triangle
{
public:
	/// @brief Default constructor
	Triangle() noexcept = default;

	/// @brief Construct from the indices
	/// @param n1,n2,n3 The three vertex indices
	AMCAX_API Triangle(int n1, int n2, int n3) noexcept;

	/// @brief Set the vertex indices
	/// @param n1,n2,n3 The three vertex indices
	AMCAX_API void Set(int n1, int n2, int n3) noexcept;

	/// @brief Get the indices of three vertices
	/// @return The tuple of the three vertices
	[[nodiscard]] AMCAX_API auto Get() const noexcept -> std::tuple<int, int, int>;

	/// @brief Get the index of the i-th vertex
	/// @param i The index of vertex
	/// @return The index of the i-th vertex
	[[nodiscard]] AMCAX_API const int& operator[](int i) const;

	/// @brief Get the index of the i-th vertex
	/// @param i The index of vertex
	/// @return The index of the i-th vertex
	[[nodiscard]] AMCAX_API int& operator[](int i);

protected:
	/// @brief The indices of three vertices
	int vid[3] = {-1, -1, -1};
};
} // namespace AMCAX
