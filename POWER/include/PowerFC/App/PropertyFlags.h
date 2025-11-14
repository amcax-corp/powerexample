#ifndef POWERFC_APP_PROPERTYTYPE_H
#define POWERFC_APP_PROPERTYTYPE_H
#pragma once
#include <Base/Flags.h>
#include <PFCGlobal.h>
#include <string>

namespace app {

enum class PropertyFlag : unsigned
{
    PROPERTY_NONE = 0,
    PROPERTY_READ_ONLY = 1,      //属性在编辑器中是只读的
    PROPERTY_TRANSIENT = 2,      //该属性的内容不会被保存到文件中，但是保存name，type和status
    PROPERTY_HIDDEN = 4,         //该属性不会出现在属性编辑器中
    PROPERTY_OUTPUT = 8,         //该属性是输出属性，其改变不会touch其owner
    PROPERTY_NO_RECOMPUTE = 16,  //该属性改变不会触发owner的重新计算
    PROPERTY_NO_PERSIST = 32     //该属性的所有信息都不会被保存到文件中，和TRANSIENT有区别
};

struct PFC_APP_API PropertyFlags : public base::Flags<PropertyFlag>
{
  public:
    using base::Flags<PropertyFlag>::Flags;
    std::string ToString() const;
    static PropertyFlags FromString(std::string_view);
};

}  // namespace app

ENABLE_BITMASK_OPERATORS(app::PropertyFlag)

#endif