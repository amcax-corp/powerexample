/// @file      MakeWedge.hpp
/// @brief     Class of making a wedge
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeWedgeImpl;
class TopoShell;
class TopoSolid;
#endif

/// @brief Class of making a wedge
class AMCAX_CLASS_API MakeWedge : public MakeShape
{
public:
	/// @brief Construct a right wedge with the size
	/// @param dx The length in the x direction
	/// @param dy The length in the y direction
	/// @param dz The length in the z direction
	/// @param ltx The length in the x direction of the right face
	AMCAX_API MakeWedge(double dx, double dy, double dz, double ltx);

	/// @brief Construct a right wedge with a local coordinate system and the size
	/// @param frame The local coordinate system
	/// @param dx The length in the x direction
	/// @param dy The length in the y direction
	/// @param dz The length in the z direction
	/// @param ltx The length in the x direction of the right face
	AMCAX_API MakeWedge(const Frame3& frame, double dx, double dy, double dz, double ltx);

	/// @brief Construct from the size
	/// @param dx The length in the x direction
	/// @param dy The length in the y direction
	/// @param dz The length in the z direction
	/// @param xmin The start x coordinate of the right face
	/// @param zmin The start z coordinate of the right face
	/// @param xmax The end x coordinate of the right face
	/// @param zmax The end z coordinate of the right face
	AMCAX_API MakeWedge(double dx, double dy, double dz, double xmin, double zmin, double xmax, double zmax);

	/// @brief Construct from a local coordinate system and the size
	/// @param frame The local coordinate system
	/// @param dx The length in the x direction
	/// @param dy The length in the y direction
	/// @param dz The length in the z direction
	/// @param xmin The start x coordinate of the right face
	/// @param zmin The start z coordinate of the right face
	/// @param xmax The end x coordinate of the right face
	/// @param zmax The end z coordinate of the right face
	AMCAX_API MakeWedge(const Frame3& frame, double dx, double dy, double dz, double xmin, double zmin, double xmax, double zmax);

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] MakeWedgeImpl& Wedge() noexcept;

#endif

	AMCAX_API void Build() override;

	/// @brief Get the shell of wedge
	/// @return The shell
	[[nodiscard]] AMCAX_API const TopoShell& Shell();

	/// @brief Get the shell of wedge
	/// @return The shell
	[[nodiscard]] AMCAX_API operator TopoShell();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API const TopoSolid& Solid();

	/// @brief Get the solid result
	/// @return The solid
	[[nodiscard]] AMCAX_API operator TopoSolid();

private:
	std::shared_ptr<MakeWedgeImpl> wedge;
};
} // namespace AMCAX
