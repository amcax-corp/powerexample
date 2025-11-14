#ifndef POWERFC_BASE_MATRIX_H_
#define POWERFC_BASE_MATRIX_H_

#pragma once

#include <string>
#include <array>

#include <Base/Vector3D.h>
#include <PFCGlobal.h>


namespace base
{

enum class ScaleType
{
    Other = -1,
    NoScaling = 0,
    NonUniformRight = 1,
    NonUniformLeft = 2,
    Uniform = 3
};

/**
 * The Matrix4D class.
 */
class PFC_BASE_API Matrix4D  // NOLINT(cppcoreguidelines-special-member-functions)
{
    using traits_type = float_traits<double>;

public:
    /// Default constructor
    /*!
     * Initialises to an identity matrix
     */
    Matrix4D();

    // clang-format off
    /// Construction
    Matrix4D(float a11, float a12, float a13, float a14,
             float a21, float a22, float a23, float a24,
             float a31, float a32, float a33, float a34,
             float a41, float a42, float a43, float a44);
    /// Construction
    Matrix4D(double a11, double a12, double a13, double a14,
             double a21, double a22, double a23, double a24,
             double a31, double a32, double a33, double a34,
             double a41, double a42, double a43, double a44);
    // clang-format on
    /// Construction
    Matrix4D(const Matrix4D& mat);
    /// Construction with an Axis
    Matrix4D(const Vector3f& rclBase, const Vector3f& rclDir, float angle);
    Matrix4D(const Vector3d& rclBase, const Vector3d& rclDir, double angle);
    /// Destruction
    ~Matrix4D() = default;

    /** @name Operators */
    //@{
    /// Matrix addition
    inline Matrix4D operator+(const Matrix4D& mat) const;
    inline Matrix4D& operator+=(const Matrix4D& mat);
    /// Matrix subtraction
    inline Matrix4D operator-(const Matrix4D& mat) const;
    inline Matrix4D& operator-=(const Matrix4D& mat);
    /// Matrix multiplication
    inline Matrix4D& operator*=(const Matrix4D& mat);
    /// Assignment
    inline Matrix4D& operator=(const Matrix4D& mat);
    /// Matrix multiplication
    inline Matrix4D operator*(const Matrix4D& mat) const;
    /// Multiplication matrix with vector
    inline Vector3f operator*(const Vector3f& vec) const;
    inline Vector3d operator*(const Vector3d& vec) const;
    inline void multVec(const Vector3d& src, Vector3d& dst) const;
    inline void multVec(const Vector3f& src, Vector3f& dst) const;
    inline Matrix4D operator*(double scalar) const;
    inline Matrix4D& operator*=(double scalar);
    /// Comparison
    inline bool operator!=(const Matrix4D& mat) const;
    /// Comparison
    inline bool operator==(const Matrix4D& mat) const;
    /// Index operator
    inline double* operator[](unsigned short usNdx);
    /// Index operator
    inline const double* operator[](unsigned short usNdx) const;
    /// Get vector of row
    inline Vector3d GetRow(unsigned short usNdx) const;
    /// Get vector of column
    inline Vector3d GetCol(unsigned short usNdx) const;
    /// Get vector of diagonal
    inline Vector3d Diagonal() const;
    /// Get trace of the 3x3 matrix
    inline double Trace3() const;
    /// Get trace of the 4x4 matrix
    inline double Trace() const;
    /// Set row to vector
    inline void SetRow(unsigned short usNdx, const Vector3d& vec);
    /// Set column to vector
    inline void SetCol(unsigned short usNdx, const Vector3d& vec);
    /// Set diagonal to vector
    inline void SetDiagonal(const Vector3d& vec);
    /// Compute the determinant of the matrix
    double Determinant() const;
    /// Compute the determinant of the 3x3 sub-matrix
    double Determinant3() const;
    /// Analyse the transformation
    std::string Analyse() const;
    /// Outer product (Dyadic product)
    Matrix4D& Outer(const Vector3f& rV1, const Vector3f& rV2);
    Matrix4D& Outer(const Vector3d& rV1, const Vector3d& rV2);
    /// Hat operator (skew symmetric)
    Matrix4D& Hat(const Vector3f& rV);
    Matrix4D& Hat(const Vector3d& rV);
    //@}

