/// @file      AttributeException.hpp
/// @brief     The class of AttributeException
/// @details   The class of AttributeException is the class of all attribute exceptions.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once

#include <exception>
#include <string>

namespace AMCAX {
/// @brief The base class of all attribute exceptions
class AttributeException: public std::exception {};

/// @brief The class of bad Attribute cast exception
class BadAttributeCast: public AttributeException {
public:
    /// @brief Construct a bad Attribute cast exception with from and to
    /// @param from The type to cast from
    /// @param to The type to cast to
    BadAttributeCast(const char* from, const char* to) noexcept
        : msg{"[Bad Attribute Cast]:" + std::string{from} + std::string{to}} {}

public:
    /// @brief Get the exception message
    /// @return The exception message
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:  
    std::string msg;
};

/// @brief The class of bad Attribute value exception
class BadAttributeValue: public AttributeException {
public:
    /// @brief Construct a bad default Attribute value
    BadAttributeValue() noexcept
        : msg{"[Bad Attribute Value]"} {};

    /// @brief Construct a bad Attribute value exception with message
    /// @param message The message of the exception
    BadAttributeValue(const char* message)
        : msg{message} {}

public:
    /// @brief Get the exception message
    /// @return The exception message
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    const std::string msg;
};

}  // namespace AMCAX