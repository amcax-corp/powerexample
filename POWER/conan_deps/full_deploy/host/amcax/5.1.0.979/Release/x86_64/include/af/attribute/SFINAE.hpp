/// @file      SFINAE.hpp
/// @brief     This file contains the SFINAE (Substitution Failure Is Not An Error) trait classes for attribute types.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/AttributeMeta.hpp>
#include <af/attribute/AttributePolicy.hpp>

namespace AMCAX {

/// @brief The trait class for attribute types.
/// @tparam T The input traited type
template<class T>
struct attribute_trait {
    constexpr static AttributeMeta default_meta{MetaSet::NotDefined};
    using value_type = typename T::value_type;
};

/// @brief The trait class for attribute policy types.
/// @tparam T The input traited type
template<typename T>
struct attribute_policy_trait {
    constexpr static AttributePolicy policy = T::policy;
};

}  // namespace AMCAX
