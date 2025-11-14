#ifndef POWERFC_APP_PROPERTY_H_
#define POWERFC_APP_PROPERTY_H_
#pragma once
#include <Base/Persistence.h>
#include <Base/Exception.h>
#include <bitset>
#include <boost/signals2.hpp>
#include <memory>
#include <string>
#include <string_view>
#include <App/PropertyFlags.h>


namespace app {
class PropertyContainer;  //forward declaration
class ObjectIdentifier;   //forward declaration

}  // namespace app

namespace app {



enum class PropertyStatusBit
{
    TOUCHED = 0,    //该状态位表示该属性是否被修改过
    IMMUTABLE = 1,  //该状态位表示该属性是否不能被修改
    READ_ONLY = 2,  //该状态位表示该属性是否只读，用于属性编辑器
    HIDDEN = 3,     //该状态位表示该属性是否隐藏，用于属性编辑器
    TRANSIENT = 4,  //该状态位表示该属性是否是瞬态的，用于ProertyContainer
    MATERIAL_EDIT = 5,
    NO_MATERIAL_LIST_EDIT = 6,
    OUTPUT = 7,
    LOCK_DYNAMIC = 8,
    NO_MODIFY = 9,  //该状态位标识是否禁止从Gui::Document::SetModified()修改该属性
    PARTIAL_TRIGGER = 10,    //该状态位标识是否允许在partial doc中改变
    NO_RECOMPUTE = 11,       //该状态位标识是否禁止属性owner在属性改变时自动重新计算
    SINGLE = 12,             //该状态位标识在保存或载入时采用的浮点精度
    ORDERED = 13,            //用于PropertyLists，表示列表中元素的顺序对于owner是否重要
    EVAL_ON_RESTORE = 14,    //对于表达式属性，该状态位标识是否在载入时进行求值并改变owner
    BUSY = 15,
    CopyOnChange = 16,  // for Link to copy the linked object on change of the property with this flag
    UserEdit = 17,      //cause property editor to create button for user defined editing

    //下面是属性的静态状态位，对应PropertyType，当属性被Add时，这些状态位被设置，并在运行时不能被改变
    //在此处设置静态状态位，目的是保证PropertyContainer::getPropertyType()是O(1)的复杂度
    PROPERTY_STATIC_BEGIN = 21,
    PROPERTY_DYNAMIC = 21,       //标识该属性是动态添加的
    PROPERTY_NO_PERSIST = 22,    //标识该属性的所有信息都不会被保存到文件中，对应PropertyType::NO_PERSIST
    PROPERTY_NO_RECOMPUTE = 23,  //标识该属性不需要重新计算，对应PropertyType::NO_RECOMPUTE
    PROPERTY_READ_ONLY = 24,     //标识该属性是只读的，对应PropertyType::READ_ONLY
    PROPERTY_TRANSIENT = 25,     //标识该属性是瞬态的，对应PropertyType::TRANSIENT
    PROPERTY_HIDDEN = 26,        //标识该属性是隐藏的，对应PropertyType::HIDDEN
    PROPERTY_OUTPUT = 27,        //标识该属性是输出属性，对应PropertyType::OUTPUT
    PROPERTY_STATIC_END = 28,

    USER1 = 28,
    USER2 = 29,
    USER3 = 30,
    USER4 = 31,
};

class PFC_APP_API Property : public base::Persistence
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()

  public:
    Property();
    virtual ~Property();

    virtual std::size_t GetEstimatedSize() const override
    {
        std::string_view name = GetName();
        //务必在所有属性类中重载该方法，以便提升读写效率
        return sizeof(m_owner) + sizeof(PropertyStatusBit);
    }

    //获取属性在其owner中的名字,
    std::string_view GetName() const;

    //判断属性是否已经设置了合理的名字
    bool HasName() const;

    //获取全名,相对于其最顶级的owner
    //例如，如果owner是A，name是B，则返回...A.B
    std::string GetFullName() const;

    //获取与该属性在属性编辑器中对应的组件类型名字
    virtual std::string_view GetEditorTypeName() const
    {
        return "";
    }

    //获取property的特性，可能即是ReadOnly，又是Output
    PropertyFlags GetFlags() const;

    //获取属性所在的group
    std::string_view GetGroupName() const;

    //获取属性所在的document
    std::string_view GetDescription() const;

    //从frame work调用，设置属性的拥有者owner
    void SetOwner(PropertyContainer* owner);

    PropertyContainer* GetOwner() const;

    //判断属性是否是动态添加的，如果owner为空，则抛出异常
    bool IsDynamicProperty() const;

    //判断属性是否是静态添加的，如果owner为空，则抛出异常
    bool IsStaticProperty() const;

    //设置属性的值
    // virtual void SetPathValue(ObjectIdentifier const& path, std::any const& value);

    //获取属性的值
    // virtual std::any GetPathValue(ObjectIdentifier const& path) const;

