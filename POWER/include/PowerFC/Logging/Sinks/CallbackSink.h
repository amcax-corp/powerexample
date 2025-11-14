#pragma once
#include <Logging/BaseSink.h>
#include <Logging/Factory.h>
#include <functional>

namespace logging {

template<typename Mutex>
class LOGGING_API CallbackSink final : public BaseSink<Mutex>
{
  public:
    explicit CallbackSink(std::function<void(Recorder const&)> callback)
      : m_callback(callback)
    {
    }

  protected:
    void SinkItImpl(Recorder && recorder) override
    {
        m_callback(recorder);
    }
    void FlushImpl() override {}

  private:
    // void (*callback)(const char* message);
    std::function<void(Recorder const&)> m_callback;
};

using CallbackSinkMT = CallbackSink<std::mutex>;
using CallbackSinkST = CallbackSink<Detail::NullMutex>;

}  // namespace logging
