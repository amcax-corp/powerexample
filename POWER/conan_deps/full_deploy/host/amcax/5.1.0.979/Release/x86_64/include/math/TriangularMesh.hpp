/// @file      TriangularMesh.hpp
/// @brief     Class of triangular mesh
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <istream>
#include <memory>
#include <ostream>
#include <vector>

#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/TransformationT.hpp>
#include <math/Triangle.hpp>

namespace AMCAX
{
class BoundingBox3;
class MeshParameters;

/// @brief Class of triangular mesh
class TriangularMesh
{
public:
	/// @brief Purpose of the triangular mesh
	enum class MeshPurpose : unsigned char
	{
		/// @brief No special use
		None = 0,

		/// @brief Mesh for algorithms
		Calculation = 1,

		/// @brief Mesh for presentation
		Presentation = 2,

		/// @brief Active mesh in a list
		Active = 4,

		/// @brief Mesh is loaded
		Loaded = 8,

		/// @brief Any mesh in a list
		AnyFallback = 16,

		/// @brief User defined purpose
		User = 32
	};

	/// @brief Default constructor
	TriangularMesh() noexcept = default;

	/// @brief Construct by initialize the number of vertices and the number of triangles
	/// @param nvert The number of vertices
	/// @param ntri The number of triangles
	/// @param hasuvcoord Does the mesh have texture coordinates
	/// @param hasnormal Does the mesh have vertex normals
	AMCAX_API TriangularMesh(int nvert, int ntri, bool hasuvcoord, bool hasnormal = false);

	/// @brief Construct from vectors of vertices and triangles
	/// @param verts The vertices
	/// @param tris The triangles
	AMCAX_API TriangularMesh(const std::vector<Point3>& verts, const std::vector<Triangle>& tris);

	/// @brief Construct from vectors of vertices, texture coordinates and triangles
	/// @param verts The vertices
	/// @param uvs The texture coordinates
	/// @param tris The triangles
	AMCAX_API TriangularMesh(const std::vector<Point3>& verts, const std::vector<Point2>& uvs, const std::vector<Triangle>& tris);

	/// @brief Copy construct from another triangular mesh
	/// @param mesh The other triangular mesh
	AMCAX_API TriangularMesh(const std::shared_ptr<const TriangularMesh>& mesh);

	/// @brief Copy the mesh
	/// @return The copied mesh
	[[nodiscard]] AMCAX_API std::shared_ptr<TriangularMesh> Copy() const;

	/// @brief Get the deflection
	/// @return The deflection
	[[nodiscard]] AMCAX_API double Deflection() const noexcept;

	/// @brief Set the deflection
	/// @param def The deflection
	AMCAX_API void Deflection(double def) noexcept;

	/// @brief Get the parameters of mesh
	/// @return The parameters of mesh
	[[nodiscard]] AMCAX_API const std::shared_ptr<MeshParameters>& Parameters() const noexcept;

	/// @brief Set the parameters of mesh
	/// @param par The parameters of mesh
	AMCAX_API void Parameters(const std::shared_ptr<MeshParameters>& par) noexcept;

	/// @brief Clear the mesh
	AMCAX_API void Clear() noexcept;

	/// @brief Does the mesh has geometry
	/// @return True if the mesh has vertices or triangles
	[[nodiscard]] AMCAX_API bool HasGeometry() const noexcept;

	/// @brief Get the number of vertices
	/// @return The number of vertices
	[[nodiscard]] AMCAX_API int NVertices() const noexcept;

	/// @brief Get the number of triangles
	/// @return The number of triangles
	[[nodiscard]] AMCAX_API int NTriangles() const noexcept;

	/// @brief Does the mesh has texture coordinates
	/// @return True if the mesh has texture coordinates
	[[nodiscard]] AMCAX_API bool HasUVCoords() const noexcept;

	/// @brief Does the mesh has normals
	/// @return True if the mesh has normals
	[[nodiscard]] AMCAX_API bool HasNormals() const noexcept;

	/// @brief Get the i-th vertex
	/// @param i The index of vertex
	/// @return The i-th vertex
	[[nodiscard]] AMCAX_API const Point3& Vertex(int i) const noexcept;

	/// @brief Set the i-th vertex
	/// @param i The index of vertex
	/// @param point The new vertex
	AMCAX_API void SetVertex(int i, const Point3& point) noexcept;

	/// @brief Get the i-th texture coordinate
	/// @param i The index of texture coordinate
	/// @return The i-th texture coordinate
	[[nodiscard]] AMCAX_API const Point2& UVCoord(int i) const noexcept;

	/// @brief Set the i-th texture coordinate
	/// @param i The index of texture coordinate
	/// @param point The new texture coordinate
	AMCAX_API void SetUVCoord(int i, const Point2& point) noexcept;

	/// @brief Get the i-th triangular face
	/// @param i The index of triangle
	/// @return The i-th triangular face
	[[nodiscard]] AMCAX_API const Triangle& Face(int i) const noexcept;

	/// @brief Set th i-th triangular face
	/// @param i The index of the triangle
	/// @param tri The new triangle
	AMCAX_API void SetFace(int i, const Triangle& tri) noexcept;

	/// @brief Get the i-th normal
	/// @param i The index of normal
	/// @return The i-the normal
	[[nodiscard]] AMCAX_API const Direction3& Normal(int i) const noexcept;

