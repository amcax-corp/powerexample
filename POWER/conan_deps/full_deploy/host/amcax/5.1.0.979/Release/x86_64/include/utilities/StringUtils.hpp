/**
 * @file StringUtils.hpp
 * @brief Defines utils for string.
 * @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd.
 * All rights reserved.
 * @par This file is part of AMCAX kernel.
 */
#pragma once

#include <utilities/Macros.hpp>

#include <string>
#include <vector>

namespace AMCAX {
namespace Meshing {

AMCAXMeshing_API std::vector<std::string> split_string(const std::string &str,
                                                       char delim);

AMCAXMeshing_API void trim_string(std::string &str);

AMCAXMeshing_API bool starts_with(const std::string &big_str,
                                  const std::string &small_str);

AMCAXMeshing_API bool ends_with(const std::string &big_str,
                                const std::string &small_str);

AMCAXMeshing_API std::string replace_first(const std::string &str,
                                           const std::string &orig,
                                           const std::string &rep);

AMCAXMeshing_API std::string replace_last(const std::string &str,
                                          const std::string &orig,
                                          const std::string &rep);

AMCAXMeshing_API std::string replace_all(const std::string &str,
                                         const std::string &orig,
                                         const std::string &rep);

} // namespace Meshing
} // namespace AMCAX