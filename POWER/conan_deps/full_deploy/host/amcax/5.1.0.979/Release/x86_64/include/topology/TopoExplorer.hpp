/// @file      TopoExplorer.hpp
/// @brief     Class of a tool for exploring the B-Rep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <topology/TopoIterator.hpp>

namespace AMCAX
{
/// @brief Class of a tool for exploring the B-Rep structure
class TopoExplorer
{
public:
	/// @brief Default constructor
	TopoExplorer() noexcept = default;

	/// @brief Construct from a shape and a type of the sub-shapes to be explored
	/// @param s The shape
	/// @param tofind The shape type to search
	/// @param toavoid The shape type to skip in the exploration
	AMCAX_API TopoExplorer(const TopoShape& s, ShapeType tofind, ShapeType toavoid = ShapeType::Shape);

	/// @brief Initialize the explorer from a shape and a type of the sub-shapes to be explored
	/// @param s The shape
	/// @param tofind The shape type to search
	/// @param toavoid The shape type to skip in the exploration
	AMCAX_API void Init(const TopoShape& s, ShapeType tofind, ShapeType toavoid = ShapeType::Shape);

	/// @brief Does the explorer have more shapes
	/// @return True if there are more shapes to be found
	[[nodiscard]] AMCAX_API bool More() const noexcept;

	/// @brief Find the next shape
	AMCAX_API void Next();

	/// @brief Get the current shape
	/// @return The current shape
	[[nodiscard]] AMCAX_API const TopoShape& Value() const noexcept;

	/// @brief Get the current shape
	/// @return The current shape
	[[nodiscard]] AMCAX_API const TopoShape& Current() const noexcept;

	/// @brief Reinitialize the explorer with the original argument
	AMCAX_API void ReInit();

	/// @brief Get the parent shape
	/// @return The parent shape
	[[nodiscard]] AMCAX_API const TopoShape& ExploredShape() const noexcept;

	/// @brief Get the current depth of the current shape.
	/// @return The depth of the current shape
	[[nodiscard]] AMCAX_API int Depth() const noexcept;

	/// @brief Clear the explorer
	AMCAX_API void Clear() noexcept;

private:
	/// @brief Stack of explorer
	std::vector<TopoIterator> stack;

	/// @brief Current shape
	TopoShape shape;

	/// @brief Type to be found
	ShapeType toFind = ShapeType::Shape;

	/// @brief Type to be avoid
	ShapeType toAvoid = ShapeType::Shape;

	/// @brief Has more shape to be found
	bool hasMore = false;
};
} // namespace AMCAX
