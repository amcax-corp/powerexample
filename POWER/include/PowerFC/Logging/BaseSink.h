#pragma once
#include <Logging/Detail/NullMutex.h>
#include <Logging/ISink.h>
#include <Logging/Stylizer.h>
#include <mutex>

namespace logging {

template<typename Mutex>
class LOGGING_API BaseSink : public ISink
{
  public:
    BaseSink();
    explicit BaseSink(std::unique_ptr<Stylizer> stylizer);
    ~BaseSink() override = default;

    BaseSink(const BaseSink&) = delete;
    BaseSink& operator=(const BaseSink&) = delete;

    BaseSink(BaseSink&&) = delete;
    BaseSink& operator=(BaseSink&&) = delete;

    void SinkIt(Recorder&& recorder) final override;
    void Flush() final override;
    void SetStylizer(std::unique_ptr<Stylizer> stylizer) final override;
    Stylizer* GetStylizer() const final override;

  protected:
    virtual void SinkItImpl(Recorder&& recorder) = 0;
    virtual void FlushImpl() = 0;
    virtual void SetSytlizerImpl(std::unique_ptr<Stylizer> stylizer);

  protected:
    std::unique_ptr<Stylizer> m_stylizer;
    Mutex m_mutex;
};
}  // namespace logging