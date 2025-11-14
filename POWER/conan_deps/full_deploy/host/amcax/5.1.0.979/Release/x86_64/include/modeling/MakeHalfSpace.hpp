/// @file      MakeHalfSpace.hpp
/// @brief     Class of making a half space
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <common/PointT.hpp>
#include <modeling/MakeShape.hpp>
#include <topology/TopoSolid.hpp>

namespace AMCAX
{
class TopoFace;
class TopoShell;

/// @brief Class of making a half space
class AMCAX_CLASS_API MakeHalfSpace : public MakeShape
{
public:
	/// @brief Construct a half space with a boundary face and reference point
	/// @param f The boundary face
	/// @param refPoint The reference point
	AMCAX_API MakeHalfSpace(const TopoFace& f, const Point3& refPoint);

	/// @brief Construct a half space with a boundary shell and reference point
	/// @param s The boundary shell
	/// @param refPoint The reference point
	AMCAX_API MakeHalfSpace(const TopoShell& s, const Point3& refPoint);

	/// @brief Get the constructed solid
	/// @return The constructed solid
	[[nodiscard]] AMCAX_API const TopoSolid& Solid() const;

	/// @brief Get the constructed solid
	/// @return The constructed solid
	[[nodiscard]] AMCAX_API operator TopoSolid() const;

private:
	TopoSolid solid;
};
} // namespace AMCAX
