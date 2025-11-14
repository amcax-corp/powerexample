/// @file      MakeBox.hpp
/// @brief     Class of making a box
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeWedgeImpl;
class TopoFace;
class TopoShell;
class TopoSolid;
#endif

/// @brief Class of making a box
class AMCAX_CLASS_API MakeBox : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeBox();

	/// @brief Construct from its size in x, y, z directions
	/// @param dx,dy,dz The size
	AMCAX_API MakeBox(double dx, double dy, double dz);

	/// @brief Construct from a corner point and its size
	/// @param p The corner point
	/// @param dx,dy,dz The size
	AMCAX_API MakeBox(const Point3& p, double dx, double dy, double dz);

	/// @brief Construct from two diagonal corner points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API MakeBox(const Point3& p1, const Point3& p2);

	/// @brief Construct from a local coordinate system and size
	/// @param frame The local coordinate system
	/// @param dx,dy,dz The size
	AMCAX_API MakeBox(const Frame3& frame, double dx, double dy, double dz);

	/// @brief Initialize and construct from its size in x, y, z directions
	/// @param dx,dy,dz The size
	AMCAX_API void Init(double dx, double dy, double dz);

	/// @brief Initialize and construct from a corner point and its size
	/// @param p The corner point
	/// @param dx,dy,dz The size
	AMCAX_API void Init(const Point3& p, double dx, double dy, double dz);

	/// @brief Initialize and construct from two diagonal corner points
	/// @param p1 The first point
	/// @param p2 The second point
	AMCAX_API void Init(const Point3& p1, const Point3& p2);

	/// @brief Initialize and construct from a local coordinate system and size
	/// @param frame The local coordinate system
	/// @param dx,dy,dz The size
	AMCAX_API void Init(const Frame3& frame, double dx, double dy, double dz);

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] MakeWedgeImpl& Wedge() noexcept;

#endif

	AMCAX_API void Build() override;

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

	/// @brief Get the face on X minimum
	/// @return The X-min face
	[[nodiscard]] AMCAX_API const TopoFace& XMinFace();

	/// @brief Get the face on X maximum
	/// @return The X-max face
	[[nodiscard]] AMCAX_API const TopoFace& XMaxFace();

	/// @brief Get the face on Y minimum
	/// @return The Y-min face
	[[nodiscard]] AMCAX_API const TopoFace& YMinFace();

	/// @brief Get the face on Y maximum
	/// @return The Y-max face
	[[nodiscard]] AMCAX_API const TopoFace& YMaxFace();

	/// @brief Get the face on Z minimum
	/// @return The Z-min face
	[[nodiscard]] AMCAX_API const TopoFace& ZMinFace();

	/// @brief Get the face on Z maximum
	/// @return The Z-max face
	[[nodiscard]] AMCAX_API const TopoFace& ZMaxFace();

private:
	std::shared_ptr<MakeWedgeImpl> wedge;
};
} // namespace AMCAX
