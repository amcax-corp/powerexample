/// @file      TypeTraits.hpp
/// @brief     Convenient helper class of type traits
/// @details   Utility classes and functions of type traits for internal use
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <type_traits>
#include <typeinfo>
#include <utility>

#ifndef DOXYGEN_SKIP

namespace AMCAX
{
/// @brief Helper class of type traits
/// @tparam ...Ts Types
template<typename... Ts>
struct are_convertible_to;

/// @brief Arbitrary number of types convertibility with recursive definition
/// @tparam To Target type
/// @tparam From The first source type
/// @tparam ...Froms Other source types
template<typename To, typename From, typename... Froms>
struct are_convertible_to<To, From, Froms...>
{
	/// @brief Value of recursive convertibility
	static constexpr bool value = std::is_convertible<From, To>::value && are_convertible_to<To, Froms...>::value;
};

/// @brief Two types convertibility using std::is_convertible
/// @tparam To Target type
/// @tparam From Source type
template<typename To, typename From>
struct are_convertible_to<To, From> : public std::is_convertible<From, To>
{
};

/// @brief Only one type is false
/// @tparam T Type
template<typename T>
struct are_convertible_to<T> : public std::false_type
{
};

/// @brief Convenient variable for multiple type convertibility
template<typename... Ts>
constexpr bool are_convertible_v = are_convertible_to<Ts...>::value;

/// @brief Check if a type is the instance of another type
template<typename, template<typename, typename...> class>
struct is_instance : public std::false_type
{
};

/// @brief Check if a type is the instance of another type
template<typename... Ts, template<typename, typename...> class U>
struct is_instance<U<Ts...>, U> : public std::true_type
{
};

/// @brief Reimplementation of std::swap for arithmatic type
/// @tparam T Type of element
/// @param left Left element
/// @param right Right element
template<typename T>
constexpr void swap_c(T& left, T& right) noexcept
{
	static_assert(std::is_arithmetic_v<T>);
	T tmp = std::move(left);
	left = std::move(right);
	right = std::move(tmp);
}
} // namespace AMCAX

// C++ 20 features
#ifndef __cpp_lib_remove_cvref
#define __cpp_lib_remove_cvref 201711L
namespace std
{
template<typename T>
struct remove_cvref
{
	using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;
} // namespace std
#endif

// C++ 23 features
#ifndef __cpp_lib_to_underlying
#define __cpp_lib_to_underlying 202102L
namespace std
{
template<class T>
[[nodiscard]] constexpr underlying_type_t<T> to_underlying(T v) noexcept
{
	return static_cast<underlying_type_t<T>>(v);
}
} // namespace std
#endif

#endif
