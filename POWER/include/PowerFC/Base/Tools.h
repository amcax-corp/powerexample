#ifndef POWERFC_BASE_TOOL_H_
#define POWERFC_BASE_TOOL_H_
#pragma once
#include <PFCGlobal.h>
#include <string>
#include <vector>

namespace base {

struct PFC_BASE_API Tools
{
    static std::string GetUniqueName(std::string_view, const std::vector<std::string_view>&, int d = 0);

    static std::string AddNumber(const std::string&, unsigned int, int d = 0);

    //将输入字符串中的非数字或大小写都转为'_'，所以中文名会变为_____
    static std::string GetIdentifier(const std::string_view);
    // 处理中文情况
    static std::string GetIdentifierWithChinese(const std::string_view);

    static std::wstring Widen(const std::string& str);

    static std::string Narrow(const std::wstring& str);

    static std::string EscapedUnicodeFromUtf8(std::string_view s);

    static std::string EscapedUnicodeToUtf8(std::string_view s);

    static std::string EscapeEncodeFilename(const std::string& s);

    /**
     * @brief CAD/CAM软件中的字符串编码有关，比如在AutoCAD DXF文件中，会使用类似 \X2\ 来表示 Unicode 字符的十六进制编码。
     * UG导出的step文件中product name会使用类似 \X2\ 来表示 Unicode 字符的十六进制编码。为了正确地显示，需要进行解码。
     * @param input 
     * @return QString 
     */
    static std::string DecodeEncodedUnicode(const std::string& input);
};

template<typename Status, class Object>
class ObjectStatusLocker
{
  public:
    ObjectStatusLocker(Status s, Object* o, bool value = true)
      : status(s)
      , obj(o)
    {
        old_value = obj->TestStatus(status);
        obj->SetStatus(status, value);
    }
    ~ObjectStatusLocker()
    {
        obj->SetStatus(status, old_value);
    }

  private:
    Status status;
    Object* obj;
    bool old_value;
};

class StateLocker
{
  public:
    StateLocker(bool& flag, bool value = true)
      : lock(flag)
    {
        old_value = lock;
        lock = value;
    }  // NOLINT
    ~StateLocker()
    {
        lock = old_value;
    }

  private:
    bool& lock;
    bool old_value;
};

}  // namespace base
#endif