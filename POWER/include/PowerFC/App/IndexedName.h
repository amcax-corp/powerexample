#ifndef POWERFC_APP_INDEXEDNAME_H
#define POWERFC_APP_INDEXEDNAME_H
#include <string>
#pragma once
#include <PFCGlobal.h>
#include <QByteArray>
#include <QHash>
#include <cassert>
#include <format>
#include <ostream>
#include <string_view>
#include <vector>


namespace data {
/**
 * @brief 实现一个类，用于存储一个名称和一个索引，名称用于表示元素类型，索引用于表示元素编号，比如EDGE1,FACE3等。并实现了比较、增减等操作。
 * m_type采用string_view,避免不必要的拷贝， 其存储在静态集合（定义在Set接口中）中，避免重复创建。
 */
class PFC_APP_API IndexedName
{
  public:
    explicit IndexedName(std::string_view name = {}, int index = 0)
      : m_index(0)
    {
        assert(index >= 0);
        if (name.empty())
        {
            this->m_type = {};
        }
        else
        {
            Set(name);
            if (index > 0)
            {
                m_index = index;
            }
        }
    }

    IndexedName(std::string_view name,
                const std::vector<std::string_view>& allowed_types,
                bool allow_others = true)
      : m_type()
      , m_index(0)
    {
        Set(name, -1, allowed_types, allow_others);
    }

    explicit IndexedName(const QByteArray& data)
      : m_type()
      , m_index(0)
    {
        Set(data.constData(), data.size());
    }

    static IndexedName FromConst(std::string_view name, int index)
    {
        assert(index >= 0);
        IndexedName res;
        res.m_type = name;
        res.m_index = index;
        return res;
    }

    void AppendToStringBuffer(std::string& buffer) const
    {
        // Note! buffer is not cleared on purpose.
        std::size_t offset = buffer.size();
        buffer += m_type;
        if (m_index > 0)
        {
            buffer += std::to_string(m_index);
        }
    }

    std::string toString() const
    {
        if (m_index > 0)
            return std::format("{}{}", m_type, m_index);
        else
            return std::string{m_type};
    }

    friend std::ostream& operator<<(std::ostream& stream, const IndexedName& indexed_name)
    {
        if (indexed_name.m_index > 0)
            std::format_to(std::ostream_iterator<char>(stream), "{}{}", indexed_name.m_type, indexed_name.m_index);
        else
            std::format_to(std::ostream_iterator<char>(stream), "{}", indexed_name.m_type);
        return stream;
    }

    bool operator==(const IndexedName& other) const
    {
        return m_type == other.m_type && m_index == other.m_index;
    }

    IndexedName& operator+=(int offset)
    {
        this->m_index += offset;
        assert(this->m_index >= 0);
        return *this;
    }

    //前置自加
    IndexedName& operator++()
    {
        ++this->m_index;
        return *this;
    }

    //前置自减
    IndexedName& operator--()
    {
        --this->m_index;
        assert(this->m_index >= 0);
        return *this;
    }

    bool operator!=(const IndexedName& other) const
    {
        return !(this->operator==(other));
    }

    int Compare(const IndexedName& other) const
    {
        auto i = m_type.compare(other.m_type);
        if (i != 0)
        {
            return i < 0 ? -1 : 1;
        }
        else
        {
            return m_index < other.m_index ? -1 : 1;
        }
    }

    bool operator<(const IndexedName& other) const
    {
        if (m_type < other.m_type)
        {
            return true;
        }
        else if (m_type > other.m_type)
        {
            return false;
        }
        else
        {
            return m_index < other.m_index;
        }
    }

    char operator[](int index) const
    {
        assert(index > 0);
        assert(index < m_type.size());
        return m_type[index];
    }

    std::string_view GetType() const
    {
        return m_type;
    }

    int GetIndex() const
    {
        return m_index;
    }

    void SetIndex(int index)
    {
        assert(index > 0);
        m_index = index;
    }

    bool IsNull() const
    {
        return m_type.empty();
    }
    explicit operator bool() const
    {
        return !IsNull();
    }

  protected:
    /**
 * 应用 IndexedName 的命名规则，存储新名称或引用现有名称。
 * 名称可来自预定义列表、动态缓存或用户输入，并自动校验合法性。
 * 
 * @param name 新名称字符串（无需持久化，内部可能拷贝）
 * @param length 名称长度（若为-1则自动计算）
 * @param allowed_names 预定义的合法名称集合（必须永久有效）
 * @param allow_others 是否允许非预定义名称（默认允许并动态缓存）
 */
    void Set(std::string_view name, int length = -1, const std::vector<std::string_view>& allowed_names = {}, bool allow_others = true);

  private:
    std::string_view m_type;
    int m_index;
};

}  // namespace data

namespace data {

//基于QByteArray实现一个ByteArray类，区别在于使用左值引用赋值时，会进行拷贝
struct ByteArray
{
    explicit ByteArray(QByteArray a)
      : bytes(std::move(a))
    {}

    ByteArray(const ByteArray& other) = default;
    ByteArray& operator=(const ByteArray& other)
    {
        bytes.clear();
        bytes.append(other.bytes.constData(), other.bytes.size());
        return *this;
    }

    ByteArray(ByteArray&& other) noexcept
      : bytes(std::move(other.bytes))
    {}

    ByteArray& operator=(ByteArray&& other)
    {
        bytes = std::move(other.bytes);
        return *this;
    }

    bool operator==(const ByteArray& other) const
    {
        return bytes == other.bytes;
    }

    void EnsureUnshared() const
    {
        QByteArray cloned;
        cloned.append(bytes.constData(), bytes.size());
        bytes = cloned;
    }

    mutable QByteArray bytes;
};

struct ByteArrayHasher
{
    std::size_t operator()(const ByteArray& bytes) const
    {
        return qHash(bytes.bytes);
    }

    std::size_t operator()(const QByteArray& bytes) const
    {
        return qHash(bytes);
    }
};

}  // namespace data

#endif