#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace base {

template<typename TProduct>
class TProducerBase
{
  public:
    using Product = TProduct;

    TProducerBase() = default;
    virtual ~TProducerBase() = default;
    virtual std::unique_ptr<Product> Produce() const
    {
      return std::make_unique<Product>();
    }

    TProducerBase(TProducerBase const&) = delete;
    TProducerBase& operator=(TProducerBase const&) = delete;
    TProducerBase(TProducerBase&&) = delete;
    TProducerBase& operator=(TProducerBase&&) = delete;
};

template<class Derived, typename TProduct, typename Key = std::string>
class TFactoryBase
{
  public:
    using ProducerBase = TProducerBase<TProduct>;
    using Product = typename ProducerBase::Product;

    static Derived& Instance()
    {
        static Derived instance;
        return instance;
    }

    virtual ~TFactoryBase() = default;

    bool CanProduce(Key const& tag) const
    {
        return m_producers.find(tag) != m_producers.end();
    }

    std::vector<Key> GetProducerNames() const
    {
        std::vector<Key> keys;
        for (auto const& [key, _] : m_producers)
        {
            keys.push_back(key);
        }
        return keys;
    }

    //注册一个Producer的生产者，并关联到tag，Producer必须是ProducerBase的派生类
    template<std::derived_from<ProducerBase> Producer>
    struct Register
    {
        Register(Key const& tag)
        {
          std::shared_ptr<ProducerBase> producer = std::make_shared<Producer>();
            Derived::Instance().RegisterInternal(tag, std::move(producer));
        }
    };

  public:
    virtual std::unique_ptr<Product> Produce(Key const& tag) const
    {
        auto it = m_producers.find(tag);
        if (it != m_producers.end())
        {
            return it->second->Produce();
        }
        return nullptr;
    }

  protected:
    TFactoryBase() = default;

  protected:
    bool RegisterInternal(Key const& tag,
                          std::shared_ptr<ProducerBase>&& producer)
    {
        return m_producers.emplace(tag, std::move(producer))
            .second;  // second is true if the insertion succeeded
    }

  protected:
    std::map<Key, std::shared_ptr<ProducerBase>> m_producers;
};

}  // namespace base