/// @file      MakeShell.hpp
/// @brief     Class of making a shell
/// @copyright Copyright (c) 2023 Hefei Jiushao Intelligent Technology Co., Ltd. All rights reserved.
/// @par       This file is part of AMCAX kernel.
#pragma once
#include <modeling/MakeShape.hpp>
#include <topology/TopoShell.hpp>

namespace AMCAX
{
#ifndef DOXYGEN_SKIP
class Geom3Surface;
class MakeShellImpl;
#endif

/// @brief Class of making a shell
class AMCAX_CLASS_API MakeShell : public MakeShape
{
public:
	/// @brief Default constructor
	AMCAX_API MakeShell();

	/// @brief Construct from a surface
	/// @param s The surface
	/// @param segment Whether segment the surface to C2 patches
	AMCAX_API explicit MakeShell(const std::shared_ptr<Geom3Surface>& s, bool segment = false);

	/// @brief Construct from a surface with parameter bounds
	/// @param s The surface
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	/// @param segment Whether segment the surface to C2 patches
	AMCAX_API MakeShell(const std::shared_ptr<Geom3Surface>& s, double uMin, double uMax, double vMin, double vMax, bool segment = false);

	/// @brief Initialize and construct from a surface with parameter bounds
	/// @param s The surface
	/// @param uMin The u first parameter
	/// @param uMax The u last parameter
	/// @param vMin The v first parameter
	/// @param vMax The v last parameter
	/// @param segment Whether segment the surface to C2 patches
	AMCAX_API void Init(const std::shared_ptr<Geom3Surface>& s, double uMin, double uMax, double vMin, double vMax, bool segment = false);

	[[nodiscard]] AMCAX_API bool IsDone() const noexcept override;

	/// @brief Get the error status
	/// @return The error status
	[[nodiscard]] AMCAX_API ShellError Error() const noexcept;

	/// @brief Get the constructed shell
	/// @return The constructed shell
	[[nodiscard]] AMCAX_API const TopoShell& Shell();

	/// @brief Get the constructed shell
	/// @return The constructed shell
	[[nodiscard]] AMCAX_API operator TopoShell();

private:
	std::shared_ptr<MakeShellImpl> makeShell;
};
} // namespace AMCAX
