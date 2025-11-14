#pragma once
#include <string>
#include <PFCGlobal.h>
#include <QObject>

namespace base {
class PFC_BASE_API IPlugin : public QObject
{
  Q_OBJECT
  public:
    virtual ~IPlugin() = default;

    virtual std::string Version() const = 0;
    virtual std::string PluginName() const = 0;
};
}  // namespace PowerCAM