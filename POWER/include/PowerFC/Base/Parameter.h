
#ifndef POWERFC_BASE_PRAMETER_H_
#define POWERFC_BASE_PRAMETER_H_
#pragma once
#include <Base/Observer.h>
#include <PFCGlobal.h>
#include <any>
#include <boost/signals2.hpp>
#include <filesystem>
#include <map>
#include <memory>
#include <vector>


namespace base {
class ParameterGroup;
class ParameterManager;

class PFC_BASE_API ParameterGroup : public std::enable_shared_from_this<ParameterGroup>, public base::Subject<std::string_view>
{
  protected:
    std::shared_ptr<ParameterGroup> SharedPointer()
    {
        return std::enable_shared_from_this<ParameterGroup>::shared_from_this();
    }
    std::shared_ptr<ParameterGroup const> SharedPointer() const
    {
        return std::enable_shared_from_this<ParameterGroup>::shared_from_this();
    }

    std::weak_ptr<ParameterGroup> WeakPointer()
    {
        return std::enable_shared_from_this<ParameterGroup>::shared_from_this();
    }
    std::weak_ptr<ParameterGroup const> WeakPointer() const
    {
        return std::enable_shared_from_this<ParameterGroup>::shared_from_this();
    }

  public:
    void CopyTo(ParameterGroup*);
    void InsertTo(ParameterGroup*);
    void ExportTo(std::filesystem::path);
    void ImportFrom(std::filesystem::path);
    //从文件中加载并插入到当前group，会重写重复的项目
    void Insert(std::filesystem::path);

    //根据名字获取参数节点
    ParameterGroup* GetGroup(std::string const& name);

    //获取所有的子参数节点
    std::vector<ParameterGroup*> GetGroups();

    bool HasParameter(std::string_view name) const;

    std::vector<std::pair<std::string, std::string>> GetNamedParameterList() const;

    //判断是否包含某个参数节点
    bool HasGroup(std::string const& name) const;

    bool IsEmpty() const;

    //移除某个子节点
    void RemoveGroup(std::string const& name);
    //重命名某个子节点
    void RenameGroup(std::string const& oldName, std::string const& newName);
    //清空所有参数
    void Clear();

    bool GetBool(std::string const& name, bool preset = false) const;
    void SetBool(std::string const& name, bool value);

    //获得所有bool类型的参数，通过filter过滤节点名字
    std::vector<bool> GetBools(std::string const& filter = {}) const;

    //获取所有bool类型的参数和对应的名字，通过filter过滤节点名字
    std::vector<std::pair<std::string, bool>> GetBoolMap(std::string const& filter = {}) const;

    void RemoveBool(std::string const& name);

    int GetInt(std::string const& name, int preset = 0) const;
    void SetInt(std::string const& name, int value);

    //获得所有int类型的参数，通过filter过滤节点名字
    std::vector<int> GetInts(std::string const& filter = {}) const;

    //获取所有int类型的参数和对应的名字，通过filter过滤节点名字
    std::vector<std::pair<std::string, int>> GetIntMap(std::string const& filter = {}) const;

    void RemoveInt(std::string const& name);

    double GetFloat(std::string const& name, double preset = 0.0) const;
    void SetFloat(std::string const& name, double value);

    //获得所有float类型的参数，通过filter过滤节点名字
    std::vector<double> GetFloats(std::string const& filter = {}) const;

    //获取所有float类型的参数和对应的名字，通过filter过滤节点名字
    std::vector<std::pair<std::string, double>> GetFloatMap(std::string const& filter = {}) const;

    void RemoveFloat(std::string const& name);

    void SetString(std::string const& name, std::string_view value);
    std::string GetString(std::string const& name, std::string const& preset = "") const;
    void RemoveString(std::string const& name);
    std::vector<std::string> GetStrings(std::string const& filter = {}) const;
    std::vector<std::pair<std::string, std::string>> GetStringMap(std::string const& filter = {}) const;

    std::string const& GetName() const;

    // 返回当前节点的路径,例如：group1/group2/group3
    std::string GetPath() const;

