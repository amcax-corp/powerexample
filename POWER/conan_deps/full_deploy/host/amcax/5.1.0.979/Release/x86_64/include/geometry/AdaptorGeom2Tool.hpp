/// @file      AdaptorGeom2Tool.hpp
/// @brief     Class of tool for 2D geometric adaptors
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <memory>

#include <common/Macros.hpp>

namespace AMCAX
{
class Geom2Curve;
class Adaptor2Curve;

/// @brief Class of tool for 2D geometric adaptors
class AdaptorGeom2Tool
{
public:
	/// @brief Make a curve from an adaptor
	/// @param ac The adaptor
	/// @return The curve
	AMCAX_API static std::shared_ptr<Geom2Curve> MakeCurve(const Adaptor2Curve& ac);
};
} // namespace AMCAX
