#pragma once
#include <Base/MacroTools.h>
#include <Base/Type.h>
#include <PFCGlobal.h>
#include <memory>

namespace base {

class PFC_BASE_API BaseClass
{
  public:
    //获取本类的类型名称
    static base::Type GetClassType();

    //!@brief 获取多态子类的类型名
    virtual std::string_view GetInstanceTypeName() const;

    //!@brief 获取多态子类的类型
    virtual base::Type GetInstanceType() const;

    //!@brief 获取多态子类的类型
    virtual Type GetClassTypePolymorphic() const;

    //!@brief 获取多态子类的类型名
    virtual std::string_view GetClassNamePolymorphic() const;

    //实例化函数，默认返回nullptr
    static void* Create();

    bool IsDerivedFrom(std::string_view class_name) const;

    bool IsDerivedFrom(Type type) const;

    template<std::derived_from<base::BaseClass> T>
    bool IsDerivedFrom() const
    {
      return IsDerivedFrom(T::GetClassType());
    }

    template<typename T>
    T* SafeDownCast()
    {
        return GetClassTypePolymorphic().IsSubTypeOf(T::GetClassType()) ? static_cast<T*>(this) : nullptr;
    }

    template<typename T>
    const T* SafeDownCast() const
    {
        return GetClassTypePolymorphic().IsSubTypeOf(T::GetClassType()) ? static_cast<const T*>(this) : nullptr;
    }

  public:
    BaseClass() = default;
    virtual ~BaseClass() = default;
    BaseClass(BaseClass const&) = default;
    BaseClass& operator=(BaseClass const&) = default;
    BaseClass(BaseClass&&) = default;
    BaseClass& operator=(BaseClass&&) = default;

  protected:
    static base::Type RegisterType(std::string_view class_name,
                                   const Type super_type,
                                   base::Type::CreateInstanceFunc create_instance_func);
};

template<typename T>
T* PFCObjectCast(BaseClass* obj)
{
    return obj ? obj->SafeDownCast<T>() : nullptr;
}

template<typename T>
const T* PFCObjectCast(const BaseClass* obj)
{
    return obj ? obj->SafeDownCast<T>() : nullptr;
}

template<typename T>
std::unique_ptr<T> PFCObjectCast(std::unique_ptr<BaseClass>&& obj)
{
    return std::unique_ptr<T>(PFCObjectCast<T>(obj.release()));
}

}  // namespace base

using base::PFCObjectCast;

//宏定义

#define PFC_TYPESYSTEM_DECL()                           \
  public:                                               \
    static base::Type GetClassType();                   \
    virtual base::Type GetClassTypePolymorphic() const; \
    static void* Create();                              \
                                                        \
  private:                                              \
    // static const bool s_is_registed;

#define PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()                      \
  public:                                                        \
    static base::Type GetClassType();                            \
    virtual base::Type GetClassTypePolymorphic() const override; \
    static void* Create();                                       \
                                                                 \
  private:                                                       \
    // static const bool s_is_registed;

#define PFC_TYPESYSTEM_IMPL(_class_, _super_class_)                                                           \
    static const bool UNIQUE_VAR(s_is_registed) = !_class_::GetClassType().IsBad();                           \
    base::Type _class_::GetClassType()                                                                        \
    {                                                                                                         \
        static_assert(sizeof(_class_), "Class is not complete");                                          \
                                                                                                              \
        constexpr const char* sClass = #_class_;                                                              \
        constexpr std::string_view vClass{sClass};                                                            \
        static_assert(!vClass.empty(), "类名不能为空");                                                       \
        static_assert(std::is_base_of<base::BaseClass, _class_>::value,                                        \
                      "类必须继承自 app::BaseClass");                                                         \
                                                                                                              \
        constexpr bool isSubClass = std::is_base_of<_super_class_, _class_>::value &&           \
                                            !std::is_same<_super_class_, _class_>::value;               \
        static_assert(isSubClass, #_class_ "必须继承自" #_super_class_);\
        if constexpr (isSubClass)                                                                     \
        {                                                                                                     \
            constexpr auto pos = vClass.find("::");                                                           \
            static_assert(pos != std::string_view::npos, "类名必须包含命名空间");                             \
            constexpr auto vNamespace = vClass.substr(0, pos);                                                \
            static_assert(!vNamespace.empty(), "命名空间不能为空");                                           \
        }                                                                                                     \
        static base::Type s_type = RegisterType(#_class_, _super_class_::GetClassType(), &(_class_::Create)); \
        return s_type;                                                                                        \
    }                                                                                                         \
    base::Type _class_::GetClassTypePolymorphic() const                                                       \
    {                                                                                                         \
        return _class_::GetClassType();                                                                       \
    }                                                                                                         \
    void* _class_::Create()                                                                                   \
    {                                                                                                         \
        return new _class_();                                                                                 \
    }

#define PFC_TYPESYSTEM_IMPL_TEMPLATE(_class_, _super_class_)                                                  \
    static const bool UNIQUE_VAR(s_is_registed) = !_class_::GetClassType().IsBad();                           \
    template<>                                                                                                \
    void* _class_::Create()                                                                                   \
    {                                                                                                         \
        return new _class_();                                                                                 \
    }                                                                                                         \
                                                                                                              \
    template<>                                                                                                \
    base::Type _class_::GetClassType()                                                                        \
    {                                                                                                         \
        static base::Type s_type = RegisterType(#_class_, _super_class_::GetClassType(), &(_class_::Create)); \
        return s_type;                                                                                        \
    }                                                                                                         \
    template<>                                                                                                \
    base::Type _class_::GetClassTypePolymorphic() const                                                       \
    {                                                                                                         \
        return _class_::GetClassType();                                                                       \
    }

#define PFC_TYPESYSTEM_IMPL_ABSTRACT(_class_, _super_class_)                                                  \
    static const bool UNIQUE_VAR(s_is_registed) = !_class_::GetClassType().IsBad();                           \
    base::Type _class_::GetClassType()                                                                        \
    {                                                                                                         \
        static base::Type s_type = RegisterType(#_class_, _super_class_::GetClassType(), &(_class_::Create)); \
        return s_type;                                                                                        \
    }                                                                                                         \
    base::Type _class_::GetClassTypePolymorphic() const                                                       \
    {                                                                                                         \
        return _class_::GetClassType();                                                                       \
    }                                                                                                         \
    void* _class_::Create()                                                                                   \
    {                                                                                                         \
        return nullptr;                                                                                       \
    }
