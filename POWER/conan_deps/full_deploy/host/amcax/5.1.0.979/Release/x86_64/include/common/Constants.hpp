/// @file      Constants.hpp
/// @brief     Commonly used mathematical constants
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <type_traits>

/// @brief Namespace of mathematical constants
namespace AMCAX::Constants
{

/// @brief Base of natural logarithm (also known as Napier's constant / Euler's number)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T e_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(2.718281828459045235360287471352662498L);

/// @brief Base of natural logarithm (also known as Napier's constant / Euler's number)
inline constexpr double e = e_v<double>;

/// @brief log2(e)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T log2e_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(1.442695040888963407359924681001892137L);

/// @brief log2(e)
inline constexpr double log2e = log2e_v<double>;

/// @brief log10(e)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T log10e_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.434294481903251827651128918916605082L);

/// @brief log10(e)
inline constexpr double log10e = log10e_v<double>;

/// @brief Mathematical constant Pi, ratio of a circle's circumference to its diameter
/// @tparam T Type of floating point
template<typename T>
inline constexpr T pi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(3.141592653589793238462643383279502884L);

/// @brief Mathematical constant Pi, ratio of a circle's circumference to its diameter
inline constexpr double pi = pi_v<double>;

/// @brief pi/2
/// @tparam T Type of floating point
template<typename T>
inline constexpr T half_pi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(1.570796326794896619231321691639751442L);

/// @brief pi/2
inline constexpr double half_pi = half_pi_v<double>;

/// @brief pi/4
/// @tparam T Type of floating point
template<typename T>
inline constexpr T quarter_pi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.785398163397448309615660845819875721L);

/// @brief pi/4
inline constexpr double quarter_pi = quarter_pi_v<double>;

/// @brief 2pi
/// @tparam T Type of floating point
template<typename T>
inline constexpr T two_pi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(6.283185307179586476925286766559005768L);

/// @brief 2pi
inline constexpr double two_pi = two_pi_v<double>;

/// @brief 1/pi
/// @tparam T Type of floating point
template<typename T>
inline constexpr T inv_pi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.318309886183790671537767526745028724L);

/// @brief 1/pi
inline constexpr double inv_pi = inv_pi_v<double>;

/// @brief 2/pi
/// @tparam T Type of floating point
template<typename T>
inline constexpr T two_inv_pi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.636619772367581343075535053490057448L);

/// @brief 2/pi
inline constexpr double two_inv_pi = two_inv_pi_v<double>;

/// @brief 1/sqrt(pi)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T inv_sqrtpi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.564189583547756286948079451560772586L);

/// @brief 1/sqrt(pi)
inline constexpr double inv_sqrtpi = inv_sqrtpi_v<double>;

/// @brief 2/sqrt(pi)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T two_inv_sqrtpi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(1.128379167095512573896158903121545172L);

/// @brief 2/sqrt(pi)
inline constexpr double two_inv_sqrtpi = two_inv_sqrtpi_v<double>;

/// @brief ln(2)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T ln2_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.693147180559945309417232121458176568L);

/// @brief ln(2)
inline constexpr double ln2 = ln2_v<double>;

/// @brief ln(10)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T ln10_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(2.302585092994045684017991454684364208L);

/// @brief ln(10)
inline constexpr double ln10 = ln10_v<double>;

/// @brief sqrt(2)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T sqrt2_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(1.414213562373095048801688724209698079L);

/// @brief sqrt(2)
inline constexpr double sqrt2 = sqrt2_v<double>;

/// @brief sqrt(2)/2
/// @tparam T Type of floating point
template<typename T>
inline constexpr T half_sqrt2_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.707106781186547524400844362104849039L);

/// @brief sqrt(2)/2
inline constexpr double half_sqrt2 = half_sqrt2_v<double>;

/// @brief 1/sqrt(2), same as half_sqrt2_v
/// @tparam T Type of floating point
template<typename T>
inline constexpr T inv_sqrt2_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.707106781186547524400844362104849039L);

/// @brief 1/sqrt(2), same as half_sqrt2
inline constexpr double inv_sqrt2 = inv_sqrt2_v<double>;

/// @brief sqrt(3)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T sqrt3_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(1.732050807568877293527446341505872367L);

/// @brief sqrt(3)
inline constexpr double sqrt3 = sqrt3_v<double>;

/// @brief 1/sqrt(3)
/// @tparam T Type of floating point
template<typename T>
inline constexpr T inv_sqrt3_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.577350269189625764509148780501957456L);

/// @brief 1/sqrt(3)
inline constexpr double inv_sqrt3 = inv_sqrt3_v<double>;

/// @brief Euler-Mascheroni constant
/// @tparam T Type of floating point
template<typename T>
inline constexpr T egamma_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(0.577215664901532860606512090082402431L);

/// @brief Euler-Mascheroni constant
inline constexpr double egamma = egamma_v<double>;

/// @brief Golden ratio
/// @tparam T Type of floating point
template<typename T>
inline constexpr T phi_v = static_cast<std::enable_if_t<std::is_floating_point_v<T>, T>>(1.618033988749894848204586834365638118L);

/// @brief Golden ratio
inline constexpr double phi = phi_v<double>;

} // namespace AMCAX::Constants
