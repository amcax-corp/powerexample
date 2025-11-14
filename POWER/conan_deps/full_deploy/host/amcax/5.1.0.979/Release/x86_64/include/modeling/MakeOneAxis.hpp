/// @file      MakeOneAxis.hpp
/// @brief     Base class of making a object with one axis
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class MakeOneAxisImpl;
class TopoFace;
class TopoShell;
class TopoSolid;
#endif

/// @brief Base class of making a object with one axis
class AMCAX_CLASS_API MakeOneAxis : public MakeShape
{
public:
#ifndef DOXYGEN_SKIP

	/// @internal
	[[nodiscard]] virtual MakeOneAxisImpl& OneAxis() = 0;

#endif

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
};
} // namespace AMCAX
