#pragma once
#ifdef _WIN32

#include <array>
#include <Logging/BaseSink.h>

namespace logging{
    
template<typename Mutex>
class LOGGING_API WinColorSink : public BaseSink<Mutex>
{
    public:
    WinColorSink(void* out_handler);
    ~WinColorSink() override;
    WinColorSink(const WinColorSink&) = delete;
    WinColorSink& operator=(const WinColorSink&) = delete;
    void SetColor(Level level, std::uint16_t color);

    private:
    std::uint16_t SetForegroundColor(std::uint16_t attribs);

    void SinkItImpl(Recorder &&) override;
    void FlushImpl() override;

    void PrintRange(std::string_view formatted, size_t start, size_t end);
    void WriteToFile(std::string_view formatted);

    private:
    void* m_out_handler;
    std::array<std::uint16_t, LevelNames::Count()> m_colors;
};

template<typename Mutex>
class WinStdOutColorSink : public WinColorSink<Mutex>
{
    public:
    explicit WinStdOutColorSink();
};
template<typename Mutex>
class WinStdErrColorSink : public WinColorSink<Mutex>
{
    public:
    explicit WinStdErrColorSink();
};

using WinStdOutColorSinkST = WinStdOutColorSink<Detail::NullMutex>;
using WinStdErrColorSinkST = WinStdErrColorSink<Detail::NullMutex>;
using WinStdOutColorSinkMT = WinStdOutColorSink<std::mutex>;
using WinStdErrColorSinkMT = WinStdErrColorSink<std::mutex>;
}
#endif
