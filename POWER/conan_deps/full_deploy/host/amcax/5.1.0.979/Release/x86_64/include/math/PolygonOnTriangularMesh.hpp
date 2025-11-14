/// @file      PolygonOnTriangularMesh.hpp
/// @brief     Class of polygon on triangular mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <istream>
#include <memory>
#include <ostream>
#include <vector>

#include <common/Macros.hpp>

namespace AMCAX
{
/// @brief Class of polygon on triangular mesh
/// @details The vertices are recorded using indices on the mesh
class PolygonOnTriangularMesh
{
public:
	/// @brief Default constructor
	PolygonOnTriangularMesh() noexcept = default;

	/// @brief Construct with a specified number of vertices
	/// @param nv The number of vertices
	/// @param hasParams Do the vertices have parameters
	AMCAX_API PolygonOnTriangularMesh(int nv, bool hasParams);

	/// @brief Construct from a vector of vertex indices
	/// @param vids The vertex indices
	AMCAX_API explicit PolygonOnTriangularMesh(const std::vector<int>& vids);

	/// @brief Construct from a vector of vertex indices and a vector of parameters
	/// @param vids The vertex indices
	/// @param params The parameters
	AMCAX_API PolygonOnTriangularMesh(const std::vector<int>& vids, const std::vector<double>& params);

	/// @brief Copy the polygon
	/// @return The copied polygon
	[[nodiscard]] AMCAX_API std::shared_ptr<PolygonOnTriangularMesh> Copy() const;

	/// @brief Get the deflection
	/// @return The deflection
	[[nodiscard]] AMCAX_API double Deflection() const noexcept;

	/// @brief Set the deflection
	/// @param def The deflection
	AMCAX_API void SetDeflection(double def) noexcept;

	/// @brief Get the number of vertices
	/// @return The number of vertices
	[[nodiscard]] AMCAX_API int NVertices() const noexcept;

	/// @brief Get the vertex indices
	/// @return The vertex indices
	[[nodiscard]] AMCAX_API const std::vector<int>& Vertices() const noexcept;

	/// @brief Get the vertex indices
	/// @return The vertex indices
	[[nodiscard]] AMCAX_API std::vector<int>& Vertices() noexcept;

	/// @brief Get the i-th vertex index
	/// @param i The index of the vertex index
	/// @return The i-th vertex index
	[[nodiscard]] AMCAX_API const int& Vertex(int i) const noexcept;

	/// @brief Set the i-th vertex index
	/// @param i The index of the vertex index
	/// @param vi The vertex index
	AMCAX_API void SetVertex(int i, int vi) noexcept;

	/// @brief Do the vertices have parameters
	/// @return True if the vertices have parameters
	[[nodiscard]] AMCAX_API bool HasParameters() const noexcept;

	/// @brief Get the parameters
	/// @return The parameters
	[[nodiscard]] AMCAX_API const std::vector<double>& Parameters() const;

	/// @brief Get the parameters
	/// @return The parameters
	[[nodiscard]] AMCAX_API std::vector<double>& Parameters();

	/// @brief Get the i-th parameter
	/// @param i The index of parameter
	/// @return The i-th parameter
	[[nodiscard]] AMCAX_API double Parameter(int i) const;

	/// @brief Set the i-th parameter
	/// @param i The index of the parameter
	/// @param value The parameter
	AMCAX_API void SetParameter(int i, double value);

	/// @brief Set the parameters
	/// @param params The parameters
	AMCAX_API void SetParameters(const std::shared_ptr<std::vector<double>>& params);

	/// @brief Write the polygon
	/// @param os The output stream
	/// @param mesh The polygon
	/// @return The output stream
	AMCAX_API friend std::ostream& operator<<(std::ostream& os, const PolygonOnTriangularMesh& mesh);

	/// @brief Read the polygon
	/// @param is The input stream
	/// @param mesh The polygon
	/// @return The input stream
	AMCAX_API friend std::istream& operator>>(std::istream& is, PolygonOnTriangularMesh& mesh);

private:
	/// @brief The deflection of polygon
	double deflection = 0.0;

	/// @brief The indices of vertices on the triangular mesh
	std::vector<int> vertexIndices;

	/// @brief The parameters associated to each vertex
	std::shared_ptr<std::vector<double>> parameters;
};
} // namespace AMCAX
