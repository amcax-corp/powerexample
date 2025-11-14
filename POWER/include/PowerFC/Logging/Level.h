#pragma once
#include <string_view>
#include <algorithm>
#include <Logging/Common.h>

namespace logging {
    //此处没有使用enum class是因为ERROR为windows um.h中定义的宏，ERROR会被宏展开为0，导致编译错误，因此命名中加入前缀LEVEL_。
enum Level : int
{
    LEVEL_TRACE = 0,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_CRITICAL,
    LEVEL_OFF,
    NUM_LEVELS
};

#define LOGGING_LEVEL_NAME_TRACE std::string_view("Trace", 5)
#define LOGGING_LEVEL_NAME_DEBUG std::string_view("Debug", 5)
#define LOGGING_LEVEL_NAME_INFO std::string_view("Info", 4)
#define LOGGING_LEVEL_NAME_WARN std::string_view("Warn", 4)
#define LOGGING_LEVEL_NAME_ERROR std::string_view("Error", 5)
#define LOGGING_LEVEL_NAME_CRITICAL std::string_view("Critical", 8)
#define LOGGING_LEVEL_NAME_OFF std::string_view("Off", 3)

class LOGGING_API LevelNames
{
    static constexpr auto names = {
        LOGGING_LEVEL_NAME_TRACE,
        LOGGING_LEVEL_NAME_DEBUG,
        LOGGING_LEVEL_NAME_INFO,
        LOGGING_LEVEL_NAME_WARN,
        LOGGING_LEVEL_NAME_ERROR,
        LOGGING_LEVEL_NAME_CRITICAL,
        LOGGING_LEVEL_NAME_OFF};

  public:
    static auto GetName(Level level)
    {
        return *(names.begin() + static_cast<int>(level));
    }

    static auto GetLevel(std::string_view name)
    {
        auto it = std::find_if(names.begin(), names.end(), [&](auto n) {
            return n == name;
        });
        return static_cast<Level>(std::distance(names.begin(), it));
    }

    static constexpr auto Count(){
        return static_cast<int>(Level::NUM_LEVELS);
    }
};

}  // namespace logging