
#ifndef BASE_VECTOR3D_H
#define BASE_VECTOR3D_H

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <functional>


#ifndef F_PI
    #define F_PI 3.1415926f
#endif

#ifndef D_PI
    #define D_PI 3.141592653589793
#endif

#ifndef FLOAT_MAX
    #define FLOAT_MAX 3.402823466E+38F
#endif

#ifndef FLOAT_MIN
    #define FLOAT_MIN 1.175494351E-38F
#endif

#ifndef DOUBLE_MAX
    #define DOUBLE_MAX 1.7976931348623157E+308 /* max decimal value of a "double"*/
#endif

#ifndef DOUBLE_MIN
    #define DOUBLE_MIN 2.2250738585072014E-308 /* min decimal value of a "double"*/
#endif

namespace base {
template<class numT>
struct float_traits
{};

template<>
struct float_traits<float>
{
    typedef float float_type;
    static inline float_type pi()
    {
        return F_PI;
    }
    static inline float_type epsilon()
    {
        return FLT_EPSILON;
    }
    static inline float_type maximum()
    {
        return FLT_MAX;
    }
};

template<>
struct float_traits<double>
{
    typedef double float_type;
    static inline float_type pi()
    {
        return D_PI;
    }
    static inline float_type epsilon()
    {
        return DBL_EPSILON;
    }
    static inline float_type maximum()
    {
        return DBL_MAX;
    }
};

/** The Vector Base class. */
template<class Precision>
class Vector3
{
  public:
    typedef Precision num_type;
    typedef float_traits<num_type> traits_type;
    static inline num_type epsilon()
    {
        return traits_type::epsilon();
    }

    /** @name Public data members */
    //@{
    Precision x; /**< x-coordinate */
    Precision y; /**< y-coordinate */
    Precision z; /**< z-coordinate */
    //@}

    /// Construction
    explicit Vector3(Precision fx = 0.0, Precision fy = 0.0, Precision fz = 0.0);
    /// Construction
    Vector3(const Vector3<Precision>& rcVct);

    /** @name Operator */
    //@{
    /// Returns a reference to a coordinate. \a usIndex must be in the range [0,2]
    Precision& operator[](unsigned short usIndex);
    /// Returns a const reference to a coordinate. \a usIndex must be in the range [0,2]
    const Precision& operator[](unsigned short usIndex) const;
    /// Vector addition
    Vector3 operator+(const Vector3<Precision>& rcVct) const;
    Vector3 operator&(const Vector3<Precision>& rcVct) const;
    /// Vector subtraction
    Vector3 operator-(const Vector3<Precision>& rcVct) const;
    /// Negative vector
    Vector3 operator-(void) const;
    /// Vector summation
    Vector3& operator+=(const Vector3<Precision>& rcVct);
    /// Vector subtraction
    Vector3& operator-=(const Vector3<Precision>& rcVct);
    /// Vector scaling
    Vector3 operator*(Precision fScale) const;
    Vector3 operator/(Precision fDiv) const;
    Vector3& operator*=(Precision fScale);
    Vector3& operator/=(Precision fDiv);
    /// Assignment
    Vector3& operator=(const Vector3<Precision>& rcVct);
    /// Scalar product
    Precision operator*(const Vector3<Precision>& rcVct) const;
    /// Scalar product
    Precision Dot(const Vector3<Precision>& rcVct) const;
    /// Cross product
    Vector3 operator%(const Vector3<Precision>& rcVct) const;
    /// Cross product
    Vector3 Cross(const Vector3<Precision>& rcVct) const;

    /// Comparing for inequality
    bool operator!=(const Vector3<Precision>& rcVct) const;
    /// Comparing for equality
    bool operator==(const Vector3<Precision>& rcVct) const;
    //@}

    /// Check if Vector is on a line segment
    bool IsOnLineSegment(const Vector3<Precision>& startVct, const Vector3<Precision>& endVct) const;

    /** @name Modification */
    //@{
    void ScaleX(Precision f);
    void ScaleY(Precision f);
    void ScaleZ(Precision f);
    void Scale(Precision fX, Precision fY, Precision fZ);
    void MoveX(Precision f);
    void MoveY(Precision f);
    void MoveZ(Precision f);
    void Move(Precision fX, Precision fY, Precision fZ);
    void RotateX(Precision f);
    void RotateY(Precision f);
    void RotateZ(Precision f);
    //@}

    void Set(Precision fX, Precision fY, Precision fZ);

    void SetX(Precision fX)
    {
        x = fX;
    }

    void SetY(Precision fY)
    {
        y = fY;
    }

    void SetZ(Precision fZ)
    {
        z = fZ;
    }

    Precision GetX() const
    {
        return x;
    }

    Precision GetY() const
    {
        return y;
    }

    Precision GetZ() const
    {
        return z;
    }

