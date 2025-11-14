/// @file      BasicAttribute.hpp
/// @brief     Define the basic attriburte value
/// @details   Define the basic attribute type traits.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/FixedIntAttribute.hpp>
#include <af/attribute/FloatPointAttribute.hpp>
#include <af/attribute/StringAttribute.hpp>

namespace AMCAX {

template<class T>
constexpr bool is_basic_attribute_v = false;

template<>
inline constexpr bool is_basic_attribute_v<Int8Attribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<Int16Attribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<Int32Attribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<Int64Attribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<UInt8Attribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<UInt16Attribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<UInt32Attribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<UInt64Attribute> = true;

template<>
inline constexpr bool is_basic_attribute_v<StringAttribute> = true;

template<>
inline constexpr bool is_basic_attribute_v<FloatAttribute> = true;
template<>
inline constexpr bool is_basic_attribute_v<DoubleAttribute> = true;
}  // namespace AMCAX
