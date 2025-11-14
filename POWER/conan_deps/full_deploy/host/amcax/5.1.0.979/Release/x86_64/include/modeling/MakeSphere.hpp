/// @file      MakeSphere.hpp
/// @brief     Class of making a sphere
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <modeling/MakeOneAxis.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeSphereImpl;
#endif

/// @brief Class of making a sphere
/// @details The radius should be positive, the rotation angle on longitude should be in (0, 2pi], the start angle on latitude should be less than the end angle, in [-pi/2, pi/2]
class AMCAX_CLASS_API MakeSphere : public MakeOneAxis
{
public:
	/// @brief Construct from a radius
	/// @param r The radius
	AMCAX_API explicit MakeSphere(double r);

	/// @brief Construct from a radius and a rotation angle
	/// @param r The radius
	/// @param angle The rotation angle (longitude)
	AMCAX_API MakeSphere(double r, double angle);

	/// @brief Construct from a radius and two angles for spherical segment
	/// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
	AMCAX_API MakeSphere(double r, double angle1, double angle2);

	/// @brief Construct from a radius, two latitude angles and a longitude angle
	/// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
	/// @param angle3 The rotation angle (longitude)
	AMCAX_API MakeSphere(double r, double angle1, double angle2, double angle3);

	/// @brief Construct from a center point and a radius
	/// @param center The center point
	/// @param r The radius
	AMCAX_API MakeSphere(const Point3& center, double r);

	/// @brief Construct from a center point, a radius and a rotation angle
	/// @param center The center point
	/// @param r The radius
	/// @param angle The rotation angle (longitude)
	AMCAX_API MakeSphere(const Point3& center, double r, double angle);

	/// @brief Construct from a center point, a radius and two angles for spherical segment
	/// @param center The center point
	/// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
	AMCAX_API MakeSphere(const Point3& center, double r, double angle1, double angle2);

	/// @brief Construct from a center point, a radius, two latitude angles and a longitude angle
	/// @param center The center point
	/// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
	/// @param angle3 The rotation angle (longitude)
	AMCAX_API MakeSphere(const Point3& center, double r, double angle1, double angle2, double angle3);

	/// @brief Construct from a local coordinate system and a radius
	/// @param frame The local coordinate system
	/// @param r The radius
	AMCAX_API MakeSphere(const Frame3& frame, double r);

	/// @brief Construct from a local coordinate system, a radius and a rotation angle
	/// @param frame The local coordinate system
	/// @param r The radius
	/// @param angle The rotation angle (longitude)
	AMCAX_API MakeSphere(const Frame3& frame, double r, double angle);

	/// @brief Construct from a local coordinate system, a radius and two angles for spherical segment
	/// @param frame The local coordinate system
	/// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
	AMCAX_API MakeSphere(const Frame3& frame, double r, double angle1, double angle2);

	/// @brief Construct from a local coordinate system, a radius, two latitude angles and a longitude angle
	/// @param frame The local coordinate system
	/// @param r The radius
	/// @param angle1 The start angle (latitude)
	/// @param angle2 The end angle (latitude)
	/// @param angle3 The rotation angle (longitude)
	AMCAX_API MakeSphere(const Frame3& frame, double r, double angle1, double angle2, double angle3);

	/// @brief Destructor
	AMCAX_API ~MakeSphere();

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] MakeOneAxisImpl& OneAxis() noexcept override;

	/// @internal
	[[nodiscard]] MakeSphereImpl& Sphere() noexcept;

#endif

private:
	std::shared_ptr<MakeSphereImpl> sphere;
};
} // namespace AMCAX
