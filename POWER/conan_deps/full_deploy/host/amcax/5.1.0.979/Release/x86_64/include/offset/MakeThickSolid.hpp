/// @file      MakeThickSolid.hpp
/// @brief     Class of making a thick solid shape
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <offset/MakeOffsetShape.hpp>

namespace AMCAX
{
/// @brief Class of making a thick solid shape
class AMCAX_CLASS_API MakeThickSolid : public MakeOffsetShape
{
public:
	/// @brief Default consturctor
	AMCAX_API MakeThickSolid();

	/// @brief Make a thick solid using simple algorithm, only for a non-closed single face or shell which contain tangent faces
	/// @param s The input face or shell
	/// @param offsetValue The value of offset
	AMCAX_API void MakeThickBySimple(const TopoShape& s, double offsetValue);

	/// @brief Make a two-sided thick solid using a simple algorithm, only for a non-closed single face or shell which contain tangent faces
	/// @param s The input face or shell
	/// @param offsetValuePositive The value of positive offset
	/// @param offsetValueNegative The value of negative offset
	AMCAX_API void MakeThickBySimple(const TopoShape& s, double offsetValuePositive, double offsetValueNegative);

	/// @brief Make a hollowed thick solid by removing some faces from a solid
	/// @param s The input solid
	/// @param closingFaces The faces to be removed
	/// @param offset The value of offset
	/// @param tol The coincidence tolerance criterion for generated shapes
	/// @param mode The construction type of parallels applied to free edges of the shape
	/// @param intersection The default is false and will be removal in a later version.
	/// @param selfInter The default is false and will be removal in a later version.
	/// @param join The type of filling the holes that may appear between parallels to the two adjacent faces
	/// @param removeIntEdges Whether to remove the internal edges from the result shape
	AMCAX_API void MakeThickByJoin(const TopoShape& s, const std::list<TopoShape>& closingFaces, double offset, double tol, BRepOffsetMode mode = BRepOffsetMode::Skin, bool intersection = false, bool selfInter = false, JoinType join = JoinType::Arc, bool removeIntEdges = false);

	AMCAX_API void Build() override;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;
};
} // namespace AMCAX
