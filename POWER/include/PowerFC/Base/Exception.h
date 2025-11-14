#ifndef POWERFC_BASE_EXCEPTION_H
#define POWERFC_BASE_EXCEPTION_H
#pragma once

#include <Base/Recorder.h>
#include <cstdint>
#include <string_view>
#include <source_location>

namespace base {

class ExceptionRecorder : public Recorder<ExceptionRecorder>
{
  public:
    using Recorder<ExceptionRecorder>::Recorder;
};

template<typename Derived>
class RecordExtension{

    public:
    Derived& operator+=(ExceptionRecorder const& recorder){
        auto& derived = *static_cast<Derived*>(this);
        derived.Exception::operator+=(recorder);
        return derived;
    }
};

class PFC_BASE_API Exception : public std::exception
{
  public:
  Exception& operator+=(ExceptionRecorder const& recorder);

  public:
    ~Exception() noexcept = default;

    Exception& operator=(const Exception&) = default;
    Exception& operator=(Exception&&) noexcept = default;

    virtual const char* what() const noexcept
    {
        return m_message.c_str();
    }

    //! @brief Report the exception to the user.It includes a mechanism to only
    //! report and exception once
    virtual void Report() const;

    inline void SetMessage(std::string_view message) noexcept;

    inline std::string_view GetMessage() const noexcept;
    inline std::string_view WhichFile() const noexcept;
    inline std::uint32_t WhichLine() const noexcept;
    inline std::string_view WhichFunction() const noexcept;
    inline bool IsTranslatable() const noexcept;
    inline bool IsReported() const noexcept;

    inline void SetTranslatable(bool translatable) noexcept;
    inline void SetReported(bool reported) noexcept;

  public:

    explicit Exception(std::string_view message = {}, std::source_location const& loc = std::source_location::current());

    Exception(const Exception& other) = default;
    Exception(Exception&& other) noexcept = default;

  protected:
    std::string m_message{};
    std::source_location m_location{};
    mutable bool m_reported{false};

    virtual std::string_view GetName() const noexcept{
        return "base::Exception";
    }

    virtual std::string_view GetDescription() const noexcept{
        return "";
    }
};
}  // namespace base




//定义抛出异常的宏，可以记录文件名、行号和函数名
#define PFC_THROW(exception,...)\
throw exception+=base::ExceptionRecorder{__VA_ARGS__}


#define PFC_DEFINE_EXCEPTION(exception, description) \
class PFC_BASE_API exception : public base::Exception, public RecordExtension<exception> \
{ \
public: \
    exception(std::string_view message={}, std::source_location const& loc = std::source_location::current()) : base::Exception(message, loc) {} \
    using RecordExtension<exception>::operator+=; \
    protected:\
    std::string_view GetName() const noexcept override { return #exception; } \
    std::string_view GetDescription() const noexcept override { return description; } \
}

namespace base{
    PFC_DEFINE_EXCEPTION(AbortException, "程序终止");
    PFC_DEFINE_EXCEPTION(AccessViolation, "访问违规内存");
    PFC_DEFINE_EXCEPTION(AttributeError, "XML属性错误");
    PFC_DEFINE_EXCEPTION(BadFormatError, "格式错误");
    PFC_DEFINE_EXCEPTION(BadGraphError, "图错误");
    PFC_DEFINE_EXCEPTION(CADKernelError, "CAD内核错误");
    PFC_DEFINE_EXCEPTION(ExpressionError, "表达式错误");
    PFC_DEFINE_EXCEPTION(FileSystemError, "文件系统错误，比如目录不存在，创建目录出错等");
    PFC_DEFINE_EXCEPTION(FileException, "文件异常");
    PFC_DEFINE_EXCEPTION(ImportError, "导入错误");
    PFC_DEFINE_EXCEPTION(IndexError, "索引错误");
    PFC_DEFINE_EXCEPTION(MemoryException, "内存异常");
    PFC_DEFINE_EXCEPTION(NameError, "名称错误");
    PFC_DEFINE_EXCEPTION(NotImplementedError, "函数未实现");
    PFC_DEFINE_EXCEPTION(OverflowError, "上溢出错误");
    PFC_DEFINE_EXCEPTION(ParserError, "解析出错");
    PFC_DEFINE_EXCEPTION(ProgramInformation, "程序信息");
    PFC_DEFINE_EXCEPTION(RestoreError, "读取文件时出错");
    PFC_DEFINE_EXCEPTION(RuntimeError, "运行时出错");
    PFC_DEFINE_EXCEPTION(TypeError, "类型错误");
    PFC_DEFINE_EXCEPTION(UnderflowError, "下溢出错误");
    PFC_DEFINE_EXCEPTION(UnicodeError, "Unicode错误");
    PFC_DEFINE_EXCEPTION(UnitsMismatchError, "单位不匹配错误");
    PFC_DEFINE_EXCEPTION(UnknownProgramOption, "未知程序选项");
    PFC_DEFINE_EXCEPTION(ValueError, "值错误");
    PFC_DEFINE_EXCEPTION(XMLAttributeError, "XML属性错误");
    PFC_DEFINE_EXCEPTION(XMLBaseException, "XML基本异常");
    PFC_DEFINE_EXCEPTION(XMLParseException, "XML解析异常");
    PFC_DEFINE_EXCEPTION(XMLWriterException, "XML编写器异常");
    PFC_DEFINE_EXCEPTION(ZeroDivisionError, "除零错误");
    PFC_DEFINE_EXCEPTION(StorageException, "存储异常");
    PFC_DEFINE_EXCEPTION(PropertyError, "属性错误");
    PFC_DEFINE_EXCEPTION(AbnormalProgramTermination, "程序异常终止");
    PFC_DEFINE_EXCEPTION(TopoShapeException, "子拓扑错误");
}

#endif