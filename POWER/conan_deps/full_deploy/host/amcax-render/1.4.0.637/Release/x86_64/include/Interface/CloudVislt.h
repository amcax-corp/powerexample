/// @file      CloudVisltFactory.h
/// @brief     Cloud Object
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender

#ifndef CloudVislt_h
#define CloudVislt_h

#include "Macros.h"
#include "Constants.h"

namespace AMCAXRender {
    /// @brief	CloudVislt Class
    class AMCAX_RENDER_API CloudVislt {
    public:
        virtual ~CloudVislt() {};

        /// @brief Get Cloud Object Data Type
        /// @return Data type, structured data, volume data, unstructured data...
        virtual int GetDataType() = 0;

        /// @brief Get Cloud Object Scalar Data Name Array
        /// @return Name array
        virtual std::vector<std::string> GetScalarNames() = 0;

        /// @brief Get Cloud Object Scalar Data Range
        /// @param[in] name Scalar name
        /// @return std::tuple Minimum to maximum value
        virtual std::tuple<double, double> GetScaleRange(std::string name) = 0;

        /// @brief Get Cloud Object Dimensions
        /// @return int[3] Dimensions in X, Y, Z directions
        virtual int* GetDimensions() = 0;

        /// @brief Get Cloud Object Cubic Cell Spacing
        /// @return double[3] Width, height, length
        virtual double* GetSpacing() = 0;

        /// @brief Get Cloud Object Origin Position
        /// @return double[3] X, Y, Z
        virtual double* GetOrigin() = 0;


        virtual int GetNumberofSteps() = 0;
        virtual void SetCurrentStep(int step) = 0;

    };
}

#endif