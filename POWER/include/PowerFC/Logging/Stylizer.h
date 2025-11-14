#pragma once
#include <Logging/Recorder.h>

namespace logging {

class LOGGING_API Stylizer
{
  public:
    virtual ~Stylizer() = default;
    virtual void Stylize(Recorder&& recorder, std::ostream& dest);
    virtual std::unique_ptr<Stylizer> Clone() const;

  protected:
    static std::string_view GetFileName(std::string_view full_name, int depth = 1);
};
}  // namespace logging