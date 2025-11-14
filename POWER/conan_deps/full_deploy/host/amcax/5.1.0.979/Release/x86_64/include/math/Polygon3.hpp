/// @file      Polygon3.hpp
/// @brief     Class of 3D polygon
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <istream>
#include <memory>
#include <ostream>
#include <vector>

#include <common/PointT.hpp>

namespace AMCAX
{
/// @brief Class of 3D polygon
/// @details If the polygon is closed, the first point and the last point coincide.
class Polygon3
{
public:
	/// @brief Default constructor
	Polygon3() noexcept = default;

	/// @brief Construct with a specified number of vertices
	/// @param nv The number of vertices
	/// @param hasParams Do the vertices have parameters
	AMCAX_API Polygon3(int nv, bool hasParams);

	/// @brief Construct from a vector of vertices
	/// @param verts The vertices
	AMCAX_API explicit Polygon3(const std::vector<Point3>& verts);

	/// @brief Construct from a vector of vertices and a vector of parameters
	/// @param verts The vertices
	/// @param params The parameters
	AMCAX_API Polygon3(const std::vector<Point3>& verts, const std::vector<double>& params);

	/// @brief Copy the polygon
	/// @return The copied polygon
	[[nodiscard]] AMCAX_API std::shared_ptr<Polygon3> Copy() const;

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
	/// @return The vertices
	[[nodiscard]] AMCAX_API const std::vector<Point3>& Vertices() const noexcept;

	/// @brief Get the vertices
	/// @return The vertices
	[[nodiscard]] AMCAX_API std::vector<Point3>& Vertices() noexcept;

	/// @brief Do the vertices have parameters
	/// @return True if the parameters are not null
	[[nodiscard]] AMCAX_API bool HasParameters() const noexcept;

	/// @brief Get the parameters
	/// @return The parameters
	[[nodiscard]] AMCAX_API const std::vector<double>& Parameters() const;

	/// @brief Get the parameters
	/// @return The parameters
	[[nodiscard]] AMCAX_API std::vector<double>& Parameters();

	/// @brief Write the polygon
	/// @param os The output stream
	/// @param poly The polygon
	/// @return The output stream
	AMCAX_API friend std::ostream& operator<<(std::ostream& os, const Polygon3& poly);

	/// @brief Read the polygon
	/// @param is The input stream
	/// @param poly The polygon
	/// @return The input stream
	AMCAX_API friend std::istream& operator>>(std::istream& is, Polygon3& poly);

private:
	/// @brief The deflection of polygon
	double deflection = 0.0;

	/// @brief The vertices of polygon
	std::vector<Point3> vertices;

	/// @brief The parameters associated with each vertex
	std::shared_ptr<std::vector<double>> parameters;
};
} // namespace AMCAX