    void GetMatrix(double matrix[16]) const;
    void SetMatrix(const double matrix[16]);
    /// get the matrix in OpenGL style
    void GetGLMatrix(double matrix[16]) const;
    /// set the matrix in OpenGL style
    void SetGLMatrix(const double matrix[16]);

    unsigned long GetMemSpace();

    /** @name Manipulation */
    //@{
    /// Makes unity matrix
    void SetToUnity();
    /// Checks if this is the unit matrix
    bool IsUnity() const;
    /// Checks if this is the unit matrix
    bool IsUnity(double tol) const;
    /// Makes a null matrix
    void Nullify();
    /// Checks if this is the null matrix
    bool IsNull() const;
    /// moves the coordinatesystem for the x,y,z value
    void Move(float x, float y, float z)
    {
        Move(Vector3f(x, y, z));
    }
    void Move(double x, double y, double z)
    {
        Move(Vector3d(x, y, z));
    }
    /// moves the coordinatesystem for the vector
    void Move(const Vector3f& vec);
    void Move(const Vector3d& vec);
    /// scale for the vector
    void Scale(float x, float y, float z)
    {
        Scale(Vector3f(x, y, z));
    }
    void Scale(double x, double y, double z)
    {
        Scale(Vector3d(x, y, z));
    }
    /// scale for the x,y,z value
    void Scale(const Vector3f& vec);
    void Scale(const Vector3d& vec);
    /// uniform scale
    void Scale(float scalexyz)
    {
        Scale(Vector3f(scalexyz, scalexyz, scalexyz));
    }
    void Scale(double scalexyz)
    {
        Scale(Vector3d(scalexyz, scalexyz, scalexyz));
    }
    /// Check for scaling factor
    ScaleType hasScale(double tol = 0.0) const;
    /// Decompose matrix into pure shear, scale, rotation and move
    std::array<Matrix4D, 4> Decompose() const;
    /// Rotate around the X axis (in transformed space) for the given value in radians
    void RotateAroundX(double angle);
    /// Rotate around the Y axis (in transformed space) for the given value in radians
    void RotateAroundY(double angle);
    /// Rotate around the Z axis (in transformed space) for the given value in radians
    void RotateAroundZ(double angle);
    /// Rotate around an arbitrary axis passing the origin in radians
    void RotateAround(const Vector3f& vec, float angle);
    /// Rotate around an arbitrary axis passing the origin in radians
    void RotateAround(const Vector3d& vec, double angle);
    /// Rotate around an arbitrary axis that needn't necessarily pass the origin in radians
    void RotateAround(const Vector3f& rclBase, const Vector3f& rclDir, float angle);
    /// Rotate around an arbitrary axis that needn't necessarily pass the origin in radians
    void RotateAround(const Vector3d& rclBase, const Vector3d& rclDir, double angle);
    /// Extract the rotation axis and angle. Therefore the 3x3 submatrix must be orthogonal.
    bool ToAxisAngle(Vector3f& rclBase, Vector3f& rclDir, float& angle, float& fTranslation) const;
    bool ToAxisAngle(Vector3d& rclBase, Vector3d& rclDir, double& angle, double& fTranslation) const;
    /// transform (move,scale,rotate) around a point
    void Transform(const Vector3f& vec, const Matrix4D& mat);
    void Transform(const Vector3d& vec, const Matrix4D& mat);
    /// Matrix is expected to have a 3x3 rotation submatrix.
    void Inverse();
    /// Matrix is expected to have a 3x3 rotation submatrix.
    void InverseOrthogonal();
    /// Arbitrary, non-singular matrix
    void InverseGauss();
    void Transpose();
    //@}

