/// @file      MakeTorus.hpp
/// @brief     Class of making a torus
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeTorusImpl;
class TopoFace;
class TopoShell;
class TopoSolid;
#endif

/// @brief Class of making a torus
/// @details The major radius and minor radius should be positive, rotation angle should be in (0, 2pi], start angle should be less than end angle and their difference should be not greater than 2pi.
class AMCAX_CLASS_API MakeTorus : public MakeShape
{
public:
	/// @brief Construct from a major radius and a minor radius
	/// @param r1 The major radius
	/// @param r2 The minor radius
	AMCAX_API MakeTorus(double r1, double r2);

	/// @brief Construct from a major radius, a minor radius and a rotation angle
	/// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle The rotation angle
	AMCAX_API MakeTorus(double r1, double r2, double angle);

	/// @brief Construct from a major radius, a minor radius and two angles that forms an arc of the section circle
	/// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle1 The start angle
	/// @param angle2 The end angle
	AMCAX_API MakeTorus(double r1, double r2, double angle1, double angle2);

	/// @brief Construct from a major radius, a minor radius, two angles that forms an arc of the section circle and a rotation angle
	/// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle1 The start angle
	/// @param angle2 The end angle
	/// @param angle The rotation angle
	AMCAX_API MakeTorus(double r1, double r2, double angle1, double angle2, double angle);

	/// @brief Construct from a local coordinate system, a major radius and a minor radius
	/// @param frame The local coordinate system
	/// @param r1 The major radius
	/// @param r2 The minor radius
	AMCAX_API MakeTorus(const Frame3& frame, double r1, double r2);

	/// @brief Construct from a local coordinate system, a major radius, a minor radius and a rotation angle
	/// @param frame The local coordinate system
	/// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle The rotation angle
	AMCAX_API MakeTorus(const Frame3& frame, double r1, double r2, double angle);

	/// @brief Construct from a local coordinate system, a major radius, a minor radius and two angles that forms an arc of the section circle
	/// @param frame The local coordinate system
	/// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle1 The start angle
	/// @param angle2 The end angle
	AMCAX_API MakeTorus(const Frame3& frame, double r1, double r2, double angle1, double angle2);

	/// @brief Construct from a local coordinate system, a major radius, a minor radius, two angles that forms an arc of the section circle and a rotation angle
	/// @param frame The local coordinate system
	/// @param r1 The major radius
	/// @param r2 The minor radius
	/// @param angle1 The start angle
	/// @param angle2 The end angle
	/// @param angle The rotation angle
	AMCAX_API MakeTorus(const Frame3& frame, double r1, double r2, double angle1, double angle2, double angle);

	/// @brief Destructor
	AMCAX_API ~MakeTorus();

	AMCAX_API void Build() override;

	/// @brief Get the lateral face
	/// @return The lateral face
	[[nodiscard]] AMCAX_API const TopoFace& Face();

	/// @brief Get the lateral face
	/// @return The lateral face
	[[nodiscard]] AMCAX_API operator TopoFace();

	/// @brief Get the shell result
	/// @return The shell
	[[nodiscard]] AMCAX_API const TopoShell& Shell();

	/// @brief Get the shell result
	/// @return The shell
	[[nodiscard]] AMCAX_API operator TopoShell();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API const TopoSolid& Solid();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API operator TopoSolid();

private:
	std::shared_ptr<MakeTorusImpl> torus;
};
} // namespace AMCAX
