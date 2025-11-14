/**
 * @file ExtendedTypeTraits.hpp
 * @brief Define extended functions for type_traits in STL.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */

#pragma once

#include <string>
#include <type_traits>
#include <typeinfo>

namespace AMCAX {
namespace Meshing {

/**
 * @brief If the type T is a reference type, provides the member typedef type
 * which is the type referred to by T with its topmost cv-qualifiers removed.
 * Otherwise type is T with its topmost cv-qualifiers removed.
 * @todo remove_cvref is provided since c++20, disable this if c++ standard is
 * updated to c++20.
 */
template <typename T>
struct remove_cvref
{
	typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

/**
 * @brief If the type T is a reference type, provides the member typedef type
 * which is the type referred to by T with its topmost cv-qualifiers removed.
 * Otherwise type is T with its topmost cv-qualifiers removed.
 * @todo remove_cvref is provided since c++20, disable this if c++ standard is
 * updated to c++20.
 */
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

/**
 * @brief check if an type is the instance of another type
 */
template <typename, template <typename, typename...> class>
struct is_instance : public std::false_type
{
};

/**
 * @brief check if an type is the instance of another type
 */
template <typename... Ts, template <typename, typename...> class U>
struct is_instance<U<Ts...>, U> : public std::true_type
{
};

template <typename T>
std::string get_type_name()
{
#ifdef _MSC_VER
	// MSVC'S type_name returns only a friendly name with name() method,
	// to get a unique name use raw_name() method instead
	return typeid(T).raw_name();
#else
	// GCC and clang curently return mangled name as name(), there is no
	// raw_name() method
	return typeid(T).name();
#endif
}

} // namespace Meshing
} // namespace AMCAX