    void Print() const;
    /// write the 16 double of the matrix into a string
    std::string ToString() const;
    /// read the 16 double of the matrix from a string
    void FromString(const std::string& str);

private:
    double m_mat[4][4];
};

inline Matrix4D Matrix4D::operator+(const Matrix4D& mat) const
{
    Matrix4D clMat;

    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            clMat.m_mat[iz][is] = m_mat[iz][is] + mat[iz][is];
        }
    }

    return clMat;
}

inline Matrix4D& Matrix4D::operator+=(const Matrix4D& mat)
{
    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            m_mat[iz][is] += mat[iz][is];
        }
    }

    return *this;
}

inline Matrix4D Matrix4D::operator-(const Matrix4D& mat) const
{
    Matrix4D clMat;

    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            clMat.m_mat[iz][is] = m_mat[iz][is] - mat[iz][is];
        }
    }

    return clMat;
}

inline Matrix4D& Matrix4D::operator-=(const Matrix4D& mat)
{
    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            m_mat[iz][is] -= mat[iz][is];
        }
    }

    return *this;
}

inline Matrix4D& Matrix4D::operator*=(const Matrix4D& mat)
{
    Matrix4D clMat;

    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            clMat.m_mat[iz][is] = 0;
            for (int ie = 0; ie < 4; ie++) {
                clMat.m_mat[iz][is] += m_mat[iz][ie] * mat.m_mat[ie][is];
            }
        }
    }

    (*this) = clMat;

    return *this;
}

inline Matrix4D Matrix4D::operator*(const Matrix4D& mat) const
{
    Matrix4D clMat;

    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            clMat.m_mat[iz][is] = 0;
            for (int ie = 0; ie < 4; ie++) {
                clMat.m_mat[iz][is] += m_mat[iz][ie] * mat.m_mat[ie][is];
            }
        }
    }

    return clMat;
}

inline Matrix4D& Matrix4D::operator=(const Matrix4D& mat)
{
    if (this == &mat) {
        return *this;
    }

    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            m_mat[iz][is] = mat.m_mat[iz][is];
        }
    }

    return *this;
}

inline Vector3f Matrix4D::operator*(const Vector3f& vec) const
{
    // clang-format off
    double sx = static_cast<double>(vec.x);
    double sy = static_cast<double>(vec.y);
    double sz = static_cast<double>(vec.z);
    return Vector3f(static_cast<float>(m_mat[0][0] * sx + m_mat[0][1] * sy + m_mat[0][2] * sz + m_mat[0][3]),
                    static_cast<float>(m_mat[1][0] * sx + m_mat[1][1] * sy + m_mat[1][2] * sz + m_mat[1][3]),
                    static_cast<float>(m_mat[2][0] * sx + m_mat[2][1] * sy + m_mat[2][2] * sz + m_mat[2][3]));
    // clang-format on
}

inline Vector3d Matrix4D::operator*(const Vector3d& vec) const
{
    // clang-format off
    return Vector3d((m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3]),
                    (m_mat[1][0] * vec.x + m_mat[1][1] * vec.y + m_mat[1][2] * vec.z + m_mat[1][3]),
                    (m_mat[2][0] * vec.x + m_mat[2][1] * vec.y + m_mat[2][2] * vec.z + m_mat[2][3]));
    // clang-format on
}

inline void Matrix4D::multVec(const Vector3d& src, Vector3d& dst) const
{
    // clang-format off
    double dx = (m_mat[0][0] * src.x + m_mat[0][1] * src.y + m_mat[0][2] * src.z + m_mat[0][3]);
    double dy = (m_mat[1][0] * src.x + m_mat[1][1] * src.y + m_mat[1][2] * src.z + m_mat[1][3]);
    double dz = (m_mat[2][0] * src.x + m_mat[2][1] * src.y + m_mat[2][2] * src.z + m_mat[2][3]);
    dst.Set(dx, dy, dz);
    // clang-format on
}

