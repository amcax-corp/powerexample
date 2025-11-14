/// @file      MakeVertex.hpp
/// @brief     Class of making a vertex
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <modeling/MakeShape.hpp>
#include <topology/TopoVertex.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeVertexImpl;
#endif

/// @brief Class of making a vertex
class AMCAX_CLASS_API MakeVertex : public MakeShape
{
public:
	/// @brief Construct from a point
	/// @param p The point
	AMCAX_API explicit MakeVertex(const Point3& p);

	/// @brief Get the constructed vertex
	/// @return The constructed vertex
	[[nodiscard]] AMCAX_API const TopoVertex& Vertex();

	/// @brief Get the constructed vertex
	/// @return The constructed vertex
	[[nodiscard]] AMCAX_API operator TopoVertex();

private:
	std::shared_ptr<MakeVertexImpl> makeVertex;
};
} // namespace AMCAX
