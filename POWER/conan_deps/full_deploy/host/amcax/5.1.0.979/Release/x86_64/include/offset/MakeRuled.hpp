/// @file      MakeRuled.hpp
/// @brief     Class of making a face or shell with a ruled surface
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
class TopoEdge;
class TopoWire;

/// @brief Class of making a face with a ruled surface
class AMCAX_CLASS_API MakeRuled : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeRuled();

	/// @brief Make a face with a ruled surface from two edges
	/// @details The two edges should have the same parameters
	/// @param edge1 The first edge
	/// @param edge2 The second edge
	AMCAX_API void PerformFace(const TopoEdge& edge1, const TopoEdge& edge2);

	/// @brief Make a shell with ruled surfaces from two wires
	/// @details The two wires should have the same number of edges and each pair of edges have the same parameters
	/// @param wire1 The first wire
	/// @param wire2 The second wire
	AMCAX_API void PerformShell(const TopoWire& wire1, const TopoWire& wire2);

	AMCAX_API void Build() override;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Generated(const TopoShape& s) override;

	[[nodiscard]] AMCAX_API const std::list<TopoShape>& Modified(const TopoShape& s) override;

	[[nodiscard]] AMCAX_API bool IsDeleted(const TopoShape& S) override;

private:
	TopoShape railShape1;
	TopoShape railShape2;
};
} // namespace AMCAX
