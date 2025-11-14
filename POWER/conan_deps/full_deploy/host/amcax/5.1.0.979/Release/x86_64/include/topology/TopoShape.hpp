/// @file      TopoShape.hpp
/// @brief     Base class of shape, containing an underlying shape with a location and an orientation
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <topology/TopoLocation.hpp>
#include <topology/TopologyMacros.hpp>

namespace AMCAX
{
class TopoTShape;

/// @brief Base class of shape, containing an underlying shape with a location and an orientation
class TopoShape
{
public:
	/// @brief Is the shape null
	/// @return True if the shape is null
	[[nodiscard]] AMCAX_API bool IsNull() const noexcept;

	/// @brief Set the shape as null
	AMCAX_API void Nullify() noexcept;

	/// @brief Get the location of shape
	/// @return The location
	[[nodiscard]] AMCAX_API const TopoLocation& Location() const noexcept;

	/// @brief Set the location of shape
	/// @param loc The location
	/// @param isthrow Determine whether throw exception
	AMCAX_API void SetLocation(const TopoLocation& loc, bool isthrow = true);

	/// @brief Get the located shape
	/// @param loc The location
	/// @param isthrow Determine whether throw exception
	/// @return The located shape
	[[nodiscard]] AMCAX_API TopoShape Located(const TopoLocation& loc, bool isthrow = true) const;

	/// @brief Get the orientation of shape
	/// @return The orientation
	[[nodiscard]] AMCAX_API OrientationType Orientation() const noexcept;

	/// @brief Set the orientation of shape
	/// @param orient The orientation
	AMCAX_API void SetOrientation(OrientationType orient) noexcept;

	/// @brief Get the shape with given orientation
	/// @param orient The orientation
	/// @return The oriented shape
	[[nodiscard]] AMCAX_API TopoShape Oriented(OrientationType orient) const noexcept;

#ifndef DOXYGEN_SKIP

	/// @brief Get the internal TShape
	/// @return The internal TShape
	[[nodiscard]] const std::shared_ptr<TopoTShape>& TShape() const noexcept;

	/// @brief Set the internal TShape
	/// @param ts The TShape
	void SetTShape(const std::shared_ptr<TopoTShape>& ts) noexcept;

#endif

	/// @brief Get the type of shape
	/// @details Require the shape is not null
	/// @return The type of shape
	[[nodiscard]] AMCAX_API ShapeType Type() const noexcept;

	/// @brief Is the shape free
	/// @details Require the shape is not null
	/// @return True if the shape is free
	[[nodiscard]] AMCAX_API bool Free() const noexcept;

	/// @brief Set the shape free or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is free or not
	AMCAX_API void Free(bool isEnable) noexcept;

	/// @brief Is the shape modified
	/// @details Require the shape is not null
	/// @return True if the shape is modified
	[[nodiscard]] AMCAX_API bool Modified() const noexcept;

	/// @brief Set the shape modified or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is modified or not
	AMCAX_API void Modified(bool isEnable) noexcept;

	/// @brief Is the shape checked
	/// @details Require the shape is not null
	/// @return True if the shape is checked
	[[nodiscard]] AMCAX_API bool Checked() const noexcept;

	/// @brief Set the shape checked or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is checked or not
	AMCAX_API void Checked(bool isEnable) noexcept;

	/// @brief Is the shape orientable
	/// @details Require the shape is not null
	/// @return True if the shape is orientable
	[[nodiscard]] AMCAX_API bool Orientable() const noexcept;

	/// @brief Set the shape orientable or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is orientable or not
	AMCAX_API void Orientable(bool isEnable) noexcept;

	/// @brief Is the shape closed
	/// @details Require the shape is not null
	/// @return True if the shape is closed
	[[nodiscard]] AMCAX_API bool Closed() const noexcept;

	/// @brief Set the shape closed or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is closed or not
	AMCAX_API void Closed(bool isEnable) noexcept;

	/// @brief Is the shape infinite
	/// @details Require the shape is not null
	/// @return True if the shape is infinite
	[[nodiscard]] AMCAX_API bool Infinite() const noexcept;

	/// @brief Set the shape infinite or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is infinite or not
	AMCAX_API void Infinite(bool isEnable) noexcept;

	/// @brief Is the shape convex
	/// @details Require the shape is not null
	/// @return True if the shape is convex
	[[nodiscard]] AMCAX_API bool Convex() const noexcept;

	/// @brief Set the shape convex or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is convex or not
	AMCAX_API void Convex(bool isEnable) noexcept;

	/// @brief Is the shape locked
	/// @details Require the shape is not null
	/// @return True if the shape is locked
	[[nodiscard]] AMCAX_API bool Locked() const noexcept;

	/// @brief Set the shape locked or not
	/// @details Require the shape is not null
	/// @param isEnable Determine whether the shape is locked or not
	AMCAX_API void Locked(bool isEnable) noexcept;

