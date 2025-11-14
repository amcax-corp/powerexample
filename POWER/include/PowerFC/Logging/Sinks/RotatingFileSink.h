#pragma once
#include <Logging/Sinks/OStreamSink.h>
#include <filesystem>
#include <fstream>

namespace logging {
template<typename Mutex>
class LOGGING_API RotatingFileSink : public OStreamSink<Mutex>
{
  public:
    RotatingFileSink(std::string const& base_filepath,
                     std::size_t max_file_size,
                     std::size_t max_file_count,
                     bool rotate_on_open = false);

    std::filesystem::path const& GetBaseFilePath() const;

  protected:
    void SinkItImpl(Recorder&& recorder) override;
    void FlushImpl() override;

  private:
    //rotate files:
    //log.txt->log.1.txt->log.2.txt->log.3.txt->delete
    void Rotate();

    static std::filesystem::path CalcFilename(std::filesystem::path& filename,
                                              std::size_t index);

  private:
    std::filesystem::path m_base_filepath;
    std::size_t m_max_file_size;
    std::size_t m_max_file_count;
    std::size_t m_current_size;
    std::ofstream m_file;
};

using RotatingFileSinkMT = RotatingFileSink<std::mutex>;
using RotatingFileSinkST = RotatingFileSink<Detail::NullMutex>;
}  // namespace logging
