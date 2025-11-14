/// @file      TopoLocation.hpp
/// @brief     Class of local transformation representing location of entities
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/TransformationT.hpp>
#include <topology/TopoLocationItemList.hpp>

namespace AMCAX
{
/// @brief Class of local transformation representing location of entities
/// @details The transformation is the composite of a list of transformations
class TopoLocation
{
public:
	/// @brief Default constructor
	/// @details The default transformation is an identity
	constexpr TopoLocation() noexcept = default;

	/// @brief Construct from a transformation
	/// @param tr The transformation
	AMCAX_API explicit TopoLocation(const Transformation3& tr);

	/// @brief Is the transformation identity
	/// @return True if the transformation is identity
	[[nodiscard]] AMCAX_API bool IsIdentity() const noexcept;

	/// @brief Set the transformation as identity
	AMCAX_API void Identity() noexcept;

	/// @brief Get the first location
	/// @return The first location
	[[nodiscard]] AMCAX_API TopoLocation FirstLocation() const;

	/// @brief Get the first power
	/// @return The first power
	[[nodiscard]] AMCAX_API int FirstPower() const noexcept;

	/// @brief Get the next location with removing the first transformation
	/// @return The location without the first transformation
	[[nodiscard]] AMCAX_API const TopoLocation& NextLocation() const noexcept;

	/// @brief Get the composite transformation
	/// @return The composite transformation
	[[nodiscard]] AMCAX_API const Transformation3& Transformation() const noexcept;

	/// @brief Get the inverted location
	/// @return The inverted location
	[[nodiscard]] AMCAX_API TopoLocation Inverted() const;

	/// @brief Get the composite of the location and the other location
	/// @param other The other location
	/// @return The composite location
	[[nodiscard]] AMCAX_API TopoLocation operator*(const TopoLocation& other) const;

	/// @brief Get the composite of the location and the inversion of the other location
	/// @param other The other location
	/// @return The composite location
	[[nodiscard]] AMCAX_API TopoLocation operator/(const TopoLocation& other) const;

	/// @brief Get the composite of the inversion of the other location and the location
	/// @param other The other location
	/// @return The composite location
	[[nodiscard]] AMCAX_API TopoLocation LeftDivide(const TopoLocation& other) const;

	/// @brief Get the location with power
	/// @param power The power
	/// @return The powered location
	[[nodiscard]] AMCAX_API TopoLocation Powered(int power) const;

	/// @brief Are two locations the same
	/// @param other The other location
	/// @return True if the all the items are same
	[[nodiscard]] AMCAX_API bool operator==(const TopoLocation& other) const noexcept;

	/// @brief Are two locations different
	/// @param other The other location
	/// @return True if the locations are not equal
	[[nodiscard]] AMCAX_API bool operator!=(const TopoLocation& other) const noexcept;

	/// @brief Clear the location items, i.e. reset the transformation to identity
	AMCAX_API void Clear() noexcept;

	/// @brief Precision of scale
	static constexpr double ScalePrecision = 1e-14;

private:
	/// @brief Transformation components
	TopoLocationItemList items;
};
} // namespace AMCAX

/// @brief Specialization of hash functions for STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoLocation>
{
	/// @brief Compute the hash value of a TopoLocation
	/// @param l The location
	/// @return The hash value
	[[nodiscard]] AMCAX_API size_t operator()(const AMCAX::TopoLocation& l) const noexcept;
};
