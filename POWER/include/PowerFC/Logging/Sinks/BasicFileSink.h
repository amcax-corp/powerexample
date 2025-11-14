#pragma once

#include <Logging/Sinks/OStreamSink.h>
#include <filesystem>
#include <fstream>

namespace logging {
template<typename Mutex>
class LOGGING_API BasicFileSink : public OStreamSink<Mutex>
{
  public:
    BasicFileSink(std::string const& filepath, bool truncate = false);

    std::filesystem::path const& GetFilePath() const;

  private:
    std::ofstream m_file;
    std::filesystem::path m_filepath;
};

using BasicFileSinkST = BasicFileSink<Detail::NullMutex>;
using BasicFileSinkMT = BasicFileSink<std::mutex>;

}  // namespace logging