/// @file      STLTool.hpp
/// @brief     Class of read and write triangular meshes of shapes in STL format
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <string>
#include <vector>

#include <common/Macros.hpp>

namespace AMCAX
{
class TopoShape;
class TriangularMesh;

/// @brief Class of read and write triangular meshes of shapes in STL format
class STLTool
{
public:
	/// @brief Write the mesh of a shape to a file
	/// @param shape The shape
	/// @param file The output file
	/// @param asciiMode Determine whether the output file is ASCII or binary
	/// @return True if the output process is succeed
	AMCAX_API static bool WriteShape(const TopoShape& shape, const std::string& file, bool asciiMode = true);

	/// @brief Write a triangular mesh to a file in binary mode
	/// @param mesh The mesh
	/// @param file The output file
	/// @return True if the output process is succeed
	AMCAX_API static bool WriteBinary(const std::shared_ptr<TriangularMesh>& mesh, const std::string& file);

	/// @brief Write a mesh to a file in ASCII mode
	/// @param mesh The mesh
	/// @param file The output file
	/// @return True if the output process is succeed
	AMCAX_API static bool WriteAscii(const std::shared_ptr<TriangularMesh>& mesh, const std::string& file);

	/// @brief Read a triangular mesh from a file
	/// @param file The input file
	/// @return The triangular mesh
	[[nodiscard]] AMCAX_API static std::shared_ptr<TriangularMesh> ReadFile(const std::string& file);

	/// @brief Read a triangular mesh from a file by merging vertices under given angle bound
	/// @param file The input file
	/// @param mergeAngle The angle bound for merging vertices
	/// @return The triangular mesh
	[[nodiscard]] AMCAX_API static std::shared_ptr<TriangularMesh> ReadFile(const std::string& file, double mergeAngle);

	/// @brief Read triangular meshes from a file by merging vertices under given angle bound
	/// @param[in] file The input file
	/// @param[in] mergeAngle The angle bound for merging vertices
	/// @param[out] meshList The triangular meshes
	AMCAX_API static void ReadFile(const std::string& file, double mergeAngle, std::vector<std::shared_ptr<TriangularMesh>>& meshList);

	/// @brief Read a triangular mesh from a file in binary mode
	/// @param file The input file
	/// @return The triangular mesh
	[[nodiscard]] AMCAX_API static std::shared_ptr<TriangularMesh> ReadBinary(const std::string& file);

	/// @brief Read a triangular mesh from a file in ASCII mode
	/// @param file The input file
	/// @return The triangular mesh
	[[nodiscard]] AMCAX_API static std::shared_ptr<TriangularMesh> ReadAscii(const std::string& file);
};
} // namespace AMCAX
