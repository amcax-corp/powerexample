#ifndef POWERFC_BASE_UUID_H_
#define POWERFC_BASE_UUID_H_
#pragma once
#include <PFCGlobal.h>
#include <string_view>
#include <string>

namespace base {

class PFC_BASE_API Uuid{
    public:

    Uuid();
    ~Uuid()=default;

    Uuid(const Uuid& other)=default;
    Uuid& operator=(const Uuid& other)=default;
    Uuid(Uuid&& other)=default;
    Uuid& operator=(Uuid&& other)=default;

    void SetValue(std::string_view str);
    std::string_view const GetValue() const;

    static Uuid Generate();

    bool operator==(const Uuid& other) const
    {
        return m_value == other.m_value;
    }

    bool operator<(const Uuid& other) const
    {
        return m_value < other.m_value;
    }

    private:
    std::string m_value;
};
}
#endif