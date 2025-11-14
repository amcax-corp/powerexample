/// @file      CloudVisltFactory.h
/// @brief     Cloud Factory
/// @details   
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAXRender

#ifndef CloudVisltFactory_h
#define CloudVisltFactory_h

#include "CloudVislt.h"
#include <memory>

namespace AMCAXRender {
    /// @brief	CloudVisltFactory Class
    class AMCAX_RENDER_API CloudVisltFactory {
    public:
        virtual ~CloudVisltFactory() {};

        /// @brief Read Cloud File
        /// @param[in] file Absolute file path
        /// @return Cloud object
        virtual std::shared_ptr<CloudVislt> ReadFile(std::string file) = 0;

        /// @brief Read Cloud File
        /// @param[in] is Cloud file stream
        /// @return Cloud object
        virtual std::shared_ptr<CloudVislt> ReadFile(std::istream& is) = 0;
    };
}

#endif