	/// @brief Set the i-th normal
	/// @param i The index of normal
	/// @param normal The new normal
	AMCAX_API void SetNormal(int i, const Direction3& normal) noexcept;

	/// @brief Get the purpose of the mesh
	/// @return The purpose of the mesh
	[[nodiscard]] AMCAX_API const unsigned char& Purpose() const noexcept;

	/// @brief Set the purpose of the mesh
	/// @param purp The purpose of the mesh
	AMCAX_API void SetPurpose(const unsigned char& purp) noexcept;

	/// @brief Get the bounding box of the mesh
	/// @return The bounding box of the mesh
	[[nodiscard]] AMCAX_API const BoundingBox3& BoundingBox() const noexcept;

	/// @brief Set the bounding box of the mesh
	/// @param box The bounding box of the mesh
	AMCAX_API void SetBoundingBox(const BoundingBox3& box);

	/// @brief Clear the bounding box
	AMCAX_API void UnsetBoundingBox() noexcept;

	/// @brief Compute the bounding box of the transformed mesh
	/// @param tr The transformation
	/// @return The bounding box of the transformed mesh
	[[nodiscard]] AMCAX_API BoundingBox3 ComputeBoundingBox(const Transformation3& tr) const noexcept;

	/// @brief Does the mesh have a bounding box
	/// @return True if the mesh has a bounding box
	[[nodiscard]] AMCAX_API bool HasBoundingBox() const noexcept;

	/// @brief Update the bounding box of the mesh
	AMCAX_API void UpdateBoundingBox();

	/// @brief Extend a bounding box by the bounding box of the transformed mesh
	/// @param[in,out] box The bounding box need to be extended
	/// @param[in] tr The transformation
	/// @param[in] isAccurate Is the bounding box of the mesh accurately computed
	/// @return True if the box is extended by a non-void bounding box
	AMCAX_API bool ExtendBoundingBox(BoundingBox3& box, const Transformation3& tr, bool isAccurate = false) const noexcept;

	/// @brief Resize the vector of vertices
	/// @param nv The new number of vertices
	AMCAX_API void ResizeVertices(int nv);

	/// @brief Resize the vector of triangles
	/// @param nt The new number of triangles
	AMCAX_API void ResizeTriangles(int nt);

	/// @brief Add capacity for texture coordinates
	AMCAX_API void AddUVCoords();

	/// @brief Clear capacity for texture coordinates
	AMCAX_API void RemoveUVCoords() noexcept;

	/// @brief Add capacity for normals
	AMCAX_API void AddNormals();

	/// @brief Clear capacity for normals
	AMCAX_API void RemoveNormals() noexcept;

	/// @brief Compute smooth normals by averaging the triangle normals
	AMCAX_API void ComputeNormals();

	/// @brief Get the triangles
	/// @return The triangles
	[[nodiscard]] AMCAX_API const std::vector<Triangle>& Triangles() const noexcept;

	/// @brief Get the triangles
	/// @return The triangles
	[[nodiscard]] AMCAX_API std::vector<Triangle>& Triangles() noexcept;

	/// @brief Get the vertices
	/// @return The vertices
	[[nodiscard]] AMCAX_API const std::vector<Point3>& Vertices() const noexcept;

	/// @brief Get the vertices
	/// @return The vertices
	[[nodiscard]] AMCAX_API std::vector<Point3>& Vertices() noexcept;

	/// @brief Get the texture coordinates
	/// @return The texture coordinates
	[[nodiscard]] AMCAX_API const std::vector<Point2>& UVCoords() const noexcept;

	/// @brief Get the texture coordinates
	/// @return The texture coordinates
	[[nodiscard]] AMCAX_API std::vector<Point2>& UVCoords() noexcept;

	/// @brief Get the normals
	/// @return The normals
	[[nodiscard]] AMCAX_API const std::vector<Direction3>& Normals() const noexcept;

	/// @brief Get the normals
	/// @return The normals
	[[nodiscard]] AMCAX_API std::vector<Direction3>& Normals() noexcept;

	/// @brief Write the mesh
	/// @param os The output stream
	/// @param mesh The mesh
	/// @return The output stream
	AMCAX_API friend std::ostream& operator<<(std::ostream& os, const TriangularMesh& mesh);

	/// @brief Read the mesh
	/// @param is The input stream
	/// @param mesh The mesh
	/// @return The input stream
	AMCAX_API friend std::istream& operator>>(std::istream& is, TriangularMesh& mesh);

protected:
	/// @brief The bounding box of triangular mesh
	std::shared_ptr<BoundingBox3> boundingbox;

	/// @brief The deflection of triangular mesh
	double deflection = 0.0;

	/// @brief The vertices of triangular mesh
	std::vector<Point3> vertices;

	/// @brief The triangles of triangular mesh
	std::vector<Triangle> triangles;

	/// @brief The UV coordinates on each vertex of triangular mesh
	std::vector<Point2> uvcoords;

	/// @brief The normals on each face of triangular mesh
	std::vector<Direction3> normals;

	/// @brief The purpose of mesh
	unsigned char purpose = static_cast<unsigned char>(MeshPurpose::None);

	/// @brief The parameters of mesh
	std::shared_ptr<MeshParameters> params;
};
} // namespace AMCAX