inline void Matrix4D::multVec(const Vector3f& src, Vector3f& dst) const
{
    double sx = static_cast<double>(src.x);
    double sy = static_cast<double>(src.y);
    double sz = static_cast<double>(src.z);

    double dx = (m_mat[0][0] * sx + m_mat[0][1] * sy + m_mat[0][2] * sz + m_mat[0][3]);
    double dy = (m_mat[1][0] * sx + m_mat[1][1] * sy + m_mat[1][2] * sz + m_mat[1][3]);
    double dz = (m_mat[2][0] * sx + m_mat[2][1] * sy + m_mat[2][2] * sz + m_mat[2][3]);
    dst.Set(static_cast<float>(dx), static_cast<float>(dy), static_cast<float>(dz));
}

inline Matrix4D Matrix4D::operator*(double scalar) const
{
    Matrix4D matrix;
    for (unsigned short i = 0; i < 4; i++) {
        for (unsigned short j = 0; j < 4; j++) {
            matrix.m_mat[i][j] = m_mat[i][j] * scalar;
        }
    }

    return matrix;
}

inline Matrix4D& Matrix4D::operator*=(double scalar)
{
    // NOLINTBEGIN
    for (unsigned short i = 0; i < 4; i++) {
        for (unsigned short j = 0; j < 4; j++) {
            m_mat[i][j] *= scalar;
        }
    }
    // NOLINTEND
    return *this;
}

inline bool Matrix4D::operator==(const Matrix4D& mat) const
{
    for (int iz = 0; iz < 4; iz++) {
        for (int is = 0; is < 4; is++) {
            if (fabs(m_mat[iz][is] - mat.m_mat[iz][is]) > traits_type::epsilon()) {
                return false;
            }
        }
    }

    return true;
}

inline bool Matrix4D::operator!=(const Matrix4D& mat) const
{
    return !((*this) == mat);
}

inline Vector3f& operator*=(Vector3f& vec, const Matrix4D& mat)
{
    vec = mat * vec;
    return vec;
}

inline double* Matrix4D::operator[](unsigned short usNdx)
{
    return m_mat[usNdx];
}

inline const double* Matrix4D::operator[](unsigned short usNdx) const
{
    return m_mat[usNdx];
}

inline Vector3d Matrix4D::GetRow(unsigned short usNdx) const
{
    return Vector3d(m_mat[usNdx][0], m_mat[usNdx][1], m_mat[usNdx][2]);
}

inline Vector3d Matrix4D::GetCol(unsigned short usNdx) const
{
    return Vector3d(m_mat[0][usNdx], m_mat[1][usNdx], m_mat[2][usNdx]);
}

inline Vector3d Matrix4D::Diagonal() const
{
    return Vector3d(m_mat[0][0], m_mat[1][1], m_mat[2][2]);
}

inline double Matrix4D::Trace3() const
{
    return m_mat[0][0] + m_mat[1][1] + m_mat[2][2];
}

inline double Matrix4D::Trace() const
{
    return m_mat[0][0] + m_mat[1][1] + m_mat[2][2] + m_mat[3][3];
}

inline void Matrix4D::SetRow(unsigned short usNdx, const Vector3d& vec)
{
    m_mat[usNdx][0] = vec.x;
    m_mat[usNdx][1] = vec.y;
    m_mat[usNdx][2] = vec.z;
}

inline void Matrix4D::SetCol(unsigned short usNdx, const Vector3d& vec)
{
    m_mat[0][usNdx] = vec.x;
    m_mat[1][usNdx] = vec.y;
    m_mat[2][usNdx] = vec.z;
}

inline void Matrix4D::SetDiagonal(const Vector3d& vec)
{
    m_mat[0][0] = vec.x;
    m_mat[1][1] = vec.y;
    m_mat[2][2] = vec.z;
}

}  // namespace Base

#endif