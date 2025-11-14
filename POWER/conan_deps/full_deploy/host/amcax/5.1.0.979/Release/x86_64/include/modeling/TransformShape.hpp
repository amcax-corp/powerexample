/// @file      TransformShape.hpp
/// @brief     Class of transforming a shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/ModifyShape.hpp>

namespace AMCAX
{
/// @brief Class of transforming a shape
class AMCAX_CLASS_API TransformShape : public ModifyShape
{
public:
	/// @brief Construct from a transformation
	/// @param tr The transformation
	AMCAX_API explicit TransformShape(const Transformation3& tr);

	/// @brief Construct from a shape with a transformation
	/// @param s The shape
	/// @param tr The transformation
	/// @param copyGeom Whether the geometry of the shape is copied
	/// @param copyMesh Whether the mesh of the shape is copied
	AMCAX_API TransformShape(const TopoShape& s, const Transformation3& tr, bool copyGeom = false, bool copyMesh = false);

	/// @brief Perform the transformation on a shape
	/// @param s The shape
	/// @param copyGeom Whether the geometry of the shape is copied
	/// @param copyMesh Whether the mesh of the shape is copied
	AMCAX_API void Perform(const TopoShape& s, bool copyGeom = false, bool copyMesh = false);

	[[nodiscard]] AMCAX_API TopoShape ModifiedShape(const TopoShape& s) const override;
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;

private:
	Transformation3 transformation;
	TopoLocation location;
	bool useModification = false;
};
} // namespace AMCAX
