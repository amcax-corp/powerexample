/// @file      TopoIterator.hpp
/// @brief     Class of iterator for B-Rep structure
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <list>

#include <topology/TopoShape.hpp>

namespace AMCAX
{
/// @brief Class of iterator for B-Rep structure
class TopoIterator
{
public:
	/// @brief Traverse the sub-shapes of a parent shape
	/// @param s The parent
	/// @param cumOri Determine whether computing cumulative orientation
	/// @param cumLoc Determine whether computing cumulative location
	AMCAX_API explicit TopoIterator(const TopoShape& s, bool cumOri = true, bool cumLoc = true);

	/// @brief Does the iterator has more shape
	/// @return True if the iterator is not the last shape
	[[nodiscard]] AMCAX_API bool More() const noexcept;

	/// @brief Move the iterator to the next shape
	AMCAX_API void Next();

	/// @brief Get the current shape
	/// @return The current shape
	[[nodiscard]] AMCAX_API const TopoShape& Value() const noexcept;

private:
	/// @brief Current subshape
	TopoShape shape;

	/// @brief Iterator of subshapes
	std::list<TopoShape>::const_iterator shapesIter;

	/// @brief Iterator of subshapes
	std::list<TopoShape>::const_iterator endIter;

	/// @brief Orientation (cumulative or not)
	OrientationType orientation = OrientationType::Forward;

	/// @brief Location (cumulative or not)
	TopoLocation location;
};
} // namespace AMCAX
