#ifndef POWERFC_APP_COLOR_H_
#define POWERFC_APP_COLOR_H_
#pragma once
#include <PFCGlobal.h>
#include <cmath>
#include <cstdint>
#include <string>

namespace app {

class PFC_APP_API Color
{
  public:
    //!@brief 构造颜色，颜色分量取值为[0,1]
    explicit Color(float R = 0.0, float G = 0.0, float B = 0.0, float A = 0.0);

    //!@brief 使用32位无符号整数构造颜色，每个分量为8位
    explicit Color(uint32_t rgba);

    Color(const Color& c) = default;
    Color(Color&&) = default;

    bool operator==(const Color& c) const;
    bool operator!=(const Color& c) const;
    
    //!@brief 设置颜色分量,颜色分量取值为[0,1],A取0时表示不透明
    void Set(float R, float G, float B, float A = 0.0);
    Color& operator=(const Color& c) = default;
    Color& operator=(Color&& c) = default;

    //!@brief 使用32位无符号整数设置颜色，每个分量为8位，0xRRGGBBAA
    Color& SetPackedValue(uint32_t rgba);

    //!@brief 使用32位无符号整数设置颜色，每个分量为8位，0xRRGGBB
    uint32_t GetPackedValue() const;

    //!@brief 返回32位无符号整数表示的颜色，每个分量为8位，0xRRGGBB
    uint32_t GetPackedRGB() const;
    
    //!@brief 使用32位无符号整数设置颜色，每个分量为8位，0xRRGGBB
    void SetPackedRGB(uint32_t);
    
    //!@brief 返回32位无符号整数表示的颜色，每个分量为8位，0xAARRGGBB
    uint32_t GetPackedARGB() const;
    
    //!@brief 使用32位无符号整数设置颜色，每个分量为8位，0xAARRGGBB
    void SetPackedARGB(uint32_t);

    //!@brief 使用其他的颜色类构造Color对象，比如QColor
    template<typename T>
    void SetValue(const T& q)
    {
        Set(q.redF(), q.greenF(), q.blueF());
    }
    
    //!@brief 返回其他颜色类，比如QColor
    template<typename T>
    inline T AsValue() const
    {
        // clang-format off
    return(T(int(std::lround(r * 255.0F)),
             int(std::lround(g * 255.0F)),
             int(std::lround(b * 255.0F))));
        // clang-format on
    }

    //!@return 返回16进制表示的颜色，比如"#FF0000"
    std::string AsHexString() const;

    //!@brief 从16进制表示的颜色中获取颜色，比如"#FF0000"
    bool FromHexString(const std::string& hex);


    /**
     * @brief 返回颜色在NX 216色调色板中的索引，如果不存在，则返回0
     * 
     * @return int 颜色在NX 216色调色板中的索引，如果不存在，则返回0
     */
    int GetIndex216() const;

    /**
     * @brief 根据NX216色调板中的索引设置颜色
     * 
     * @param index 1-216，如果不在此范围，返回false
     * @return true 
     * @return false 
     */
    bool SetIndex216(int index);

    float GetRedF() const
    {
        return r;
    }
    float GetGreenF() const
    {
        return g;
    }
    float GetBlueF() const
    {
        return b;
    }
    float GetAlphaF() const
    {
        return a;
    }

    uint8_t GetRed() const
    {
        return static_cast<uint8_t>(std::lround(r * 255.0F));
    }
    uint8_t GetGreen() const
    {
        return static_cast<uint8_t>(std::lround(g * 255.0F));
    }
    uint8_t GetBlue() const
    {
        return static_cast<uint8_t>(std::lround(b * 255.0F));
    }
    uint8_t GetAlpha() const
    {
        return static_cast<uint8_t>(std::lround(a * 255.0F));
    }

    void SetRedF(float r)
    {
        this->r = r;
    }
    void SetGreenF(float g)
    {
        this->g = g;
    }
    void SetBlueF(float b)
    {
        this->b = b;
    }
    void SetAlphaF(float a)
    {
        this->a = a;
    }

    void SetRed(uint8_t r)
    {
        this->r = r / 255.0F;
    }
    void SetGreen(uint8_t g)
    {
        this->g = g / 255.0F;
    }
    void SetBlue(uint8_t b)
    {
        this->b = b / 255.0F;
    }
    void SetAlpha(uint8_t a)
    {
        this->a = a / 255.0F;
    }

    static const Color Black()
    {
        return Color(0.0, 0.0, 0.0, 1.0);
    }

    static const Color White()
    {
        return Color(1.0, 1.0, 1.0, 1.0);
    }

    static const Color Red()
    {
        return Color(1.0, 0.0, 0.0, 1.0);
    }

    static const Color Green()
    {
        return Color(0.0, 1.0, 0.0, 1.0);
    }

    static const Color Blue()
    {
        return Color(0.0, 0.0, 1.0, 1.0);
    }

    static const Color Yellow()
    {
        return Color(1.0, 1.0, 0.0, 1.0);
    }

    static const Color Cyan()
    {
        return Color(0.0, 1.0, 1.0, 1.0);
    }
    static const Color Magenta()
    {
        return Color(1.0, 0.0, 1.0, 1.0);
    }

  private:
    /// color values, public accessible
    float r, g, b, a;
};
}  // namespace app

#endif