    //将path转为规范表示
    //TODO: 啥是规范表示
    // virtual app::ObjectIdentifier GetCanonicalPath(app::ObjectIdentifier const& path) const;

    //获取该属性的所有合法的path，用于auto completer
    // virtual void GetPathList(std::vector<app::ObjectIdentifier>& path_list) const;

    /** 状态位接口函数--------------------------------------------------------------------**/
    //@{

    ///设置touched
    void Touch();

    inline bool IsTouched() const
    {
        return m_status_bits.test(static_cast<size_t>(PropertyStatusBit::TOUCHED));
    }

    inline void PurgeTouched()
    {
        m_status_bits.reset(static_cast<size_t>(PropertyStatusBit::TOUCHED));
    }

    inline unsigned long GetStatusValue() const
    {
        return m_status_bits.to_ulong();
    }

    void SetStatusValue(unsigned long status_bits);

    inline bool TestStatus(PropertyStatusBit pos) const
    {
        return m_status_bits.test(static_cast<size_t>(pos));
    }

    void SetStatus(PropertyStatusBit pos, bool on);

    void SetReadOnly(bool on);

    inline bool IsReadOnly() const
    {
        return TestStatus(PropertyStatusBit::READ_ONLY);
    }

    inline bool IsDynamic() const{
        return TestStatus(PropertyStatusBit::PROPERTY_DYNAMIC);
    }

    //设置单精度浮点数或者双精度浮点数
    void SetSinglePrecision(bool single)
    {
        SetStatus(PropertyStatusBit::SINGLE, single);
    }

    inline bool IsSinglePrecision() const
    {
        return TestStatus(PropertyStatusBit::SINGLE);
    }
    //@}

    //返回该属性的一个新的拷贝，主要用在Undo/Redo和transactions
    virtual std::unique_ptr<Property> Clone() const = 0;

    //将from的值拷贝到当前属性中，主要用于Undo/Redo和transactions
    virtual void Paste(Property const& from) = 0;

    //Compare
    virtual bool IsSame(Property const& other) const;

    /** 读写相关的函数，用于在读写后做一些定制化处理--------------------------------**/
    //@{
    /**
    * @brief 该方法在Document::AfterRestore()中的开头调用
    * TODO:搞清楚具体用法，参考freecad
    */
    virtual void AfterRestore() {}

    /**
        * @brief 该方法在调用DocumentObject::OnDocumentRestored()前调用
        * 这个方法会在完成对象所有属性的Property::AfterRestore()的调用之后调用，
        * 此时对象的依赖信息被认为准备好了，所以，不像Property::AfterRestore()，
        * 这个方法可以被具有依赖顺序的对象中调用。
        */
    virtual void OnOwnerRestored() {}

    virtual void BeforeSave() const {}

    //@}

    /**
     * @brief Return a unique ID for the property
     *
     * The ID of a property is generated from a monotonically increasing
     * internal counter. The intention of the ID is to be used as a key for
     * mapping, instead of using the raw pointer. Because, it is possible for
     * the runtime memory allocator to reuse just deleted memory, which will
     * cause hard to debug problem if use pointer as key.
     * 
     * @return int64_t 
     */
    int64_t GetID() const
    {
        return m_id;
    }

    virtual void BeforeStore() const {}

  protected:
    std::bitset<32> m_status_bits;

    /// Gets called by all setValue() methods after the value has changed
    virtual void HasSetValue();
    /// Gets called by all setValue() methods before the value has changed
    virtual void AboutToSetValue();

    //当某个子属性已经改变值后调用(Called when a child property has changed value)
    virtual void HasSetChildValue(Property&) {}

    //在改变某个子属性值之前调用(Called before a child property changing value)
    virtual void AboutToSetChildValue(Property&) {}

    /// Verify a path for the current property
    // virtual void VerifyPath(const app::ObjectIdentifier & p) const;

    /// 获取一个适合存储该属性的文件名,正常来说是prefix+full_name+postfix
    std::string GetFileName(std::string const& postfix = {}, std::string const& prefix = {}) const;

    friend class PropertyContainer;
    friend class StaticPropertyTable;
    friend class DynamicPropertyTable;

  private:
    //更新PropetyFlags到StatusBit中
    void SyncFlags(PropertyFlags flags);

    /**
     * @brief 用于安全地删除动态属性对象，调用该接口后
     * p的所有权将转移到PropertyCleaner中，当PropertyCleaner析构时，会自动删除p
     */
    //
    static void DeleteLater(std::unique_ptr<Property> p);

  private:
    PropertyContainer* m_owner;
    std::string_view m_name;
    int64_t m_id;

  public:
    boost::signals2::signal<void(const app::Property&)> signalChanged;
};
}  // namespace app