	/// @brief Move the shape by a location
	/// @param loc The location
	/// @param isthrow Determine whether throw exception
	AMCAX_API void Move(const TopoLocation& loc, bool isthrow = true);

	/// @brief Get the shape moved by a location
	/// @param loc The location
	/// @param isthrow Determine whether throw exception
	/// @return The moved shape
	[[nodiscard]] AMCAX_API TopoShape Moved(const TopoLocation& loc, bool isthrow = true) const;

	/// @brief Reverse the orientation of the shape
	/// @details Forward <-> Reversed, Internal and External are not changed
	AMCAX_API void Reverse() noexcept;

	/// @brief Get the shape with reversed orientation
	/// @return The shape with reversed orientation
	[[nodiscard]] AMCAX_API TopoShape Reversed() const noexcept;

	/// @brief Complement the orientation of the shape
	/// @details Forward <-> Reversed, Internal <-> External
	AMCAX_API void Complement() noexcept;

	/// @brief Get the shape with complemented orientation
	/// @return The shape with complemented orientation
	[[nodiscard]] AMCAX_API TopoShape Complemented() const noexcept;

	/// @brief Compose the orientation with the other orientation
	/// @param orient The other orientation
	AMCAX_API void Compose(OrientationType orient) noexcept;

	/// @brief Get the shape having an orientation composed with the other orientation
	/// @param orient The other orientation
	/// @return The shape having an orientation composed with the other orientation
	[[nodiscard]] AMCAX_API TopoShape Composed(OrientationType orient) const noexcept;

	/// @brief Get the number of child shapes
	/// @return The number of child shapes
	[[nodiscard]] AMCAX_API int NChildren() const noexcept;

	/// @brief Does the shape share the same pointer to the actual shape with the other shape
	/// @param other The other shape
	/// @return True if two shapes share the same pointer to the actual shape
	[[nodiscard]] AMCAX_API bool IsPartner(const TopoShape& other) const noexcept;

	/// @brief Is the shape a partner of the other shape, and does it have the same location with the other shape
	/// @param other The other shape
	/// @return True if two shapes are partners and have the same location
	[[nodiscard]] AMCAX_API bool IsSame(const TopoShape& other) const noexcept;

	/// @brief Is the shape same as the other shape, and does it have a same orientation with the other shape
	/// @param other The other shape
	/// @return True if two shapes are the same and has the same orientations
	[[nodiscard]] AMCAX_API bool IsEqual(const TopoShape& other) const noexcept;

	/// @brief Is the shape equal to the other shape
	/// @param other The other shape
	/// @return True if two shapes are equal
	[[nodiscard]] AMCAX_API bool operator==(const TopoShape& other) const noexcept;

	/// @brief Is the shape inequal to the other shape
	/// @param other The other shape
	/// @return True if two shapes are not equal
	[[nodiscard]] AMCAX_API bool IsInequal(const TopoShape& other) const noexcept;

	/// @brief Is the shape inequal to the other shape
	/// @param other The other shape
	/// @return True if two shapes are not equal
	[[nodiscard]] AMCAX_API bool operator!=(const TopoShape& other) const noexcept;

	/// @brief Remove the sub-shapes of the shape
	AMCAX_API void EmptyCopy();

	/// @brief Copy the shape except for its sub-shapes
	/// @return The empty copied shape
	[[nodiscard]] AMCAX_API TopoShape EmptyCopied() const;

private:
	/// @brief Pointer to the actual shape
	std::shared_ptr<TopoTShape> tShape;

	/// @brief Local transformation
	TopoLocation location;

	/// @brief Orientation
	OrientationType orientation = OrientationType::External;
};

/// @brief The equality operator for oriented shapes
struct OrientedShapeEqualTo
{
	/// @brief Determine whether two shapes are equal
	/// @param left The first shape
	/// @param right The second shape
	/// @return True if two shapes are equal
	[[nodiscard]] AMCAX_API bool operator()(const TopoShape& left, const TopoShape& right) const noexcept;
};
} // namespace AMCAX

/// @brief Specialization of hash function of TopoShape used in STL unordered_set and unordered_map
template<>
struct std::hash<AMCAX::TopoShape>
{
	/// @brief Get the hash value for a shape
	/// @param s The shape
	/// @return The hash value
	[[nodiscard]] AMCAX_API size_t operator()(const AMCAX::TopoShape& s) const noexcept;
};

/// @brief Specialization of equal function of TopoShape used in STL unordered_set and unordered_map
template<>
struct std::equal_to<AMCAX::TopoShape>
{
	/// @brief Determine whether two shapes are the same
	/// @param left The first shape
	/// @param right The second shape
	/// @return True if two shapes are the same
	[[nodiscard]] AMCAX_API bool operator()(const AMCAX::TopoShape& left, const AMCAX::TopoShape& right) const noexcept;
};
