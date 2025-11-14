/// @file      CopyShape.hpp
/// @brief     Class of copying a shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/ModifyShape.hpp>

namespace AMCAX
{
/// @brief Class of copying a shape
class AMCAX_CLASS_API CopyShape : public ModifyShape
{
public:
	/// @brief Default constructor
	AMCAX_API CopyShape();

	/// @brief Copy from a shape
	/// @param s The shape
	/// @param copyGeom Whether the geometry of the shape is copied
	/// @param copyMesh Whether the mesh of the shape is copied
	AMCAX_API explicit CopyShape(const TopoShape& s, bool copyGeom = true, bool copyMesh = false);

	/// @brief Perform the copy operation
	/// @param s The shape
	/// @param copyGeom Whether the geometry of the shape is copied
	/// @param copyMesh Whether the mesh of the shape is copied
	AMCAX_API void Perform(const TopoShape& s, bool copyGeom = true, bool copyMesh = false);
};
} // namespace AMCAX