namespace app {
/**
     * @brief 对于一些属性类，有可能会嵌套调用多次aboutToSetValue/hasSetValue，此时可能需要只在最后一次改变时才调用。
     * 模板类P需要有一个signal_counter成员变量
     */

template<class P>
class AtomicPropertyChangeInterface
{
  protected:
    class AtomicPropertyChange
    {
      public:
        AtomicPropertyChange(P& property, bool mark_change = true)
          : m_property(property)
        {
            m_property.signal_counter++;
            if (mark_change)
            {
                AboutToChange();
            }
        }

        /**
             * @brief 标记该属性为已经改变的
             * 
             */
        void AboutToChange()
        {
            if (!m_property.has_changed)
            {
                m_property.has_changed = true;
                m_property.AboutToSetValue();
            }
        }

        ~AtomicPropertyChange()
        {
            // Signal counter == 1? meaning we are the last one. Invoke
            // hasSetValue() before decrease counter to prevent recursive call
            // triggered by another AtomicPropertyChange created inside
            // hasSetValue(), as it has now been changed to a virtual function.

            if (m_property.signal_counter == 1 && m_property.has_changed)
            {
                // Must make sure to not throw in a destructor
                try
                {
                    m_property.HasSetValue();
                }
                catch (base::Exception const& e)
                {
                    e.Report();
                }
                catch (...)
                {}

                m_property.has_changed = false;
            }
            if (m_property.signal_counter > 0)
            {
                m_property.signal_counter--;
            }
        }

        /** Check and invoke property's hasSetValue()
            *
            * Check if this is the last instance and the property has been marked
            * as changed. If so, invoke property's hasSetValue().
            */
        // Destructor cannot throw. So we provide this function to allow error
        // propagation.
        void TryInvoke()
        {
            if (m_property.signal_counter == 1 && m_property.has_changed)
            {
                m_property.HasSetValue();
                if (m_property.signal_counter > 0)
                {
                    m_property.signal_counter--;
                }
                m_property.has_changed = false;
            }
        }

      private:
        P& m_property;
    };

  protected:
    AtomicPropertyChangeInterface() {}

  protected:
    int signal_counter{0};
    bool has_changed{false};
};
}  // namespace app

#if 1

#include <set>

namespace app {

class PropertyListsBase
{
  public:
    virtual void Resize(size_t new_size) = 0;
    virtual size_t GetSize() const = 0;

    virtual size_t GetCount() const{
        return GetSize();
    }

    std::set<size_t> const& GetTouchList() const
    {
        return m_touch_list;
    }

    void ClearTouchList()
    {
        m_touch_list.clear();
    }

  protected:
    std::set<size_t> m_touch_list;
};

class PFC_APP_API PropertyLists : public Property, public PropertyListsBase
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE()
  public:
    // if the order of the elements in the list relevant?
    // if yes, certain operations, like restoring must make sure that the
    // order is kept despite errors.
    inline void SetOrderRelevant(bool on)
    {
        Property::SetStatus(PropertyStatusBit::ORDERED, on);
    }
    inline bool IsOrderRelevant() const
    {
        return Property::TestStatus(PropertyStatusBit::ORDERED);
    }
};

template<class T, class ListT = std::vector<T>, class ParentT = PropertyLists>
class PropertyListsT: public ParentT, public AtomicPropertyChangeInterface<PropertyListsT<T, ListT, ParentT>>
{
    public:
    using const_reference = typename ListT::const_reference;
    using list_type = ListT;
    using parent_type = ParentT;
    using atomic_change_type = typename AtomicPropertyChangeInterface<PropertyListsT<T, ListT, ParentT>>::AtomicPropertyChange;

    friend atomic_change_type;

    virtual void Resize(size_t new_size, const_reference preset)
    {
        m_elements.resize(new_size, preset);
    }

    virtual void Resize(size_t new_size) override
    {
        m_elements.resize(new_size);
    }

    virtual size_t GetSize() const override
    {
        return m_elements.size();
    }

    void SetValue(const_reference value){
        SetValues(list_type{value});
    }

    void SetElement(const list_type& new_elements = {})
    {
        SetValues(new_elements);
    }

    virtual void SetValues(const list_type& new_elements = {})
    {
        atomic_change_type change_guard(*this);
        this->m_elements = new_elements;
        this->m_touch_list.clear();
        change_guard.TryInvoke();
    }
    
    list_type const& GetValues() const
    {
        return m_elements;
    }

    const_reference operator[](size_t index) const
    {
        return m_elements[index];
    }

    virtual void SetOneValue(size_t index, const_reference value)
    {
        size_t size = GetSize();
        if (index > size) {
            PFC_THROW(base::RuntimeError("Index out of range"));
        }
        atomic_change_type change_guard(*this);
        if (index == size) {
            Resize(size+1, value);
        }else{
            m_elements[index] = value;
        }
        this->m_touch_list.insert(index);
        change_guard.TryInvoke();
    }

    protected:
    ListT m_elements;
};



}  // namespace app
#endif

#endif