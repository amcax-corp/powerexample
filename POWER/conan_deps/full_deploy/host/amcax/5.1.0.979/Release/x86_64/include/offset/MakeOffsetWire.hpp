/// @file      MakeOffsetWire.hpp
/// @brief     Class of making offset wires
/// @details   Create the offset wires of the input planar wires, topology changes are supported.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/Precision.hpp>
#include <math/GeometryMacros.hpp>
#include <modeling/MakeShape.hpp>
#include <topology/TopoFace.hpp>
#include <topology/TopoWire.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepOffsetMakeOffsetWire;
#endif

/// @brief Class of making offset wires, it support wire offset on the plane or parameter domain
class AMCAX_CLASS_API MakeOffsetWire : public MakeShape
{
public:
	/// @brief Constructor
	/// @param face The face with a plane surface
	/// @param wire The planar wire, closed or not closed
	/// @param join The blend type used to control the shape of the blend curve between two not-connected offset edges
	/// @param offset The offset distance, positive is to the right and negative is to the left,
	/// which means for an outer wire, positive offset is outer (larger) and negative offset is inner (smaller)
	/// @param isDoubleSided Whether the offset is double-sided, true for double-sided and false for single-sided.
	AMCAX_API explicit MakeOffsetWire(const TopoFace& face, const TopoWire& wire, JoinType join, double offset, bool isDoubleSided = false);

	/// @brief Set offset value to reset offset
	/// @param offset The new offset value
	AMCAX_API void SetOffset(double offset);

	/// @brief Set tolerance of connection judgement
	/// @param tol The tolerance
	AMCAX_API void SetTolerance(double tol);

	/// @brief Build function which is called in Shape()
	AMCAX_API void Build() override;

	/// @brief Get the generated shapes of the input shape
	/// @param s The query edge or vertex of the original shape
	/// @return The offset edges of the offset shape
	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;

private:
	TopoWire mWire;
	TopoFace mFace;
	JoinType joinType;
	double mOffset;
	double mPrecision = Precision::Confusion();
	bool mDoubleSided;
	std::shared_ptr<BRepOffsetMakeOffsetWire> offsetTool;
};
} // namespace AMCAX
