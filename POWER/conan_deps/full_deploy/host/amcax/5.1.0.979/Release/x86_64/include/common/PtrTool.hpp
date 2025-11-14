/// @file      PtrTool.hpp
/// @brief     Class used to unify the behavior of pointer and non-pointer values
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

namespace AMCAX
{
/// @brief Class used to unify the behavior of pointer and non-pointer values
class PtrTool
{
public:
	/// @brief Get the pointer from a value
	/// @tparam T The type of value
	/// @param a The value
	/// @return The pointer to the value
	template<typename T>
	static T* GetPtr(T& a) noexcept
	{
		return &a;
	}

	/// @brief Get the pointer from a shared pointer
	/// @tparam T The type of value
	/// @param a The shared pointer
	/// @return The raw pointer
	template<typename T>
	static T* GetPtr(std::shared_ptr<T> a) noexcept
	{
		return a.get();
	}

	/// @brief Get the pointer
	/// @tparam T The type of value
	/// @param a The pointer
	/// @return The pointer
	template<typename T>
	static T* GetPtr(T* a) noexcept
	{
		return a;
	}
};
} // namespace AMCAX
