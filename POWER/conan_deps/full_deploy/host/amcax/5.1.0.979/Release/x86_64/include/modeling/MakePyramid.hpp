/// @file      MakePyramid.hpp
/// @brief     Class of making a pyramid
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/FrameT.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakePyramidImpl;
class TopoShell;
class TopoSolid;
#endif

/// @brief Class of making a pyramid
class AMCAX_CLASS_API MakePyramid : public MakeShape
{
public:
	/// @brief Construct a tetrahedron
	/// @param p1,p2,p3 Points on the base plane
	/// @param apex Apex point
	AMCAX_API MakePyramid(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& apex);

	/// @brief Construct a quadrilateral pyramid
	/// @param p1,p2,p3,p4 Points on the base plane
	/// @param apex Apex point
	AMCAX_API MakePyramid(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4, const Point3& apex);

	/// @brief Construct a pyramid with base points and an apex point
	/// @param basepoints Points on the base plane
	/// @param apex Apex point
	AMCAX_API MakePyramid(const std::vector<Point3>& basepoints, const Point3& apex);

	/// @brief Construct a regular pyramid
	/// @param frame The local coordinate system
	/// @param radius Radius of the circumcircle of the base polygon
	/// @param nside Number of sides of the base polygon
	/// @param height Height of the polygon
	AMCAX_API MakePyramid(const Frame3& frame, double radius, int nside, double height);

	/// @brief Construct a tetrahedron with a given plane frame
	/// @param frame The frame of base plane
	/// @param p1,p2,p3 Points that are projected onto the base plane
	/// @param apex Apex point
	AMCAX_API MakePyramid(const Frame3& frame, const Point3& p1, const Point3& p2, const Point3& p3, const Point3& apex);

	/// @brief Construct a quadrilateral pyramid with a given plane frame
	/// @param frame The frame of base plane
	/// @param p1,p2,p3,p4 Points that are projected onto the base plane
	/// @param apex Apex point
	AMCAX_API MakePyramid(const Frame3& frame, const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4, const Point3& apex);

	/// @brief Construct a pyramid with a given base plane frame
	/// @param frame The frame of base plane
	/// @param basepoints Points that are projected onto the base plane
	/// @param apex Apex point
	AMCAX_API MakePyramid(const Frame3& frame, const std::vector<Point3>& basepoints, const Point3& apex);

	/// @brief Construct a pyramid with a given location on the base plane
	/// @details The base plane are determined by the location point and the first two base points
	/// @param baseLocation The location of the base plane
	/// @param basepoints The base points that are projected onto the base plane
	/// @param apex Apex point
	AMCAX_API MakePyramid(const Point3& baseLocation, const std::vector<Point3>& basepoints, const Point3& apex);

	AMCAX_API void Build() override;

	/// @brief Get the shell of pyramid
	/// @return The shell
	[[nodiscard]] AMCAX_API const TopoShell& Shell();

	/// @brief Get the shell of pyramid
	/// @return The shell
	[[nodiscard]] AMCAX_API operator TopoShell();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API const TopoSolid& Solid();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API operator TopoSolid();

private:
	std::shared_ptr<MakePyramidImpl> pyramid;
};
} // namespace AMCAX
