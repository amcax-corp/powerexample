/// @file      BoundingBox3.hpp
/// @brief     Class of 3D axis-aligned bounding box
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/DirectionT.hpp>
#include <common/PointT.hpp>
#include <common/TransformationT.hpp>

namespace AMCAX
{
/// @brief Class of 3D bounding box
/// @details A bounding box is parallel to the axes of the coordinate system.
///          If the bounding box is finite, it is defined by two corner point pointMin and pointMax.
///          If the bounding box is infinite, some of the direction is set to be open.
class BoundingBox3
{
public:
	/// @brief Default constructor
	/// @details The default bounding box is void
	AMCAX_API BoundingBox3() noexcept;

	/// @brief Construct the bounding box by setting boundary points
	/// @param pmin The minimal point
	/// @param pmax The maximal point
	AMCAX_API BoundingBox3(const Point3& pmin, const Point3& pmax) noexcept;

	/// @brief Set the bounding box to be the whole space
	AMCAX_API void SetWhole() & noexcept;

	/// @brief Set the bounding box to be void
	AMCAX_API void SetVoid() & noexcept;

	/// @brief Set the bounding box as a point
	/// @param p The point
	AMCAX_API void Set(const Point3& p) & noexcept;

	/// @brief Set the bounding box as a ray starting from a point along a direction
	/// @param p The point
	/// @param d The direction
	AMCAX_API void Set(const Point3& p, const Direction3& d) & noexcept;

	/// @brief Update the bounding box with the given minimal and maximal values
	/// @param xmin The minimal x value
	/// @param ymin The minimal y value
	/// @param zmin The minimal z value
	/// @param xmax The maximal x value
	/// @param ymax The maximal y value
	/// @param zmax The maximal z value
	AMCAX_API void Update(double xmin, double ymin, double zmin, double xmax, double ymax, double zmax) & noexcept;

	/// @brief Update the bounding box with a point (x, y, z)
	/// @param x The x coordinate
	/// @param y The y coordinate
	/// @param z The z coordinate
	AMCAX_API void Update(double x, double y, double z) & noexcept;

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
	/// @param[out] zmin The minimal z value
	/// @param[out] xmax The maximal x value
	/// @param[out] ymax The maximal y value
	/// @param[out] zmax The maximal z value
	AMCAX_API void Get(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) const;

	/// @brief Get the minimal point
	/// @details If the bounding box is void, throw a construction error.
	/// @return The minimal point
	[[nodiscard]] AMCAX_API Point3 CornerMin() const;

	/// @brief Get the maximal point
	/// @details If the bounding box is void, throw a construction error.
	/// @return The maximal point
	[[nodiscard]] AMCAX_API Point3 CornerMax() const;

	/// @brief Set the x negative direction to be open
	AMCAX_API void OpenXmin() & noexcept;

	/// @brief Set the x positive direction to be open
	AMCAX_API void OpenXmax() & noexcept;

	/// @brief Set the y negative direction to be open
	AMCAX_API void OpenYmin() & noexcept;

	/// @brief Set the y positive direction to be open
	AMCAX_API void OpenYmax() & noexcept;

	/// @brief Set the z negative direction to be open
	AMCAX_API void OpenZmin() & noexcept;

	/// @brief Set the z positive direction to be open
	AMCAX_API void OpenZmax() & noexcept;

	/// @brief Is the bounding box open
	/// @return True if at least one direction is open
	[[nodiscard]] AMCAX_API bool IsOpen() const noexcept;

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

	/// @brief Is the z negative direction open
	/// @return True if the z negative direction is open
	[[nodiscard]] AMCAX_API bool IsOpenZmin() const noexcept;

	/// @brief Is the z positive direction open
	/// @return True if the z positive direction is open
	[[nodiscard]] AMCAX_API bool IsOpenZmax() const noexcept;

	/// @brief Is the bounding box the whole space
	/// @return True if the bounding box is the whole space
	[[nodiscard]] AMCAX_API bool IsWhole() const noexcept;

	/// @brief Is the bounding box void
	/// @return True if the bounding box is void
	[[nodiscard]] AMCAX_API bool IsVoid() const noexcept;

	/// @brief Is the range in x direction thin
	/// @param tol The tolerance
	/// @return True if the width of range in x direction is smaller than the tolerance
	[[nodiscard]] AMCAX_API bool IsXThin(double tol) const noexcept;

	/// @brief Is the range in y direction thin
	/// @param tol The tolerance
	/// @return True if the width of range in y direction is smaller than the tolerance
	[[nodiscard]] AMCAX_API bool IsYThin(double tol) const noexcept;

