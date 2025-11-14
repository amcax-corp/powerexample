#pragma once

#include <PFCGlobal.h>
#include <filesystem>
#include <functional>
#include <istream>
#include <memory>
#include <optional>
#include <queue>

namespace base {
class PFC_BASE_API IStorage
{
  public:
    std::uint32_t GetVersion() const
    {
        return m_version;
    }

    std::istream& GetNextEntry(std::string const& entry_path);

    std::string PushFileRestoringTask(std::string const& entry_path,
                                      std::function<void(std::istream&,std::uint32_t)>&& reader);

    virtual void Finalize();

  protected:
    virtual std::istream& GetNextEntryImpl(std::string const& entry_path) = 0;

  protected:
    void SetVersion(std::uint32_t version)
    {
        m_version = version;
    }


  protected:
    struct FileRestoringTask
    {
        std::filesystem::path entry_path;
        std::function<void(std::istream&,std::uint32_t)> reader;
    };

    std::uint32_t m_version;  //存储器版本

    std::queue<FileRestoringTask> m_file_restoring_tasks;  //文件保存任务，在Finalize时执行

    std::vector<std::filesystem::path> m_all_entry_paths;  //当前存储器中所有entry的路径
};



//压缩包存储器
class IZipStorageImpl;
class PFC_BASE_API IZipStorage : public IStorage
{
  public:

    IZipStorage(std::filesystem::path const& zip_path);
    ~IZipStorage();

  protected:
    std::istream& GetNextEntryImpl(std::string const& entry_path) override;

private:
    // struct Private;
    std::unique_ptr<IZipStorageImpl> m_p;
};
}  // namespace base