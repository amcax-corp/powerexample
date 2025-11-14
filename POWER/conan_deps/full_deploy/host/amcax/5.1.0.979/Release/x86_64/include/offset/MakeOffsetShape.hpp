/// @file      MakeOffsetShape.hpp
/// @brief     Class of build a shell out of a shape algorithm
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/GeometryMacros.hpp>
#include <modeling/MakeShape.hpp>
#include <offset/BRepOffsetMacros.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepOffsetMakeOffset;
class BRepOffsetMakeSimpleOffset;
#endif

/// @brief Class of build a shell out of a shape algorithm
/// @details The result is an unlooped shape parallel to the source shape
class AMCAX_CLASS_API MakeOffsetShape : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeOffsetShape();

	/// @brief Construct an offset shape using the simple algorithm without intersections computation
	/// @details The input must be a non-closed single face or a shell which only contain tangent faces.
	/// @param s The input face or shell
	/// @param offsetValue The value of offset
	AMCAX_API void PerformBySimple(const TopoShape& s, double offsetValue);

	/// @brief Construct a shape parallel to a given shape
	/// @param s The input shape, which can be face, shell, or solid
	/// @param offset The offset value defines the thickness of the walls.
	///               Its sign indicates which side of the surface of the solid the hollowed shape is built on.
	/// @param tol The coincidence tolerance criterion for generated shapes
	/// @param mode The construction type of parallels applied to free edges of the shape
	/// @param intersection The default is false and will be removal in a later version.
	/// @param selfInter The default is false and will be removal in a later version.
	/// @param join The type of filling the holes that may appear between parallels to the two adjacent faces
	/// @param removeIntEdges Whether to remove the internal edges from the result shape
	AMCAX_API void PerformByJoin(const TopoShape& s, double offset, double tol, BRepOffsetMode mode = BRepOffsetMode::Skin, bool intersection = false, bool selfInter = false, JoinType join = JoinType::Arc, bool removeIntEdges = false);

	AMCAX_API void Build() override;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;

	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& s) override;

	/// @brief Get the type of join
	/// @return The type of join
	[[nodiscard]] AMCAX_API JoinType GetJoinType() const;

protected:
	/// @brief Type of offset algorithm
	enum class OffsetAlgoType
	{
		None,
		Join,
		Simple
	};

	/// @brief Type of last used algorithm
	OffsetAlgoType lastUsedAlgo;

	/// @brief Internal tool for making offset shape
	std::shared_ptr<BRepOffsetMakeOffset> offsetShapeTool;

	/// @brief Internal tool for making simple offset shape
	std::shared_ptr<BRepOffsetMakeSimpleOffset> simpleOffsetShapeTool;
};
} // namespace AMCAX