    Precision& X()
    {
        return x;
    }

    Precision& Y()
    {
        return y;
    }
    Precision& Z()
    {
        return z;
    }

    /** @name Mathematics */
    //@{
    /// Length of the vector.
    Precision Length(void) const;
    /// Squared length of the vector.
    Precision Sqr(void) const;
    /// Set length to 1.
    Vector3& Normalize(void);

    Precision* Data();
    const Precision* Data() const;

    Vector3 Normalized(void) const;
    /// Checks whether this is the null vector
    bool IsNull() const;
    /// Get angle between both vectors. The returned value lies in the interval [0,pi].
    Precision GetAngle(const Vector3& rcVect) const;
    /** Transforms this point to the coordinate system defined by origin \a rclBase,
    * vector \a vector rclDirX and vector \a vector rclDirY.
    * \note \a rclDirX must be perpendicular to \a rclDirY, i.e. \a rclDirX * \a rclDirY = 0..
    */
    void TransformToCoordinateSystem(const Vector3& rclBase, const Vector3& rclDirX, const Vector3& rclDirY);
    /**
     * @brief IsEqual
     * @param rclPnt
     * @param tol
     * @return true or false
     * If the distance to point \a rclPnt is within the tolerance \a tol both points are considered
     * equal.
     */
    bool IsEqual(const Vector3& rclPnt, Precision tol) const;
    /// Projects this point onto the plane given by the base \a rclBase and the normal \a rclNorm.
    Vector3& ProjectToPlane(const Vector3& rclBase, const Vector3& rclNorm);
    /**
     * Projects this point onto the plane given by the base \a rclBase and the normal \a rclNorm
     * and stores the result in rclProj.
     */
    void ProjectToPlane(const Vector3& rclBase, const Vector3& rclNorm, Vector3& rclProj) const;
    /// Projects this point onto the line given by the base \a rclPoint and the direction \a rclLine.
    /**
     * Projects a point \a rclPoint onto the line defined by the origin and the direction \a rclLine.
     * The result is a vector from \a rclPoint to the point on the line. The length of this vector
     * is the distance from \a rclPoint to the line.
     * Note: The resulting vector does not depend on the current vector.
     */
    Vector3& ProjectToLine(const Vector3& rclPoint, const Vector3& rclLine);
    /**
     * Get the perpendicular of this point to the line defined by rclBase and rclDir.
     * Note: Do not mix up this method with ProjectToLine.
     */
    Vector3 Perpendicular(const Vector3& rclBase, const Vector3& rclDir) const;
    /** Computes the distance to the given plane. Depending on the side this point is located
     * the distance can also be negative. The distance is positive if the point is at the same
     * side the plane normal points to, negative otherwise.
     */
    Precision DistanceToPlane(const Vector3& rclBase, const Vector3& rclNorm) const;
    /// Computes the distance from this point to the line given by \a rclBase and \a rclDirect.
    Precision DistanceToLine(const Vector3& rclBase, const Vector3& rclDirect) const;
    /** Computes the vector from this point to the point on the line segment with the shortest
     * distance. The line segment is defined by \a rclP1 and \a rclP2.
     * Note: If the projection of this point is outside the segment then the shortest distance
     * to \a rclP1 or \a rclP2 is computed.
     */
    Vector3 DistanceToLineSegment(const Vector3& rclP1, const Vector3& rclP2) const;
    //@}
};

// global functions

/// Returns the distance between two points
template<class Precision>
inline Precision Distance(const Vector3<Precision>& v1, const Vector3<Precision>& v2)
{
    Precision x = v1.x - v2.x, y = v1.y - v2.y, z = v1.z - v2.z;
    return static_cast<Precision>(sqrt((x * x) + (y * y) + (z * z)));
}

/// Returns the squared distance between two points
template<class Precision>
inline Precision DistanceP2(const Vector3<Precision>& v1, const Vector3<Precision>& v2)
{
    Precision x = v1.x - v2.x, y = v1.y - v2.y, z = v1.z - v2.z;
    return x * x + y * y + z * z;
}

template<class T>
inline T clamp(T num, T lower, T upper)
{
    return std::max<T>(std::min<T>(upper, num), lower);
}

/// Multiplication of scalar with vector.
template<class Precision>
inline Vector3<Precision> operator*(Precision fFac, const Vector3<Precision>& rcVct)
{
    return Vector3<Precision>(rcVct.x * fFac, rcVct.y * fFac, rcVct.z * fFac);
}

template<class _Pr1, class _Pr2>
inline Vector3<_Pr1> ToVector(const Vector3<_Pr2>& v)
{
    return Vector3<_Pr1>(static_cast<_Pr1>(v.x), static_cast<_Pr1>(v.y), static_cast<_Pr1>(v.z));
}

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

}  // namespace base

#endif  // BASE_VECTOR3D_H
