
#pragma once
#include "IPlugin.h"
#include <QDir>
#include <QLibrary>
#include <memory>
#include <PFCGlobal.h>

namespace base {

class PFC_BASE_API IPluginManager
{
  public:
    //实例化函数指针类型，需要在dll中导出该类型的函数，函数名为GetInstantiationName()
    typedef void* (*InstantiateFunction)();

  public:
    IPluginManager() = default;
    virtual ~IPluginManager();

    void LoadAll();
    void UnloadAll();

    QStringList GetAllPluginNames() const;

    /*如果是目录，则遍历目录下所有的动态库，如果是文件，则直接加载
    */
    QFileInfo const& GetPluginPath() const
    {
        return m_plugin_path;
    }

    /*如果是目录，则遍历目录下所有的动态库，如果是文件，则直接加载
    */
    void SetPluginPath(QString path)
    {
        m_plugin_path = QFileInfo(path);
    }

  protected:
    /**该名称是dll中的实例化函数名，导入库时会在dll中查找该符号，需要在dll中导出对应的函数
     */
    virtual QString GetInstantiationName() const
    {
        return "CreateInstance";
    }

  protected:
    bool TryLoad(QString const& library_filepath);
    bool TryLoad(QString const& library_filepath, QString& message);

    template<typename PluginT>
    std::shared_ptr<PluginT> GetPluginInternal(QString const& name) const
    {
        if (m_plugins.contains(name))
        {
            return std::dynamic_pointer_cast<PluginT>(m_plugins[name]);
        }
        return nullptr;
    }

  private:
    QFileInfo m_plugin_path;
    QHash<QString, std::shared_ptr<IPlugin>> m_plugins;
    QHash<QString, QLibrary*> m_libs;
};

}  // namespace base
