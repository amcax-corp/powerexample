#ifndef LOGGING_SYLIZERRAW_H
#define LOGGING_SYLIZERRAW_H
#pragma once
#include <Logging/Stylizer.h>

namespace logging {
class LOGGING_API StylizerRaw : public Stylizer
{
  public:
    StylizerRaw() = default;
    ~StylizerRaw() override = default;

    void Stylize(Recorder&& recorder, std::ostream& dest) override;
    std::unique_ptr<Stylizer> Clone() const override;
};
}  // namespace logging

#endif  // LOGGING_STYLLIZERRAW_H