#ifndef PFC_APP_MAPPEDNAME_H_
#define PFC_APP_MAPPEDNAME_H_
#pragma once

#include <App/ElementNaming.h>
#include <App/IndexedName.h>
#include <QByteArray>
#include <QHash>


namespace data {

class PFC_APP_API MappedName
{
  public:  //构造函数
    explicit MappedName(std::string_view name)
      : m_is_raw(false)
    {
        if (!name.empty())
        {
            if (name.starts_with(ELEMENT_MAP_PREFIX))
            {
                name = name.substr(ELEMENT_MAP_PREFIX.size());
            }
            m_data = QByteArray(name.data(), name.size());
        }
    }

    explicit MappedName(const IndexedName& element)
      : m_data(QByteArray::fromRawData(element.GetType().data(),
                                       static_cast<int>(element.GetType().size())))
      , m_is_raw(true)
    {
        if (element.GetIndex() > 0)
        {
            m_data += QByteArray::number(element.GetIndex());
            this->m_is_raw = false;
        }
    }

    MappedName()
      : m_is_raw(false)
    {}

    MappedName(const MappedName& other) = default;
    MappedName(MappedName&& other) noexcept
      : m_data(std::move(other.m_data))
      , m_postfix(std::move(other.m_postfix))
      , m_is_raw(other.m_is_raw)
    {}

    MappedName(const MappedName& other, int start, int size = -1)
      : m_is_raw(false)
    {
        Append(other, start, size);
    }

    ~MappedName() = default;

  public:
    /**
     * @brief 将当前对象和其他对象视为连续的字节数组，将其他对象的数据追加到当前对象。
     * 如果当前对象为空，则从start开始共享其他对象的data。
     * 如果当前对象不为空，则将所有数据追加到后缀(postfix)中。
     * 如果复制操作跨越了其他对象data和postfix的边界：
     * 1. 若当前对象原本为空，则m_data止于其他对象data结束处，剩余部分放入后缀
     * 2. 否则，复制操作将无视其他对象数据和后缀的区分，连续进行
     * @param other 提供数据的MappedName对象。
     * @param start 复制起始字节位置（必须为正整数且小于other对象数据+后缀的总长度）
     * @param size 要复制的字节数（考虑start后，不能超出other对象数据存储的末尾）
     */
    void Append(const MappedName& other, int start = 0, int size = -1);

    /**
     * @brief 追加数据，如果m_data为空，则直接追加，否则追加到m_postfix
     * 
     * @param data 
     */
    void Append(std::string_view data)
    {
        if (!data.empty())
        {
            if (IsEmpty())
            {
                m_data.append(data.data(), data.size());
            }
            else
            {
                m_postfix.append(data.data(), data.size());
            }
        }
    }

  public:
    static MappedName FromRawData(const MappedName& other, int start, int size = -1);

    int Size() const
    {
        return m_data.size() + m_postfix.size();
    }

    bool IsEmpty() const
    {
        return m_data.isEmpty() && m_postfix.isEmpty();
    }

    bool IsRaw() const
    {
        return m_is_raw;
    }

    /**
   * @brief 如果当前数据是共享的，则创建并返回一个非共享的副本。
   * 如果已经是非共享的，则不会创建新副本，而是返回一个与当前实例共享数据的新实例。
   * @return MappedName 
   */
    MappedName Clone() const
    {
        if (!IsRaw())
        {
            return *this;
        }
        MappedName cloned;
        cloned.m_data.append(m_data.constData(), m_data.size());
        cloned.m_postfix = m_postfix;
        return cloned;
    }

    /**
     * @brief 如果offset在data部分，返回data从offset开始到data的结尾，如果offset在postfix部分，返回postfix从offset开始到postfix的结尾
     * 
     * @param offset 
     * @param size 
     * @return std::string_view 
     */
    std::string_view ToConstString(int offset, int& size) const;

    std::string ToString(int start = 0, int size = -1) const;

  public:  //查找

  /**
   * @brief 从data-->postfix进行find，target要么在data中，要么在postfix中，若找到，返回target在MappedName中的位置
   * 
   * @param target 
   * @param start 
   * @return int 
   */
    int Find(std::string_view target, int start = 0) const;

    /**
     * @brief 从postfix-->data进行rfind，若找到则返回target在MappedName中的起始位置，、
     * 否则返回-1，不考虑target跨越了data和postfix的情况,即返回-1
     * 
     * @param target 
     * @param from 
     * @return int 
     */
    int RFind(std::string_view target, int from = -1) const;

    /**
     * @brief 从编码后的元素名称中提取 tag 及其他信息。
     * 
     * @param tag 输出的tag值
     * @param length 用于接收 tag 字段后的长度字段，该字段表示从给定元素名称起始处到前一个哈希元素名称的长度。
     * @param postfix 用于接收从找到的 tag 字段开始的后缀部分。
     * @param type 用于接收元素类型字符。
     * @param negative 是否返回负值的 tag。若禁用，则始终返回正值的 tag。负值 tag 有时用于元素消歧。
     * @param recursive 是否递归查找最后一个非零的 tag。
     * @return int 返回 tag 字段的结束位置，若未找到则返回 -1
     */
    int FindTagInElementName(long* tag = nullptr, int* length = nullptr, std::string* postfix = nullptr, char* type = nullptr, bool negative = false, bool recursive = true) const;

    std::size_t Hash() const
    {
        return qHash(m_data, qHash(m_postfix));
    }

  private:
    QByteArray m_data;     //不可改变的部分
    QByteArray m_postfix;  //可改变的部分
    bool m_is_raw;
};

}  // namespace data
#endif