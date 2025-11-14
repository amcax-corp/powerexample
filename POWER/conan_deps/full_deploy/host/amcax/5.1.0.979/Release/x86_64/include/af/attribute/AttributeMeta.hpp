/// @file      AttributeMeta.hpp
/// @brief     The class of AttributeMeta
/// @details   This class defines the attribute meta information.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <cstdint>
namespace AMCAX {
using AttributeMeta = uint32_t;

#ifndef DOXYGEN_SKIP
struct MetaSet {
    constexpr static AttributeMeta NotDefined{0};     //
    constexpr static AttributeMeta Hidden{1u << 31};  // Hidden to outer user
    constexpr static AttributeMeta Dynamic{1u << 0};
    constexpr static AttributeMeta Readonly{1u << 1};         // No writing controller provided
    constexpr static AttributeMeta Persistable{1u << 2};      // Serialization controller provided
    constexpr static AttributeMeta HasDefaultValue{1u << 3};  // Has a default value
    constexpr static AttributeMeta PositionRelative{1u << 4};
    constexpr static AttributeMeta SizeRelative{1u << 5};
    constexpr static AttributeMeta RigidBodyRelative{1u << 6};  // Transforms with rigid body transformation
    constexpr static AttributeMeta MultiValue{1u << 7};
};

/// @brief Check if the attribute is dynamic
/// @param meta The attribute meta information
/// @return True if the attribute is dynamic, otherwise return false
constexpr bool checkHidden(AttributeMeta meta) {
    return (meta & MetaSet::NotDefined) == 0 && (meta & MetaSet::Hidden) != 0;
}

/// @brief Check if the attribute is readonly
/// @param meta The attribute meta information
/// @return True if the attribute is readonly, otherwise return false
constexpr bool checkReadonly(AttributeMeta meta) {
    return (meta & MetaSet::NotDefined) == 0 && (meta & MetaSet::Readonly) != 0;
}

/// @brief Check if the attribute is persistable
/// @param meta The attribute meta information
/// @return True if the attribute is persistable, otherwise return false
constexpr bool checkPersistable(AttributeMeta meta) {
    return (meta & MetaSet::NotDefined) == 0 && (meta & MetaSet::Persistable) != 0;
}

/// @brief Check if the attribute is has default value
/// @param meta The attribute meta information
/// @return True if the attribute is has default value, otherwise return false
constexpr bool checkHasDefaultValue(AttributeMeta meta) {
    return (meta & MetaSet::NotDefined) == 0 && (meta & MetaSet::HasDefaultValue) != 0;
}
/// @brief Check if the attribute is not defined
/// @param meta The attribute meta information
/// @return True if the attribute is not defined, otherwise return false
constexpr bool checkNotDefined(AttributeMeta meta) {
    return (meta & MetaSet::NotDefined) != 0;
}
#endif  // DOXYGEN_SKIP
}