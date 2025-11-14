/// @file      MakeRightPrism.hpp
/// @brief     Class of making a right prism
/// @copyright Copyright (c) 2024 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <vector>

#include <common/FrameT.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeRightPrismImpl;
class TopoShell;
class TopoSolid;
#endif

/// @brief Class of making a prism with right angle
class AMCAX_CLASS_API MakeRightPrism : public MakeShape
{
public:
	/// @brief Construct a right triangular prism
	/// @param p1,p2,p3 Points on the base plane
	/// @param apex A point on the top plane
	AMCAX_API MakeRightPrism(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& apex);

	/// @brief Construct a right quadrilateral prism
	/// @param p1,p2,p3,p4 Points on the base plane
	/// @param apex A point on the top plane
	AMCAX_API MakeRightPrism(const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4, const Point3& apex);

	/// @brief Construct a right prism with base points and a point on the top plane
	/// @param basepoints Points on the base plane
	/// @param apex A point on the top plane
	AMCAX_API MakeRightPrism(const std::vector<Point3>& basepoints, const Point3& apex);

	/// @brief Construct a right regular prism
	/// @param frame The local coordinate system
	/// @param radius Radius of the circumcircle of the base polygon
	/// @param nside Number of sides of the base polygon
	/// @param height Height of the polygon
	AMCAX_API MakeRightPrism(const Frame3& frame, double radius, int nside, double height);

	/// @brief Construct a right triangular prism with a given plane frame
	/// @param frame The frame of base plane
	/// @param p1,p2,p3 Points that are projected onto the base plane
	/// @param apex A point on the top plane
	AMCAX_API MakeRightPrism(const Frame3& frame, const Point3& p1, const Point3& p2, const Point3& p3, const Point3& apex);

	/// @brief Construct a right quadrilateral prism with a given plane frame
	/// @param frame The frame of base plane
	/// @param p1,p2,p3,p4 Points that are projected onto the base plane
	/// @param apex A point on the top plane
	AMCAX_API MakeRightPrism(const Frame3& frame, const Point3& p1, const Point3& p2, const Point3& p3, const Point3& p4, const Point3& apex);

	/// @brief Construct a right prism with a given base plane frame
	/// @param frame The frame of base plane
	/// @param basepoints Points that are projected onto the base plane
	/// @param apex A point on the top plane
	AMCAX_API MakeRightPrism(const Frame3& frame, const std::vector<Point3>& basepoints, const Point3& apex);

	/// @brief Construct a right prism with a given location on the base plane
	/// @details The base plane are determined by the location point and the first two base points
	/// @param baseLocation The location of the base plane
	/// @param basepoints The base points that are projected onto the base plane
	/// @param apex A point on the top plane
	AMCAX_API MakeRightPrism(const Point3& baseLocation, const std::vector<Point3>& basepoints, const Point3& apex);

	AMCAX_API void Build() override;

	/// @brief Get the shell of prism
	/// @return The shell
	[[nodiscard]] AMCAX_API const TopoShell& Shell();

	/// @brief Get the shell of prism
	/// @return The shell
	[[nodiscard]] AMCAX_API operator TopoShell();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API const TopoSolid& Solid();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API operator TopoSolid();

private:
	std::shared_ptr<MakeRightPrismImpl> rightPrism;
};
} // namespace AMCAX
