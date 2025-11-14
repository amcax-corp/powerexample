#ifndef POWERFC_GUI_AUTOSAVER_H
#define POWERFC_GUI_AUTOSAVER_H

#pragma once

#include <QObject>

#include <Base/XMLWriter.h>
#include <boost/signals2.hpp>
#include <map>
#include <set>
#include <string>


namespace app {
class Document;
class DocumentObject;
class Property;
}  // namespace app
namespace gui {
class ViewProvider;

class AutoSaveProperty
{
  public:
    AutoSaveProperty(const app::Document* document);
    ~AutoSaveProperty();
    int timerId;
    std::set<std::string> touched;
    std::filesystem::path dir;
    std::map<std::string, std::string> file_map;

  private:
    void SlotNewObject(const app::DocumentObject&);
    void SlotChangePropertyData(const app::Property&);
    using Connection = boost::signals2::connection;
    Connection document_new;
    Connection document_mod;
};
}  // namespace gui

namespace gui {

class AutoSaver : public QObject
{
    Q_OBJECT

  private:
    static AutoSaver* self;
    AutoSaver(QObject* parent);
    ~AutoSaver() override;

  public:
    static AutoSaver* Instance();
    /*!
     Sets the timeout in milliseconds. A value of 0 means that no timer is used.
     */
    void SetTimeout(int ms);
    /*!
     Enables or disables to create compreesed recovery files.
     */
    void SetCompressed(bool on);

  protected:
    void SlotCreateDocument(const app::Document& document);
    void SlotDeleteDocument(const app::Document& document);
    void timerEvent(QTimerEvent* event) override;
    void StoreDocument(const std::string&, AutoSaveProperty&);

  public Q_SLOTS:
    void RenameFile(QString dir_name, QString file, QString tmp_file);

  private:
    int m_timeout{15*60*1000}; /*时间间隔，ms*/
    bool m_is_compressed{true};
    std::map<std::string, AutoSaveProperty*> m_saver_map;
};

class RecoveryStorage : public base::OFileStorage
{
  public:
  RecoveryStorage(AutoSaveProperty&);
    ~RecoveryStorage() override;

    /*!
     * 此方法可在子类中重新实现，用于控制是否跳过某些对象的写入操作。
     * 默认实现始终返回 true（即默认写入所有对象）。
     */
    bool ShouldWrite(const std::string&, const base::Persistence*) const override;
    void Finalize() override;

  private:
    AutoSaveProperty& saver;
};

}  // namespace gui

#endif  //POWERFC_GUI_AUTOSAVER_H