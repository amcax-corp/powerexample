#pragma once
#include <Logging/BaseSink.h>
#include <array>

namespace logging {

struct ColorCodes
{
    // Formatting codes
    static constexpr std::string_view reset = "\033[m";
    static constexpr std::string_view bold = "\033[1m";
    static constexpr std::string_view dark = "\033[2m";
    static constexpr std::string_view underline = "\033[4m";
    static constexpr std::string_view blink = "\033[5m";
    static constexpr std::string_view reverse = "\033[7m";
    static constexpr std::string_view concealed = "\033[8m";
    static constexpr std::string_view clear_line = "\033[K";

    // Foreground colors
    static constexpr std::string_view black = "\033[30m";
    static constexpr std::string_view red = "\033[31m";
    static constexpr std::string_view green = "\033[32m";
    static constexpr std::string_view yellow = "\033[33m";
    static constexpr std::string_view blue = "\033[34m";
    static constexpr std::string_view magenta = "\033[35m";
    static constexpr std::string_view cyan = "\033[36m";
    static constexpr std::string_view white = "\033[37m";

    // Background colors
    static constexpr std::string_view on_black = "\033[40m";
    static constexpr std::string_view on_red = "\033[41m";
    static constexpr std::string_view on_green = "\033[42m";
    static constexpr std::string_view on_yellow = "\033[43m";
    static constexpr std::string_view on_blue = "\033[44m";
    static constexpr std::string_view on_magenta = "\033[45m";
    static constexpr std::string_view on_cyan = "\033[46m";
    static constexpr std::string_view on_white = "\033[47m";

    // Bold colors
    static constexpr std::string_view yellow_bold = "\033[33m\033[1m";
    static constexpr std::string_view red_bold = "\033[31m\033[1m";
    static constexpr std::string_view bold_on_red = "\033[1m\033[41m";
};

template<typename Mutex>
class LOGGING_API AnsiColorSink : public BaseSink<Mutex>
{
  public:
    AnsiColorSink(FILE* target_file);
    AnsiColorSink(AnsiColorSink const&) = delete;
    AnsiColorSink& operator=(AnsiColorSink const&) = delete;
    AnsiColorSink(AnsiColorSink&&) = delete;
    AnsiColorSink& operator=(AnsiColorSink&&) = delete;
    ~AnsiColorSink() override = default;

    void SetColor(Level level, std::string_view color);

  private:
    void PrintColorCode(std::string_view color_code);
    void PrintRange(std::string_view formatted, size_t start, size_t end);

  protected:
    void SinkItImpl(Recorder && recorder) override;
    void FlushImpl() override;

    FILE* m_target_file;
    std::array<std::string, LevelNames::Count()> m_colors;
};

template<typename Mutex>
class AnsiStdOutColorSink : public AnsiColorSink<Mutex>
{
    public:
    explicit AnsiStdOutColorSink();
};

template<typename Mutex>
class AnsiStdErrColorSink : public AnsiColorSink<Mutex>
{
    public:
    explicit AnsiStdErrColorSink();
};

using AnsiStdOutColorSinkST = AnsiStdOutColorSink<Detail::NullMutex>;
using AnsiStdErrColorSinkST = AnsiStdErrColorSink<Detail::NullMutex>;
using AnsiStdOutColorSinkMT = AnsiStdOutColorSink<std::mutex>;
using AnsiStdErrColorSinkMT = AnsiStdErrColorSink<std::mutex>;
}  // namespace logging