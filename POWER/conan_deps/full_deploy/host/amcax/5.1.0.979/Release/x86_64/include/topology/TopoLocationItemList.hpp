/// @file      TopoLocationItemList.hpp
/// @brief     Internal class of list of item used in location
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class TopoLocationItem;
struct TopoLocationItemListNode;

/// @internal
/// @brief Internal class of list of item used in location
class TopoLocationItemList
{
public:
	constexpr TopoLocationItemList() noexcept = default;

	TopoLocationItemList(const TopoLocationItem& item, const TopoLocationItemList& tail);

	[[nodiscard]] bool operator==(const TopoLocationItemList& other) const noexcept
	{
		return node == other.node;
	}

	[[nodiscard]] bool IsEmpty() const noexcept
	{
		return !node;
	}

	void Clear() noexcept
	{
		node.reset();
	}

	[[nodiscard]] const TopoLocationItem& Value() const noexcept;

	[[nodiscard]] const TopoLocationItemList& Tail() const noexcept;

	void Construct(const TopoLocationItem& item)
	{
		node = TopoLocationItemList(item, *this).node;
	}

	[[nodiscard]] bool More() const noexcept
	{
		return node.operator bool();
	}

	void Next() noexcept
	{
		node = Tail().node;
	}

private:
	std::shared_ptr<TopoLocationItemListNode> node;
};

#endif

} // namespace AMCAX
