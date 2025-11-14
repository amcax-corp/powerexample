#pragma once
#include <PFCGlobal.h>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>


namespace base {
class Persistence;

class PFC_BASE_API OStorage
{
  public:
    OStorage(std::uint32_t version = 1);
    virtual ~OStorage() = default;

    int GetVersion() const;

    /**
     * @brief 如果entry_name在当前的存储结构中不存在，则创建一个新文件，
     * 并返回一个指向该文件的输出流，否则抛出StorageException
     * 
     * @throw StorageException
     * @param entry_name 
     * @return std::shared_ptr<std::ostream>
     */
    std::ostream& PutNextEntry(std::string const& entry_name);

    /**
     * @brief 提交一个文件保存任务，任务将在存储器调用Finalize时执行
     * 
     * @param filename 
     * @param writer 
     * @return std::string 
     */
    std::string PushFileSavingTask(std::string const& filename,
                                   base::Persistence const* object,
                                   std::function<bool(std::ostream&, std::uint32_t)>&& writer);

    /**
     * @brief 执行所有文件保存任务，清空任务队列
     */
    virtual void Finalize();

    virtual void SetComment(std::string_view comment){};

  protected:
    /**
     * @brief 在存储器中获取一个唯一的文件路径，该文件路径在当前的存储结构中是不存在的
     * 通过添加递增的数字实现，比如path1/a1.txt, path1/a2.txt是已经存在的，path1/a.txt对应的文件名为path1/a3.txt
     * @param filename 
     * @return std::string 
     */
    std::string GetUniqueEntryPath(std::string const& filepath);

    /**
     * @brief 此处要求valid_entry_name在当前的存储结构中是不存在的
     * 该函数为纯虚函数，须要在子类中实现
     * @param valid_entry_name 
     * @return std::shared_ptr<std::ostream> 
     */
    virtual std::ostream& PutNextEntryImpl(std::string const& valid_entry_name) = 0;

  protected:
    struct FileSavingTask
    {
        std::filesystem::path entry_path;
        base::Persistence const* object;
        std::function<bool(std::ostream&, std::uint32_t)> writer;
    };

    std::uint32_t m_version;  //存储器版本

    std::queue<FileSavingTask> m_file_saving_tasks;  //文件保存任务，在Finalize时执行

    std::vector<std::filesystem::path> m_all_entry_paths;  //当前存储器中所有entry的路径
};

/**
 * @brief 文件夹存储器
 * 
 */
class PFC_BASE_API OFileStorage : public OStorage
{
  protected:
    std::filesystem::path m_dir_path;
    std::map<std::filesystem::path, std::shared_ptr<std::ofstream>> m_ofs_map;

  public:
    OFileStorage(std::filesystem::path const& dir_path, std::uint32_t version = 1);

    std::filesystem::path const& GetDir() const
    {
        return m_dir_path;
    }

  protected:
    std::ostream& PutNextEntryImpl(std::string const& valid_entry_name) override;
    virtual bool ShouldWrite(const std::string& name, const base::Persistence* Object) const;
    void Finalize() override;
};

class OZipStorageImpl;
/**
 * @brief 压缩包存储器
 * 
 */
class PFC_BASE_API OZipStorage : public OStorage
{
  public:
    explicit OZipStorage(std::filesystem::path const& zip_path, std::uint32_t version = 1);

    ~OZipStorage() override;

    std::ostream& PutNextEntryImpl(std::string const& valid_entry_name) override;

    void SetComment(std::string_view comment) override;
    void SetLevel(std::uint32_t level);

    void Finalize() override;

    OZipStorage(OZipStorage const&) = delete;
    OZipStorage& operator=(OZipStorage const&) = delete;
    OZipStorage(OZipStorage&&) = delete;
    OZipStorage& operator=(OZipStorage&&) = delete;

    bool IsOpen() const;

  private:
    std::unique_ptr<OZipStorageImpl> m_p;
};

class PFC_BASE_API OStringStorage : public OStorage
{
  public:
    std::string GetContent() const
    {
        return m_oss.str();
    }

  protected:
    std::ostream& PutNextEntryImpl(std::string const& valid_entry_name) override
    {
        return m_oss;
    }

  private:
    std::ostringstream m_oss;
};

}  // namespace base