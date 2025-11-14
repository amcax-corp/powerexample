/**
 * @file Type.h
 * @author 王康 (wkcagd@hotmail.com)
 * @brief 实现类型系统，PFC的大多数类都应该在实例化之前注册到类型系统中。通过类型系统，可以实现
 * 继承关系判断，类比较以及通过类名实例化类对象等。
 * @note 父类必须在子类之前注册到类型系统中。
 * @version 0.1
 * @date 2024-12-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <PFCGlobal.h>
#include <vector>
#include <string_view>

namespace base {

class TypeInfo;

class PFC_BASE_API Type
{
  public:
    //Constructions
    Type() = default;
    Type(Type const&) = default;
    Type(Type&&) = default;
    Type& operator=(Type const&) = default;
    Type& operator=(Type&&) = default;

    ~Type() = default;

    void* CreateInstance() const;

    static void* CreateInstanceByName(std::string_view name);

    using CreateInstanceFunc = void* (*)();

    static Type FromName(std::string_view name);
    static Type FromIndex(unsigned int index);
    std::string_view GetName() const;
    Type GetSuper() const;
    bool IsSubTypeOf(Type const& type) const;
    bool IsSubTypeOf(std::string_view class_name) const;
    bool IsDerivedFrom(Type const& type) const;
    bool IsDerivedFrom(std::string_view class_name) const;
    bool HasSubType(std::string_view sub_class_name) const;

    static void GetAllSubTypesOf(Type const& super_type, std::vector<Type>& types);

    static Type GetSubTypeOf(Type const& parent, std::string_view name);

    static std::size_t GetNumberOfTypes();

    static Type CreateType(const Type& super_type, std::string_view name, CreateInstanceFunc create_instance_func = nullptr);

    unsigned int GetIndex() const
    {
        return index;
    }

    bool IsBad() const
    {
        return index == 0;
    }

    static Type BadType()
    {
        return Type();
    }

    static void ImportModule(std::string_view module_name);

    bool operator==(Type const& other) const
    {
        return index == other.index;
    }
    bool operator!=(Type const& other) const
    {
        return index != other.index;
    }

    bool operator<(Type const& other) const
    {
        return index < other.index;
    }

    bool operator>(Type const& other) const
    {
        return index > other.index;
    }

    bool operator<=(Type const& other) const
    {
        return index <= other.index;
    }
    bool operator>=(Type const& other) const
    {
        return index >= other.index;
    }

    operator bool() const
    {
        return index != 0;
    }

    operator unsigned int() const
    {
        return index;
    }

  private:
    unsigned int index{0};

    Type(unsigned int index)
      : index(index)
    {
    }

    friend class TypeManager;
};

}  // namespace base