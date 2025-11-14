#ifndef POWERFC_BASE_INVOKINGTRACER_H_
#define POWERFC_BASE_INVOKINGTRACER_H_
#pragma once
#include <string_view>
#include <sstream>
#include <format>
#include <Base/MacroTools.h>
#include <PFCGlobal.h>

namespace base {

class PFC_BASE_API InvokingTracer
{
  // std::shared_ptr<std::stringstream> stream;
  std::string message;


  public:
    InvokingTracer(std::string_view method_name):
    message(GetMethodName(method_name)){
      Enter();
    }
    
    template<typename... Args>
    InvokingTracer(std::string_view method_name, std::format_string<Args...> fmt, Args&&... args)
    :message(GetMethodName(method_name)+std::format(fmt, std::forward<Args>(args)...))
    {
      Enter();
    }
    
    ~InvokingTracer()
    {
        Leave();
    }

    private:
    //只保留File中的文件名部分
    static std::string GetMethodName(std::string_view method_name);

    InvokingTracer(const InvokingTracer&) = delete;
    InvokingTracer& operator=(const InvokingTracer&) = delete;
    InvokingTracer(InvokingTracer&&) = delete;
    InvokingTracer& operator=(InvokingTracer&&) = delete;

  protected:
    void Enter();
    void Leave();
};
}  // namespace Base


#ifdef PFC_DEBUG
#define PFC_INVOKING_TRACER(method_name,...) auto UNIQUE_VAR(__invoking_tracer) = base::InvokingTracer(#method_name"[`" __FILE__ ":" TO_STRING(__LINE__)"]", __VA_ARGS__)
#else
struct None{
    template<typename... Args>
    inline void operator()(std::format_string<Args...> fmt, Args&&... args){}
};
#define PFC_INVOKING_TRACER(method_name,...)
#endif

#endif