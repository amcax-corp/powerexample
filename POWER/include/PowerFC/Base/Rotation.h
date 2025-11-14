#ifndef POWERFC_BASE_ROTATION_H_
#define POWERFC_BASE_ROTATION_H_
#include <Base/Matrix.h>
#include <Base/Vector3D.h>
#include <PFCGlobal.h>

namespace base {

class PFC_BASE_API Rotation
{
  public:
    Rotation() = default;
    Rotation(const Vector3d& axis, double angle);
    Rotation(const Matrix4D& matrix);
    Rotation(const double q[4]);
    Rotation(double q0, double q1, double q2, double q3);
    Rotation(const Vector3d& rotate_from, const Vector3d& rotate_to);
    Rotation(const Rotation& rot) = default;
    Rotation(Rotation&& rot) = default;
    ~Rotation() = default;

  public:
    void SetValue(base::Vector3d const& axis, double const angle);
    void SetValue(base::Vector3d const& from_axis, base::Vector3d const& to_axis);
    void SetValue(base::Matrix4D const& matrix);

    //The Euler angles (yaw,pitch,roll)(in radians) are in XY'Z''-notation
    void SetYawPitchRoll(double yaw, double pitch, double roll);

    std::tuple<double, double, double> GetYawPitchRoll() const;

    bool IsIdentity() const;
    bool IsIdentity(double tol) const;
    bool IsNull() const;
    bool IsSame(const Rotation&) const;
    bool IsSame(const Rotation&, double tol) const;

    Rotation& Invert();
    Rotation Inverse() const;

    Rotation& operator*=(const Rotation& q);
    Rotation operator*(const Rotation& q) const;
    bool operator==(const Rotation& q) const;
    bool operator!=(const Rotation& q) const;

    Rotation& operator=(const Rotation&) = default;
    Rotation& operator=(Rotation&&) = default;

    double& operator[](unsigned short index)
    {
        return m_quaternion[index];
    }
    const double& operator[](unsigned short index) const
    {
        return m_quaternion[index];
    }

    double const GetX() const { return m_quaternion[0]; }
    double const GetY() const { return m_quaternion[1]; }
    double const GetZ() const { return m_quaternion[2]; }
    double const GetW() const { return m_quaternion[3]; }

    Rotation& MultiplyRight(const base::Rotation& q);
    Rotation& MultiplyLeft(const base::Rotation& q);

    Vector3d RotateVector(const Vector3d& src) const;
    Vector3f RotateVector(const Vector3f& src) const;

    void GetValue(base::Matrix4D& matrix) const;

    void ScaleAngle(double scale_factor);
    //@}

    /** Specialty constructors */
    static Rotation Slerp(const Rotation& q0, const Rotation& q1, double t);
    static Rotation Identity();

    protected:
    void SetValue(double q0, double q1, double q2, double q3);
    void SetUnitQuaternion(double x, double y, double z, double w);
    void EvaluateVector();

    void Normalize();

  private:
    double m_quaternion[4]{.0, .0, .0, 1.0};
    base::Vector3d m_axis{.0, .0, 1.0};
    double m_angle{.0};
};

}  // namespace base

#endif