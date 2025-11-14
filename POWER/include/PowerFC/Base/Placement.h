#ifndef POWERFC_BASE_PLACEMENT_H_
#define POWERFC_BASE_PLACEMENT_H_
#pragma once
#include <Base/Rotation.h>
#include <Base/Vector3D.h>

namespace base {

class PFC_BASE_API Placement
{
  public:
    /// default constructor
    Placement();
    Placement(const Placement&) = default;
    Placement(Placement&&) = default;
    Placement(const base::Matrix4D& matrix);
    Placement(const Vector3d& position, const Rotation& rotation);
    Placement(const Vector3d& position, const Rotation& rotation, const Vector3d& Cnt);

    /** specialty constructors */
    //@{
    // static Placement fromDualQuaternion(DualQuat qq);
    //@}

    /// Destruction
    ~Placement() = default;

    Matrix4D ToMatrix() const;
    void FromMatrix(const Matrix4D& m);
    // DualQuat toDualQuaternion() const;
    const Vector3d& GetPosition() const
    {
        return m_position;
    }
    const Rotation& GetRotation() const
    {
        return m_rotation;
    }
    void SetPosition(const Vector3d& position)
    {
        m_position = position;
    }
    void SetRotation(const Rotation& rotation)
    {
        m_rotation = rotation;
    }

    bool IsIdentity() const;
    bool IsIdentity(double tol) const;
    void Invert();
    Placement Inverse() const;
    void Move(const Vector3d& MovVec);

    bool IsSame(const Placement&) const;
    bool IsSame(const Placement&, double tol) const;

    /** Operators. */
    //@{
    Placement& operator*=(const Placement& p);
    Placement operator*(const Placement& p) const;
    bool operator==(const Placement&) const;
    bool operator!=(const Placement&) const;
    Placement& operator=(const Placement&) = default;
    Placement& operator=(Placement&&) = default;

    Placement& MultiplyRight(const base::Placement& p);
    Placement& MultiplyLeft(const base::Placement& p);

    Vector3d TransformVector(const Vector3d& src) const;
    Vector3f TransformVector(const Vector3f& src) const;
    //@}

    static Placement Slerp(const Placement& p0, const Placement& p1, double t);
    static Placement Slerp(const Placement& p0, const Placement& p1, double t, bool shorten = true);

  private:
    Vector3<double> m_position;
    base::Rotation m_rotation;
};
}  // namespace base

#endif