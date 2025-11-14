/// @file      AttributeTool.hpp
/// @brief     The class of AttributeTool
/// @details   This class defines the operations to manipulate attributes.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include "af/attribute/DynamicAttribute.hpp"
#include <af/attribute/Attribute.hpp>
#include <af//attribute/StringAttribute.hpp>
#include <af/attribute/FixedIntAttribute.hpp>
#include <af/attribute/FloatPointAttribute.hpp>
#include <af/attribute/ColorAttribute.hpp>
#include <af/label/SignalType.hpp>
#include <common/Macros.hpp>
#include <memory>

namespace AMCAX {
class Label;
enum class NotifyType;

/// @brief The class of AttributeTool
/// @details The class of AttributeTool is used to provide some static functions to set attributes
class AttributeTool {
#ifndef DOXYGEN_SKIP
    friend class WithAttrBase;
    friend class Label;
#endif  // DOXYGEN_SKIP

public:
    /// @brief Make an attribute with the given id and arguments
    /// @tparam _Attr The type of the attribute
    /// @tparam Args The type of the arguments
    /// @param id The id of the attribute
    /// @param args The argument list to initialize the attribute
    /// @return The shared pointer of the attribute
    template<typename _Attr, typename... Args>
    AMCAX_API static std::shared_ptr<Attribute> MakeAttribute(const std::string& id, Args&&... args)
    {
        return std::make_shared<_Attr>(id, std::forward<Args>(args)...);
    }
    
private:
    /// @brief Update the attribute value
    template<typename _Attr>
    AMCAX_API static void UpdateAttribute(Attribute& targetAttr, Attribute& srcAttr)
    {
        auto value = srcAttr.GetValue<_Attr>();
        targetAttr.SetValue<_Attr>(value);
    }

    /// @brief Find an attribute on the label with the given guid
    AMCAX_API static std::shared_ptr<Attribute> FindAttribute(const Label& label, const std::string& guid);

    /// @brief Add an attribute to the label
    /// @param label The label to add the attribute
    /// @param attr The attribute to add
    /// @param notifyType The notify type
    AMCAX_API static void AddAttrToLabel(Label& label, std::shared_ptr<Attribute> attr, NotifyType notifyType);

    
    static AMCAX_API bool UpdateAttribute(Label& label, std::shared_ptr<Attribute> sourceAttribute);

    /// @brief Delete an attribute from the label with the same guid of guid
    /// @param guid The id of the attribute to delete
    AMCAX_API static void DelAttrOnLabel(Label& label, const std::string& guid);

    /// @brief Update the attribute value
    /// @details If the attribute is existing then its value will be updated
    /// @param targetLabel The label to update attribute
    /// @param target The target attribute
    /// @param source The source attribute
    template<typename T>
    static bool UpdateAttribute(std::shared_ptr<Attribute>& target, std::shared_ptr<Attribute>& source) {
        auto targetVal = target->GetValue<T>();
        auto sourceVal = source->GetValue<T>();
        if (targetVal != sourceVal) {
            target->SetValue<T>(sourceVal);
            return true;
        }
        return false;
    }
};
}