#pragma once
#include <atomic>
#include <Logging/Common.h>
#include <Logging/Stylizer.h>
#include <Logging/Recorder.h>

namespace logging {
class LOGGING_API ISink
{
  public:
    virtual ~ISink() = default;
    virtual void SinkIt(Recorder && recorder) = 0;
    virtual void Flush() = 0;
    virtual void SetStylizer(std::unique_ptr<Stylizer> stylizer) = 0;
    virtual Stylizer* GetStylizer() const = 0;

    void SetLevel(logging::Level level);
    logging::Level GetLevel() const;
    bool ShouldSink(Level recorder_level) const;

  protected:
    std::atomic<Level> m_level{LEVEL_TRACE};
};
}  // namespace logging