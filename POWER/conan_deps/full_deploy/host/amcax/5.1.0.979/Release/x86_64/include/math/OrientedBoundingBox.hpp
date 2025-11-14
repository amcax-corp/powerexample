/// @file      OrientedBoundingBox.hpp
/// @brief     Class of 3D Oriented Bounding Box (OBB)
/// @copyright Copyright (c) 2025 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/FrameT.hpp>

namespace AMCAX
{
class BoundingBox3;

/// @brief Class of Oriented Bounding Box (OBB)
/// @details The OBB is defined by a center of the box, the axes and the half sizes of its three dimensions.
///          The OBB can be used more effectively for non-interfering objects.
class OrientedBoundingBox
{
public:
	/// @brief Default constructor, constructor an empty oriented bounding box
	OrientedBoundingBox() noexcept = default;

	/// @brief Construct an oriented bounding box by setting all parameters
	/// @param center The center point
	/// @param xDirection The x-axis direction
	/// @param yDirection The y-axis direction
	/// @param zDirection The z-axis direction
	/// @param xHSize The x-axis half size
	/// @param yHSize The y-axis half size
	/// @param zHSize The z-axis half size
	AMCAX_API OrientedBoundingBox(const Point3& center, const Direction3& xDirection, const Direction3& yDirection, const Direction3& zDirection, double xHSize, double yHSize, double zHSize);

	/// @brief Construct an oriented bounding box by an axis-aligned bounding box
	/// @param box The other axis-aligned bounding box
	AMCAX_API OrientedBoundingBox(const BoundingBox3& box);

	/// @brief Creates new oriented bounding box covering all points
	/// @param points The point vector
	/// @param tolerances The tolerances for every such point
	/// @param isOptimal The flag defines the build mode, indicating whether the calculation of the bounding box is more accurate
	AMCAX_API void ReBuild(const std::vector<Point3>& points, const std::vector<double>* tolerances = nullptr, bool isOptimal = false);

	/// @brief Set the center of oriented bounding box
	/// @param center The new center
	AMCAX_API void SetCenter(const Point3& center) noexcept;

	/// @brief Set the x-component of oriented bounding box
	/// @param xDirection The x-axis direction
	/// @param xHSize The x-axis half size
	AMCAX_API void SetXComponent(const Direction3& xDirection, double xHSize);

	/// @brief Set the y-component of oriented bounding box
	/// @param yDirection The y-axis direction
	/// @param yHSize The y-axis half size
	AMCAX_API void SetYComponent(const Direction3& yDirection, double yHSize);

	/// @brief Set the z-component of oriented bounding box
	/// @param zDirection The z-axis direction
	/// @param zHSize The z-axis half size
	AMCAX_API void SetZComponent(const Direction3& zDirection, double zHSize);

	/// @brief Get the local coordinate system of this oriented box.
	/// @details In this frame, The box ((-XHSize, -YHSize, -ZHSize), (XHSize, YHSize, ZHSize)) will produce this oriented box.
	/// @return The local coordinate system of this oriented box
	[[nodiscard]] AMCAX_API Frame3 Position() const;

	/// @brief Get the center of this oriented box.
	/// @return The center of this oriented box.
	[[nodiscard]] AMCAX_API const Coord3& Center() const noexcept;

	/// @brief Get the x direciton of this oriented box.
	/// @return The x direciton of this oriented box.
	[[nodiscard]] AMCAX_API const Coord3& XDirection() const noexcept;

	/// @brief Get the y direciton of this oriented box.
	/// @return The y direciton of this oriented box.
	[[nodiscard]] AMCAX_API const Coord3& YDirection() const noexcept;

	/// @brief Get the z direciton of this oriented box.
	/// @return The z direciton of this oriented box.
	[[nodiscard]] AMCAX_API const Coord3& ZDirection() const noexcept;

	/// @brief Get the x half size of this oriented box.
	/// @return The x half size of this oriented box.
	[[nodiscard]] AMCAX_API double XHSize() const noexcept;

	/// @brief Get the y half size of this oriented box.
	/// @return The y half size of this oriented box.
	[[nodiscard]] AMCAX_API double YHSize() const noexcept;

	/// @brief Get the z half size of this oriented box.
	/// @return The z half size of this oriented box.
	[[nodiscard]] AMCAX_API double ZHSize() const noexcept;

	/// @brief Is the oriented bounding box empty.
	/// @return True if the half size in any direction is less than zero
	[[nodiscard]] AMCAX_API bool IsVoid() const noexcept;

	/// @brief Set the oriented bounding box to be empty
	AMCAX_API void SetVoid() noexcept;

	/// @brief Enlarge the gap
	/// @param gap The given gap
	AMCAX_API void Enlarge(double gap) noexcept;

	/// @brief Get the array of 8 corner points of this oriented box.
	/// @param[out] p The array of points
	/// @details Index == 0: (-XHSize(), -YHSize(), -ZHSize()) \n
	//!			 Index == 1: ( XHSize(), -YHSize(), -ZHSize()) \n
	//!			 Index == 2: (-XHSize(),  YHSize(), -ZHSize()) \n
	//!			 Index == 3: ( XHSize(),  YHSize(), -ZHSize()) \n
	//!			 Index == 4: (-XHSize(), -YHSize(),  ZHSize()) \n
	//!			 Index == 5: ( XHSize(), -YHSize(),  ZHSize()) \n
	//!			 Index == 6: (-XHSize(),  YHSize(),  ZHSize()) \n
	//!			 Index == 7: ( XHSize(),  YHSize(),  ZHSize()).
	/// @return True if the box is not empty
	AMCAX_API bool GetVertex(Point3 p[8]) const noexcept;

	/// @brief Get the squared distance of the diagonal of this oriented box.
	/// @return The squared diagonal distance
	[[nodiscard]] AMCAX_API double SquareDiagonal() const noexcept;

	/// @brief Determine whether an oriented bounding box is out of the oriented bounding box or not
	/// @param other The other oriented bounding box
	/// @return True if the oriented other bounding box is out of the oriented bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const OrientedBoundingBox& other) const noexcept;

	/// @brief Determine whether a point is out of the oriented bounding box or not
	/// @param p The point
	/// @return True if the point is out of the oriented bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const Point3& p) const noexcept;

	/// @brief Determine whether a oriented is completely inside the oriented bounding box or not
	/// @param other The other oriented bounding box
	/// @return True if the oriented other bounding box is completely inside the oriented bounding box
	[[nodiscard]] AMCAX_API bool IsCompletelyInside(const OrientedBoundingBox& other) const;

	/// @brief Enlarge the bounding box with an oriented bounding box
	/// @param other The oriented bounding box
	AMCAX_API void Add(const OrientedBoundingBox& other);

	/// @brief Enlarge the bounding box with a point
	/// @param p The point
	AMCAX_API void Add(const Point3& p);

protected:
	void ProcessOnePoint(const Point3& p) noexcept;

private:
	Coord3 center;
	Coord3 axes[3];
	double hDims[3] = {-1.0, -1.0, -1.0};
	bool isAxisAligned = false;
};
} // namespace AMCAX
