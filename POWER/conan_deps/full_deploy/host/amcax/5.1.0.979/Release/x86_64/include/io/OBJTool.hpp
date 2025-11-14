/// @file      OBJTool.hpp
/// @brief     Class of read and write triangular meshes of shapes in OBJ format
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>
#include <string>

#include <common/Macros.hpp>

namespace AMCAX
{
class TopoShape;
class TriangularMesh;

/// @brief Class of read and write triangular meshes of shapes in OBJ format
class OBJTool
{
public:
	/// @brief Write the mesh of a shape to a file
	/// @param shape The shape
	/// @param file The output file
	/// @param divideGroup Determine whether divide the mesh into groups according to the shape compounds
	/// @return True if the output process is succeed
	AMCAX_API static bool WriteShape(const TopoShape& shape, const std::string& file, bool divideGroup = true);

	/// @brief Read a mesh from a file
	/// @param file The input file
	/// @return The triangular mesh
	[[nodiscard]] AMCAX_API static std::shared_ptr<TriangularMesh> ReadFile(const std::string& file);
};
} // namespace AMCAX
