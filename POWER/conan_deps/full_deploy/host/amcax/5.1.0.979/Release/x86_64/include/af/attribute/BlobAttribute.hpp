/// @file      BlobAttribute.hpp
/// @brief     The class of BlobAttribute
/// @details   The class of BlobAttribute is used to store a raw memory block.
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX Kernel.
#pragma once
#include <af/attribute/Attribute.hpp>
#include <common/Macros.hpp>
#include <memory>
#include <string>

namespace AMCAX {

/// @brief The class of BlobAttribute
/// @details The class of BlobAttribute is used to store a raw memory block.
class BlobAttribute : public Attribute {
public:
    /// @brief The class of BlobData
    typedef struct BlobData {
        /// @brief Construct a BlobData with ptr and size
        /// @param ptr The input pointer
        /// @param size The size of the blob data
        AMCAX_API BlobData(void* ptr, size_t size) noexcept;

        /// @brief Construct a default BlobData
        /// @details Construct With no argument
        AMCAX_API BlobData() noexcept;

        /// @brief Construct a BlobData with other
        /// @param other Another blob data
        AMCAX_API BlobData(const BlobData& other) noexcept;
        
        /// @brief Overload the assignment operator
        /// @param rhs The one to assign
        AMCAX_API BlobData& operator=(const BlobData& rhs) noexcept;

        /// @brief Check if the BlobData is valid
        /// @return True if hold blob data, otherwise return false
        AMCAX_API bool holds() const noexcept;

        /// @brief Get the size of the BlobData
        /// @return The size of the blob data
        AMCAX_API size_t size() const noexcept;

        /// @brief Get the data pointer of the BlobData
        /// @return The data pointer of the blob data
        AMCAX_API const void* data() const noexcept;

    private:
        std::unique_ptr<uint8_t[]> _ptr;
        size_t _size = 0;
    } value_type;

    static constexpr AttributeMeta default_meta = 0;

public:
    /// @brief Construct a BlobAttribute with id, metainfo and data
    /// @param id The input id
    /// @param metainfo The input metainfo
    /// @param data The input data
    AMCAX_API BlobAttribute(const std::string& id, AttributeMeta metainfo, BlobData data) noexcept;

    /// @brief Construct a default BlobAttribute
    /// @details Costruct with no argument list, the id is ""
    AMCAX_API BlobAttribute() noexcept;

    /// @brief Construct a BlobAttribute with id and data
    /// @param id The input id
    /// @param data The input data
    AMCAX_API BlobAttribute(const std::string& id, BlobData data) noexcept;

public:
    /// @brief Set the value of the BlobAttribute
    /// @param data The BlobData to set
    AMCAX_API void SetValue(const BlobData& data) noexcept;
    
    /// @brief Get the value of the BlobAttribute
    /// @return The value of the BlobAttribute
    AMCAX_API const BlobData& GetValue() const;

    /// @brief Implement the clone function to create a new instance of BlobAttribute
    /// @return A new instance of BlobAttribute
    AMCAX_API std::shared_ptr<Attribute> Clone() override;

    /// @brief Serialize the attribute to string
    /// @return The serialized string
    AMCAX_API std::string Serialize() const override;
private:
    BlobData _data;
};
}  // namespace AMCAX