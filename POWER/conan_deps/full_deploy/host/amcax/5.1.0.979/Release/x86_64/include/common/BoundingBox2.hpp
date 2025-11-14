/// @file      BoundingBox2.hpp
/// @brief     Class of 2D bounding box
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/TransformationT.hpp>

namespace AMCAX
{
/// @brief Class of 2D bounding box
class BoundingBox2
{
public:
	/// @brief Default constructor
	/// @details The default bounding box is void
	AMCAX_API BoundingBox2() noexcept;

	/// @brief Set the bounding box as the whole space
	AMCAX_API void SetWhole() & noexcept;

	/// @brief Set the bounding box as the void
	AMCAX_API void SetVoid() & noexcept;

	/// @brief Set the bounding box as a point
	/// @param p The point
	AMCAX_API void Set(const Point2& p) & noexcept;

	/// @brief Set the bounding box as a ray starting from a point along a direction
	/// @param p The point
	/// @param d The direction
	AMCAX_API void Set(const Point2& p, const Direction2& d) & noexcept;

	/// @brief Update the bounding box with the given minimal and maximal values
	/// @param xmin The minimal x value
	/// @param ymin The minimal y value
	/// @param xmax The maximal x value
	/// @param ymax The maximal y value
	AMCAX_API void Update(double xmin, double ymin, double xmax, double ymax) & noexcept;

	/// @brief Update the bounding box with a point (x, y)
	/// @param x The x coordinate
	/// @param y The y coordinate
	AMCAX_API void Update(double x, double y) & noexcept;

	/// @brief Get the gap
	/// @return The gap
	[[nodiscard]] AMCAX_API double GetGap() const noexcept;

	/// @brief Set the gap
	/// @param tol The new gap
	AMCAX_API void SetGap(double tol) & noexcept;

	/// @brief Enlarge the gap
	/// @details If the given gap is smaller than the current gap, keep the current gap
	/// @param tol The given gap
	AMCAX_API void Enlarge(double tol) & noexcept;

	/// @brief Get the bounds with gap
	/// @details If the bounding box is void, throw a construction error.
	/// @param[out] xmin The minimal x value
	/// @param[out] ymin The minimal y value
	/// @param[out] xmax The maximal x value
	/// @param[out] ymax The maximal y value
	AMCAX_API void Get(double& xmin, double& ymin, double& xmax, double& ymax) const;

	/// @brief Set the x negative direction to be open
	AMCAX_API void OpenXmin() & noexcept;

	/// @brief Set the x positive direction to be open
	AMCAX_API void OpenXmax() & noexcept;

	/// @brief Set the y negative direction to be open
	AMCAX_API void OpenYmin() & noexcept;

	/// @brief Set the y positive direction to be open
	AMCAX_API void OpenYmax() & noexcept;

	/// @brief Is the x negative direction open
	/// @return True if the x negative direction is open
	[[nodiscard]] AMCAX_API bool IsOpenXmin() const noexcept;

	/// @brief Is the x positive direction open
	/// @return True if the x positive direction is open
	[[nodiscard]] AMCAX_API bool IsOpenXmax() const noexcept;

	/// @brief Is the y negative direction open
	/// @return True if the y negative direction is open
	[[nodiscard]] AMCAX_API bool IsOpenYmin() const noexcept;

	/// @brief Is the y positive direction open
	/// @return True if the y positive direction is open
	[[nodiscard]] AMCAX_API bool IsOpenYmax() const noexcept;

	/// @brief Is the bounding box the whole space
	/// @return True if the bounding box is the whole space
	[[nodiscard]] AMCAX_API bool IsWhole() const noexcept;

	/// @brief Is the bounding box void
	/// @return True if the bounding box is void
	[[nodiscard]] AMCAX_API bool IsVoid() const noexcept;

	/// @brief Get the transformed bounding box
	/// @param tr The transformation
	/// @return The transformed bounding box
	[[nodiscard]] AMCAX_API BoundingBox2 Transformed(const Transformation2& tr) const noexcept;

	/// @brief Enlarge the bounding box with a bounding box
	/// @param b The bounding box
	AMCAX_API void Add(const BoundingBox2& b) & noexcept;

	/// @brief Enlarge the bounding box with a point
	/// @param p The point
	AMCAX_API void Add(const Point2& p) & noexcept;

	/// @brief Enlarge the bounding box with a ray
	/// @param p The start point
	/// @param d The ray direction
	AMCAX_API void Add(const Point2& p, const Direction2& d) & noexcept;

	/// @brief Enlarge the bounding box with a direction
	/// @param d The direction
	AMCAX_API void Add(const Direction2& d) & noexcept;

	/// @brief Determine whether a point is out of the bounding box or not
	/// @param p The point
	/// @return True if the point is out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const Point2& p) const noexcept;

	/// @brief Determine whether a segment is out of the bounding box (no intersection) or not
	/// @param p0 The start point of the segment
	/// @param p1 The end point of the segment
	/// @return True if the segment is out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const Point2& p0, const Point2& p1) const noexcept;

	/// @brief Determine whether a bounding box is out of the bounding box
	/// @param b The other bounding box
	/// @return True if the bounding box is out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const BoundingBox2& b) const noexcept;

	/// @brief Determine whether a transformed bounding box is out of the bounding box
	/// @param b The other bounding box
	/// @param tr The transformation
	/// @return True is the other transformed bounding box is out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const BoundingBox2& b, const Transformation2& tr) const noexcept;

	/// @brief Determine whether another transformed bounding box is out of the transformed bounding box
	/// @param tr1 The transformation to self
	/// @param b The other bounding box
	/// @param tr2 The transformation to the other bounding box
	/// @return True if the other transformed bounding box is out of the transformed bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const Transformation2& tr1, const BoundingBox2& b, const Transformation2& tr2) const noexcept;

	/// @brief Get the squared length of the diagonal of the bounding box
	/// @return The squared diagonal length
	[[nodiscard]] AMCAX_API double SquareDiagonal() const noexcept;

	/// @brief Get the length of the diagonal of the bounding box
	/// @return The diagonal length
	[[nodiscard]] AMCAX_API double Diagonal() const noexcept;

#ifndef DOXYGEN_SKIP
protected:
	/// @brief Class of type of mask, showing that a direction is open or not
	enum class MaskType
	{
		Void = 0b00001,
		Xmin = 0b00010,
		Xmax = 0b00100,
		Ymin = 0b01000,
		Ymax = 0b10000,
		Whole = 0b11110
	};

	/// @brief Minimal point
	Coord2 pointMin;

	/// @brief Maximal point
	Coord2 pointMax;

	/// @brief Gap
	double gap = 0.0;

	/// @brief Mask flag
	int flags = 1;
#endif
};
} // namespace AMCAX
