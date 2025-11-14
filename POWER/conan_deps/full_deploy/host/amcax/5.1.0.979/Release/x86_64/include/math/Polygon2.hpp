/// @file      Polygon2.hpp
/// @brief     Class of 2D polygon
/// @details   Implementation of 2D polygon
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <istream>
#include <ostream>
#include <vector>

#include <common/PointT.hpp>

namespace AMCAX
{
/// @brief The polygon in 2D.
/// @details If the polygon is closed, the first point and the last point coincide.
class Polygon2
{
public:
	/// @brief Construct with a specified number of vertices
	/// @param nv The number of vertices
	AMCAX_API explicit Polygon2(int nv);

	/// @brief Construct from a vector of vertices
	/// @param verts The vertices
	AMCAX_API explicit Polygon2(const std::vector<Point2>& verts);

	/// @brief Get the deflection
	/// @return The deflection
	[[nodiscard]] AMCAX_API double Deflection() const noexcept;

	/// @brief Set the deflection
	/// @param def The deflection
	AMCAX_API void SetDeflection(double def) noexcept;

	/// @brief Get the number of vertices
	/// @return The number of vertices
	[[nodiscard]] AMCAX_API int NVertices() const noexcept;

	/// @brief Get the vertices
	/// @return The vectices
	[[nodiscard]] AMCAX_API const std::vector<Point2>& Vertices() const noexcept;

	/// @brief Get the vertices
	/// @return The vertices
	[[nodiscard]] AMCAX_API std::vector<Point2>& Vertices() noexcept;

	/// @brief Calculate the minimum distance from vertex to polygon
	/// @return The minimum distance
	[[nodiscard]] AMCAX_API double Distance(const Point2& pt) noexcept;

	/// @brief Calculate the nearest point from vertex to polygon
	/// @return The nearest point
	[[nodiscard]] AMCAX_API Point2 NearestPoint(const Point2& pt) noexcept;

	/// @brief Write the polygon
	/// @param os The output stream
	/// @param poly The polygon
	/// @return The output stream
	AMCAX_API friend std::ostream& operator<<(std::ostream& os, const Polygon2& poly);

	/// @brief Read the polygon
	/// @param is The input stream
	/// @param poly The polygon
	/// @return The input stream
	AMCAX_API friend std::istream& operator>>(std::istream& is, Polygon2& poly);

private:
	/// @brief The deflection of polygon
	double deflection = 0.0;

	/// @brief The vertices in the polygon
	std::vector<Point2> vertices;
};
} // namespace AMCAX
