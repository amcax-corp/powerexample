/// @file      commom.h
/// @brief     This file defines the commom class
/// @copyright Copyright (c) 2023 Hefei Jiushuo Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender
#ifndef COMMOM_H
#define COMMOM_H
#include <memory>
#include"Macros.h"
namespace AMCAXRender
{
    /// @brief Transform
    class AMCAX_RENDER_API CTransform
    {
    public:
        CTransform();
        ~CTransform();

        /// @brief Set the transformation to the identity transformation. 
        /// @note If the transform has an Input, then the transformation will be
        /// reset so that it is the same as the Input.
        void Identity();

        /// @brief Create a translation matrix and concatenate it with the current
        /// transformation according to PreMultiply semantics.
        void Translate(double x, double y, double z);

        /// @brief Create a rotation matrix and concatenate it with the current
        /// transformation according to PreMultiply semantics.
        /// @param[in] angle The angle is in degrees,
        /// @param[in] (x,y,z) specifies the axis that the rotation will be performed around.
        void RotateWXYZ(double angle, double x, double y, double z);

        /// @brief Create a scale matrix (i.e. set the diagonal elements to x, y, z)
        /// and concatenate it with the current transformation according to PreMultiply semantics.
        void Scale(double x, double y, double z);

        /// @brief Return the position from the current transformation matrix
        void GetPosition(double pos[3]);

        /// @brief Return the Scale from the current transformation matrix
        void GetScale(double scale[3]);

        /// @brief Set the current matrix directly.
        /// @note the current matrix is set to the identity, then the input matrix is concatenated.
        void SetData(double data[16]);

        /// @brief Get the current matrix directly.
        void GetData(double* data);

        void Concatenate(CTransform* transform);

        std::shared_ptr<CTransform> DeepClone() const;

    private:
        CTransform(const CTransform&) = delete;
        void operator=(const CTransform&) = delete;
        void* impl = nullptr;
    };

}

#endif