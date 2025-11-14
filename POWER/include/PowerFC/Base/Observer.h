

#ifndef BASE_OBSERVER_H
#define BASE_OBSERVER_H

#include <Base/Exception.h>
#include <Logging/Logging.h>
#include <set>

namespace base {

template<class MessageT>
class Subject;

template<class MessageT>
class Observer
{
  public:
    using MessageType = MessageT;

    Observer() {}
    virtual ~Observer() {}

    /**
   * 此方法需要从具体的Observer重新实现，并由被观察的类调用
   */
    virtual void OnChange(Subject<MessageT>& caller, MessageT const& reason) = 0;

    /**
   * 此方法需要从具体的Observer重新实现，并由被观察的类调用
   */
    virtual void OnDestroy(Subject<MessageT>& caller)
    {
        (void)caller;
    }

    /**
   * 此方法可以从具体的观察者重新实现，并返回观察者的名称
   */
    virtual std::string_view GetName(void)
    {
        return "";
    }
};

/** Subject class
 *  继承FCSubject的观察对象将在发生更改时调用其所有观察者。观察者类必须将自己附加到被观察对象上
 */
template<class MessageT>
class Subject
{
  public:
    using ObserverType = Observer<MessageT>;
    using MessageType = MessageT;
    using SubjectType = Subject<MessageT>;

    Subject() {}

    virtual ~Subject() {}

    /** Attach an Observer
   * 将观察者连接到观察者列表，这些观察者在通知时被调用。
   */
    void Attach(Observer<MessageT>* observer)
    {
        if (!m_mutex) m_observer_set.insert(observer);
        else
        {
            m_delayed_actions.push_back([this, observer]() {
                Attach(observer);
            });
        }
    }

    /** Detach an Observer
   * 从观察者列表中去除一个观察者时调用。
   */
    void Detach(Observer<MessageT>* observer)
    {
        if (!m_mutex) m_observer_set.erase(observer);
        else
        {
            m_delayed_actions.push_back([this, observer]() {
                Detach(observer);
            });
        }
    }

    /** 
   * 通知所有观察者向附带的所有观察者发送一条消息。
   */
    void Notify(MessageT const& reason)
    {
        m_mutex = true;
        for (auto& observer : m_observer_set)
        {
            try
            {
                observer->OnChange(*this, reason);  // send OnChange-signal
            }
            catch (base::Exception& e)
            {
                LOGGING_ERROR("Unhandled base::Exception caught when notifying observer.\n"
                              "The error message is: {}\n",
                              e.what());
            }
            catch (std::exception& e)
            {
                LOGGING_ERROR("Unhandled std::Exception caught when notifying observer.\n"
                              "The error message is: {}\n",
                              e.what());
            }
            catch (...)
            {
                LOGGING_ERROR("Unhandled unknown exception caught in when notifying observer.");
            }
        }
        m_mutex = false;

        if (!m_delayed_actions.empty())
        {
            for (const auto& action : m_delayed_actions)
            {
                if (action) action();
            }
            m_delayed_actions.clear();
        }
    }

    /** 
     * 通过名字获得观察员
   */
    ObserverType* GetObserver(std::string const& name)
    {
        auto iter = std::find_if(m_observer_set.begin(), m_observer_set.end(), [name](auto const& observer) {
            return observer->GetName() == name;
        });
        if (iter != m_observer_set.end())
        {
            return *iter;
        }
        return nullptr;
    }

    /** 
     * 清除所有已注册的观察者的列表
   */
    void ClearObserver()
    {
        if (!m_mutex) m_observer_set.clear();
        else
        {
            m_delayed_actions.push_back([this]() {
                ClearObserver();
            });
        }
    }

    bool IsObservedBy(Observer<MessageT>* observer) const
    {
        return m_observer_set.find(observer) != m_observer_set.end();
    }

    bool IsObserved() const
    {
        return !m_observer_set.empty();
    }

  protected:
    bool m_mutex { false };
    std::set<Observer<MessageT>*> m_observer_set;
    std::vector<std::function<void()>> m_delayed_actions;
};

}  //namespace base

#endif  // BASE_OBSERVER_H
