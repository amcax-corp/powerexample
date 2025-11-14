/// @file      MakeOffset.hpp
/// @brief     Class of making offset wires
/// @details   Create the offset wires of the input planar wires.
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <math/GeometryMacros.hpp>
#include <modeling/MakeShape.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class BRepFillOffsetWire;
class TopoWire;
class TopoShape;
#endif

/// @brief Class of making offset wires
class AMCAX_CLASS_API MakeOffset : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeOffset();

	/// @brief Construct from a face and make an offset on its wires
	/// @param spine The face
	/// @param join Join type between unlink vertices of offset wires
	/// @param isOpenResult Result is open or closed
	AMCAX_API explicit MakeOffset(const TopoFace& spine, JoinType join = JoinType::Arc, bool isOpenResult = false);

	/// @brief Construct from a wire
	/// @param spine Input wires
	/// @param join The join type between unlink vertices of offset wires
	/// @param isOpenResult Result is open or closed
	AMCAX_API explicit MakeOffset(const TopoWire& spine, JoinType join = JoinType::Arc, bool isOpenResult = false);

	/// @brief Initialize the algorithm
	/// @param spine The face with its wires
	/// @param join Join type between unlink vertices of offset wires
	/// @param isOpenResult Result is open or closed
	AMCAX_API void Init(const TopoFace& spine, JoinType join = JoinType::Arc, bool isOpenResult = false);

	/// @brief Initialize the algorithm
	/// @param join Join type between unlink vertices of offset wires
	/// @param isOpenResult Result is open or closed
	AMCAX_API void Init(const JoinType join = JoinType::Arc, bool isOpenResult = false);

	/// @brief Set if use approximation to make the input wire consist of lines and circles
	/// @param toApprox Whether use approximation
	AMCAX_API void SetApprox(bool toApprox);

	/// @brief Add the wire to be offset
	/// @param spine The spine wire
	AMCAX_API void AddWire(const TopoWire& spine);

	/// @brief Compute the offset wire of the input spines
	/// @param offset The distance between result and the input shape.
	///               The distance is calculated along the normal of the input spines
	/// @param alt The distance above the plane
	AMCAX_API void Perform(double offset, double alt = 0.0);

	AMCAX_API void Build() override;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;

	/// @brief Convert all wires of a face to arcs and line segments
	/// @param face The face
	/// @param angleTolerance The angle tolerance
	[[nodiscard]] AMCAX_API TopoFace ConvertFace(const TopoFace& face, double angleTolerance);

private:
	bool isInitialized = false;
	bool isLastLeft = false;
	JoinType joinType = JoinType::Arc;
	bool isOpenResult = false;
	bool isToApprox = false;
	TopoFace face;
	std::list<TopoShape> wires;
	std::shared_ptr<std::list<BRepFillOffsetWire>> left;
	std::shared_ptr<std::list<BRepFillOffsetWire>> right;
};
} // namespace AMCAX