	/// @brief Is the range in z direction thin
	/// @param tol The tolerance
	/// @return True if the width of range in z direction is smaller than the tolerance
	[[nodiscard]] AMCAX_API bool IsZThin(double tol) const noexcept;

	/// @brief Is the range in all the directions thin
	/// @param tol The tolerance
	/// @return True if the widths of ranges in all the directions are smaller than the tolerance
	[[nodiscard]] AMCAX_API bool IsThin(double tol) const noexcept;

	/// @brief Get the transformed bounding box
	/// @param tr The transformation
	/// @return The transformed bounding box
	[[nodiscard]] AMCAX_API BoundingBox3 Transformed(const Transformation3& tr) const noexcept;

	/// @brief Enlarge the bounding box with a bounding box
	/// @param b The bounding box
	AMCAX_API void Add(const BoundingBox3& b) & noexcept;

	/// @brief Enlarge the bounding box with a point
	/// @param p The point
	AMCAX_API void Add(const Point3& p) & noexcept;

	/// @brief Enlarge the bounding box with a ray
	/// @param p The start point
	/// @param d The ray direction
	AMCAX_API void Add(const Point3& p, const Direction3& d) & noexcept;

	/// @brief Enlarge the bounding box with a direction
	/// @param d The direction
	AMCAX_API void Add(const Direction3& d) & noexcept;

	/// @brief Determine whether a point is out of the bounding box or not
	/// @param p The point
	/// @return True if the point is out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const Point3& p) const noexcept;

	/// @brief Determine whether a bounding box is out of the bounding box or not
	/// @param b The other bounding box
	/// @return True if the other bounding box is out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const BoundingBox3& b) const noexcept;

	/// @brief Determine whether a transformed bounding box is out of the bounding box or not
	/// @param b The other bounding box
	/// @param tr The transformation
	/// @return True if the other transformed bounding box is out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const BoundingBox3& b, const Transformation3& tr) const noexcept;

	/// @brief Determine whether a transformed bounding box is out of the transformed bounding box or not
	/// @param tr1 The transformation to self
	/// @param bm The other bounding box
	/// @param tr2 The transformation to the other bounding box
	/// @return True if the other transformed bounding box is out of the transformed bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const Transformation3& tr1, const BoundingBox3& bm, const Transformation3& tr2) const noexcept;

	/// @brief Determine whether two parallel lines are out of the bounding box (no intersection) or not
	/// @param p1 The point on the first line
	/// @param p2 The point on the second line
	/// @param d The line direction
	/// @return True if two parallel lines are out of the bounding box
	[[nodiscard]] AMCAX_API bool IsOut(const Point3& p1, const Point3& p2, const Direction3& d) const noexcept;

	/// @brief Compute the minimum distance between two bounding boxes
	/// @details If either of the two bounding boxes is void, throw a construction error.
	/// @param other The other bounding box
	/// @return The distance between two bounding boxes
	[[nodiscard]] AMCAX_API double Distance(const BoundingBox3& other) const;

	/// @brief Get the squared distance of the diagonal of the bounding box
	/// @return The squared diagonal distance
	[[nodiscard]] AMCAX_API double SquareDiagonal() const noexcept;

	/// @brief Get the distance of the diagonal of the bounding box
	/// @return The diagonal distance
	[[nodiscard]] AMCAX_API double Diagonal() const noexcept;

	/// @brief Get the finite part of an infinite bounding box
	/// @return The finite part of bounding box
	[[nodiscard]] AMCAX_API BoundingBox3 FinitePart() const noexcept;

	/// @brief Does the bounding box have finite part
	/// @return True if the bounding box are not void and has positive length of bounding box
	[[nodiscard]] AMCAX_API bool HasFinitePart() const noexcept;

#ifndef DOXYGEN_SKIP
protected:
	/// @brief Class of type of mask, showing that a direction is open or not
	enum class MaskType
	{
		Void = 0b0000001,
		Xmin = 0b0000010,
		Xmax = 0b0000100,
		Ymin = 0b0001000,
		Ymax = 0b0010000,
		Zmin = 0b0100000,
		Zmax = 0b1000000,
		Whole = 0b1111110
	};

	/// @brief Minimal point
	Coord3 pointMin;

	/// @brief Maximal point
	Coord3 pointMax;

	/// @brief Gap
	double gap = 0.0;

	/// @brief Mask flag
	int flags = 1;
#endif
};
} // namespace AMCAX
