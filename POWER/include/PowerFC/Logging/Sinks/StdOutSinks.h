#include <Logging/Sinks/OStreamSink.h>

namespace logging {
template<typename Mutex>
class LOGGING_API StdOutSink : public OStreamSink<Mutex>
{
  public:
    StdOutSink(bool force_flush = false)
      : OStreamSink<Mutex>(std::cout, force_flush)
    {}
};

template<typename Mutex>
class StdErrSink : public OStreamSink<Mutex>
{
  public:
    StdErrSink(bool force_flush = false)
      : OStreamSink<Mutex>(std::cerr, force_flush)
    {}
};

template<typename Mutex>
class StdLogSink : public OStreamSink<Mutex>
{
  public:
    StdLogSink(bool force_flush = false)
      : OStreamSink<Mutex>(std::clog, force_flush)
    {}
};

using StdOutSinkST = StdOutSink<Detail::NullMutex>;
using StdErrSinkST = StdErrSink<Detail::NullMutex>;
using StdLogSinkST = StdLogSink<Detail::NullMutex>;
using StdOutSinkMT = StdOutSink<std::mutex>;
using StdErrSinkMT = StdErrSink<std::mutex>;
using StdLogSinkMT = StdLogSink<std::mutex>;

}  // namespace logging