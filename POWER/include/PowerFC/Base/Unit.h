#ifndef POWERFC_BASE_UNIT_H_
#define POWERFC_BASE_UNIT_H_
#include <PFCGlobal.h>
#include <cstdint>
#include <string>
#include <string_view>

#pragma once

namespace base {

//添加注释
// 1. 物理量的单位
#define UNIT_SIGNATURE_LENGTH_BITS 4                     //长度
#define UNIT_SIGNATURE_MASS_BITS 4                       //质量
#define UNIT_SIGNATURE_TIME_BITS 4                       //时间
#define UNIT_SIGNATURE_ELECTRIC_CURRENT_BITS 4           //电流
#define UNIT_SIGNATURE_THERMODYNAMIC_TEMPERATURE_BITS 4  //热力学温度
#define UNIT_SIGNATURE_AMOUNT_OF_SUBSTANCE_BITS 4        //物质的量
#define UNIT_SIGNATURE_LUMINOUS_INTENSITY_BITS 4         //发光强度
#define UNIT_SIGNATURE_ANGLE_BITS 4                      //角度

// https://en.cppreference.com/w/cpp/language/bit_field
// https://stackoverflow.com/questions/33723631/signed-bit-field-in-c14

struct UnitSignature
{
    int32_t length : UNIT_SIGNATURE_LENGTH_BITS{0};
    int32_t mass : UNIT_SIGNATURE_MASS_BITS{0};
    int32_t time : UNIT_SIGNATURE_TIME_BITS{0};
    int32_t electric_current : UNIT_SIGNATURE_ELECTRIC_CURRENT_BITS{0};
    int32_t thermodynamic_temperature : UNIT_SIGNATURE_THERMODYNAMIC_TEMPERATURE_BITS{0};
    int32_t amount_of_substance : UNIT_SIGNATURE_AMOUNT_OF_SUBSTANCE_BITS{0};
    int32_t luminous_intensity : UNIT_SIGNATURE_LUMINOUS_INTENSITY_BITS{0};
    int32_t angle : UNIT_SIGNATURE_ANGLE_BITS{0};
};

class PFC_BASE_API Unit
{
    public:
    explicit Unit(int8_t length,
                  int8_t mass = 0,
                  int8_t time = 0,
                  int8_t electric_current = 0,
                  int8_t thermodynamic_temperature = 0,
                  int8_t amount_of_substance = 0,
                  int8_t luminous_intensity = 0,
                  int8_t angle = 0);

    Unit() = default;
    Unit(const Unit& other) = default;
    Unit& operator=(const Unit& other) = default;
    Unit(std::string_view expr);

    ~Unit() = default;

    /** Operators. */
    //@{
    inline Unit& operator*=(const Unit& that);
    inline Unit& operator/=(const Unit& that);
    Unit operator*(const Unit&) const;
    Unit operator/(const Unit&) const;
    bool operator==(const Unit&) const;
    bool operator!=(const Unit& that) const
    {
        return !(*this == that);
    }
    Unit& operator=(Unit&&) = default;
    Unit Pow(double exp) const;
    //@}

    const UnitSignature& GetSignature() const
    {
        return m_signature;
    }

    bool IsEmpty() const;

    std::string ToString() const;

    /// get the type as an string such as "Area", "Length" or "Pressure".
    std::string GetTypeString() const;

    static const Unit Length;  // 长度
    static const Unit Mass;    // 质量

    static const Unit Angle;            // 角度
    static const Unit AngleOfFriction;  // 摩擦角

    static const Unit Density;  // 密度

    static const Unit Area;          // 面积
    static const Unit Volume;        // 体积
    static const Unit TimeSpan;      // 时间间隔
    static const Unit Frequency;     // 频率
    static const Unit Velocity;      // 速度
    static const Unit Acceleration;  // 加速度
    static const Unit Temperature;   // 温度

    static const Unit CurrentDensity;          // 电流密度
    static const Unit ElectricCurrent;         // 电流
    static const Unit ElectricPotential;       // 电势
    static const Unit ElectricCharge;          // 电荷
    static const Unit MagneticFieldStrength;   // 磁场强度
    static const Unit MagneticFlux;            // 磁通量
    static const Unit MagneticFluxDensity;     // 磁通量密度
    static const Unit Magnetization;           // 磁化强度
    static const Unit ElectricalCapacitance;   // 电容
    static const Unit ElectricalInductance;    // 电感
    static const Unit ElectricalConductance;   // 电导
    static const Unit ElectricalResistance;    // 电阻
    static const Unit ElectricalConductivity;  // 电导率
    static const Unit AmountOfSubstance;       // 物质的量
    static const Unit LuminousIntensity;       // 发光强度

    // Pressure
    static const Unit CompressiveStrength;      // 抗压强度
    static const Unit Pressure;                 // 压力
    static const Unit ShearModulus;             // 剪切模量
    static const Unit Stress;                   // 应力
    static const Unit UltimateTensileStrength;  // 抗拉强度
    static const Unit YieldStrength;            // 屈服强度
    static const Unit YoungsModulus;            // 杨氏模量

    static const Unit Stiffness;         // 刚度
    static const Unit StiffnessDensity;  // 刚度密度

    static const Unit Force;   // 力
    static const Unit Work;    // 功
    static const Unit Power;   // 功率
    static const Unit Moment;  // 力矩

    static const Unit SpecificEnergy;                         // 能量密度
    static const Unit ThermalConductivity;                    // 热导率
    static const Unit ThermalExpansionCoefficient;            // 热膨胀系数
    static const Unit VolumetricThermalExpansionCoefficient;  // 体积热膨胀系数
    static const Unit SpecificHeat;                           // 比热容
    static const Unit ThermalTransferCoefficient;             // 热传导系数
    static const Unit HeatFlux;                               // 热流密度
    static const Unit DynamicViscosity;                       // 动态粘度
    static const Unit KinematicViscosity;                     // 运动粘度
    static const Unit VacuumPermittivity;                     // 真空介电常数
    static const Unit VolumeFlowRate;                         // 体积流量
    static const Unit DissipationRate;                        // 损耗率

    static const Unit InverseLength;  // 长度的倒数
    static const Unit InverseArea;    // 面积的倒数
    static const Unit InverseVolume;  // 体积的倒数

  private:
    UnitSignature m_signature;
};

inline Unit& Unit::operator*=(const Unit& that)
{
    *this = *this * that;
    return *this;
}

inline Unit& Unit::operator/=(const Unit& that)
{
    *this = *this / that;
    return *this;
}

}  // namespace app

#endif