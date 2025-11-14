/// @file      BRepAdaptorCurve2.hpp
/// @brief     Class of adaptor of 2D curves in B-Rep
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <geometry/AdaptorGeom2Curve.hpp>
#include <topology/TopoEdge.hpp>
#include <topology/TopoFace.hpp>

namespace AMCAX
{
/// @brief Class of adaptor of 2D curves in B-Rep
class AMCAX_CLASS_API BRepAdaptorCurve2 : public AdaptorGeom2Curve
{
public:
	/// @brief Default constructor
	BRepAdaptorCurve2() noexcept = default;

	/// @brief Construct from an edge and a face
	/// @param e The edge
	/// @param f The face
	AMCAX_API BRepAdaptorCurve2(const TopoEdge& e, const TopoFace& f);

	[[nodiscard]] AMCAX_API std::shared_ptr<Adaptor2Curve> ShallowCopy() const override;

	/// @brief Initialize from an edge and a face
	/// @param e The edge
	/// @param f The face
	AMCAX_API void Initialize(const TopoEdge& e, const TopoFace& f);

	/// @brief Get the edge
	/// @return The edge
	[[nodiscard]] AMCAX_API const TopoEdge& Edge() const noexcept;

	/// @brief Get the face
	/// @return The face
	[[nodiscard]] AMCAX_API const TopoFace& Face() const noexcept;

private:
	/// @brief Edge
	TopoEdge edge;

	/// @brief Face where the edge lies
	TopoFace face;
};
} // namespace AMCAX
