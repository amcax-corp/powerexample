/// @file      AdaptorGeom3Tool.hpp
/// @brief     Class of tool for 3D geometric adaptors
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom3Curve;
class Geom3Surface;
class Adaptor3Curve;
class Adaptor3Surface;

/// @brief Class of tool for 3D geometric adaptors
class AdaptorGeom3Tool
{
public:
	/// @brief Make a curve from an adaptor
	/// @param c The adaptor
	/// @return The curve
	AMCAX_API static std::shared_ptr<Geom3Curve> MakeCurve(const Adaptor3Curve& c);

	/// @brief Make a surface from an adaptor
	/// @param s The adaptor
	/// @param trim Determine whether make a trimmed surface
	/// @return The surface
	AMCAX_API static std::shared_ptr<Geom3Surface> MakeSurface(const Adaptor3Surface& s, bool trim = true);
};
} // namespace AMCAX
