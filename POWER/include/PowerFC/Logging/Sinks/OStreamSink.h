#pragma once
#include <Logging/BaseSink.h>
#include <Logging/Stylizer.h>
#include <iostream>

namespace logging {

template<typename Mutex>
class LOGGING_API OStreamSink : public BaseSink<Mutex>
{
  public:
    explicit OStreamSink(std::ostream& os, bool force_flush = false);

    OStreamSink(const OStreamSink&) = delete;
    OStreamSink& operator=(const OStreamSink&) = delete;

  protected:
    void SinkItImpl(Recorder && recorder) override;

    void FlushImpl() override;

  protected:
    std::ostream& m_ostream;
    bool m_force_flush;
};

using OStreamSinkMT = OStreamSink<std::mutex>;
using OStreamSinkST = OStreamSink<Detail::NullMutex>;

}  // namespace logging