    //通知所有观察者所有entries的内容，不通知sub-group的内容
    void NotifyAll();

    virtual ~ParameterGroup();

    void Print(std::ostream& os) const;

    ParameterGroup* GetParent() const
    {
        return m_parent;
    }

    ParameterManager* GetManager() const
    {
        return m_manager;
    }

  protected:
    ParameterGroup(std::string const& name = {}, ParameterGroup* parent = nullptr);

    static std::shared_ptr<ParameterGroup> Create(std::string const& name, ParameterGroup* parent);

    ParameterGroup* GetGroupImpl(std::string const& name);

    //判断是否有观察者引用，从而判断是否可以删除，使用引用计数实现
    //如果引用计数>1，则认为有观察者，不能删除
    //如果引用计数=1，则认为没有观察者，可以删除
    //所以在别处使用std::shared_ptr<ParameterGroup>时，要小心，避免破坏了此机制
    //因此ParameterGroup的成员函数都使用ParameterGroup*作为返回类型，不会增加引用计数
    bool ShouldRemove() const;

    std::string m_name;
    std::map<std::string, std::shared_ptr<ParameterGroup>> m_sub_groups;

    ParameterGroup* m_parent = nullptr;
    ParameterManager* m_manager = nullptr;

    struct Impl;
    std::shared_ptr<Impl> m_impl;

    friend ParameterManager;
};

/** The parameter serializer class
 *  This is a helper class to serialize a parameter XML document.
 *  Does loading and saving the DOM document from and to files.
 *  In sub-classes the load and saving of XML documents can be
 *  customized.
 *  @see ParameterManager
 */
class PFC_BASE_API ParameterSerializer
{
  public:
    explicit ParameterSerializer(std::filesystem::path file_path);
    ParameterSerializer(const ParameterSerializer&) = delete;
    ParameterSerializer(ParameterSerializer&&) = delete;
    virtual ~ParameterSerializer();

    virtual void SaveDocument(const ParameterManager&);
    virtual int LoadDocument(ParameterManager&);
    virtual bool LoadOrCreateDocument(ParameterManager&);
    std::filesystem::path const& GetFilePath() const
    {
        return m_file_path;
    }

    ParameterSerializer& operator=(const ParameterSerializer&) = delete;
    ParameterSerializer& operator=(ParameterSerializer&&) = delete;

  private:
    std::filesystem::path m_file_path;
};

/**
 * @brief 此类是ParameterGroup的根类，管理所有的参数
 * 需要注意的是, 必须创建Document，才能够正确创建ParameterGroup，
 * 创建Document可以通过CreateDocument或者LoadDocument或者LoadOrCreateDocument
 *  
 */
class PFC_BASE_API ParameterManager : public ParameterGroup
{
  protected:
    ParameterManager();

  public:
    ~ParameterManager();

    static std::shared_ptr<ParameterManager> Create();

    boost::signals2::signal<void(ParameterGroup*, std::string_view /*name*/, std::any /*value*/)> SignalParameterChanged;

    int LoadDocument(std::filesystem::path);
    /**
     * @brief 载入或者创建
     * 
     * @return true 表示载入
     * @return false 表示创建
     */
    bool LoadOrCreateDocument(std::filesystem::path);

    void SaveDocument(std::filesystem::path) const;

    void CreateDocument();

    void CheckDocument();

    //! @brief 通过serializer载入
    int LoadDocument();

    //! @brief 通过serializer载入或者创建
    bool LoadOrCreateDocument();

    //! @brief 通过serializer保存
    void SaveDocument() const;

    void SetSerializer(std::filesystem::path file_path);
    bool HasSerializer() const;
    const std::filesystem::path& GetSerializeFilePath() const;

    void SetIgnoreSave(bool value);
    bool IgnoreSave() const;

  private:
    int __LoadDocument(std::filesystem::path);

  private:
    struct Proxy;
    std::shared_ptr<Proxy> m_proxy;

    std::unique_ptr<ParameterSerializer> m_serializer;

    bool m_ignore_save;
};
}  // namespace base

#endif