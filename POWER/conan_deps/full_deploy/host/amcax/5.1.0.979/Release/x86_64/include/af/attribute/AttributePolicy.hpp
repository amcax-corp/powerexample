/// @file      AttributePolicy.hpp
/// @brief     The class of AttributePolicy
/// @details   This enum class defines the policy of attributes to resolve the attribute conflict.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once

#include <common/Macros.hpp>
namespace AMCAX {
///@brief The enumeration of attribute policy to resolve attribute conflict
enum class AttributePolicy {
    /// @brief When attribute conflicts occur, the attributes are dropped
    ATTRIBUTE_POLICY_DROP,
    /// @brief When attribute conflicts occur, the attributes from first argument are keeped
    ATTRIBUTE_POLICY_KEEP_ARGUMENT,
    /// @brief When attribute conflicts occur, the attributes from first tool are keeped
    ATTRIBUTE_POLICY_KEEP_TOOL,
};
}