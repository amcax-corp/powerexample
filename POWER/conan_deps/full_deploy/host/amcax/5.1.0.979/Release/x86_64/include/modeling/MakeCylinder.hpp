/// @file      MakeCylinder.hpp
/// @brief     Class of making a cylinder
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/FrameT.hpp>
#include <modeling/MakeOneAxis.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeCylinderImpl;
#endif

/// @brief Class of making a cylinder
/// @details The radius and height should be positive and the rotation angle should be in (0, 2pi]
class AMCAX_CLASS_API MakeCylinder : public MakeOneAxis
{
public:
	/// @brief Construct from a radius and a height
	/// @param r The radius
	/// @param h The height
	AMCAX_API MakeCylinder(double r, double h);

	/// @brief Construct from a radius, a height and a rotation angle
	/// @param r The radius
	/// @param h The height
	/// @param angle The rotation angle to construct a part cylinder
	AMCAX_API MakeCylinder(double r, double h, double angle);

	/// @brief Construct from a local coordinate system, a radius and a height
	/// @param frame The local coordinate system
	/// @param r The radius
	/// @param h The height
	AMCAX_API MakeCylinder(const Frame3& frame, double r, double h);

	/// @brief Construct from a local coordinate system, a radius, a height and a rotation angle
	/// @param frame The local coordinate system
	/// @param r The radius
	/// @param h The height
	/// @param angle The rotation angle to construct a part cylinder
	AMCAX_API MakeCylinder(const Frame3& frame, double r, double h, double angle);

	/// @brief Destructor
	AMCAX_API ~MakeCylinder();

#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] MakeOneAxisImpl& OneAxis() noexcept override;

	/// @internal
	[[nodiscard]] MakeCylinderImpl& Cylinder() noexcept;

#endif

private:
	std::shared_ptr<MakeCylinderImpl> cylinder;
};
} // namespace AMCAX
